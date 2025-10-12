#include <stdio.h>

typedef struct{
    char name[50];
    float price;
    int num;
    float total;
}order;

void calcutotal(order* orders){
    orders->total = orders->price * orders->num;
}

void swap(order* order1,order* order2){
        order temp;
        temp = *order1;
        *order1 = *order2;
        *order2 = temp;
}

void bubble(order orders[],int size){
    int i,j;
    for(i = 0; i < size - 1; i++){
        for(j = 0; j < size - 1 - i; j++){
            if(orders[j].total > orders[j + 1].total){
                swap(&orders[j],&orders[j+1]);
            }
        }
    }
}

int bi_serch(order orders[],int size,float target){
    int right = size - 1;
    int left = 0;
    while(left <= right){
        int mid = (right + left) / 2;
        if(orders[mid].total == target){
            return mid;
        }

        if(target < orders[mid].total){
            right = mid - 1;
        }else{
            left = mid + 1;
        }
    }
    return -1;

}

int main(){
    order orders[10];

    for(int i = 0;i < 10; i++){
        scanf("%s %f %d",
        orders[i].name,
        &orders[i].price,
        &orders[i].num);
        calcutotal(&orders[i]);
    }
    float target;
    scanf("%f",&target);

    bubble(orders,10);
    for(int i = 0; i < 10; i++){
        printf("%s %.2f %d %.2f\n",
        orders[i].name,
        orders[i].price,
        orders[i].num,
        orders[i].total);
    }
    

    int index = bi_serch(orders,10,target);
    if(index == -1){
        printf("Not found");
    }else{
        printf("%s %.2f %d %.2f",
        orders[index].name,
        orders[index].price,
        orders[index].num,
        orders[index].total);
    }

    return 0;
}