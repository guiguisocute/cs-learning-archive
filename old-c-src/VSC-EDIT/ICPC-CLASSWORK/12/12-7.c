#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#define ll long long int

ll getnext(ll date) {
    int year = date / 10000;
    int month = (date / 100) % 100;
    int day = date % 100;

    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) {
        days[2] = 29;
    }

    day++;
    if(day > days[month]) {
        day = 1;
        month++;
        if(month > 12) {
            month = 1;
            year++;
        }
    }
    return (ll)year * 10000 + month * 100 + day;
}

int ishuiwen(ll date) {
    char str[9];
    sprintf(str,"%08lld",date);
    for(int i = 0; i < 4; i++) {
        if(str[i] != str[7 - i]) {
            return 0;
        }
    }
    return 1;
}

int solve(ll date1, ll date2) {
    int count = 0;
    ll current = date1;
    
    while(current <= date2) {
        if(ishuiwen(current)) {
            count++;
        }
        current = getnext(current);
    }
    return count;
}

int main() {
    ll date1, date2;
    scanf("%lld",&date1);
    scanf("%lld",&date2);
    printf("%d",solve(date1,date2));
    return 0;
}