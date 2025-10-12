/*
编写算法函数void levelorder(tree t)实现树的层次遍历。
*/
 
#include "tree.h"

void levelorder(tree t)    /* t为指向树根结点的指针*/
/*其实感觉有点按图索骥的感觉毕竟名称其实都定死了……就像让你写一个冒泡那不就是左右比较一下大的交换然后如法炮制，而树的层次遍历就是按层从上到下，从左到右访问树的所有节点，基本上也只能用队列先进先出后进后出了吧*/
{
  tree queue[MAXLEN];   //队列的话肯定还是数组爽啊
  int front = 0, rear = 0;
  int i;

  if(!t){     //空树返回不说了
    return;
  }

  queue[rear] = t;
  rear++;

  while(front < rear){
    tree temp = queue[front];   //只要队列不空就出队一个节点
    front++;
    printf("%c",temp->data);  //访问打印节点的数据

    //然后就是实现怎么把该节点的孩子们全入队
    for(i = 0; i < m; i++){
      if(temp->child[i]){     //孩子有值就入队
        queue[rear] = temp->child[i];
        rear++;   
      }
    }
  }
}

void levelorder2(tree t){
  //现在改成用链式队列实现层次遍历
  if(!t){
    return;
  }
  //无头结点，有尾指针的链表作为链式队列
  linklist queue;
  linklist rear;
  
  // 创建并入队第一个节点
  queue = (linklist)malloc(sizeof(linknode));
  queue->info = t;
  queue->next = NULL;
  rear = queue;

  while(queue){       //只要队列非空
    tree temp = queue->info;   //保存队头信息
    printf("%c", temp->data);

    // 将当前节点的所有非空子节点入队
    for(int i = 0; i < m; i++){
      if(temp->child[i]){
        linklist newnode = (linklist)malloc(sizeof(linknode));
        newnode->info = temp->child[i];
        newnode->next = NULL;
        rear->next = newnode;
        rear = newnode;
      }
    }

    // 出队
    linklist p = queue;
    queue = queue->next;
    free(p);
  }
}

int main()
{
  tree t;
  printf("please input the preorder sequence of the tree:\n");
  t = createtree(); // 看了一下头文件，这里要使用#代表空树
  printf("\nthe levelorder is:");
  levelorder2(t);
  return 0;
}
