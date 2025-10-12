#include <stdio.h>
#include <string.h>

int main()
{
    char s[201][100], a[100], b[100];
    char c;
    int n = 1;

    do {
        scanf("%s", s[n]); 
        ++n;
    } while ((c = getchar()) == ' '); 

    scanf("%s %s", a, b); 

    for (int i = 1; i < n; ++i)
    {
        if (strcmp(s[i], a) == 0) 
            strcpy(s[i], b); 
        printf("%s ", s[i]); 
    }
    return 0;
}
