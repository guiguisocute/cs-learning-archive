/*
假设树采用指针方式的孩子表示法表示，试编写一个函数int equal(tree t1, tree t2)，
判断两棵给定的树是否等价（两棵树等价当且仅当其根结点的值相等且其对应的子树均相互等价）。
*/
#include "tree.h"
#define TRUE  1
#define FALSE 0
 
int equal(tree t1,tree t2)      //功能：就是判断两个树是不是一样（无论他是不是子树）
{
  // 没限制递归要求终于可以让gcc帮我管理栈了有点爽啊，这属于递归中的“如法炮制”，子树的比较过程与整棵树的比较过程是完全相同的，所以很容易可以想出来是怎么递过去。
  if(t1 == NULL && t2 == NULL){     //空树相等
    return TRUE;
  }
  if(t1 == NULL || t2 == NULL){     //一空一有肯定不一样
    return FALSE;
  }

  if(t1->data != t2->data){        // 你之前是不是索嗨啊根节点忘记补了
    return FALSE;
  }

  for(int i = 0; i < m; i++){
    if(!equal(t1->child[i],t2->child[i])){    //都非空就递归（调用这个同名同功能函数来判断一下子树们是不是都一样）
      return FALSE;
    }
  }
  return TRUE;
}

int main ()
{
    tree t1,t2;
    printf("please input the preorder sequence of the tree:\n");
    t1=createtree();
    getchar();
    printf("please input the preorder sequence of the tree:\n");
    t2=createtree();
    if ( equal(t1,t2) == TRUE)
    {
  	printf ("两树相等\n");
    }
    else
    {
	printf ("两树不相等\n");
    }
    return 0;
}
