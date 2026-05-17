# 固定分区分配与回收实验教学说明

## 1. 实验在模拟什么

这个实验模拟的是操作系统里的固定分区存储管理。

所谓“固定分区”，就是在作业真正装入之前，系统已经先把用户区切成若干块大小固定的分区。之后每次来一个作业，系统不是重新切空间，而是直接去分区表里找一个“装得下并且当前空闲”的分区，把它分给这个作业使用。等作业运行结束，再把对应分区回收为空闲状态。

这个模型虽然简单，但它非常适合拿来理解三个核心问题：

- 操作系统到底需要记录哪些信息，才能决定一块内存能不能分配给某个作业。
- “分配”这件事本质上是在修改哪张表、哪几个字段。
- 为什么固定分区实现简单，但会带来空间浪费，也就是常见的内部碎片问题。

如果你只盯着“怎么把代码写出来”，很容易把这个实验做成一堆输入输出判断题。真正需要理解的是：程序里的“分区表状态变化”，对应的就是操作系统在做内存管理决策。

## 2. 这次你真正要学会什么

完成这个实验后，你至少应该能清楚回答下面这些问题：

- 一个分区最少要记录哪些信息，才能支持装入和回收。
- 为什么作业 `30KB` 会进入 `32KB` 分区，而不会进入 `12KB` 分区。
- 为什么分配时要同时判断“容量是否足够”和“当前是否空闲”。
- 回收为什么是“按作业名查找分区”，而不是重新输入分区号。
- 固定分区为什么会产生浪费，以及这种浪费出现在哪里。

从代码角度看，你的核心任务只有两件：

- 实现“作业装入”逻辑。
- 实现“作业回收”逻辑。

但是从实验理解角度看，你更应该观察的是：

- 分区表在每次操作前后如何变化。
- 哪些字段是输入给定的，哪些字段是程序运行过程中动态修改的。
- 终端打印的 `0` 和 `JOB1 / JOB2 / JOB3` 分别代表什么。

## 3. 项目当前是什么状态

这个项目不是单纯的“空白模板”，也不是直接交差的最终答案，而是两条线并存：

- `src/` 目录里放的是教学骨架。
- `docs/` 目录里保留了已经验证过的完整参考实现。

这样做的目的很明确：

- 你可以先自己完成实验，不会一打开源码就直接看到答案。
- 你卡住时又能去参考文档核对思路，而不是重新到处找资料。

也就是说，当前源码是“故意没有写完”的。`allocate_job_to_partition()` 和 `recycle_job_by_name()` 中保留了 `TODO`，这是本实验的核心学习部分，不是遗漏。

## 4. 目录怎么读，先看哪里

建议你第一次打开项目时，不要从上到下机械翻文件，而是按下面顺序看：

- [README.md](/home/guiguisocute/Project/jxnu-OS-src/lab07/README.md)
  先建立对实验目标、目录结构、实现顺序和常见误区的整体认识。

- [include/partition.h](/home/guiguisocute/Project/jxnu-OS-src/lab07/include/partition.h)
  先看数据结构。你要先知道“程序维护了什么信息”，再谈算法。

- [src/main.c](/home/guiguisocute/Project/jxnu-OS-src/lab07/src/main.c)
  看清楚程序主流程：什么时候输入分区、什么时候输入作业、什么时候打印、什么时候进入回收循环。

- [src/partition.c](/home/guiguisocute/Project/jxnu-OS-src/lab07/src/partition.c)
  这里才是你真正要补的实验核心。

- [data/case1.txt](/home/guiguisocute/Project/jxnu-OS-src/lab07/data/case1.txt)
  对照题目样例输入，理解交互过程。

- [docs/case_reference_output.md](/home/guiguisocute/Project/jxnu-OS-src/lab07/docs/case_reference_output.md)
  观察样例运行时每一步分区表应该变成什么样。

