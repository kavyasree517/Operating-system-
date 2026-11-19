# Operating Systems (CSA0404) — Assignments 1 to 5 (CO1–CO5)

- **Student Name:** Kavya Sree T
- **Register Number:** 192524444
- **Course:** Operating Systems (`CSA0404`)
- **Institution:** SIMATS Engineering (Saveetha School of Engineering)
- **GitHub Repository:** https://github.com/kavyasree517/Operating-system-.git
- **Execution Environment:** Linux x86_64 (`Kernel 6.12.105+`), `gcc 12.2.0` (`-std=c11 -Wall -Wextra -O2 -pthread`)

## Repository Structure

| Folder | Course Outcome | Contents |
| :--- | :--- | :--- |
| `Assignment_1_CO1/` | CO1 – Smart Hospital OS Design | Question PDF, Updated Answer `.docx`, C11 Source (`Task06`, `Task07`, `Task10`), Verified Outputs |
| `Assignment_2_CO2/` | CO2 – Process Management, Sync & Deadlocks | Question PDF, Updated Answer `.docx`, C11 Source (`Q1`–`Q6`), Verified Outputs |
| `Assignment_3_CO3/` | CO3 – Memory & Disk Management | Question PDF, Updated Answer `.docx`, C11 Source (`Q1`–`Q7`), Verified Outputs |
| `Assignment_4_CO4/` | CO4 – File Storage & Disk Scheduling | Question PDF, Updated Answer `.docx`, C11 & Bash Source (`Task01`–`Task06`), Verified Outputs |
| `Assignment_5_CO5/` | CO5 – Linux, Docker & Kubernetes | Question PDF, Updated Answer `.docx`, Bash, Flask, Dockerfile, Compose, K8s YAML, Ansible, Verified Outputs |

## Quick Build & Run Examples
```bash
# Assignment 1 (CO1)
gcc -std=c11 -Wall -Wextra -O2 Assignment_1_CO1/src/Task06/task06_copy_file.c -o task06 && ./task06
gcc -std=c11 -Wall -Wextra -O2 Assignment_1_CO1/src/Task07/task07_shell_jobs.c -o task07 && ./task07

# Assignment 2 (CO2)
gcc -std=c11 -Wall -Wextra -O2 Assignment_2_CO2/src/Q2/q2_round_robin.c -o q2 && ./q2
gcc -std=c11 -Wall -Wextra -O2 -pthread Assignment_2_CO2/src/Q5/q5_bounded_buffer.c -o q5 && ./q5
gcc -std=c11 -Wall -Wextra -O2 Assignment_2_CO2/src/Q6/q6_bankers.c -o q6 && ./q6

# Assignment 3 (CO3)
gcc -std=c11 -Wall -Wextra -O2 Assignment_3_CO3/src/Q2/paging_translator.c -o q2_1024 && ./q2_1024
gcc -std=c11 -Wall -Wextra -O2 Assignment_3_CO3/src/Q5/page_replacement.c -o q5_pr && ./q5_pr

# Assignment 4 (CO4)
gcc -std=c11 -Wall -Wextra -O2 Assignment_4_CO4/src/Task02/file_allocation.c -o t2 && ./t2
gcc -std=c11 -Wall -Wextra -O2 Assignment_4_CO4/src/Task04/disk_scheduling.c -o t4 && ./t4

# Assignment 5 (CO5)
bash Assignment_5_CO5/src/TaskB1/log_summary.sh
```

## Push to GitHub (Progressive Commits Included)
Run `./push_to_github.sh` inside the extracted folder to initialize Git, create progressive commits for Assignments 1 through 5, link `https://github.com/kavyasree517/Operating-system-.git`, and push to `main`.
