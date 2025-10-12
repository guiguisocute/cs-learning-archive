#include <stdio.h>
#include <stdlib.h>

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

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int n_s[n];
    for(int i = 0; i < n; i++) {
        scanf("%d", &n_s[i]);
    }
    bubblesort(n_s,n);

    int unique[n];
    int unique_count = 0;

    for(int i = 0; i < n; i++) {
        if (i == 0 || n_s[i] != n_s[i - 1]) {
            unique[unique_count++] = n_s[i];
        }
    }
    
    if(k > unique_count) {
        printf("NO RESULT\n");
    } else {
        printf("%d\n", unique[k - 1]);
    }

    system("pause");
    return 0;

}
