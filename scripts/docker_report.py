import fire
import os
import re
import json
import sys
import termios
import tty

def get_regex_patterns():
    return [
        r".*MySQL:.*\bJSON\b.*",
    ]

def compile_regex_patterns(patterns):
    return [re.compile(pattern) for pattern in patterns]

def matches_any_regex(text, regex_list):
    return any(regex.search(text) for regex in regex_list)

def get_report(core):
    with open(f"/tmp/QueryHouse/{core}/report.Fuzzlog", "r") as f:
        report = f.read()
    return report

def split_report(report):
    return report.split("\nperiod")

def load_progress(progress_file):
    if os.path.exists(progress_file):
        with open(progress_file, "r") as f:
            return json.load(f)
    return {}

def save_progress(progress_file, progress):
    with open(progress_file, "w") as f:
        json.dump(progress, f)

def read_single_key():
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(fd)
        key = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return key

def report_viewer(tmp_dir="/tmp/QueryHouse", progress_file="/tmp/QueryHouse/progress.json"):
    regex_list = compile_regex_patterns(get_regex_patterns())

    progress = load_progress(progress_file)

    core_list = os.listdir(tmp_dir)
    core_list = [core for core in core_list if os.path.exists(f"{tmp_dir}/{core}/report.Fuzzlog")]
    core_list.sort()

    core_index = 0

    while core_index < len(core_list):
        core = core_list[core_index]

        current_index = progress.get(core, 0)

        report = get_report(core)
        periods = split_report(report)

        while True:
            os.system("clear")
            print(f"Core: {core} ({core_index + 1}/{len(core_list)}) | BUG: {current_index + 1}/{len(periods)}")
            print(periods[current_index])
            print("\nCommands: [n] Next, [p] Previous, [q] Quit")
            # if matches_any_regex(periods[current_index], regex_list):
            #     current_index = min(current_index + 1, len(periods) - 1)
            #     if current_index == len(periods) - 1:
            #         core_index = min(core_index + 1, len(core_list) - 1)
            #         break
            #     elif current_index == 0:
            #         core_index = max(core_index - 1, 0)
            #         break
            #     else:
            #         continue

            key = read_single_key()

            if key == "n":
                if current_index == len(periods) - 1:
                    core_index = min(core_index + 1, len(core_list) - 1)
                    break
                current_index = min(current_index + 1, len(periods) - 1)
            elif key == "p":
                if current_index == 0:
                    core_index = max(core_index - 1, 0)
                    break
                current_index = max(current_index - 1, 0)
            elif key == "q":
                save_progress(progress_file, progress)
                exit(0)
            else:
                print(f"Invalid command: {key}")

            progress[core] = current_index
            save_progress(progress_file, progress)

if __name__ == "__main__":
    fire.Fire(report_viewer)
