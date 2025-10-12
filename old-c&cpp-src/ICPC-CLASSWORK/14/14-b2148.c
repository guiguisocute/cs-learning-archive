#include<stdio.h>

double solve(int n, double x) {
    if(n == 1) {
        return x / (1 + x);
    }
    return x / (n + solve(n - 1, x));
}

int main(){
    int n; 
    double x;
    scanf("%lf %d", &x, &n);
    printf("%.2lf", solve(n, x));
    return 0;
}