#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main() {
    int q;
    scanf("%d", &q);

    char document[201];  
    scanf("%s", document);  

    while (q--) {
        int operation;
        scanf("%d", &operation);  

        if (operation == 1) {
            
            char str[101];
            scanf("%s", str);
            strcat(document, str);  
            printf("%s\n", document);

        } else if (operation == 2) {
            
            int a, b;
            scanf("%d %d", &a, &b);
            char temp[201];
            strncpy(temp, document + a, b);  
            temp[b] = '\0';  
            strcpy(document, temp);  
            printf("%s\n", document);

        } else if (operation == 3) {
            
            int a;
            char str[101];
            scanf("%d %s", &a, str);

            char temp[201];
            strncpy(temp, document, a);  
            temp[a] = '\0';  
            strcat(temp, str);  
            strcat(temp, document + a);  
            strcpy(document, temp);  
            printf("%s\n", document);

        } else if (operation == 4) {
           
            char str[101];
            scanf("%s", str);
            char *pos = strstr(document, str);  
            if (pos != NULL) {
                printf("%ld\n", pos - document);
            } else {
                printf("-1\n");
            }
        }
    }

    return 0;
}