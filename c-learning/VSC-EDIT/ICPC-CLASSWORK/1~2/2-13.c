#include<stdio.h>
#include<stdlib.h>

int main(){
    char alphabet_C[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char input;
    scanf("%c",&input);
     for (int i=0; i < 26; i++){
        if (alphabet[i] == input){
            printf("%c \n", alphabet_C[i]);
            break;      
        }    
     }
     system("pause");
     return 0;
}