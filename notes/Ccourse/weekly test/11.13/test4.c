#include <stdio.h>
void swap(int* a,int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int* arr,int size){
    for(int i = 0; i < size - 1; i++){
        for(int j = 0; j < size - 1 - i; j++){
            if(arr[j] > arr[j + 1]){
                swap(&arr[j],&arr[j + 1]);
            }
        }
    }
}

void print_arr1(int arr[],int size){
	int i;
	for(i = 0; i < size; i++){
		printf("%d\n",arr[i]);
	}
    printf("\n");
}

void select_sort(int* arr,int size){
    for(int i = size - 1; i > 0; i--){
        int max = arr[0];
        int max_index = 0;
        for(int j = 0; j <= i;j++){
            if(max < arr[j]){
                max = arr[j];
                max_index = j;
            }
        }
        swap(&arr[max_index],&arr[i]);
    }
}
//优化方法：最大值和最小值同时排序，省一半的时间左端点和右端点从数组两端向中间移动
void select_sort2(int* arr,int size){
    int left = 0;
    int right = size - 1;
    
    while(left < right){
        int min = arr[left];
        int min_index = left;
        int max = arr[left];
        int max_index = left;
        
        // 在一次遍历中同时找最大值和最小值
        for(int i = left; i <= right; i++){
            if(arr[i] > max){
                max = arr[i];
                max_index = i;
            }
            if(arr[i] < min){
                min = arr[i];
                min_index = i;
            }
        }
        
        // 先把最小值放到左边
        swap(&arr[min_index], &arr[left]);
        
        // 如果最大值刚好在left位置，由于上面的交换，现在最大值在min_index位置
        if(max_index == left){
            max_index = min_index;
        }
        
        // 把最大值放到右边
        swap(&arr[max_index], &arr[right]);
        
        left++;
        right--;
    }
}
int main(){
    int b[5] = {3,2,6,8,1};
    select_sort2(b,5);
    print_arr1(b,5);
    return 0;
}