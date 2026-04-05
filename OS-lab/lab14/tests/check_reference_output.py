#!/usr/bin/env python3
import subprocess
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
BUILD_DIR = ROOT / "build"
BIN = BUILD_DIR / "disk_scheduler"

REQUIRED_FILES = [
    "include/app.h",
    "include/io.h",
    "include/scheduler_api.h",
    "include/scheduler_common.h",
    "include/disk_scheduler.h",
    "src/app.c",
    "src/io.c",
    "src/scheduler_common.c",
    "src/scheduler_fcfs.c",
    "src/scheduler_sstf.c",
    "src/scheduler_scan.c",
    "docs/reference_solution.md",
    "docs/reference_output.md",
    "docs/report_template.md",
    "docs/debug_checklist.md",
    "data/case_already_sorted_up.txt",
    "data/case_already_sorted_down.txt",
    "data/case_single_request.txt",
    "data/case_all_same_request.txt",
    "data/case_contains_current.txt",
    "data/case_edge_cylinders.txt",
]

REQUIRED_CASE_NAMES = [
    "already_sorted_up",
    "already_sorted_down",
    "single_request",
    "all_same_request",
    "contains_current",
    "edge_cylinders",
]


def run(cmd):
    return subprocess.run(cmd, cwd=ROOT, text=True, capture_output=True)


def main():
    BUILD_DIR.mkdir(exist_ok=True)

    missing_files = [path for path in REQUIRED_FILES if not (ROOT / path).exists()]
    if missing_files:
        sys.stderr.write("missing required project files:\n")
        for path in missing_files:
            sys.stderr.write(f"- {path}\n")
        return 1

    reference_output = (ROOT / "docs" / "reference_output.md").read_text(encoding="utf-8")
    missing_case_names = [name for name in REQUIRED_CASE_NAMES if name not in reference_output]
    if missing_case_names:
        sys.stderr.write("reference_output.md missing case sections:\n")
        for name in missing_case_names:
            sys.stderr.write(f"- {name}\n")
        return 1

    compile_result = run(
        [
            "cc",
            "-std=c11",
            "-Wall",
            "-Wextra",
            "-pedantic",
            "-Iinclude",
            "-o",
            str(BIN),
            "src/main.c",
            "src/app.c",
            "src/io.c",
            "src/scheduler_common.c",
            "src/scheduler_fcfs.c",
            "src/scheduler_sstf.c",
            "src/scheduler_scan.c",
        ]
    )
    if compile_result.returncode != 0:
        sys.stderr.write("scaffold build failed\n")
        sys.stderr.write(compile_result.stdout)
        sys.stderr.write(compile_result.stderr)
        return 1

    run_result = subprocess.run(
        [str(BIN)],
        cwd=ROOT,
        text=True,
        input="1\n8\n98 183 37 122 14 124 65 67\n53\n0\n",
        capture_output=True,
    )
    if run_result.returncode != 1:
        sys.stderr.write("unexpected scaffold exit code\n")
        sys.stderr.write(run_result.stdout)
        sys.stderr.write(run_result.stderr)
        return 1

    expected_snippets = [
        "*****************磁盘驱动调度*****************",
        "***********FCFS磁盘移臂调度过程***********",
        "当前记录的起始柱面为：",
        "[TODO] 请在 FCFS 中补全核心调度逻辑。",
        "调度结束！",
    ]

    for snippet in expected_snippets:
        if snippet not in run_result.stdout:
            sys.stderr.write(f"missing expected output snippet: {snippet}\n")
            sys.stderr.write(run_result.stdout)
            return 1

    sys.stdout.write("scaffold structure and runtime checks passed\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
