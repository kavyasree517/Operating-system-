#!/usr/bin/env bash
set -euo pipefail

git init
git branch -M main

git add README.md .gitignore push_to_github.sh
git commit -m "Initial commit: Add CSA0404 Operating Systems repository structure and README"

git add Assignment_1_CO1/
git commit -m "Assignment 1 (CO1): Add Smart Hospital OS report, question PDF, C11 source code, and outputs"

git add Assignment_2_CO2/
git commit -m "Assignment 2 (CO2): Add Process Management & Deadlock report, question PDF, C11 source code, and outputs"

git add Assignment_3_CO3/
git commit -m "Assignment 3 (CO3): Add Memory & Disk Management report, question PDF, C11 source code, and outputs"

git add Assignment_4_CO4/
git commit -m "Assignment 4 (CO4): Add File Storage & Disk Scheduling report, question PDF, C11/Bash code, and outputs"

git add Assignment_5_CO5/
git commit -m "Assignment 5 (CO5): Add Linux/Docker/Kubernetes report, question PDF, scripts, YAML, and outputs"

git remote remove origin 2>/dev/null || true
git remote add origin https://github.com/kavyasree517/Operating-system-.git
git push -u origin main
