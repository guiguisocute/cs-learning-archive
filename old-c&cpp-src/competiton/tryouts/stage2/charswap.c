#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    int t;
    scanf("%d",&t);

    char a[4], b[4];
    char a_kai[t][4],b_kai[t][4];

    for(int i = 0; i < t; i++){
        scanf("%s %s",a,b);

        char temp = a[0];
        a[0] = b[0];
        b[0] = temp;

        strcpy(a_kai[i],a);
        strcpy(b_kai[i],b);
    }

    for (int i = 0; i < t; i++) {
        printf("%s %s\n", a_kai[i], b_kai[i]);
    }

    system("pause");
    return 0;
}