#include <stdio.h>
#include <stdlib.h>
#include <filehc.h>

void pc(int(*pa)(int,int),int a,int b){
	int result;
	result = pa(a,b);
	printf("%d\n",result);
	
}

int add(int a,int b){
	int c;
	c = a + b;
	return c;
}

int minus(int a,int b){
	int c;
	c = a - b;
	return c;
}

int main(){
	int(*pf)(int,int);
	pf = add;
	printf("%d\n",pf(2,3));
	pf = minus;
	printf("%d\n",pf(2,3));
	
	pc(add,5,6);
	pc(minus,7,8);
	
	return 0;
	
	
}


