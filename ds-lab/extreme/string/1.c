/*以顺序存储结构表示串，设计算法。求串S中出现的第一个最长重复子串及其位置并分析算法的时间复杂度。
例如：若S="abceebccadddddaaadd!”，则最长重复子串为
"ddddd”。位置是9。
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} linknode;

typedef linknode *linklist;

int main(){
    //两指针双暴力遍历（i前j后），遇到相等的就步进j，长度计数器也++，直到遇到不同的值，就对比max与当前count，如果能替换max就记录pos（i的位置）
    int max = 0, count;
    char s[100];
    printf("输入主串\n");
    scanf("%s", s);
    printf("\n");

    int i = 0,j = 0, pos;
    int m = strlen(s);
    for(;i < m; i++){
        j = i + 1;
        count = 1;
        while(s[j] != '\0' && s[i] == s[j]){
            count++;
            j++;
        }
        if(count > max){
            max = count;
            pos = i;
        }
    }

    printf("%d",pos);

    return 0;
}

