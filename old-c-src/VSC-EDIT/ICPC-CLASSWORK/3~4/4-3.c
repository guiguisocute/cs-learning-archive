#include <stdio.h>
#include <stdlib.h>

int main() {
    char a;
    scanf("%c", &a);

    if (a == 'G') {
        printf("Hello, my master!\nI'm Xiaoluo.");
    } 
    else if (a == 'N') {
        printf("I'm Xiaoluo.");
    } 
    else if (a == 'S') {
        printf("Teinei teinei teinei~");
    } 
    else if (a == 'B' || a == 'Q') {
        printf("Bye bye!");
    } 
    else {
        printf("Sorry...");
    }

    system("pause");
    return 0;
}