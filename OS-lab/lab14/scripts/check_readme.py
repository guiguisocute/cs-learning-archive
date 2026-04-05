#!/usr/bin/env python3
from pathlib import Path
import sys


ROOT = Path(__file__).resolve().parent.parent
README = ROOT / "README.md"

REQUIRED_SECTIONS = [
    "## 项目定位",
    "## 仓库结构",
    "## 学生要完成什么",
    "## 建议实现路径",
    "## 验收关注点",
    "## 题面与样例差异",
    "## 如何使用参考解",
    "## 构建与验证",
]


def main():
    content = README.read_text(encoding="utf-8")
    missing = [section for section in REQUIRED_SECTIONS if section not in content]

    if missing:
        sys.stderr.write("README 缺少以下章节：\n")
        for section in missing:
            sys.stderr.write(f"- {section}\n")
        return 1

    sys.stdout.write("README sections check passed\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
