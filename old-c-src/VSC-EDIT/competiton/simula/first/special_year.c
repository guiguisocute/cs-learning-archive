#include <stdio.h>
#include <stdlib.h>

int main() {
    char year[5]; 
    int count = 0;

    for (int i = 0; i < 5; i++) {
        scanf("%s", year); 
        if (year[0] == year[2] && (year[3] - '0') == (year[1] - '0' + 1)) {
            count++;
        }
    }

    printf("%d", count);

    system("pause");
    return 0;
}