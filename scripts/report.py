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

def get_report():
    with open(f"/tmp/report.Fuzzlog", "r") as f:
        report = f.read()
    return report

def split_report(report):
    return report.split("\nbatch-index")

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

def report_viewer(tmp_dir="/tmp/", progress_file="/tmp/progress.json"):
    regex_list = compile_regex_patterns(get_regex_patterns())

    progress = load_progress(progress_file)

    fuzzlog_path = os.path.join(tmp_dir, "report.Fuzzlog")
    if not os.path.exists(fuzzlog_path):
        print(f"File not found: {fuzzlog_path}")
        return

    current_index = progress.get("report.Fuzzlog", 0)

    report = get_report(fuzzlog_path)
    reports = split_report(report)

    if not reports:
        print("No valid reports found in the report.")
        return

    while True:
        os.system("clear")
        print(f"File: report.Fuzzlog | BUG: {current_index + 1}/{len(reports)}")

        if current_index >= len(reports):
            current_index = len(reports) - 1

        print(reports[current_index])
        print("\nCommands: [n] Next, [p] Previous, [q] Quit")

        key = read_single_key()

        if key == "n":
            current_index = min(current_index + 1, len(reports) - 1)
        elif key == "p":
            current_index = max(current_index - 1, 0)
        elif key == "q":
            progress["report.Fuzzlog"] = current_index
            save_progress(progress_file, progress)
            exit(0)
        else:
            print(f"Invalid command: {key}")

        progress["report.Fuzzlog"] = current_index
        save_progress(progress_file, progress)

if __name__ == "__main__":
    fire.Fire(report_viewer)
