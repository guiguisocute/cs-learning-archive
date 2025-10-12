#include<stdio.h>
typedef struct{
    int* rown;
    int lenth;
}row;

int main(){
    int a[3][3] = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    for(int i = 0; i < 3;i++){
        for(int j = 0; j < 3; j++){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }

    row row1 = {{10,20,30,40},4};
    int row2[]= {5,15};
    int row3[] = {1,2,3,4,5};

    int* parr[] = {&row1,row2,row3};
    int row_lengths[] = {4, 2, 5};
    for(int i = 0; i < 3; i++){
        int* p = parr[i];
        for(int j = 0; j < row_lengths[i]; j++){
            printf("%d ",*p);
            p++;
        }
        printf("\n");
    }
}