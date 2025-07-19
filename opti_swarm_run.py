import os
import fire
import time
import psutil
import shutil
import sys




COPY_DIR = ["srcs", "third_party"]
COPY_FILES = ["scripts/oracle_run.sh", "CMakeLists.txt", "lint.cmake", ".clang-format", ".clang-tidy"]

CPU_LOAD = []

TMP_DIR = "/tmp/QueryHouse"


def get_color(color):
    colors = {
        "red": '\033[91m',
        "green": '\033[92m',
        "yellow": '\033[93m',
        "blue": '\033[94m',
        "purple": '\033[95m',
        "cyan": '\033[96m',
        "white": '\033[97m',
        "black": '\033[30m',
        "default": '\033[39m',
    }
    return colors[color]

    
def str_colorize(string, color):
    return get_color(color) + string + reset_color()

def colorize(value):
    if value < 50: # Green
        return "\033[92m" + str(value)
    elif value < 80: # Yellow
        return "\033[93m" + str(value)
    else: # Red
        return "\033[91m" + str(value)
def reset_color():
    return '\033[0m'

def cpu_usage(core):
    cpu_usage = psutil.cpu_percent(interval=1, percpu=True)
    return cpu_usage[core]

def memory_usage():
    return psutil.virtual_memory().percent

def disk_usage():
    return psutil.disk_usage('/tmp').percent

def get_terminal_width():
    """Returns the width of the terminal."""
    return shutil.get_terminal_size((80, 20)).columns  # Defaults to 80 if terminal size cannot be determined


def copy_to_docker():
    for dir in COPY_DIR:
        os.system(f"cp -r {dir} docker/")
    for file in COPY_FILES:
        os.system(f"cp {file} docker/")
        
def docker_build(name):
    os.system(f"docker build -t {name} .")
    

def swarm_init(advertise_addr):
    os.system(f"docker swarm init --advertise-addr {advertise_addr}")
    os.system("docker swarm join-token worker")
    os.system("docker swarm join-token manager")

def docker_run(name, core):
    os.system(f"sudo rm -rf /tmp/QueryHouse/{core}")
    os.system(f"mkdir -p /tmp/QueryHouse/{core}")
    os.system(f"chmod -R 777 /tmp/QueryHouse/{core}")
    os.system(f"docker service create --name {core} --env CPU={core} --mount type=bind,source=/tmp/QueryHouse/{core},destination=/tmp fuzz")
    CPU_LOAD.append(core)
    print(f"Waiting for {core} to start...")
    while not get_fuzzer_stats(core, "execs_done"):
        time.sleep(5)
    while not get_fuzzer_stats(core, 'execs_per_sec'):
        time.sleep(5)
    while not get_feedback_log(core):
        time.sleep(5)

def parse_stats_log(stats_log):
    stats = {
        "base_query_count": 0,
        "base_statement_count": 0,
        "dbms_statement_count": 0,
        "dbms_valid_queries": {},
        "validity_scores": {},
    }
    lines = stats_log.split('\n')
    i = 0
    while i < len(lines):
        line = lines[i].strip()
        if line.startswith("[INFO] Base query count:"):
            stats["base_query_count"] = int(line.split(":")[1].strip())
            i += 1
        elif line.startswith("[INFO] Base statement count:"):
            stats["base_statement_count"] = int(line.split(":")[1].strip())
            i += 1
        elif line.startswith("[INFO] DBMS statement count:"):
            stats["dbms_statement_count"] = int(line.split(":")[1].strip())
            i += 1
        elif line.startswith("[INFO] DBMS-specific valid queries:"):
            stats["dbms_valid_queries"] = {}
            # Read the next lines for DBMS-specific counts
            i += 1
            while i < len(lines) and lines[i].startswith("  - "):
                dbms_line = lines[i].strip().lstrip("- ").split(":")
                dbms = dbms_line[0].strip()
                count = int(dbms_line[1].strip())
                stats["dbms_valid_queries"][dbms] = count
                i += 1
        elif line.startswith("[INFO] Validity score distribution:"):
            stats["validity_scores"] = {}
            # Read the next lines for score distribution
            i += 1
            while i < len(lines) and lines[i].startswith("  - "):
                score_line = lines[i].strip().lstrip("- ").split(":")
                score = int(score_line[0].strip())
                count = int(score_line[1].strip())
                stats["validity_scores"][score] = count
                i += 1
        else:
            i += 1
                
    return stats

def get_feedback_log(core):
    if not os.path.exists(f"/tmp/QueryHouse/{core}/feedback.Fuzzlog"):
        return None
    with open(f"/tmp/QueryHouse/{core}/feedback.Fuzzlog", "r") as f:
        return parse_stats_log(f.read())
    
def parse_fuzzer_stats(stats):
    parsed_stats = {}
    stats = stats.split("\n")
    for i in range(len(stats)):
        line = stats[i].split(":")
        if len(line) == 2:
            parsed_stats[line[0].strip()] = line[1].strip()
    return parsed_stats

