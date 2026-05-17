# Fixed Partition Allocation Lab Implementation Plan

> **For agentic workers:** REQUIRED: Use superpowers:subagent-driven-development (if subagents available) or superpowers:executing-plans to implement this plan. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build a fixed-partition memory-management OS lab with a verified reference implementation, then reduce the project source back to a compileable teaching scaffold with TODOs.

**Architecture:** Keep the interactive program terminal-first and close to the provided screenshot. Store shared data structures and declarations in `include/partition.h`, use `src/main.c` for I/O flow, use `src/partition.c` for partition operations, and preserve the fully working solution in documentation after validation.

**Tech Stack:** C11, `gcc`, `make`, Markdown docs, shell helper scripts, VS Code C/C++ configuration

---

## Chunk 1: Project Skeleton And Reference Targets

### Task 1: Define file layout and sample assets

**Files:**
- Create: `Makefile`
- Create: `include/partition.h`
- Create: `src/main.c`
- Create: `src/partition.c`
- Create: `data/case1.txt`
- Create: `README.md`
- Create: `.vscode/settings.json`
- Create: `.vscode/c_cpp_properties.json`

- [ ] **Step 1: Write the failing compile check**

Run: `make`
Expected: FAIL because the project files do not exist yet.

- [ ] **Step 2: Add the initial project skeleton**

Create the source, header, build file, sample data, and editor config with the agreed directory structure.

- [ ] **Step 3: Run compile check again**

Run: `make`
Expected: either compile success for stubs or a focused compile error showing the next missing implementation detail.

## Chunk 2: Verified Reference Implementation

### Task 2: Add a behavior-first reference test case

**Files:**
- Create: `tests/case1.expected.txt`
- Modify: `data/case1.txt`

- [ ] **Step 1: Write the failing output expectation**

Record the expected key output sections for the sample interaction using the screenshot-aligned prompt wording.

- [ ] **Step 2: Run the program against the sample input**

Run: `./build/fixed_partition_lab < data/case1.txt`
Expected: FAIL to match the expected behavior before implementation is complete.

- [ ] **Step 3: Implement the minimal complete reference behavior**

Fill in the allocation, printing, and recycle logic so the sample case behaves correctly.

- [ ] **Step 4: Re-run the sample case**

Run: `./build/fixed_partition_lab < data/case1.txt`
Expected: output structure and key states match the expected sample behavior.

## Chunk 3: Convert Runtime Code Back To Teaching Scaffold

### Task 3: Preserve the solution while restoring TODOs

**Files:**
- Modify: `src/main.c`
- Modify: `src/partition.c`
- Create: `docs/reference_solution.md`
- Create: `docs/case_reference_output.md`

- [ ] **Step 1: Save the verified implementation into docs**

Copy the final working code into `docs/reference_solution.md` with richer teaching comments.

- [ ] **Step 2: Replace core student work with TODO stubs**

Keep the public functions compileable while removing solved allocation and recycle logic from the starter source.

- [ ] **Step 3: Compile the scaffold**

Run: `make`
Expected: PASS with a buildable teaching scaffold.

## Chunk 4: Teaching Materials And Final Verification

### Task 4: Finish teaching docs and environment helpers

**Files:**
- Modify: `README.md`
- Create: `docs/report.md`
- Create: `docs/questions.md`
- Create: `scripts/run_case1.sh`

- [ ] **Step 1: Write the README with all required sections**

Include experiment overview, file responsibilities, implementation order, screenshot-vs-handout notes, naming crosswalk, exact commands, and a self-check list.

- [ ] **Step 2: Add report/questions/supporting docs**

Write a report template, memory-management reflection questions, and sample output notes.

- [ ] **Step 3: Add a runnable replay helper**

Create a terminal helper for replaying the sample case from `data/case1.txt`.

- [ ] **Step 4: Run final verification**

Run: `make clean && make`
Expected: PASS

Run: `./build/fixed_partition_lab < data/case1.txt`
Expected: starter scaffold compiles and runs, while README clearly explains that core logic is intentionally left as TODO for students.
