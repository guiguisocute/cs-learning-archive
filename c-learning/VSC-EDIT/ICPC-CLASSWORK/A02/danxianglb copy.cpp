#include <iostream>
typedef struct order{
	char name[50];
	int num;
	float price;
	float total;
}order;

void calculate(order* orders){
	orders->total=orders->num*orders->price;
}
void exchange(order* order1,order* order2){
	order temp=*order1;
	*order1=*order2;
	*order2=temp;
}
void bubblesort(order orders[],int size){
	for(int i=0;i<size-1;i++){
		for(int j=0;j<size-1-i;j++){
			if(orders[j].total>orders[j+1].total){
				exchange(&orders[j],&orders[j+1]);
			}
		}
	}
}
int search(order orders[],int size,float target){
	int end =size;
	int start =0;
	while(start<=end){
		int mid=(start+end)/2;
		if(orders[mid].total == target){
			return mid;
		}
		if(orders[mid].total>target){
			end=mid-1;
		}
		else{
			start=mid+1;
		}
	}
	return -1;
}
int main(int argc, char** argv) {
	order orders[10];
	for(int i=0;i<10;i++){
	scanf("%d %f %s ",
	&orders[i].num,
	&orders[i].price,
	orders[i].name);
	calculate(&orders[i]);}
	
	float target;
	scanf("%f",&target);
	
	bubblesort(orders,10);
	for(int i=0;i<10;i++){
	scanf("%d %f %s ",
	&orders[i].num,
	&orders[i].price,
	orders[i].name);
	calculate(&orders[i]);}
	
	
	int find =search(orders,10,target);
	if(find == -1){
		printf("not find");
	}
	else{
		printf("%d %.2f %s %.2f",
		orders[find].num,
		orders[find].price,
		orders[find].name,
		orders[find].total);
	}
	return 0;
}