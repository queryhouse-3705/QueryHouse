import time
import os

core_count = int(input("Enter the number of cores: "))

log_file_paths = [f"/tmp/QueryHouse/{core}/stats.Fuzzlog" for core in range(core_count)]
output_file_path = "/tmp/query_execution_counts.log"

previous_counts = [0] * core_count
first_core_detected = False

def log_execution_count(core, current_count, total_count, output_path):
    with open(output_path, "a") as log_file:
        log_file.write(f"[{time.strftime('%Y-%m-%d %H:%M:%S')}] "
                       f"Core {core} - Current executed queries: {current_count}, "
                       f"Total executed queries: {total_count}\n")

def wait_for_file(file_path):
    print(f"Waiting for log file {file_path} to be created...")
    while not os.path.exists(file_path):
        time.sleep(0.001)

try:
    print("Monitoring started. Press Ctrl+C to stop.")
    while True:
        total_increment = 0
        total_executed_queries = 0
        for core in range(core_count):
            log_file_path = log_file_paths[core]

            if not os.path.exists(log_file_path):
                if not first_core_detected:
                    wait_for_file(log_file_path)
                else:
                    continue

            with open(log_file_path, "r") as log_file:
                for line in log_file:
                    if "DBMS statement count:" in line:
                        current_count = int(line.strip().split(":")[1].strip())

                        increment = current_count - previous_counts[core]
                        previous_counts[core] = current_count

                        log_execution_count(core, increment, current_count, output_file_path)
                        print(f"Core {core} - Logged: {increment} queries in last minute, Total: {current_count}")

                        if not first_core_detected:
                            first_core_detected = True

                        total_increment += increment
                        total_executed_queries += current_count

        print (f"Total increment across all cores: {total_executed_queries}")  
        with open(output_file_path, "a") as log_file:
            log_file.write(f"[{time.strftime('%Y-%m-%d %H:%M:%S')}] "
                           f"Total increment across all cores: {total_increment}\n")
            log_file.write(f"[{time.strftime('%Y-%m-%d %H:%M:%S')}] "
                           f"Total executed queries across all cores: {total_executed_queries}\n")

        time.sleep(60)

except KeyboardInterrupt:
    print("\nMonitoring stopped.")
