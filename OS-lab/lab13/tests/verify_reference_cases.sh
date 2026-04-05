#!/bin/sh
set -eu

cc -std=c11 -Wall -Wextra -Werror -Iinclude tests/reference_device_manager.c -o /tmp/reference_device_manager

/tmp/reference_device_manager < data/sample_case_01.in > /tmp/case01.out
/tmp/reference_device_manager < data/sample_case_02_no_controller.in > /tmp/case02.out
/tmp/reference_device_manager < data/sample_case_03_no_good_device.in > /tmp/case03.out
/tmp/reference_device_manager < data/sample_case_04_duplicate_job.in > /tmp/case04.out
/tmp/reference_device_manager < data/sample_case_05_release_and_reuse.in > /tmp/case05.out

grep -q "job2占用设备的设备相对号和设备绝对号及SDT号" /tmp/case01.out
grep -q "回收成功！" /tmp/case01.out

grep -q "系统剩余可用控制器数量：0" /tmp/case02.out
grep -q "分配失败！可用设备或控制器数量不足！" /tmp/case02.out

grep -q "scanner    1            0" /tmp/case03.out
grep -q "设备可用数量为：0" /tmp/case03.out
grep -q "分配失败！可用设备或控制器数量不足！" /tmp/case03.out

grep -q "分配失败！作业名已存在！" /tmp/case04.out
grep -q "job1占用设备的设备相对号和设备绝对号及SDT号" /tmp/case04.out

grep -q "回收成功！" /tmp/case05.out
grep -q "job2占用设备的设备相对号和设备绝对号及SDT号" /tmp/case05.out
grep -q "printer    3            1" /tmp/case05.out

echo "reference cases verified"
