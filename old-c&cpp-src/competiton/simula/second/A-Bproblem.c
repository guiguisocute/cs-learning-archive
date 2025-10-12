#include <stdio.h>
#include <stdlib.h>
#define lli long long int

void bubblesort(lli num_in[], lli n) {
    lli temp;
    for(lli i = 0; i < n - 1; i++) {
        for(lli j = 0; j < n - i - 1; j++) {
            if(num_in[j] > num_in[j + 1]) {
                temp = num_in[j];
                num_in[j] = num_in[j + 1];
                num_in[j + 1] = temp;
            }
        }
    }
}

int main() {
    lli n, c, count = 0;
    scanf("%lld %lld", &n, &c);
    lli n_s[n];
    
    for(lli i = 0; i < n; i++) {
        scanf("%lld", &n_s[i]);
    }

    bubblesort(n_s, n);

    for(lli i = 0; i < n; i++) {
        for(lli j = 0; j < n; j++) {
            if(n_s[i] - n_s[j] == c && i != j) {
                count++;
            }
        }
    }

    printf("%lld", count);

    system("pause");
    return 0;
}