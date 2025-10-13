#include<stdio.h>
#include<stdlib.h>

void bubblesort(int num_in[],int n){    
    int temp;
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(num_in[j] > num_in[j + 1]){
                temp = num_in[j];
                num_in[j] = num_in[j + 1];   
                num_in[j + 1] = temp;
            }
        }
    }
}

int main(){
    int num_in[3]; char in[4];
    for(int i = 0; i < 3; i++){
        scanf("%d",&num_in[i]);
    }
    bubblesort(num_in,3);
    scanf("%s", in);



    for(int i = 0; i < 3; i++){
        if(in[i] == 'A'){
            printf("%d ",num_in[0]);
        }else if(in[i] == 'B'){
            printf("%d ",num_in[1]);
        }else if(in[i] == 'C'){
            printf("%d ",num_in[2]);
        }

        
    }
    printf("\n");
    system("pause");
    return 0;







}