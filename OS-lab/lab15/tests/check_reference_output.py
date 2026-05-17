#!/usr/bin/env python3
"""验证位示图实验程序在 empty 模式下的关键输出是否符合预期。"""

import subprocess
import sys
import os

BINARY = os.path.join("build", "bitmap_lab")
DATA_DIR = "data"

CHECKS = [
    {
        "case": "sample_case_01.in",
        "expect_all": [
            "辅存申请成功",
            "辅存剩余空闲块数: 950",
            "辅存剩余空闲块数: 920",
            "回收成功",
            "辅存剩余空闲块数: 970",
            "辅存剩余空闲块数: 1000",
        ],
    },
    {
        "case": "case_basic_success.in",
        "expect_all": [
            "辅存剩余空闲块数: 95",
            "辅存剩余空闲块数: 92",
            "辅存剩余空闲块数: 97",
            "辅存剩余空闲块数: 100",
        ],
    },
    {
        "case": "case_insufficient_space.in",
        "expect_all": ["剩余空闲块不足"],
    },
    {
        "case": "case_duplicate_job.in",
        "expect_all": ["存在同名作业"],
    },
    {
        "case": "case_invalid_size.in",
        "expect_all": ["作业空间大小必须大于 0"],
    },
    {
        "case": "case_recycle_missing.in",
        "expect_all": ["未找到作业 ghost"],
    },
    {
        "case": "case_fill_then_fail.in",
        "expect_all": [
            "辅存剩余空闲块数: 0",
            "剩余空闲块不足",
            "回收成功",
            "辅存剩余空闲块数: 8",
        ],
    },
]


def run_case(case_file):
    input_path = os.path.join(DATA_DIR, case_file)
    with open(input_path, "r") as f:
        input_data = f.read()
    env = os.environ.copy()
    env["BITMAP_LAB_INIT_MODE"] = "empty"
    result = subprocess.run(
        [os.path.join(".", BINARY)],
        input=input_data,
        capture_output=True,
        text=True,
        timeout=10,
        env=env,
    )
    return result.stdout + result.stderr


def main():
    if not os.path.isfile(BINARY):
        print(f"FAIL: binary not found at {BINARY}", file=sys.stderr)
        sys.exit(1)

    passed = 0
    failed = 0

    for check in CHECKS:
        case = check["case"]
        try:
            output = run_case(case)
        except Exception as e:
            print(f"FAIL [{case}]: {e}")
            failed += 1
            continue

        case_ok = True
        for expect in check["expect_all"]:
            if expect not in output:
                print(f"FAIL [{case}]: missing expected string: {expect!r}")
                case_ok = False

        if case_ok:
            print(f"PASS [{case}]")
            passed += 1
        else:
            failed += 1

    print(f"\n{passed} passed, {failed} failed out of {passed + failed} checks.")
    sys.exit(1 if failed > 0 else 0)


if __name__ == "__main__":
    main()
