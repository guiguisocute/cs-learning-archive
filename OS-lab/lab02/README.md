# 进程调度实验教学型脚手架

这个目录不是完整答案，而是为了帮助你通过 C11 风格的 coding 理解调度原理。

## 这个实验在做什么

这个实验要你模拟先来先服务调度算法（FCFS, First Come First Served）。

FCFS 的核心规则很简单：

- 哪个进程先到达，就先执行哪个进程
- 当前进程一旦开始运行，就一直运行到结束
- 后来的进程需要在就绪队列里等待

通过这个实验，你会把“调度算法”拆成可以落到代码里的几个具体问题：

- 如何表示进程、时间和队列
- 如何按到达时间组织就绪队列
- 如何计算开始时间、完成时间、周转时间、带权周转系数
- 如何把调度结果输出成一张可读的表

## 目录结构

```text
lab02/
├── .vscode/
│   ├── c_cpp_properties.json
│   ├── settings.json
│   ├── launch.json
│   └── extensions.json
├── include/
│   ├── process.h
│   ├── queue.h
│   ├── fcfs.h
│   └── logger.h
├── src/
│   ├── main.c
│   ├── fcfs.c
│   └── logger.c
├── data/
│   ├── case_fcfs_5.txt
│   ├── case_fcfs_10.txt
│   ├── case_compare.txt
│   ├── case_idle_gap.txt
│   ├── case_same_arrival.txt
│   ├── case_single.txt
│   └── case_unsorted_mix.txt
├── docs/
│   ├── case_reference_output.md
│   ├── report.md
│   ├── questions.md
│   └── runnable_reference.md
├── scripts/
│   └── run_fcfs.exp
└── Makefile
```

## 学习路径

1. 先读 `include/` 里的数据结构，弄清楚每个字段在调度里表示什么。
2. 再补 `src/fcfs.c` 里的基础函数，让队列能初始化、插入、删除。
3. 然后完成时间相关函数，再写 `run_fcfs_schedule()` 主过程。
4. 最后补 `print_schedule_results()` 和 `src/logger.c`，把结果和过程打印出来。

## 你会接触到的核心概念

- 到达时间：进程进入系统、准备参与调度的时刻
- 执行时间：进程真正占用 CPU 运行的时间
- 开始时间：这个进程第一次开始执行的时刻
- 完成时间：这个进程执行结束的时刻
- 周转时间：从到达系统到执行完成，总共经历了多久
- 带权周转系数：周转时间相对于执行时间的比例

如果这些概念一开始有点绕，建议先手推一两个样例进程，再回头写代码。

## 当前设计目标

- 你需要自己完成核心算法。
- 脚手架已经帮你准备好数据结构、文件组织、样例数据、学习问题和实验报告模板。
- 代码里故意保留 `TODO` 和“思考点”，方便你边写边理解。
- 当前骨架默认使用 C11 和 C 语言风格，而不是 C++。
- 工作区附带 `.vscode/`，便于在 WSL 中稳定使用 IntelliSense、构建任务和 GDB 调试。

## 最短上手顺序

如果你想快速进入可开发状态，可以按这个顺序补：

1. `include/process.h`、`include/queue.h`
2. `src/fcfs.c` 里的 `init_process_queue()`、`insert_process_by_arrival()`、`remove_front_process()`
3. `src/fcfs.c` 里的 `is_earlier_time()`、`add_minutes_to_time()`、`calculate_time_difference()`
4. `src/fcfs.c` 里的 `read_processes()`、`run_fcfs_schedule()`、`print_schedule_results()`
5. `src/main.c`
6. `src/logger.c`

这样做的好处是：先把数据结构和基础操作打通，再处理调度逻辑，最后再补交互和输出，不容易乱。

## 头文件和源文件分别负责什么

### `include/`

- `process.h`
  定义单个进程结点和时间结构体，是整个实验的数据基础。
- `queue.h`
  定义就绪队列的头尾指针。
- `fcfs.h`
  声明 FCFS 相关函数，告诉你这一题要实现哪些核心接口。
- `logger.h`
  声明日志输出函数，方便你后面观察调度过程。

### `src/`

- `main.c`
  程序入口。负责把输入、调度、输出这些步骤串起来。
- `fcfs.c`
  实验核心。这里面既有链表操作，也有时间计算和 FCFS 调度主逻辑。
- `logger.c`
  负责过程日志和辅助输出，不直接决定调度结果，但有助于你理解程序执行过程。

