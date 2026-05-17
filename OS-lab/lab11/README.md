# 请求分页式存储管理实验 README

## 1. 这份工程是拿来做什么的

这不是一份直接交作业的“现成答案工程”，而是一份有明确教学目的的实验脚手架。

你要完成的实验主题是：在请求分页式存储管理中，模拟页面访问过程，并比较两种页面置换算法：

- `FIFO`：先进先出，淘汰最早进入内存的页面
- `LRU`：最近最久未使用，淘汰距离当前时刻最久没有被访问的页面

这份工程已经帮你准备好：

- 交互式菜单框架
- 样例输入
- 文档化的参考答案
- 样例参考输出
- 报告模板和思考题

但它故意没有把核心算法留在源码里。你真正要自己完成的是：

- 怎么判断命中和缺页
- 怎么决定替换哪个页面
- 怎么把“每一步”的物理块状态记录下来
- 怎么把过程表输出得和实验截图接近

如果你直接去看参考答案，你只能得到“程序长什么样”；如果你先用这份脚手架自己补完，再回头看参考答案，你才会真正理解“这个实验为什么要这样写”。

## 2. 先用原理把实验想明白

### 2.1 请求分页到底在模拟什么

程序给你的是一个页面访问串，例如：

```text
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
```

你可以把它理解成“作业依次要访问哪些页面”。

操作系统每访问一个页面，都要先看这个页面当前是否已经在内存的物理块里：

- 在内存里：命中，直接访问
- 不在内存里：缺页，必须装入内存

缺页时又分两种情况：

- 物理块还没满：直接装入
- 物理块已经满：必须先淘汰一个旧页，再装入新页

所以，这个实验的本质不是“打印一个表”，而是不断回答下面这个问题：

> 当前要访问的新页面不在内存里时，应该换出谁？

FIFO 和 LRU 的区别，就集中在这个问题上。

### 2.2 FIFO 在想什么

FIFO 不关心哪个页面最近被用过，也不关心哪个页面马上还会再用。

它只记一件事：

> 谁最早进入内存，谁就最先出去。

因此它实现起来通常比较直接：

- 命中时不换页
- 缺页时，如果物理块已满，就淘汰“驻留时间最长”的那个页

你可以把它理解成一个循环队列或队首指针问题。

这个算法的优点是实现简单，缺点也很明显：它不利用“局部性”信息。某个页面即使刚刚被频繁访问过，只要它进入内存最早，仍然可能被淘汰。

### 2.3 LRU 在想什么

LRU 的思路比 FIFO 更接近“最近的访问行为更有参考价值”。

它关心的是：

> 哪个页面已经很久没有再被访问过？

因此它通常需要多记录一份信息：

- 每个物理块中的页面，上一次被访问是在第几步

一旦发生缺页且物理块已满，就去找“最近一次访问时间最早”的那个页，把它换出去。

这就是为什么很多同学写 FIFO 很顺，写 LRU 就容易乱：FIFO 只要管“进入顺序”，LRU 还要在命中时动态更新时间信息。

### 2.4 为什么这次实验最容易写错

这个实验最容易出现的错误，不是语法错误，而是“状态没有记录完整”。

你至少要同时维护三类信息：

- 当前物理块里有哪些页面
- 哪一步发生了缺页
- 每一步结束后，物理块整体长什么样

很多程序最后缺页率不对，不是因为替换条件写错，而是因为下面这些细节没处理好：

- 命中时忘了更新 LRU 的“最近访问时刻”
- 只在缺页时记录快照，命中时没记录
- 替换页面后更新了当前状态，但没有把这一列写入过程表
- 输出时把“页面序列”和“时间下标”混了

如果你脑子里先没有这三类状态的分工，代码会越来越乱。

## 3. 这份工程里每个文件是干什么的

- [src/main.c](/home/guiguisocute/Project/jxnu-OS-src/lab11/src/main.c)  
  教学脚手架主文件。这里保留了老师题面中的主流程和函数名，但核心算法已经改成 `TODO`。

