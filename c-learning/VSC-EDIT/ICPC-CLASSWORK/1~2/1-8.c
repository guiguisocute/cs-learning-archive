//想让这个题目更体现编程的思想

#include <stdio.h>
#include <stdlib.h>

void deposit (int *balance, int amount) {
    *balance += amount;
    printf("%d \n",*balance);
}

void withdraw(int *balance, int amount){
    *balance -= amount;
    printf("%d \n",*balance);
}

void checkbalance(int balance){
    printf("%d \n",balance);
}


int main(){
    int balance = 100;
    deposit(&balance, 10);
    withdraw(&balance, 20);
    withdraw(&balance, balance);

    system("pause");
    return 0;
}