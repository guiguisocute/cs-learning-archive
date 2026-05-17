# Segment-Paged Memory Lab Implementation Plan

> **For agentic workers:** REQUIRED: Use superpowers:subagent-driven-development (if subagents available) or superpowers:executing-plans to implement this plan. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build a C11 segment-paged memory management lab with a verified reference implementation, then reduce the source tree back to a compileable teaching scaffold with TODO anchors.

**Architecture:** Keep the user-facing interaction close to the provided screenshot while splitting responsibilities into model, view, and main-flow files. First build a runnable reference binary and verify it with sample and edge cases, then preserve the full code in docs and replace the project source with a compileable starter that keeps the teacher-required public functions.

**Tech Stack:** C11, `make`, `gcc`, shell scripts, `expect`, VS Code C/C++ config

---

## File Map

- Create: `include/seg_paged_mem.h`
- Create: `include/seg_paged_io.h`
- Create: `src/main.c`
- Create: `src/mem_model.c`
- Create: `src/io_view.c`
- Create: `src/reference_main.c`
- Create: `tests/reference_cases.sh`
- Create: `data/case_sample.txt`
- Create: `data/case_small_fit.txt`
- Create: `data/case_multi_job.txt`
- Create: `data/case_address_ok.txt`
- Create: `data/case_address_oob.txt`
- Create: `data/case_no_space.txt`
- Create: `data/case_recycle_missing.txt`
- Create: `scripts/run_case.exp`
- Create: `.vscode/settings.json`
- Create: `.vscode/c_cpp_properties.json`
- Create: `Makefile`
- Create: `README.md`
- Create: `docs/reference_solution.md`
- Create: `docs/case_reference_output.md`
- Create: `docs/report.md`
- Create: `docs/questions.md`

## Chunk 1: Project Skeleton And First Failing Build Test

### Task 1: Create directory layout and build contract

**Files:**
- Create: `include/seg_paged_mem.h`
- Create: `include/seg_paged_io.h`
- Create: `src/main.c`
- Create: `src/mem_model.c`
- Create: `src/io_view.c`
- Create: `src/reference_main.c`
- Create: `Makefile`

- [ ] **Step 1: Write the failing build test**

Create `tests/reference_cases.sh` with a first check that runs:

```bash
make reference
```

Expected before implementation:
- build fails because source files or symbols are incomplete

- [ ] **Step 2: Run test to verify it fails**

Run:

```bash
bash tests/reference_cases.sh build
```

Expected:
- non-zero exit code from `make reference`

- [ ] **Step 3: Write minimal buildable project skeleton**

Add:
- headers with shared structs and prototypes
- stub `.c` files
- `Makefile` targets: `reference`, `student`, `clean`

- [ ] **Step 4: Run test to verify build passes**

Run:

```bash
bash tests/reference_cases.sh build
```

Expected:
- `make reference` exits `0`

## Chunk 2: Reference Implementation With Red-Green Coverage

### Task 2: Add allocation success flow

**Files:**
- Modify: `tests/reference_cases.sh`
- Modify: `src/reference_main.c`
- Modify: `src/mem_model.c`
- Modify: `src/io_view.c`
- Modify: `include/seg_paged_mem.h`
- Modify: `include/seg_paged_io.h`
- Test: `data/case_sample.txt`

- [ ] **Step 1: Write failing allocation test**

Add a test that runs the reference binary with `data/case_sample.txt` and checks for:
- initial bitmap output
- job allocation success labels
- non-empty page-table lines

- [ ] **Step 2: Run test to verify it fails**

Run:

```bash
bash tests/reference_cases.sh sample
```

Expected:
- grep-based assertion failure because allocation output is missing

- [ ] **Step 3: Implement minimal allocation path**

Implement:
- memory config parsing
- bitmap initialization
- job creation
- free-block search
- page-table filling
- screenshot-style output

- [ ] **Step 4: Run test to verify it passes**

Run:

```bash
bash tests/reference_cases.sh sample
```

Expected:
- script exits `0`

### Task 3: Add recycle flow

**Files:**
- Modify: `tests/reference_cases.sh`
- Modify: `data/case_multi_job.txt`
- Modify: `data/case_recycle_missing.txt`
- Modify: `src/reference_main.c`
- Modify: `src/mem_model.c`
- Modify: `src/io_view.c`

- [ ] **Step 1: Write failing recycle tests**

Add tests for:
- recycling an existing job restores free blocks
- recycling a missing job prints an error

- [ ] **Step 2: Run tests to verify they fail**

Run:

```bash
bash tests/reference_cases.sh recycle
```

Expected:
- assertions fail before recycle logic exists

- [ ] **Step 3: Implement minimal recycle path**

Implement:
- job lookup by name
- block release
- list removal
- updated bitmap and summary output

- [ ] **Step 4: Run tests to verify they pass**

Run:

