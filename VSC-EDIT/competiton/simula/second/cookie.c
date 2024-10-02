#include <stdio.h>
#include <stdlib.h>

int main() {
    int group;
    scanf("%d", &group);

    for (int i = 0; i < group; i++) {
        long long n, k; 
        scanf("%lld %lld", &n, &k);

        long long required = (k * (k + 1)) / 2;

        if (n >= required) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    system("pause");
    return 0;
}