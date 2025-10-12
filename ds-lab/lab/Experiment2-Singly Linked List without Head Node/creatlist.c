#include "slnklist.h"
 
int main()
{
    datatype x;
    linklist head;
    head=creatbyqueue();		/*尾插入法建立单链表*/
    print(head);
    delList(head);				/*释放单链表空间*/
    return 0;
}
