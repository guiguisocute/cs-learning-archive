#include <stdio.h>
#include <stdlib.h>

int main() {
    long long int x, n, sum = 0;
    scanf("%lld %lld", &x, &n);

    for (int i = 0; i < n; i++) {
        int xday = (x + i - 1) % 7; 
        if (xday == 5 || xday == 6) {
            continue;
        }
        sum += 250; 
    }

    printf("%lld", sum);

    system("pause");
    return 0;
}