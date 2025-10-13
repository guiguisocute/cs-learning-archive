#include <stdio.h>
#include <stdlib.h>

int main(){
    int total;
    scanf("%d",&total);
  
  for (int a = total / 3; a <= total; a++){
    for(int b = 0; b<= total; b++){
        int c = total - a - b;
        if(c >= 0 && (6 * b - 2 * a - 2 * c == 7 * c - b - a) && (7 * c - b - a == 4 * a - 4 * b - 4 * c)){
            printf("%d %d %d \n",a,b,c);

            system("pause");
            return 0;
        }
    }
  }
  printf("invaild date \n");

  system("pause");
  return 0;
}