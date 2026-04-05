#!/bin/sh
set -eu

ROOT_DIR=$(CDPATH= cd -- "$(dirname "$0")/.." && pwd)
BIN="$ROOT_DIR/build/paging_lab"
REF_BIN="$ROOT_DIR/build/paging_lab_reference"

output=$("$BIN" < "$ROOT_DIR/data/case_3_blocks.txt")

printf '%s\n' "$output" | grep -q "请求分页式存储管理"
printf '%s\n' "$output" | grep -q "TODO: 在 solve1 中实现 FIFO 页面置换。"
printf '%s\n' "$output" | grep -q "TODO: 在 solve2 中实现 LRU 页面置换。"
printf '%s\n' "$output" | grep -q "TODO: 请先在 solve1/solve2 中完成页面置换核心逻辑。"

check_reference_case() {
    case_file=$1
    expected_fifo=$2
    expected_lru=$3

    ref_output=$("$REF_BIN" < "$case_file")
    printf '%s\n' "$ref_output" | grep -q "缺页率为：$expected_fifo"
    printf '%s\n' "$ref_output" | grep -q "缺页率为：$expected_lru"
}

check_reference_case "$ROOT_DIR/data/case_3_blocks.txt" "75.00" "60.00"
check_reference_case "$ROOT_DIR/data/case_4_blocks.txt" "50.00" "40.00"
check_reference_case "$ROOT_DIR/data/case_single_frame.txt" "87.50" "87.50"
check_reference_case "$ROOT_DIR/data/case_all_same_page.txt" "16.67" "16.67"
check_reference_case "$ROOT_DIR/data/case_frames_ge_pages.txt" "42.86" "42.86"
check_reference_case "$ROOT_DIR/data/case_alternating_hotset.txt" "75.00" "66.67"
check_reference_case "$ROOT_DIR/data/case_short_sparse.txt" "75.00" "75.00"

printf 'starter scaffold smoke test passed\n'
printf 'reference boundary tests passed\n'
