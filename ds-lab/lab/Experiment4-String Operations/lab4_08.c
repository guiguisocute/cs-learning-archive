/*
8．编写快速模式匹配 KMP（Knuth-Morris-Pratt） 算法，请将相关函数补充完整。（实验代码详见 lab4_08.c）
*/

// KMP特色：当匹配失败时，主串指针不回溯，因为之前已经匹配成功的字符可以给我们提供一些有用的信息，通过next数组决定模式串指针的移动位置。最终复杂度O(m+n)
#include <stdlib.h>
#include <stdio.h>
#include<string.h>           //这题头文件包含内容都没写是啥意思

#define maxsize 100
typedef struct{
      char str[maxsize];
      int length ;
} seqstring;

/*KMP算法思路有那么一点点绕，但是并不复杂，我试着理一下，分步去想：

1.首先第一步，和我上面实验那个错误的“同步推进”函数一样，两个匹配了就一起往前推

2.然后如果真的一次就成了当然返回就行，但是现实不会这么好运，那么怎么办捏

3.首先我们肯定就会想，草啊我真的不是很想回溯主链指针啊，i为什么能走到这里，不就是因为前面匹配的比较多啊

4.这时候我们就想了，诶，是否有一个比较聪明的办法，使得主链指针就能固定下来，借助已经匹配成功的字符给我们提供一些有用的信息，让主链指针不要回去了

5.这就要搬出next数组存储模式串的所有 子串的最长公共前后缀的长度先，先别管是怎么算的，我们先知道结果，然后看一下这个公共前后缀长度能在这个算法里起到什么作用

6. 回到我们匹配失败的情形，那么我们在第一次匹配失败的时候，i前面那个一串，肯定是完美匹配成功的子串的子串，而且，j前面位置也一样，如果我们有next储存算出每一个子串的子串的 ·最长公共前后缀的长度t·，我们会发现i指针的前t个，和子串最开始的t个，是他妈的完全相同的！！！那么，就可以直接把字符串“滑”到一个对应的位置，这样我们惊奇的会发现，在主串指针没动的情况下，居然又能快乐进行重新验证是否符合能共同向前了！

7. 现在我们只要重复这个过程直到子串指针j指到空字符，就算匹配成功啦*/

/*求模式p的next[]值，请将函数补充完整*/
void getnext(seqstring p,int next[])            
{
      //可以规定一下，next索引代表的就是子串的长度，整个数组大小也就是p的长度+1，这样好理解一些
      next[0] = -1;
      int k = -1;       //可回溯的指针
      int j = 0;        //不可回溯的指针

      while(j < p.length){
            if(k == -1 || p.str[j] == p.str[k]){
                  k++;
                  j++;
                  if(j < p.length){       //防止next出现些奇奇怪怪的数
                        next[j] = k; // 如果成功了就一起走，最大公共前后缀的长度显然递增
                  }
            }else{                  //如果没成功怎么办呢？没成功那肯定只能找更短的退而求其次了，但是我们要一个一个暴力吗，不用！实际上也只用对比一次就行了，因为我们的j指针可是一路和k碰撞才来到这的，前面的数相等的我们当然也要利用好，正好上一个记录了对应的最大公共前后缀，我们只要对应相加就可以了
                  k = next[k];      
            }
      }
}
//可以把next再处理一下，和next里面的next索引进行比较，不一样就照抄，一样的话就照抄前面




/*快速模式匹配算法，请将函数补充完整*/
int kmp(seqstring t,seqstring p,int next[])     //应该也就是返回第一次的索引值
{
      int i = 0;        //主串不回溯指针
      int j = 0;        //模式串随时回溯的指针

      while (i < t.length && j < p.length)
      {
            if (j == -1 || t.str [i] == p.str[j])
            {
                  i++;
                  j++;
            }
            else
            {
                  j = next[j];
            }
      }
      if (p.str[j] == '\0'){
            return i - p.length;
      }else{
            return -1;
      }
      
}


int  main()
 {   seqstring t, p;
     int next[maxsize],pos;

     printf("请输入主串：\n");
     fgets(t.str,sizeof(t.str),stdin);
     t.str[strcspn(t.str,"\n")] = '\0';
     t.length=strlen(t.str);

     printf("请输入模式串：\n");
     fgets(p.str, sizeof(p.str), stdin);
     p.str[strcspn(p.str, "\n")] = '\0';
     p.length=strlen(p.str);
     
     getnext(p,next);
     pos=kmp(t,p,next);
     printf("\n");
     printf("%d",pos);
     return 0;
}