- [docs/reference_solution.md](/home/guiguisocute/Project/jxnu-OS-src/lab07/docs/reference_solution.md)
  只有在你自己尝试后再去看，效果最好。

## 5. 每个文件到底负责什么

- [include/partition.h](/home/guiguisocute/Project/jxnu-OS-src/lab07/include/partition.h)
  放分区结构体、全局数组、常量和函数声明。这个文件定义了“程序要管理的数据长什么样”。

- [src/main.c](/home/guiguisocute/Project/jxnu-OS-src/lab07/src/main.c)
  负责整体交互流程，不负责复杂决策。它更像调度者：先读入数据，再调用函数分配，再进入回收循环。

- [src/partition.c](/home/guiguisocute/Project/jxnu-OS-src/lab07/src/partition.c)
  负责分区相关行为，是本实验的核心实现区。你主要要补的就是这里。

- [data/case1.txt](/home/guiguisocute/Project/jxnu-OS-src/lab07/data/case1.txt)
  提供可直接重放的样例输入，避免你每次手打一长串数据。

- [tests/case1.expected.txt](/home/guiguisocute/Project/jxnu-OS-src/lab07/tests/case1.expected.txt)
  这是我在生成参考实现阶段用来比对输出的参考文本，你可以把它当成“样例行为说明”，但不建议你在没写完前就逐行照抄。

- [docs/reference_solution.md](/home/guiguisocute/Project/jxnu-OS-src/lab07/docs/reference_solution.md)
  保存已经跑通样例的一份完整实现，并附有“思考 / 思路”说明。

- [docs/case_reference_output.md](/home/guiguisocute/Project/jxnu-OS-src/lab07/docs/case_reference_output.md)
  保存样例输入对应的终端输出，适合你在调试时逐段对照。

- [docs/report.md](/home/guiguisocute/Project/jxnu-OS-src/lab07/docs/report.md)
  实验报告模板。

- [docs/questions.md](/home/guiguisocute/Project/jxnu-OS-src/lab07/docs/questions.md)
  思考题，帮助你把“代码现象”转换成“操作系统概念理解”。

- [scripts/run_case1.exp](/home/guiguisocute/Project/jxnu-OS-src/lab07/scripts/run_case1.exp)
  用 `expect` 按提示逐步回放样例输入，终端效果接近手工交互。

- [.vscode/settings.json](/home/guiguisocute/Project/jxnu-OS-src/lab07/.vscode/settings.json)
  工作区基础设置。

- [.vscode/c_cpp_properties.json](/home/guiguisocute/Project/jxnu-OS-src/lab07/.vscode/c_cpp_properties.json)
  C11 头文件路径和 IntelliSense 配置。

## 6. 你应该先理解的数据结构

老师给的题面里核心结构是：

- 分区号
- 分区大小
- 分区起址
- 分区状态

当前项目里把它整理成了更清晰的 C11 命名：

- `partition_info.id`：分区号
- `partition_info.size_kb`：分区大小
- `partition_info.start_kb`：分区起址
- `partition_info.status`：分区状态

这里最值得你注意的是 `status`。

实验现象里你看到的是：

- 空闲时打印 `0`
- 被占用时打印 `JOB1`、`JOB2`、`JOB3`

但在实现层面，通常不会真的把空闲状态保存成字符 `"0"`。更自然的做法是：

- 内部用空字符串表示“空闲”
- 打印时再把空字符串显示成 `0`

这样做的好处是判断空闲状态更直接，代码也更干净。你如果只盯着终端输出而不思考“内部如何表示”，就很容易把显示逻辑和存储逻辑混在一起。

## 7. 推荐实现顺序，不要一上来就乱写

下面这个顺序是专门按“最少卡壳路径”安排的，建议照着做：

### 第一步：先读懂主流程

先打开 [src/main.c](/home/guiguisocute/Project/jxnu-OS-src/lab07/src/main.c)，不要急着改。

你至少先回答自己这几个问题：

