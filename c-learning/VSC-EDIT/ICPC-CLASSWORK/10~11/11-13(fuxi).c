#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char s[201], k[201];
int l;

int str_cmp(char *a, char *b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    if (len_a != len_b)
        return len_a - len_b;
    return strcmp(a, b);
}

int main() {
    scanf("%s", s);
    l = strlen(s) - 1;

    int all_nine = 1;
    for (int i = 0; i <= l; i++) {
        if (s[i] != '9') {
            all_nine = 0;
            break;
        }
    }
    if (all_nine) {
        printf("1");
        for (int i = 0; i < l; i++) 
            printf("0");
        printf("1\n");
        return 0;
    }

    strcpy(k, s);
    for (int i = 0; i <= l/2; i++)
        k[l-i] = k[i];

    if (str_cmp(k, s) <= 0) {
        int mid = (l)/2;
        if (l % 2 == 0) {
            mid = l/2;
        }
        while (mid >= 0 && k[mid] == '9') {
            k[mid] = k[l-mid] = '0';
            mid--;
        }
        if (mid >= 0) {
            k[mid] = k[l-mid] = k[mid] + 1;
        }
    }

    printf("%s\n", k);
    return 0;
}