/*
    已知线性表采用带头结点的单链表存储结构。
    编写程序：在带头结点的l1中删除在l2中存在的元素，例如：
    链表l1为：10，20，40，30，60，50，80
    链表l2为：40，20，80，100，9，2
    则调用subab(l1,l2);后,链表l1为：10,30,60,50
	请将test_1.c中的subab(linklist  l1, linklist  l2); 补充完整！
	已知链式存储结构已定义好（详见linklist.h）,请勿修改main函数。
*/
#include "slnklist.h"
void subab(linklist l1, linklist l2)
//就是两个指针，L1因为要删所以多加一个删除的pre指针，l1一边移动一边找l2就行，虽然o（nm）确实蠢但考试也没办法了
{
    linklist p1 = l1->next;
    linklist p1pre = l1;
    linklist p2 = l2->next;

    while(p1 != NULL){
        p2 = l2->next;      //每次都从l2的头开始检查
        int found = 0;      //看看是否在l2中找到p1的元素
        while(p2 != NULL){
            if (p1->info == p2->info) {
                found = 1;      //如果找到了就标记一下再跳出循环
                break;
            }
            p2 = p2->next;
        }


        if(found){
            //删除p1节点
            p1pre->next = p1->next; 
            free(p1); 
            p1 = p1pre->next;
        }else{
            //如果没有找到，继续向后走
            p1pre = p1;
            p1 = p1->next;
        }
    }

}

int main()
{
     linklist l1,l2;
     l1= creatLink("data1.txt",7);
     print(l1);                  //输出表l1
     l2=creatLink("data2.txt",6);
     print(l2);                 //输出表l2
     subab(l1,l2);
     print(l1);
     return 0;
}
