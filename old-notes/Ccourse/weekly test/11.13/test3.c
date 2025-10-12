#include <stdio.h>

void print_arr1(int arr[],int size){
	int i;
	for(i = 0; i < size; i++){
		arr[i]++;
		printf("%d\n",arr[i]);
	}
    printf("\n");
}

void print_arr2(int* arr,int size){
	int i;
	for(i = 0; i < size; i++){
		printf("%d\n",*(arr + i));
	}
    printf("\n");
}

void print_arr3(int* arr, int size){
	int i;
	int* pa = arr;
	for(i = 0; i < size; i++){
		printf("%d\n",*pa);
		pa++;
	}
    printf("\n");
}

void print_arr4(int* arr, int size){
	int* ptr;
    for (ptr = arr; ptr < arr + size; ptr++) {
        printf("%d\n", *ptr);
        (*ptr)++;
    }
    printf("\n");
}

int main(){
	int a[5] = {1,2,3,4,5};
	print_arr1(a,5);
	print_arr2(a,5);
	print_arr3(a,5);
	print_arr4(a,5);
	
	return 0;
}