- 分区表是在什么时候输入的？
- 作业大小是在什么时候输入的？
- 哪一步之后会打印“作业名 作业大小”？
- 哪一步之后会打印“分区信息”？
- 回收循环什么时候结束？

如果这些顺序你都没理清，就不应该直接写算法。

### 第二步：补 `allocate_job_to_partition()`

再看 [src/partition.c](/home/guiguisocute/Project/jxnu-OS-src/lab07/src/partition.c) 里的 `allocate_job_to_partition()`。

你要做的不是“找一个最大分区”，也不是“找最接近的分区”，而是按题目和截图当前行为去做：

- 从前往后扫描分区表。
- 找到第一个容量足够且状态为空闲的分区。
- 把状态设置成对应的作业名。
- 找到后立刻停止。

你写完这个函数后，先不要着急回收。先运行样例，看第一次分配结束后的分区表是不是：

- `32KB` 分区对应 `JOB1`
- `64KB` 分区对应 `JOB2`
- `128KB` 分区对应 `JOB3`

如果这一步都不对，后面的回收肯定也不对。

### 第三步：补 `recycle_job_by_name()`

分配正确后，再写回收逻辑。

注意这个实验里有一个很重要的“题面与样例差异”：

- 题面提示写的是“请输入回收的作业名”
- 你给的样例输入却写的是 `2`、`3`、`1`

因此一个更稳妥的实现是：

- 如果用户输入 `JOB2`，程序能识别
- 如果用户输入 `2`，程序也能识别

这就是为什么项目里专门保留了 `normalize_job_name()` 这样的辅助接口。它的学习价值不在于“语法技巧”，而在于让你意识到：交互输入和内部标准表示，不一定要完全相同。

### 第四步：最后才微调输出格式

很多同学会一开始就花时间调空格、调制表符、调标题。这个顺序是反的。

正确顺序应该是：

1. 先确保分配逻辑正确。
2. 再确保回收逻辑正确。
3. 最后才调整输出和截图尽量一致。

因为格式错了你一眼能看出来，逻辑错了才是真正难查的地方。

## 8. 看截图时你应该观察什么

你给的截图不是单纯“长得像就行”的参考图，它其实是在告诉你实验判分最看重什么。

应该重点观察这三件事：

- 初始分区表里，所有状态都是 `0`
- 三个作业装入后，只有合适的分区状态发生变化
- 每次回收后，只有对应作业所在分区恢复为空闲

换句话说，截图真正传达的不是排版，而是“状态迁移过程”。

你调试时也应该按这个思路做：

- 先看初始状态有没有全空闲
- 再看分配后是不是只改了该改的三项
- 再看每次回收是不是只影响一个分区

## 9. 题面骨架和截图之间有哪些不一致

这里必须明确说清楚，否则你写的时候很容易怀疑自己：

### 不一致 1：题面用了 C++ 风格 `string`

老师给的伪代码用了 `string`。但这个项目按 OS 实验更常见的 C11 风格实现，因此状态字段用的是字符数组，不再依赖 C++。

这不是“和题目不一样”，而是把题目的思路换成更适合当前工程结构的 C 语言写法。

### 不一致 2：回收输入提示和样例输入不一致

题面像是在让你输入 `JOB2` 这种作业名。
样例却直接输入 `2`、`3`、`1`。

当前项目把截图和样例行为视为更高优先级，因此推荐你实现兼容两种输入。

### 不一致 3：截图更强调打印时机

如果你只照着伪代码抄，很容易忽略每个阶段都应该打印什么。

截图实际上明确了这些打印节点：

- 初始分区信息打印一次
- 作业信息打印一次
- 分配结束后再打印分区信息
- 每次回收完成后再打印分区信息

当前骨架按这个节奏组织主流程。

## 10. 命名映射，为什么没有完全照抄老师变量名

老师原始题面里的名字偏短，作为草稿可以，作为项目代码可读性不够好。因此当前项目做了规范化，但保留了必须对题目友好的接口名。

对应关系如下：

