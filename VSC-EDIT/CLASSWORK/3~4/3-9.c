#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
    if (a > c) {
        int temp = a;
        a = c;
        c = temp;
    }
    if (b > c) {
        int temp = b;
        b = c;
        c = temp;
    }
    

    if (a + b <= c) {
        printf("Not triangle\n");
    } else {
        if (a*a + b*b == c*c) {
            printf("Right triangle\n");
        }
        if (a*a + b*b < c*c) {
            printf("Obtuse triangle\n");
        }
        if (a*a + b*b > c*c) {
            printf("Acute triangle\n");
        }
        if (a == b && b == c) {
            printf("Equilateral triangle\n");
        }
        if (a == b || b == c || a == c) {
            printf("Isosceles triangle\n");
        }
    }
    
    system("pause");
    return 0;
}