/*
假设树采用指针方式的孩子表示法存储结构，试编写一个函数tree Ct(char s[])，
根据输入的树的括号表示字符串s，生成树的存储结构。例如，若要建立教材图6.4所示的树，
应输入`A(B(E,F),C,D(G(I,J,K),H)`。（说明，tree.h中定义的常量m表示树的最大度，请根据建树的需要自行修改m的值）
*/

#include "tree.h"
/*请将本函数补充完整，并进行测试*/
// 函数键入和返回的是字符串，所以得用到第四章的知识使用一个字符串指针进行遍历
int index = 0;
tree Ct(char s[MAXLEN])    //函数究竟想干什么：用括号表示法建立树 
{
    //其实本质也是前序遍历，顺序同样是根-左-右，只不过省去了每一个非满度节点都要输空树的麻烦
    //用题目实例来表示的话，如果用头文件的方法生成，那么写出来是`ABE###F####C###DGI###J###K###H####`实值顺序是一模一样的，但是该怎么把,与()对应上，这才是这道题要重点解决的问题。

    if(index >= (int)strlen(s)){
        return NULL;
    }
    //最基本的回溯空逻辑，不解释了

    if(s[index] != '(' || ')' || ','){
        tree root = (tree)malloc(sizeof(node));
        root->data = s[index];   
        //非符号情况下，直接建立一个新结点，然后如果一个是非符号，后面肯定跟着逗号或者括号，毕竟孩子表示法前序建表的话后面的非符号数要么是亲子关系要么就是兄弟关系
        for(int i = 0; i < m ; i++){
            root->child[i] = NULL;
            //反正不管怎么说建立新结点就算不知道后面怎么处理了也必须得先做一个初始化，野指针肯定还是危险的
        }
        index++;        //现在就依靠后面的符号来判断操作是怎么样

        if(index < (int)strlen(s) && s[index] == '('){
            index++;
            int childindex = 0;
            //直到遇见右括号前，在子节点上跳过逗号建立新子树，递归处理
            while(index < (int)strlen(s) && s[index] != ')'){
                root->child[childindex++] = Ct(s);      //这里的s已经被全局变量index给掌握了，不用担心会复用栈，放心填进去就行了
                if(s[index] == ','){
                    index++;    //跳过逗号
                }
            }
            index++;    //跳过右括号
        }
        return root;
    }
}

int main ()
{
    char s[MAXLEN];
    tree root = NULL;
    printf ("请用树的括号表示法输入一棵树:\n");
    scanf ("%s",s);
    root = Ct(s);
    preorder(root);  /*前序遍历树*/
    return 0;
}
