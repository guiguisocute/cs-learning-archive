# data 目录说明

这里的输入文件不是随便堆出来的，它们分别对应你实现段页式存储管理时会遇到的不同场景。

## 主流程

- `case_sample.txt`
  题目主样例，覆盖初始化、分配和查看状态。
- `case_multi_job.txt`
  连续装入多个作业，再回收其中一个。
- `case_multi_recycle_chain.txt`
  连续装入、连续回收，适合检查链表删除和空闲块恢复是否稳定。

## 分配边界

- `case_small_fit.txt`
  刚好装满主存。
- `case_no_space.txt`
  第二次装入时主存不足。
- `case_duplicate_job.txt`
  重名作业重复装入。
- `case_page_capacity_mismatch.txt`
  页数容量不足以容纳作业大小。

## 地址转换边界

- `case_address_ok.txt`
  合法地址转换。
- `case_address_oob.txt`
  页号越界。
- `case_address_segment_oob.txt`
  段号越界。
- `case_address_offset_oob.txt`
  页内偏移越界。

## 回收边界

- `case_recycle_missing.txt`
  回收不存在的作业。

建议做法：

1. 每实现一个功能，只跑覆盖该功能的最小样例。
2. 功能通过后，再跑同类边界样例。
3. 最后用 `./scripts/run_case.exp --all` 做一次批量回放。
