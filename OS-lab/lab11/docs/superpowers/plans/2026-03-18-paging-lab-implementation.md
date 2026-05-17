# Paging Lab Implementation Plan

> **For agentic workers:** REQUIRED: Use superpowers:subagent-driven-development (if subagents available) or superpowers:executing-plans to implement this plan. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 为请求分页实验生成 C11 参考实现，并回退为可编译教学脚手架。

**Architecture:** 工程保留 `include/` + `src/` + `data/` + `docs/` + `scripts/` 结构。先在 `src/main.c` 完整实现 FIFO/LRU 并用样例验证，再将同名函数收回为 `TODO` 版本，把完整答案和参考输出放入 `docs/`。

**Tech Stack:** C11, Makefile, POSIX shell, Expect

---

## Chunk 1: 参考实现与验证

### Task 1: 样例与测试入口

**Files:**
- Create: `data/case_3_blocks.txt`
- Create: `data/case_4_blocks.txt`
- Create: `tests/test_cases.sh`
- Create: `Makefile`

- [ ] 写入样例数据
- [ ] 先写失败测试
- [ ] 运行 `make test`，确认在没有实现时失败
- [ ] 补齐编译目标

### Task 2: 完整实现 FIFO/LRU

**Files:**
- Create: `include/paging_lab.h`
- Create: `src/main.c`

- [ ] 实现 `out`、`input`、`print`
- [ ] 实现 `solve1` 的 FIFO 逻辑
- [ ] 实现 `solve2` 的 LRU 逻辑
- [ ] 运行 `make test`

## Chunk 2: 教学脚手架与文档

### Task 3: 生成教学版 starter

**Files:**
- Modify: `src/main.c`

- [ ] 保留老师给出的函数名
- [ ] 将核心算法改回 `TODO`
- [ ] 保证 `make` 仍可编译通过

### Task 4: 教学文档与回放

**Files:**
- Create: `README.md`
- Create: `docs/reference_solution.md`
- Create: `docs/case_reference_output.md`
- Create: `docs/report.md`
- Create: `docs/questions.md`
- Create: `.vscode/settings.json`
- Create: `.vscode/c_cpp_properties.json`
- Create: `scripts/run_cases.exp`

- [ ] 记录截图与题面差异
- [ ] 记录命名映射
- [ ] 写清 build/run/replay 命令
- [ ] 补全报告模板与思考题