- 老师的 `struct Y` 对应 `partition_info`
- 老师的 `a` 对应 `partitions`
- 老师的 `v` 对应 `job_sizes`
- 老师的 `sz` 对应 `size_kb`
- 老师的 `address` 对应 `start_kb`
- 老师的 `station` 对应 `status`
- 老师要求的 `input()`、`print()` 仍然保留

这样处理的好处是：

- 你写代码时更容易看懂字段含义
- 你答辩或解释题目时，也还能说清楚和老师原题面的对应关系

## 11. 现在源码里哪些地方是故意留空的

请直接重点看 [src/partition.c](/home/guiguisocute/Project/jxnu-OS-src/lab07/src/partition.c)：

- `allocate_job_to_partition()`
- `recycle_job_by_name()`

这两个函数的 `TODO` 不是装饰，而是本实验的主任务。

此外还有两类“可选改进”：

- `input()` 中可以补充输入合法性检查
- `print()` 中可以继续优化输出排版

但要注意主次顺序：

- 分配和回收逻辑是核心
- 输入校验和对齐格式是加分或完善项

## 12. 构建、运行、回放该怎么做

编译：

```bash
make
```

运行程序：

```bash
./build/fixed_partition_lab
```

直接重放样例：

```bash
expect scripts/run_case1.exp
```

如果你只是想对照正确输出，而不是自己手敲，可以看：

- [docs/case_reference_output.md](/home/guiguisocute/Project/jxnu-OS-src/lab07/docs/case_reference_output.md)

如果你已经自己写完，想核对完整思路和代码，可以看：

- [docs/reference_solution.md](/home/guiguisocute/Project/jxnu-OS-src/lab07/docs/reference_solution.md)

## 13. 调试时最容易犯的错

下面这些错误非常常见，建议你在开写前先有意识地规避：

- 只判断分区大小，不判断分区是否空闲。
- 找到一个合适分区后没有 `break`，导致同一个作业占了多个分区。
- 把空闲状态真的存成字符串 `"0"`，后面比较时逻辑变乱。
- 回收时按分区号删，而不是按作业名查找。
- 没有兼容输入 `2` 和输入 `JOB2` 两种写法。
- 先花很多时间调输出格式，却没有先确认分配逻辑是否正确。

如果你运行后发现“程序能打印，但状态永远不变”，那通常不是 `print()` 的问题，而是分配和回收逻辑根本还没写进去。

## 14. 建议你如何自己检查，而不是直接看答案

你可以按下面这个自检流程走：

1. 先运行程序，确认初始时所有分区状态都是 `0`。
2. 实现分配函数后，再运行样例，确认 `JOB1`、`JOB2`、`JOB3` 是否进入了正确分区。
3. 再实现回收函数，分别检查输入 `2`、`3`、`1` 后，是否只回收对应分区。
4. 最后把终端输出和 [docs/case_reference_output.md](/home/guiguisocute/Project/jxnu-OS-src/lab07/docs/case_reference_output.md) 做人工对照。

如果你能在不看参考实现的前提下把这四步都做对，这个实验基本就真正掌握了。

## 15. 最后的自检清单

在你打开参考解之前，至少先确认下面这些问题全部能回答：

- 什么叫固定分区，和“运行时再切空间”有什么不同？
- 分区表里哪几个字段是静态输入，哪个字段会动态变化？
- `30KB / 60KB / 90KB` 为什么分别进入那三个分区？
- 为什么空闲分区在界面上显示 `0`？
- 为什么回收逻辑应该按作业名定位？
- 你的程序是否兼容截图里的回收输入方式？
- 你的分配逻辑是否只占用一个分区且找到后立即停止？
- 你的回收逻辑是否只清空匹配作业的那个分区？

如果这些问题你还有一半说不清，那就先别看参考答案，回到 [src/partition.c](/home/guiguisocute/Project/jxnu-OS-src/lab07/src/partition.c) 继续补和调。
