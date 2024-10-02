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
    int n, c, count = 0;
    scanf("%d %d", &n, &c);
    int n_s[n];
    
    for(int i = 0; i < n; i++) {
        scanf("%d", &n_s[i]);
    }

    bubblesort(n_s, n);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(n_s[i] - n_s[j] == c && i != j) {
                count++;
            }
        }
    }

    printf("%d", count);

    system("pause");
    return 0;
}