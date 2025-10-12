#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


int is_prime[10001];

void sieve() {
    memset(is_prime, 1, sizeof(is_prime));
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i * i <= 10001; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= 10001; j += i) {
                is_prime[j] = 0;
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    sieve();

    for(int current = 4; current <= n; current += 2) {
        for(int num1 = 2; num1 <= current / 2; num1++) {
            int num2 = current - num1;
            if(is_prime[num1] && is_prime[num2]) {
                printf("%d=%d+%d\n", current, num1, num2);
                break;
            }
        }
    }

    return 0;
}