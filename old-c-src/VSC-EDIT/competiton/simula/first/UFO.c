#include<stdio.h>
#include<stdlib.h>

int main(){
     char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
     char metror[7]; char group[7];
     long long int num_m = 1 ,num_g = 1;

     scanf("%s",metror);
     scanf("%s",group);

    for(int i = 0; i < 6 && metror[i] != '\0'; i++) {
        for(int j = 0; j < 26; j++) {
            if(alphabet[j] == metror[i]) {
                num_m *= (j + 1); 
                break;
            }
        }
    }

    for(int i = 0; i < 6 && group[i] != '\0'; i++) {
        for(int j = 0; j < 26; j++) {
            if(alphabet[j] == group[i]) {
                num_g *= (j + 1); 
                break; 
            }
        }
    }

     if(num_g % 47 == num_m % 47){
        printf("GO");
     }else{
        printf("STAY");
     }

     system("pause");
     return 0;

     
}