#!/usr/bin/env bash
set -euo pipefail

mode="${1:-all}"

assert_file_exists() {
    local path="$1"
    if [ ! -f "$path" ]; then
        echo "missing file: $path"
        return 1
    fi
}

assert_contains() {
    local file="$1"
    local pattern="$2"
    if ! grep -q "$pattern" "$file"; then
        echo "missing pattern: $pattern"
        echo "--- output ---"
        cat "$file"
        echo "--------------"
        return 1
    fi
}

run_build_expect_fail() {
    if make reference >/tmp/lab12-build.log 2>&1; then
        echo "expected make reference to fail before skeleton exists"
        return 1
    fi
    return 0
}

run_build_expect_pass() {
    make clean >/tmp/lab12-build.log 2>&1 || true
    make reference >/tmp/lab12-build.log 2>&1
}

run_reference_case() {
    local case_file="$1"
    local output_file="$2"
    make reference >/tmp/lab12-build.log 2>&1
    ./bin/reference_lab <"$case_file" >"$output_file" 2>&1
}

run_sample_case() {
    local output_file
    output_file="$(mktemp)"
    run_reference_case "data/case_sample.txt" "$output_file"
    assert_contains "$output_file" "位示图"
    assert_contains "$output_file" "分配成功"
    assert_contains "$output_file" "作业job1的分配情况如下"
    assert_contains "$output_file" "页号"
}

run_recycle_case() {
    local output_file
    output_file="$(mktemp)"
    run_reference_case "data/case_multi_job.txt" "$output_file"
    assert_contains "$output_file" "去配成功"
    assert_contains "$output_file" "剩余空闲块数"

    output_file="$(mktemp)"
    run_reference_case "data/case_recycle_missing.txt" "$output_file"
    assert_contains "$output_file" "未找到作业"
}

run_translate_case() {
    local output_file
    output_file="$(mktemp)"
    run_reference_case "data/case_address_ok.txt" "$output_file"
    assert_contains "$output_file" "物理块号"
    assert_contains "$output_file" "物理地址"

    output_file="$(mktemp)"
    run_reference_case "data/case_address_oob.txt" "$output_file"
    assert_contains "$output_file" "地址转换失败"
}

run_boundary_case() {
    local output_file
    output_file="$(mktemp)"
    run_reference_case "data/case_small_fit.txt" "$output_file"
    assert_contains "$output_file" "分配成功"

    output_file="$(mktemp)"
    run_reference_case "data/case_no_space.txt" "$output_file"
    assert_contains "$output_file" "主存空间不足"
}

run_replay_case() {
    if [ ! -x ./scripts/run_case.exp ]; then
        echo "missing replay script"
        return 1
    fi
    make clean >/tmp/lab12-build.log 2>&1 || true
    make student >/tmp/lab12-build.log 2>&1
    ./scripts/run_case.exp --case data/case_sample.txt >/tmp/lab12-replay.log 2>&1
}

run_scaffold_case() {
    make clean >/tmp/lab12-build.log 2>&1 || true
    make student >/tmp/lab12-build.log 2>&1
    grep -q "TODO: 请实现 distribute" src/main.c
    grep -q "TODO: 请实现作业分配算法" src/mem_model.c
    grep -q "TODO: 请输出位示图矩阵" src/io_view.c
}

run_dataset_inventory_case() {
    assert_file_exists "data/README.md"
    assert_file_exists "data/case_duplicate_job.txt"
    assert_file_exists "data/case_page_capacity_mismatch.txt"
    assert_file_exists "data/case_address_segment_oob.txt"
    assert_file_exists "data/case_address_offset_oob.txt"
    assert_file_exists "data/case_multi_recycle_chain.txt"

    grep -q "重名作业重复装入" data/README.md
    grep -q "页数容量不足" data/README.md
    grep -q "段号越界" data/README.md
    grep -q "页内偏移越界" data/README.md
    grep -q "连续装入、连续回收" data/README.md
}

run_replay_all_case() {
    if [ ! -x ./scripts/run_case.exp ]; then
        echo "missing replay script"
        return 1
    fi
    make clean >/tmp/lab12-build.log 2>&1 || true
    make student >/tmp/lab12-build.log 2>&1
    ./scripts/run_case.exp --all >/tmp/lab12-replay-all.log 2>&1
    assert_contains /tmp/lab12-replay-all.log "case_sample.txt"
    assert_contains /tmp/lab12-replay-all.log "case_duplicate_job.txt"
    assert_contains /tmp/lab12-replay-all.log "case_address_segment_oob.txt"
}

case "${mode}" in
    build)
        run_build_expect_pass
        ;;
    sample)
        run_sample_case
        ;;
    recycle)
        run_recycle_case
        ;;
    translate)
        run_translate_case
        ;;
    boundary)
        run_boundary_case
        ;;
    replay)
        run_replay_case
        ;;
    scaffold)
        run_scaffold_case
        ;;
    datasets)
        run_dataset_inventory_case
        ;;
    replay-all)
        run_replay_all_case
        ;;
    all)
        run_build_expect_pass
        run_sample_case
        run_recycle_case
        run_translate_case
        run_boundary_case
        run_replay_case
        run_replay_all_case
        run_scaffold_case
        run_dataset_inventory_case
        ;;
    *)
        echo "unsupported mode: ${mode}" >&2
        exit 2
        ;;
esac
