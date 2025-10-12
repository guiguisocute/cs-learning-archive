#include<stdio.h>
#include<stdlib.h>
int i;

typedef struct{
    int a[10];
    int l;
}array;

void printarray(array a){
    for(i = 0; i < a.l; i++){
        printf("%d ",a.a[i]);
    }
    printf("\n");
}
void insert(array* a, int pos, int v){
    for(i = a->l - 1;  i >= pos; i--){
        a->a[i+1] = a->a[i];
    }
    a->a[pos] = v;
    a->l++;
}
void del(array* a, int pos){
    for(i = pos; i < a->l - 1; i++){
        a->a[i] = a->a[i+1];
    }
    a->l--;
}

int main(){
    int* b = (int*)malloc(5 * sizeof(int));
    for(i = 0; i < 5; i++){
        b[i] = i;
    }
    b = (int*)realloc(b,10 * sizeof(int));
    b[8] = 100;
    for(i = 0; i < 10; i++){
        printf("%d ",b[i]);
    }
    printf("\n");

    array a = {{0,1,2,3,4},5};
    insert(&a,2,10);
    del(&a,3);
    printarray(a);

    free(b);

    return 0;
    
}