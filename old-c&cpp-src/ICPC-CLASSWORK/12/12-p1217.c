#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

int check1(int n) {
    if((1000 <= n && n <= 9999) || (100000 <= n && n <= 999999)) {
        return 0;  
    }
    return 1;
}


int check2(int n) {
    if (n < 0 || (n % 10 == 0 && n != 0)) {
        return 0;
    }
    
    int reversed = 0;
    while (n > reversed) {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }
    
    return n == reversed || n == reversed/10;
}

int check3(int n){
    if (n == 1) return 0;
    for(int i = 2; i * i <= n; i++){
        if (n % i == 0) return 0;
    }
    return 1;
}

int main() {
    int l, r;
    scanf("%d %d", &l, &r);
    
    if(l <= 2 && 2 <= r) {
        printf("2\n");
    }
    
    if(l % 2 == 0) l++;
    
    r = (r > 9999999) ? 9999999 : r;
    
    int i;
    for(i = l; i <= r; i += 2) {
        if(check1(i) == 0) continue;
        if(check2(i) == 0) continue;
        if(check3(i) == 0) continue;
        
        printf("%d\n", i);
    }
    
    return 0;
}