```bash
bash tests/reference_cases.sh recycle
```

Expected:
- script exits `0`

### Task 4: Add address translation flow

**Files:**
- Modify: `tests/reference_cases.sh`
- Modify: `data/case_address_ok.txt`
- Modify: `data/case_address_oob.txt`
- Modify: `src/reference_main.c`
- Modify: `src/mem_model.c`
- Modify: `src/io_view.c`

- [ ] **Step 1: Write failing translation tests**

Add tests for:
- valid translation prints physical block and physical address
- invalid segment/page/offset prints explicit error

- [ ] **Step 2: Run tests to verify they fail**

Run:

```bash
bash tests/reference_cases.sh translate
```

Expected:
- assertions fail because translation menu path is missing

- [ ] **Step 3: Implement minimal translation path**

Implement:
- locate job
- validate segment index
- validate page index
- validate intra-page offset
- compute physical address

- [ ] **Step 4: Run tests to verify they pass**

Run:

```bash
bash tests/reference_cases.sh translate
```

Expected:
- script exits `0`

## Chunk 3: Edge Cases, Replay Helpers, And Documentation

### Task 5: Add no-space and exact-fit coverage

**Files:**
- Modify: `tests/reference_cases.sh`
- Modify: `data/case_small_fit.txt`
- Modify: `data/case_no_space.txt`
- Modify: `src/reference_main.c`
- Modify: `src/mem_model.c`
- Modify: `src/io_view.c`

- [ ] **Step 1: Write failing boundary tests**

Add tests for:
- exact-fit allocation
- insufficient free space rejection

- [ ] **Step 2: Run tests to verify they fail**

Run:

```bash
bash tests/reference_cases.sh boundary
```

Expected:
- assertions fail

- [ ] **Step 3: Implement minimal boundary handling**

Add:
- total-page capacity checks
- duplicate-job-name checks
- friendly error output

- [ ] **Step 4: Run tests to verify they pass**

Run:

```bash
bash tests/reference_cases.sh boundary
```

Expected:
- script exits `0`

### Task 6: Add replay tooling and editor config

**Files:**
- Create: `scripts/run_case.exp`
- Create: `.vscode/settings.json`
- Create: `.vscode/c_cpp_properties.json`

- [ ] **Step 1: Write failing replay smoke test**

Extend `tests/reference_cases.sh` to check:

```bash
./scripts/run_case.exp --case data/case_sample.txt
```

Expected before script exists:
- command fails

- [ ] **Step 2: Run test to verify it fails**

Run:

```bash
bash tests/reference_cases.sh replay
```

Expected:
- script exits non-zero

- [ ] **Step 3: Implement replay helper and VS Code config**

Create:
- one `expect` entry point with `--case` and `--all`
- VS Code settings aligned with C11 and include path

- [ ] **Step 4: Run test to verify it passes**

Run:

```bash
bash tests/reference_cases.sh replay
```

Expected:
- script exits `0` if `expect` exists, or prints a clear skip reason if `expect` is unavailable

## Chunk 4: Convert Verified Source To Teaching Scaffold

### Task 7: Preserve full solution in docs and reduce source to TODO scaffold

**Files:**
- Modify: `src/main.c`
- Modify: `src/mem_model.c`
- Modify: `src/io_view.c`
- Create: `docs/reference_solution.md`
- Create: `README.md`
- Create: `docs/case_reference_output.md`
- Create: `docs/report.md`
- Create: `docs/questions.md`

- [ ] **Step 1: Write failing scaffold build test**

Add a check that:
- `make student` builds
- source files still contain explicit TODO blocks in the handout-named public functions

- [ ] **Step 2: Run test to verify it fails**

Run:

```bash
bash tests/reference_cases.sh scaffold
```

Expected:
- TODO-presence assertion fails before reduction

- [ ] **Step 3: Convert source to compileable teaching scaffold**

Do:
- move complete code into `docs/reference_solution.md`
- replace student source with safe stubs and TODO anchors
- keep interaction wording and required function names
- add README, report template, questions, and reference-output doc

- [ ] **Step 4: Run test to verify it passes**

Run:

```bash
bash tests/reference_cases.sh scaffold
```

Expected:
- `make student` exits `0`
- TODO checks pass

## Chunk 5: Final Verification

### Task 8: Run full verification

**Files:**
- Modify: `tests/reference_cases.sh`

- [ ] **Step 1: Run the complete verification suite**

Run:

```bash
bash tests/reference_cases.sh all
make clean && make reference && make student
```

Expected:
- all assertions pass
- both binaries build successfully

- [ ] **Step 2: Manually inspect generated docs against the scaffold checklist**

Check:
- README sections
- naming crosswalk
- screenshot-vs-handout discrepancy notes
- exact commands
- self-check list

- [ ] **Step 3: Review final diff before reporting**

Run:

```bash
git status --short
```

Expected:
- only intended files changed
