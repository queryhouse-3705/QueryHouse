import time
import os

log_file_path = "/tmp/stats.Fuzzlog"
output_file_path = "/tmp/query_execution_counts.log"

previous_count = 0

def log_execution_count(current_count, total_count, output_path):
    with open(output_path, "a") as log_file:
        log_file.write(f"[{time.strftime('%Y-%m-%d %H:%M:%S')}] "
                       f"Current executed queries: {current_count}, "
                       f"Total executed queries: {total_count}\n")

def wait_for_file(file_path):
    print(f"Waiting for log file {file_path} to be created...")
    while not os.path.exists(file_path):
        time.sleep(0.001)  

try:
    print("Monitoring started. Press Ctrl+C to stop.")
    while True:
        if not os.path.exists(log_file_path):
            wait_for_file(log_file_path)

        with open(log_file_path, "r") as log_file:
            for line in log_file:
                if "DBMS statement count" in line:
                    current_count = int(line.strip().split(":")[1].strip())
                    
                    increment = current_count - previous_count
                    previous_count = current_count

                    log_execution_count(increment, current_count, output_file_path)
                    print(f"Logged: {increment} queries in last minute, Total: {current_count}")

        time.sleep(60)

except KeyboardInterrupt:
    print("\nMonitoring stopped.")
