#include<stdio.h>
#include<string.h>
#define ll long long

//step1：相邻1之间的距离是否全部相同？step2：相邻1的距离是否超过了n？
//特例：只有1个1，

char a[1000010],w[1000010]; 

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        ll n,m;
        scanf("%lld %lld",&n,&m);
        ll count = 0;
        for(ll i = 1; i <= m; i++){
            char c;
            scanf("%c",&c);
            a[i] = c - '0';
            if(a[i] == 1){
                w[++count] = i;     //主要是先自增再赋值
            }
        }
        if(count == 0){
            if(m > n){
                printf("No\n");
            }else{
                printf("Yes\n");
            }
            continue;
        }
        if(count == 1){
            if(w[1] - 1 > n || (m - w[1] > n)){
                printf("No\n");
            }else{
                printf("Yes\n");
            }
            continue;
        }
        ll len = w[2] - w[1] - 1;
        if (len > n){
            printf("No\n");
        }
        if(w[1] - 1 > len){
            printf("No\n");
        }
        int flag = 1;
        for(ll i = 3; i <= count; i++){
            if(w[i] - w[i - 1] - 1 != len){
                printf("No\n");
                flag = 0;
                break;
            }
        }
        if (!flag){
            continue;
        }
        if(m - w[count] > len){
            printf("No\n");
            continue;
        }
        if(flag){
            printf("Yes\n");
        }
    }

    return 0;
// 这段代码是在解决一个关于01序列的问题。让我来解释主要逻辑:

// 1. 首先扫描输入的01序列,记录所有1的位置到数组w中,count记录1的个数
// 2. 特殊情况处理:
//    - 如果没有1(count=0): 只需判断m和n的大小关系
//    - 如果只有一个1(count=1): 判断第一个1前面的长度和后面的长度是否都不超过n
// 3. 对于有多个1的情况:
//    - 计算第一个1和第二个1之间的间隔长度len
//    - 检查第一个1前面的长度是否超过len
//    - 检查所有相邻1之间的间隔是否都等于len
//    - 检查最后一个1到m的距离是否超过len
// 4. 如果所有检查都通过,输出"Yes",否则输出"No"

// 这个问题似乎是在判断一个01序列是否满足某种规律,其中n是一个限制条件
}