- [include/paging_lab.h](/home/guiguisocute/Project/jxnu-OS-src/lab11/include/paging_lab.h)  
  常量和函数声明。你先别把注意力放在这里，优先看 `src/main.c`。

- [data/case_3_blocks.txt](/home/guiguisocute/Project/jxnu-OS-src/lab11/data/case_3_blocks.txt)  
  3 个物理块的样例输入。

- [data/case_4_blocks.txt](/home/guiguisocute/Project/jxnu-OS-src/lab11/data/case_4_blocks.txt)  
  4 个物理块的样例输入。

- [data/case_single_frame.txt](/home/guiguisocute/Project/jxnu-OS-src/lab11/data/case_single_frame.txt)  
  1 个物理块边界测试，验证“只有连续重复访问才会命中”。

- [data/case_all_same_page.txt](/home/guiguisocute/Project/jxnu-OS-src/lab11/data/case_all_same_page.txt)  
  全部访问同一页面，验证首次缺页后应持续命中。

- [data/case_frames_ge_pages.txt](/home/guiguisocute/Project/jxnu-OS-src/lab11/data/case_frames_ge_pages.txt)  
  物理块数大于不同页面数，验证只应在首次装入时缺页。

- [data/case_alternating_hotset.txt](/home/guiguisocute/Project/jxnu-OS-src/lab11/data/case_alternating_hotset.txt)  
  热点集合切换测试，用来观察 FIFO 和 LRU 的差异。

- [data/case_short_sparse.txt](/home/guiguisocute/Project/jxnu-OS-src/lab11/data/case_short_sparse.txt)  
  短访问串测试，检查短数据和空位输出时是否稳定。

- [docs/reference_solution.md](/home/guiguisocute/Project/jxnu-OS-src/lab11/docs/reference_solution.md)  
  已验证的完整 C11 参考实现。建议你至少先把 `solve1` 和 `solve2` 自己写完，再来看这份文档。

- [docs/case_reference_output.md](/home/guiguisocute/Project/jxnu-OS-src/lab11/docs/case_reference_output.md)  
  样例输出和关键缺页率结果。适合在你写完程序后做人工对照。

- [docs/report.md](/home/guiguisocute/Project/jxnu-OS-src/lab11/docs/report.md)  
  实验报告模板。

- [docs/questions.md](/home/guiguisocute/Project/jxnu-OS-src/lab11/docs/questions.md)  
  思考题。建议你在实现后再回头回答，会更具体。

- [scripts/run_cases.exp](/home/guiguisocute/Project/jxnu-OS-src/lab11/scripts/run_cases.exp)  
  用交互方式批量回放样例，比纯输入重定向更接近截图里的运行体验。

## 4. 题面、截图和这份工程之间有什么不一致

这里必须提前说明，不然后面你会越写越疑惑。

### 4.1 题面给的是 C++ 风格框架，但本工程是 C11

老师原始材料里用了 `string`、`vector`、`priority_queue` 这类 C++ 结构，但你后续明确要求用 C11，所以工程已经全部改成：

- `.c` 源文件
- C11 编译方式
- 数组和普通函数实现

这不是“和题面冲突”，而是“保留实验思想，换成你要求的语言形式”。

### 4.2 菜单里写的是 `LRU(LFU)`，但实验描述更接近 LRU

截图和题面菜单写的是：

```text
2. LRU(LFU)分配
```

但文字说明写的是“选择最长时间没有被引用的页面”，这对应的是 `LRU`，不是标准意义上的 `LFU`。

所以本工程采用的策略是：

- 菜单文案保留截图写法，方便你和实验截图一致
- 算法语义按 `LRU` 处理，方便你和题目文字描述一致

### 4.3 源码为什么不是完整答案

因为这份工程的目标是“让你动手实现”，不是“让你复制后直接运行截图结果”。

所以：

- 工程源码是教学脚手架
- 文档里保存完整参考实现

这个拆分是故意做的，不是漏写。

## 5. 命名对照表

