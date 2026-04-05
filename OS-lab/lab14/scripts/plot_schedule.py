#!/usr/bin/env python3
import argparse
from pathlib import Path


def parse_args():
    parser = argparse.ArgumentParser(description="绘制磁盘调度折线图（SVG）")
    parser.add_argument("--title", default="磁盘调度过程", help="图标题")
    parser.add_argument(
        "--sequence",
        nargs="+",
        type=int,
        required=True,
        help="按访问顺序给出的柱面号序列",
    )
    parser.add_argument(
        "--output",
        type=Path,
        default=Path("schedule.svg"),
        help="输出 SVG 路径",
    )
    parser.add_argument(
        "--max-cylinder",
        type=int,
        default=199,
        help="最大柱面号，默认 199",
    )
    return parser.parse_args()


def map_x(index, total, left, width):
    if total <= 1:
        return left + width / 2.0
    return left + index * (width / float(total - 1))


def map_y(value, max_cylinder, top, height):
    ratio = value / float(max_cylinder if max_cylinder > 0 else 1)
    return top + ratio * height


def build_svg(title, sequence, max_cylinder):
    width = 1100
    height = 520
    left = 50
    top = 80
    plot_width = 980
    plot_height = 360

    points = []
    for index, value in enumerate(sequence):
        x = map_x(index, len(sequence), left, plot_width)
        y = map_y(value, max_cylinder, top, plot_height)
        points.append((x, y, value))

    polyline = " ".join(f"{x:.2f},{y:.2f}" for x, y, _ in points)
    labels = "\n".join(
        f'<text x="{x:.2f}" y="{top - 18}" font-size="18" text-anchor="middle" fill="#111">{value}</text>'
        for x, _, value in points
    )
    dots = "\n".join(
        f'<circle cx="{x:.2f}" cy="{y:.2f}" r="4.5" fill="red" />'
        for x, y, _ in points
    )

    return f"""<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="{height}" viewBox="0 0 {width} {height}">
  <rect width="100%" height="100%" fill="white" />
  <text x="{width / 2:.2f}" y="36" font-size="24" text-anchor="middle" fill="#111">{title}</text>
  <rect x="{left - 20}" y="{top - 20}" width="{plot_width + 40}" height="{plot_height + 40}" rx="6" fill="#f1f1f1" />
  <line x1="{left - 20}" y1="{top}" x2="{left + plot_width + 20}" y2="{top}" stroke="#d0d0d0" stroke-width="1" />
  <polyline points="{polyline}" fill="none" stroke="#111" stroke-width="2" />
  {dots}
  {labels}
</svg>
"""


def main():
    args = parse_args()
    args.output.parent.mkdir(parents=True, exist_ok=True)
    svg_text = build_svg(args.title, args.sequence, args.max_cylinder)
    args.output.write_text(svg_text, encoding="utf-8")


if __name__ == "__main__":
    main()
