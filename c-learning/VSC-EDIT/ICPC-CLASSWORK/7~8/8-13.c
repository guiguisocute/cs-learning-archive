#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){
    int n;
    scanf("%d",&n);

    int light[20000001] = {0};

    double a;
    int t;

    for(int i = 0; i < n; i++) {
        scanf("%lf %d", &a, &t);

        for(int j = 1; j <= t; j++) {
            int light_Num = (int)floor(a * j);  
            light[light_Num] ^= 1;  
        }
    }

    for(int i = 1; i <= 2000000; i++) {
        if (light[i] == 1) {
            printf("%d\n", i);
            break;
        }
    }

    return 0;
}