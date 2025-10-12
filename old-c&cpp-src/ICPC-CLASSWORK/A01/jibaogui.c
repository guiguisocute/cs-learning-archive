#include <stdio.h>
#include <stdlib.h>


int *guizi[100000] = {NULL};
int gezi[100000] = {0};

void ensure(int i,int j){
    if(gezi[i] < j) {
        int newgezi = j;
        guizi[i] = (int*)realloc(guizi[i],newgezi * sizeof(int));
        for (int k = gezi[i]; k < newgezi; k++){
            guizi[i][k] = 0;
        }
        gezi[i] = newgezi;
    }
}

int main(){
    int n,q;
    scanf("%d %d",&n,&q);
    

    for(int t = 0; t < q; t++){
        int op;
        scanf("%d",&op);

        if(op == 1){
            int i, j, k;
            scanf("%d %d %d",&i,&j,&k);
            i--; j--;

            ensure(i,j + 1);
            guizi[i][j] = k;
        }else if(op == 2){
            int i, j;
            scanf("%d %d",&i,&j);
            i--; j--;

            printf("%d\n",guizi[i][j]);
        }
    }

    for(int i = 0; i < n; i++){
        free(guizi[i]);
    }

    return 0;
}
