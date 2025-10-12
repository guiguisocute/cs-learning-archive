#include<stdio.h>

void swap(int* a,int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selctsort(int a[],int length){
    for(int i = 0; i < length - 1; i++){
        int min_index = i;
        for(int j = i; j < length; j++){
            if(a[j] < a[min_index]){
                min_index = j;
            }
        }
        swap(&a[i],&a[min_index]);
    }
}

int bi_serch(int a[],int length,int x){
    int left = 0;
    int right = length - 1;
    while(left <= right){
        int mid = (left + right) / 2;
        if(a[mid] == x){
            return mid;
        }else if(x < a[mid]){
            right = mid - 1;
        }else if(x > a[mid]){
            left = mid + 1;
        }
    }
    return -1;
}

int main (){

}