## `fcfs.c` 里的函数分类

可以把 `fcfs.c` 里的函数分成 4 类来看：

1. 队列基础操作
   - `init_process_queue()`
   - `insert_process_by_arrival()`
   - `remove_front_process()`

2. 时间处理函数
   - `is_earlier_time()`
   - `add_minutes_to_time()`
   - `calculate_time_difference()`

3. 输入与输出
   - `read_processes()`
   - `print_schedule_results()`

4. 调度主过程
   - `run_fcfs_schedule()`

如果一开始直接盯着 `run_fcfs_schedule()` 看会很乱，建议先把前 3 类函数都理解清楚，再回来看主过程。

## 编译

```bash
make
./scheduler_lab
```

如果 C/C++ 扩展偶发性找不到系统头文件，可以先执行：

```text
C/C++: Reset IntelliSense Database
Developer: Reload Window
```

## 输入说明

程序默认从标准输入读取，你也可以重定向样例文件：

```bash
./scheduler_lab < data/case_fcfs_5.txt
```

如果你要一键验证当前实现是否仍然符合脚手架基准，请直接运行：

```bash
./scripts/run_fcfs.exp --all ./scheduler_lab data
```

每个样例的参考输出已经写在 [case_reference_output.md](/home/guiguisocute/Project/jxnu-OS-src/lab02/docs/case_reference_output.md) 里，便于你直接在终端输出后人工对照。

实验要求进程名使用“姓名 + 序号”，例如：

```text
5001 李小龙1 9:40 20
5002 李小龙2 9:55 15
```

## 建议的阅读方式

不要把整个项目从第一行硬读到最后一行。更有效的方式是：

1. 先看结构体字段都表示什么
2. 再看队列是怎么组织起来的
3. 然后看时间是怎么计算的
4. 最后再看 FCFS 主过程怎么把这些东西串起来

这样读，代码会更像“拼装模块”，而不是一整坨难以下手的实现。

## 与原指南的命名对照

为了提高可读性，这个脚手架把老师原始框架里一些较难读的命名做了规范化。核心数据结构、结果含义和程序流程没有改变，只是名字更直白了。如果老师按原讲义检查，你可以按下面这张表对应说明。

### 核心数据结构对照

| 原指南命名 | 当前项目命名 | 含义 |
| --- | --- | --- |
| `Time` | `TimePoint` | 一个时刻，包含 `hour` 和 `min` |
| `node` | `ProcessNode` | 单个进程结点 |
| `Q` | `ProcessQueue` | 就绪队列，包含队头和队尾 |
| `id` | `process_id` | 进程编号 |
| `name` | `process_name` | 进程名 |
| `arrive` | `arrival_time` | 到达就绪队列时间 |
| `zx` | `burst_time` | 执行时间 |
| `start` | `start_time` | 开始时间 |
| `finish` | `finish_time` | 完成时间 |
| `zz` | `turnaround_time` | 周转时间 |
| `zzxs` | `weighted_turnaround_time` | 带权周转系数 |
| `end` | `rear` | 队尾指针 |

### 函数命名对照

| 原指南函数名 | 当前项目函数名 | 作用 |
| --- | --- | --- |
| `check` | `is_earlier_time` | 比较两个时刻先后 |
| `init` | `init_process_queue` | 初始化就绪队列 |
| `insert` | `insert_process_by_arrival` | 按到达时间插入进程结点 |
| `dele` | `remove_front_process` | 删除队头进程结点 |
| `input` | `read_processes` | 读取进程输入并构建队列 |
| `cal` | `add_minutes_to_time` | 由开始时间和执行时间推出结束时间 |
| `deline` | `calculate_time_difference` | 计算两个时刻的分钟差 |
| `fcfs` | `run_fcfs_schedule` | 执行 FCFS 调度过程 |
| `output` | `print_schedule_results` | 输出调度结果和平均值 |

### 程序流程对照

老师原指南里的主流程大意是：

1. 初始化队列
2. 输入进程
3. 执行 FCFS 调度
4. 输出结果
5. 释放链表

当前项目对应的主流程也是同一套逻辑，只是函数名改成了更易读的版本：

1. `init_process_queue()`
2. `read_processes()`
3. `run_fcfs_schedule()`
4. `print_schedule_results()`
5. `remove_front_process()`

如果老师问为什么和讲义上的名字不一样，你可以直接说明：只是做了命名规范化，算法、数据项和程序框架没有改。
