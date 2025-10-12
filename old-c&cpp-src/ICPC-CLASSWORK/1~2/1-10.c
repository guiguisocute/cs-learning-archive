#include <stdio.h>
#include <stdlib.h>

int main(){
    int day = 4;
    int peach = 1;
    for(int i =1; i < day; i++){
        peach = (peach + 1)*2;
    }
    printf("%d \n", peach);
    
    system("pause");
    return 0;
}