题面里原始命名有些比较短，不利于调试。为了让你更容易读懂代码，内部名字做了规范化，但老师题面里明确点名的函数名仍然保留。

- `out` -> `out`
- `input` -> `input`
- `print` -> `print`
- `solve1` -> `solve1`
- `solve2` -> `solve2`
- `s` -> `job_name`
- `n` -> `frame_count_limit`
- `m` -> `job_length`
- `ss` -> `page_seq`
- `vis` -> `page_fault`
- `ans` -> `frame_snapshot`
- `u` -> `fault_page`
- `Y` -> `Y`

为什么要保留 `Y` 这个结构名：因为它出现在老师原始材料中，虽然当前教学脚手架并不依赖它，但保留声明有助于你和题面对照。

## 6. 30 分钟开工路线

如果你现在就要开始写，别从头乱翻，按这个顺序来。

### 第一步：先只读 `src/main.c`

你先只看 [src/main.c](/home/guiguisocute/Project/jxnu-OS-src/lab11/src/main.c)，重点回答三个问题：

- 哪些变量是输入数据？
- 哪些变量是算法结果？
- 哪些变量只是为了最后打印过程表？

如果这一步没分清，后面会把“算法逻辑”和“显示逻辑”写在一起。

### 第二步：先写 FIFO，不碰 LRU

先把 `solve1` 写出来，只做 FIFO。

这一步你只要保证四件事：

- 能判断命中
- 能判断缺页
- 能在缺页时把新页面装入或替换
- 能在每一步之后把当前物理块状态写进快照数组

此时不用追求输出特别漂亮，先让逻辑正确。

### 第三步：用样例先看缺页率，不急着看全过程

先用样例看看关键结果是否接近：

- 3 块时 FIFO 应是 `75.00`
- 4 块时 FIFO 应是 `50.00`

如果这一步都不对，说明问题出在算法，不在打印。

### 第四步：再写 LRU

在 `solve2` 里补 LRU。

这里的关键不是“换出谁”本身，而是：

> 页面命中时，你有没有及时更新“最近一次访问时间”？

LRU 最常见的错法，就是只在缺页时更新时间，导致算法退化成别的东西。

### 第五步：最后补 print

`print` 是最后做，不是最先做。

原因很简单：如果算法还不稳定，先折腾对齐格式只会干扰你判断 bug。

你最后再统一检查：

- 列标题是否是时间步 `0..m-1`
- 行是否表示物理块
- 缺页时是否打印 `+`
- 缺页页号是否显示在正确列
- 未使用位置是否留空

## 7. 按函数分拆的实现提示

这里不是直接告诉你答案，而是告诉你每个函数应该承担什么责任。

### 7.1 `input`

它应该只做输入，不做任何调度决策。

你要确认：

- 作业名能读入
- 页面长度能读入
- 页面访问串能完整读入

不要在 `input` 里偷偷算缺页率，也不要在这里初始化某种算法状态。

### 7.2 `solve1`

它应该只负责 FIFO 调度。

你在这里至少要完成：

- 初始化本轮运行状态
- 顺序扫描页面访问串
- 判断当前页是否已经在物理块中
- 缺页时设置缺页标记
- 物理块已满时按 FIFO 替换
- 每一步把物理块状态复制到快照数组

如果你写到一半发现 `print` 也得跟着改，先忍住。`solve1` 的任务是“算结果”，不是“负责展示”。

### 7.3 `solve2`

它应该只负责 LRU 调度。

你可以先想一个问题：

> 当物理块里已经有 3 个页面时，我凭什么知道哪个最久没被访问？

这说明你需要额外维护一份“最近访问时刻”信息。最简单的方式是：

- 每个物理块位置都有一个最近访问时间
- 命中时更新
- 缺页且已满时，找最小值对应的物理块替换

### 7.4 `print`

这个函数不应该重新计算调度逻辑。

它应该只读取已经准备好的结果数组，然后按实验要求输出：

- 标题
- 时间下标
- 每一行物理块内容
- 缺页标记
- 缺页页号
- 缺页率

