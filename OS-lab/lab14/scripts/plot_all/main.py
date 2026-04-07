#!/usr/bin/env python3
"""
Disk Scheduling Algorithm Visualization

Generates matplotlib plots for all 5 disk scheduling algorithms:
FCFS, SSTF, Oneway Scan (C-SCAN), Twoway Scan (SCAN), Elevator (LOOK).

Usage:
    uv run main.py                          # Show interactive windows
    uv run main.py --save                   # Save PNG files to ../../docs/images/
    uv run main.py --save --output-dir DIR  # Save to custom directory
"""

import argparse
from pathlib import Path

import matplotlib.pyplot as plt

MAX_CYLINDER = 199


def fcfs(sequence, current):
    return [current] + list(sequence)


def sstf(sequence, current):
    remaining = list(sequence)
    path = [current]
    cur = current
    while remaining:
        best = min(remaining, key=lambda x: abs(x - cur))
        path.append(best)
        remaining.remove(best)
        cur = best
    return path


def oneway_scan(sequence, current):
    sorted_seq = sorted(sequence)
    right = [x for x in sorted_seq if x >= current]
    left = [x for x in sorted_seq if x < current]
    return [current] + right + [MAX_CYLINDER, 0] + left


def twoway_scan(sequence, current):
    sorted_seq = sorted(sequence)
    right = [x for x in sorted_seq if x >= current]
    left = [x for x in sorted_seq if x < current]
    return [current] + right + [MAX_CYLINDER] + left[::-1]


def elevator(sequence, current):
    sorted_seq = sorted(sequence)
    right = [x for x in sorted_seq if x >= current]
    left = [x for x in sorted_seq if x < current]
    return [current] + left[::-1] + right


def calc_total_movement(path):
    return sum(abs(path[i + 1] - path[i]) for i in range(len(path) - 1))


def plot_schedule(ax, title, path):
    total = calc_total_movement(path)
    steps = list(range(len(path)))

    ax.plot(path, steps, "r-o", markersize=5, linewidth=1.5)
    ax.set_title(f"{title}\n(total: {total})", fontsize=12)
    ax.set_xlabel("Cylinder", fontsize=10)
    ax.set_ylabel("Step", fontsize=10)
    ax.set_xlim(-5, MAX_CYLINDER + 5)
    ax.invert_yaxis()

    for cyl, step in zip(path, steps):
        ax.annotate(str(cyl), (cyl, step), textcoords="offset points",
                    xytext=(8, 0), fontsize=8, color="darkblue")


def main():
    parser = argparse.ArgumentParser(description="Disk scheduling visualization")
    parser.add_argument("--save", action="store_true",
                        help="Save plots as PNG instead of showing")
    parser.add_argument("--output-dir", type=Path, default=None,
                        help="Output directory for PNG files")
    parser.add_argument("--sequence", nargs="+", type=int,
                        default=[98, 183, 37, 122, 14, 124, 65, 67],
                        help="Request sequence")
    parser.add_argument("--current", type=int, default=53,
                        help="Current cylinder position")
    args = parser.parse_args()

    if args.output_dir is None:
        args.output_dir = Path(__file__).resolve().parent.parent.parent / "docs" / "images"

    sequence = args.sequence
    current = args.current

    algorithms = [
        ("FCFS", fcfs),
        ("SSTF", sstf),
        ("C-SCAN (Oneway)", oneway_scan),
        ("SCAN (Twoway)", twoway_scan),
        ("LOOK (Elevator)", elevator),
    ]

    if args.save:
        args.output_dir.mkdir(parents=True, exist_ok=True)

    fig, axes = plt.subplots(1, 5, figsize=(22, 6), sharey=True)
    fig.suptitle(f"Disk Scheduling (seq: {sequence}, start: {current})", fontsize=14)

    for ax, (name, func) in zip(axes, algorithms):
        path = func(sequence, current)
        plot_schedule(ax, name, path)

    plt.tight_layout()

    if args.save:
        combined_path = args.output_dir / "disk_scheduling_all.png"
        fig.savefig(combined_path, dpi=150, bbox_inches="tight")
        print(f"Saved: {combined_path}")

    for name, func in algorithms:
        fig_single, ax_single = plt.subplots(figsize=(6, 6))
        path = func(sequence, current)
        plot_schedule(ax_single, name, path)
        plt.tight_layout()

        if args.save:
            fname = name.lower().replace(" ", "_").replace("(", "").replace(")", "")
            single_path = args.output_dir / f"disk_{fname}.png"
            fig_single.savefig(single_path, dpi=150, bbox_inches="tight")
            print(f"Saved: {single_path}")

    if not args.save:
        plt.show()
    else:
        plt.close("all")


if __name__ == "__main__":
    main()
