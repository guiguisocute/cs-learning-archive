#include<stdio.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
typedef struct shangpin{
	char name[50];
	float price;
	int num;
	float P;
}shangpin;

int main(int argc, char** argv) {
	float p;
	shangpin sp[10];
	//输入 
	for(int i=0;i<10;i++){
		scanf("%s %.2f %d",&sp[i].name,&sp[i].price,&sp[i].num);
	}
	scanf("%.2f",&p);
	//计算总价 
	for(int i=0;i<10;i++){
		sp[i].P=sp[i].num*sp[i].price;
	}
	//总价升序排列 
	for(int j =0;j<9;j++){
		for(int i=0;i<10-j;i++){
			if(sp[i].P<sp[i+1].P){
				shangpin huan = sp[i];
				sp[i] = sp[i+1];
				sp[i+1] = huan;
			}
		}
	}
	//输出 
	for(int i=0;i<10;i++){
		printf("%s %.2f %d %.2f\n",&sp[i].name,&sp[i].price,&sp[i].num,&sp[i].P);
	}
	//查找目标总价
	int start=0,middle,end=9;
	int c=1;
	while(start<=end){
		middle=(start+end)/2;
		if(p>sp[middle].P){
			start=middle+1;
		}
		if(p<sp[middle].P){
			end=middle-1;
		}
		else if(p=sp[middle].P){
				printf("%s %.2f %d %.2f\n",&sp[middle].name,&sp[middle].price,&sp[middle].num,&sp[middle].P);
			c=0;
		}
	} 
	if(c=1){
		printf("Not found");
	}
	return 0;
}