def get_fuzzer_stats(core, stats):
    if not os.path.exists(f"/tmp/QueryHouse/{core}/fuzz/default/fuzzer_stats"):
        return None
    with open(f"/tmp/QueryHouse/{core}/fuzz/default/fuzzer_stats", "r") as f:
        return parse_fuzzer_stats(f.read())[stats]

def monitor(cpu, memory, disk, get_fuzzer_stats_execs_done, get_fuzzer_stats_execs_per_sec, get_feedback_log):
    os.system("clear")
    
    # Get terminal width
    terminal_width = get_terminal_width()
    separator_line = "=" * terminal_width

    # Header (labels)
    print(f"{'Core':<10}{'CPU Usage':<15}{'Execs Per Second':<20}{'Execs Done':<20}{'Query Executed':<20}{'Valid Testcases':<20}")
    print(separator_line)
    
    # Core data
    for core in CPU_LOAD:
        core_index = CPU_LOAD.index(core)
        print(
            f"{core:<10}"
            f"{cpu[core_index]:<15}"
            f"{get_fuzzer_stats_execs_per_sec[core_index]:<20}"
            f"{get_fuzzer_stats_execs_done[core_index]:<20}"
            f"{get_feedback_log[core_index]['source_query_statement_counts']:<20}"
            f"{get_feedback_log[core_index]['all_normal_states']:<20}"
        )
    
    # Memory and Disk Usage
    print(f"\n{separator_line}")
    print(f"Memory Usage: {colorize(memory)}%{reset_color()}")
    print(f"Disk Usage: {colorize(disk)}%{reset_color()}")

def prepare_monitor(EXECS_PER_SEC_LIMIT, max_core):
    get_fuzzer_stats_execs_done = []
    get_fuzzer_stats_execs_per_sec = []
    feedback_log = []
    for core in CPU_LOAD:
        get_fuzzer_stats_execs_done.append(get_fuzzer_stats(core, 'execs_done'))
        get_fuzzer_stats_execs_per_sec.append(get_fuzzer_stats(core, 'execs_per_sec'))
        feedback_log.append(get_feedback_log(core))
        print(f"Core {core} execs per sec: {get_fuzzer_stats_execs_per_sec[-1]}")
        if float(get_fuzzer_stats_execs_per_sec[-1]) > EXECS_PER_SEC_LIMIT and CPU_LOAD[-1]+1 < max_core:
            print(f"Core {core} execs per sec is bigger than {EXECS_PER_SEC_LIMIT}.\n More run")
            run_core = CPU_LOAD[-1] + 1
            docker_run("fuzz", run_core)
    cpu = []
    for core in CPU_LOAD:
        cpu.append(cpu_usage(core))
    memory = memory_usage()
    disk = disk_usage()
    monitor(cpu, memory, disk, get_fuzzer_stats_execs_done, get_fuzzer_stats_execs_per_sec, feedback_log)

def run(max_core, advertise_addr = "127.0.0.1", EXECS_PER_SEC_LIMIT = 1):
    copy_to_docker()
    docker_build("fuzz")
    swarm_init(advertise_addr)
    for core in range(0, max_core):
        docker_run("fuzz", core)
        print(f"Core {core} started")
        print(f"Core {core} execs per sec: {get_fuzzer_stats(core, 'execs_per_sec')}")
        if float(get_fuzzer_stats(core, 'execs_per_sec')) < EXECS_PER_SEC_LIMIT:
            print(f"Core {core} execs per sec is less than {EXECS_PER_SEC_LIMIT}.\n No more run")
            break
    try:
        while True:
            prepare_monitor(EXECS_PER_SEC_LIMIT, max_core)
            time.sleep(1)
    except KeyboardInterrupt:
        print("Monitoring stopped")

def usage():
    """Prints usage information for the script."""
    print("""
Usage: python opti_swarm_run.py [max_core] ([advertise_addr] [EXECS_PER_SEC_LIMIT])
Arguments:
    max_core: The maximum number of cores to use
    advertise_addr: The address to advertise for the swarm (default: 127.0.0.1)
    EXECS_PER_SEC_LIMIT: The limit for execs per second (default: 1)
    """)

if __name__ == "__main__":
    if "--help" in sys.argv or "--usage" in sys.argv or len(sys.argv) < 2:
        usage()
        sys.exit(1)
    if os.getuid() != 0:
        print("This script must be run as root. Please use sudo.")
        sys.exit(1)
    try:
        with open("/proc/sys/kernel/core_pattern", "r") as f:
            core_pattern = f.read().strip()
            if core_pattern != "core":
                print("Core pattern is not set. Please set it to a valid value.")
                print("echo core | sudo tee /proc/sys/kernel/core_pattern")
                sys.exit(1)
    except FileNotFoundError:
        print("Core pattern file not found. Please check your system.")
        sys.exit(1)
    except PermissionError:
        print("Permission denied. Please run this script as root.")
        sys.exit(1)
        
    print(str_colorize("Please turn off the Queryhouse docker swarm and container manually","red"))
    fire.Fire(run)
