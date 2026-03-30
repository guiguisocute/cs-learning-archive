#!/bin/sh

set -eu

make

if [ "${1:-}" = "--all" ]; then
    for f in data/case*.in data/case*.txt; do
        [ -f "$f" ] || continue
        echo "===== $f ====="
        ./build/fixed_partition_lab < "$f"
    done
else
    ./build/fixed_partition_lab < "${1:-data/case1.txt}"
fi
