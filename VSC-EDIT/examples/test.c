#include<stdio.h>
#include<stdlib.h>

void bubblesort(int num_in[], int n) {
    int temp;
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(num_in[j] > num_in[j+1]) {
                temp = num_in[j];
                num_in[j] = num_in[j+1];
                num_in[j+1] = temp;
            }
        }
    }
}

int main() {
    int num_in[3];
    char order[4];  // 输入的顺序字母
    // 读取三个整数
    for(int i = 0; i < 3; i++) {
        scanf("%d", &num_in[i]);
    }
    // 排序数字
    bubblesort(num_in, 3);
    
    // 读取顺序字母
    scanf("%s", order);

    // 根据输入的顺序打印出对应的数字
    for(int i = 0; i < 3; i++) {
        if(order[i] == 'A') {
            printf("%d ", num_in[0]);
        } else if(order[i] == 'B') {
            printf("%d ", num_in[1]);
        } else if(order[i] == 'C') {
            printf("%d ", num_in[2]);
        }
    }
    printf("\n");

    return 0;
}