如果你在 `print` 里又重新判断页面是否命中，说明函数职责已经乱了。

## 8. 现在就能用的命令

构建工程：

```bash
make
```

运行程序：

```bash
./build/paging_lab
```

批量回放样例：

```bash
scripts/run_cases.exp --all
```

回放单个样例：

```bash
scripts/run_cases.exp data/case_3_blocks.txt
```

运行脚手架 smoke test：

```bash
make test
```

`make test` 现在会做两层检查：

- 教学脚手架 smoke test：确认 [src/main.c](/home/guiguisocute/Project/jxnu-OS-src/lab11/src/main.c) 仍然是可编译的 TODO 版本
- 参考校验 test：使用 [tests/reference_paging.c](/home/guiguisocute/Project/jxnu-OS-src/lab11/tests/reference_paging.c) 对全部样例和边界数据核对缺页率

查看参考实现：

```bash
sed -n '1,260p' docs/reference_solution.md
```

查看样例参考输出：

```bash
sed -n '1,220p' docs/case_reference_output.md
```

## 9. 做实验时最常见的卡点，以及先查哪里

### 现象 1：FIFO 的缺页率就不对

先查：

- 初始物理块是否被正确当作“空”
- 缺页时是“先替换再记录”，还是“先记录再替换”
- FIFO 队首是否每次替换后都前移

### 现象 2：LRU 和 FIFO 算出来几乎一样

先查：

- 命中时有没有更新最近访问时间
- 替换时找的是“最早进入”，还是“最久未访问”

### 现象 3：缺页率对了，但过程表不对齐

先查：

- 快照是不是每一步都存了
- `frame_snapshot` 的行列含义有没有反
- 空位置是不是统一输出为空格

### 现象 4：打印出的缺页页号错列

先查：

- `fault_page[i]` 是否记录在当前访问步 `i`
- 只在缺页时写值，非缺页时是否保留为空标记

### 建议先跑的边界数据

如果你觉得自己“基本写完了”，不要只跑老师给的两组样例，至少再跑下面几组：

- `case_single_frame.txt`：检查极端小物理块是否仍正确
- `case_all_same_page.txt`：检查命中分支是否稳定
- `case_frames_ge_pages.txt`：检查“物理块足够大”时是否只在首次装入缺页
- `case_alternating_hotset.txt`：检查 LRU 是否真的利用了最近访问信息
- `case_short_sparse.txt`：检查短访问串和过程表空位

## 10. 写完以后怎么自检

在你看参考答案之前，先自己回答下面几项：

- 我能清楚解释 FIFO 为什么只需要关注进入顺序。
- 我能清楚解释 LRU 为什么必须在命中时更新时间。
- 我知道为什么“每一步快照”是这个实验最核心的数据之一。
- 我能不用看代码，只根据思路讲出 `solve1` 和 `solve2` 各自应该怎么工作。
- 我的 4 个关键缺页率是否对得上：
  - `75.00`
  - `60.00`
  - `50.00`
  - `40.00`

如果这些都能回答上来，再去看 [docs/reference_solution.md](/home/guiguisocute/Project/jxnu-OS-src/lab11/docs/reference_solution.md)，你会看得非常快。

## 11. 最后再看参考资料的顺序

推荐顺序如下：

1. 先自己完成 `solve1`
2. 再自己完成 `solve2`
3. 对照 [docs/case_reference_output.md](/home/guiguisocute/Project/jxnu-OS-src/lab11/docs/case_reference_output.md) 看缺页率和过程表
4. 仍然定位不到问题时，再看 [docs/reference_solution.md](/home/guiguisocute/Project/jxnu-OS-src/lab11/docs/reference_solution.md)
5. 最后填写 [docs/report.md](/home/guiguisocute/Project/jxnu-OS-src/lab11/docs/report.md) 并回答 [docs/questions.md](/home/guiguisocute/Project/jxnu-OS-src/lab11/docs/questions.md)

这样使用这份工程，你学到的是“怎么完成一个页面置换实验”，而不是“怎么照抄一份答案”。
