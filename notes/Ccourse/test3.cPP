#include<bits/stdc++.h>

using namespace std;

typedef struct book{
	char a[10];
	int num;
	float count;
	float sum;	
}book;

typedef struct T{
	book a;
}T; 

void exchange(T* a,T* b){
	T c=*a;
	*a=*b;
	*b=c;
}


void SUM(T b[]){
	for(int i=0;i<10;i++){
		b[i].a.sum=b[i].a.count*b[i].a.num;
		}
}
void X(T b[]){
		for(int i=0;i<10;i++){
		int min=1000000;
		int p_min=0;
		for(int j=i;j<10;j++){
			if(min>b[j].a.sum){
				min=b[j].a.sum;
				p_min=j;
			}
		}
		exchange(&b[p_min],&b[i]);
	}
}
void Printf_book(T b[]){
		for(int i=0;i<10;i++){
	printf("%s %.2f %d %.2f\n",b[i].a.a,b[i].a.count,b[i].a.num,b[i].a.sum);
	}
}

int main()
{
	
T b[10];
for(int i=0;i<10;i++){
	scanf("%s %f %d",b[i].a.a,&b[i].a.count,&b[i].a.num);
}

float price1;
float price2;
scanf("%f",&price2);

SUM(b);
X(b);
Printf_book(b);

	int i=0;
	int j=9;
while(6){	
	price1=b[(i+j)/2].a.count;
	if(i==j&&price1!=price2){
		printf("Not found\n");
		break;
		}	
	if(price1 == price2){
		printf("%s %.2f %d %.2f\n",b[(i+j)/2].a.a,b[(i+j)/2].a.count,b[(i+j)/2].a.num,b[(i+j)/2].a.sum);
		break;
		}
	else{
		if(price1>price2){
			j=(i+j)/2-1;
			}
		else{
			i=(i+j)/2+1;
			}
		}	
	}
	

return 0;
}