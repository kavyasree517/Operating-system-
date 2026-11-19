#!/usr/bin/env bash
set -euo pipefail
THRESHOLD=80
df -P | awk -v max="$THRESHOLD" 'NR>1 {
    use = $5; sub(/%/, "", use);
    if (use + 0 >= max)
        printf "[DISK ALERT] %s mounted on %s is at %d%% capacity (Avail: %s)\n", $1, $6, use, $4
    else
        printf "[DISK OK]    %s mounted on %s is at %d%% capacity\n", $1, $6, use
}'
