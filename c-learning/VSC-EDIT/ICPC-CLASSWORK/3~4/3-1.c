#include<stdio.h>
#include<stdlib.h>

int main() {
    int L;
    scanf("%d", &L); 
    
    for (int i = 1; i <= L; i++) {
        if (i == 1) {
            printf("Today, I ate %d apple.\n", i);
        }else{
            printf("Today, I ate %d apples.\n", i);
        }
    }

    system("pause");
    return 0;
}