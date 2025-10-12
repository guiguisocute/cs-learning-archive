#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int next_child[n+1];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &next_child[i]);
    }

    int head;
    scanf("%d", &head);
    int current = head;
    while (current != 0) {
        printf("%d ", current);
        current = next_child[current];
    }
    return 0;
}

