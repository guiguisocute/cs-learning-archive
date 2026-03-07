import sys

class Queue:
    def __init__(self, max_size=100):
        self.items = []
        self.max_size = max_size

    def is_empty(self):
        return len(self.items) == 0

    def is_full(self):
        return len(self.items) >= self.max_size

    def print_queue(self):
        if self.is_empty():
            print("顺序队列是空的！")
        else:
            print("该队列为：")
            print("    " + "    ".join(map(str, self.items)))

def print_menu():
    print("******************************")
    print("*1、新建                     *")
    print("*2、初始化                   *")
    print("*3、出队                     *")
    print("*4、入队                     *")
    print("*5、打印队列                 *")
    print("*6、清空队列                 *")
    print("*7、队列是否为满             *")
    print("*8、队列是否空               *")
    print("*9、退出                     *")
    print("******************************")

def main():
    q = Queue(max_size=20) # 假设最大容量为20
    print_menu()

    while True:
        try:
            choice = input("请选择要进行的操作:")
            
            if choice == '1':
                count = int(input("请输入需要创建队列的个数:"))
                for _ in range(count):
                    val = input("请输入需要插入的值:")
                    q.items.append(int(val))
                q.print_queue()
                
            elif choice == '2':
                q.items = [] # 初始化清空
                print("顺序队列是空的！")
                
            elif choice == '3':
                if q.is_empty():
                    print("顺序队列是空的！")
                else:
                    val = q.items.pop(0)
                    print(f"出队的元素为: {val}")
                    q.print_queue()
                    
            elif choice == '4':
                if q.is_full():
                    print("队列已满！")
                else:
                    val = input("请输入需要插入的值: ")
                    q.items.append(int(val))
                    q.print_queue()
                    
            elif choice == '5':
                q.print_queue()
                
            elif choice == '6':
                q.items = []
                print("顺序队列是空的！")
                
            elif choice == '7':
                if q.is_full():
                    print("队列是满的！")
                else:
                    print("队列不是满的！")
                    
            elif choice == '8':
                if q.is_empty():
                    print("队列是空的！")
                else:
                    print("队列不是空的！")
                    
            elif choice == '9':
                break
                
            else:
                print("无效的选择，请重新输入！")
                
        except ValueError:
            print("请输入有效的数字！")
        except KeyboardInterrupt:
            print("\n程序已退出。")
            break

if __name__ == "__main__":
    main()