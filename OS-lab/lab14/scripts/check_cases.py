#!/usr/bin/env python3
from pathlib import Path
import sys


ROOT = Path(__file__).resolve().parent.parent
DATA_DIR = ROOT / "data"
CASE_FILES = [
    "case_already_sorted_up.txt",
    "case_already_sorted_down.txt",
    "case_single_request.txt",
    "case_all_same_request.txt",
    "case_contains_current.txt",
    "case_edge_cylinders.txt",
]
MAX_CYLINDER = 199


def parse_case(path: Path):
    lines = [line.strip() for line in path.read_text(encoding="utf-8").splitlines() if line.strip()]
    if len(lines) != 3:
        raise ValueError("expected exactly 3 non-empty lines: length, sequence, current")

    length = int(lines[0])
    sequence = [int(token) for token in lines[1].split()]
    current = int(lines[2])

    if len(sequence) != length:
        raise ValueError(f"length mismatch: declared {length}, got {len(sequence)}")
    if not (0 <= current <= MAX_CYLINDER):
        raise ValueError(f"current cylinder out of range: {current}")
    for value in sequence:
        if not (0 <= value <= MAX_CYLINDER):
            raise ValueError(f"request out of range: {value}")

    return length, sequence, current


def main():
    for name in CASE_FILES:
        path = DATA_DIR / name
        if not path.exists():
            sys.stderr.write(f"missing case file: {name}\n")
            return 1
        try:
            parse_case(path)
        except Exception as exc:
            sys.stderr.write(f"invalid case file {name}: {exc}\n")
            return 1

    sys.stdout.write("dataset files check passed\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
