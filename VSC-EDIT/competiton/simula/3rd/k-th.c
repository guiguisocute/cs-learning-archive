#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void bubblesort(int num_in[], int n) {
    int temp;
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(num_in[j] > num_in[j + 1]) {
                temp = num_in[j];
                num_in[j] = num_in[j + 1];
                num_in[j + 1] = temp;
            }
        }
    }
}

int main(){
    int n, q;
    scanf("%d %d", &n, &q);

    int *a = (int *)malloc(n * sizeof(int));

    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }

    int l, r, x;
    for(int i = 0; i < q; i++){
        scanf("%d %d %d", &l, &r, &x);
        for(int j = l - 1; j < r; j++){
            a[j] += x;
        }
    }

    bubblesort(a, n);
    int k;
    scanf("%d", &k);

    printf("%d", a[k - 1]);

    free(a);
    return 0;
}