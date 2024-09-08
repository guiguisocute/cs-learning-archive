#include<stdio.h>
#include<stdlib.h>

int main(){
    char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char input_a = 'M'; int input_n =18;
    for (int i = 0; i < 26; i++){
        if (alphabet[i] == input_a){
            printf("%d \n", i + 1);
            break;
            
        }
    }
    printf("%c \n", alphabet[input_n - 1]);

    system("pause");
    return 0;
}