import os
import re

# 预定义的精准翻译词典（包含计算机科学专业术语）
TRANSLATIONS = {
    "线性表的顺序实现": "Linear List Sequential Implementation",
    "不带头结点的单链表": "Singly Linked List without Head Node",
    "带头结点的单链表": "Singly Linked List with Head Node",
    "栈与字符串": "Stack & String",  # 推测实际应为字符串操作
    "递归": "Recursion",
    "树": "Tree Structures",
    "二叉树": "Binary Tree Implementation",
    "图": "Graph Algorithms",
    "检索": "Search Algorithms",
    "排序": "Sorting Techniques"
}

def rename_folders():
    # 创建正则表达式模式匹配中文文件夹名
    pattern = re.compile(r'^实验(\d+)-(.*)$')
    
    # 获取并处理当前目录下的所有文件夹
    for folder in os.listdir():
        if os.path.isdir(folder):
            match = pattern.match(folder)
            if match:
                # 提取实验编号和中文描述
                exp_num = match.group(1)
                cn_description = match.group(2)
                
                # 生成新文件名
                if cn_description in TRANSLATIONS:
                    new_name = f"Experiment{exp_num}-{TRANSLATIONS[cn_description]}"
                    try:
                        os.rename(folder, new_name)
                        print(f"成功重命名：{folder} -> {new_name}")
                    except Exception as e:
                        print(f"重命名失败：{folder} | 错误信息：{str(e)}")
                else:
                    print(f"未找到翻译：{cn_description}")

if __name__ == "__main__":
    print("== 开始批量重命名操作 ==")
    rename_folders()
    print("== 操作完成 ==")