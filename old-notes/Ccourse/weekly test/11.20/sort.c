#include<stdio.h>

void swap(int*a, int*b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int ascend(int a,int b){
    return (a > b ? 1:0);
}

int discend(int a,int b){
    return (a < b ? 1:0);
}

void print_arr(int* a,int size){
    int i;
    for(i = 0; i < size; i++){
        printf("%d\n",a[i]);
    }
    printf("======================================\n");
}


void bubblesort_ex(int* a, int size, int (*pf)(int,int)){
    int i,j;
    for(i = 0; i < size - 1; i++){
        for(j = 0; j < size - 1 - i; j++){
            if(pf(a[j], a[j + 1])){
                swap(&a[j], &a[j + 1]);
            }
        }
    }
    print_arr(a,size);

}

void slectsort_ex(int* a,int size,int(*pf)(int,int)){       
    int i,j;
    int target,target_index;
    for(i = 0 ; i < size - 1; i++){
        target = a[i];
        target_index = i;
        for(j = i + 1; j < size; j++){
            if(pf(target,a[j])){
                target = a[j];
                target_index = j;
            }
        }
        if(target_index != i){
            swap(&a[i],&a[target_index]);
        }
        
    }
    print_arr(a,size);
}


int main(){
    int a[6] = {4,22,1,897,2,771};
    bubblesort_ex(a,6,ascend);
    bubblesort_ex(a,6,discend);
    slectsort_ex(a,6,ascend);
    slectsort_ex(a,6,discend);

    return 0;
}