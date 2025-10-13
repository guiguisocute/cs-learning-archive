#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

struct problem{
    char name[11];
    int scores[21];
    int sum;
    double biaozhuncha;
};

int cmp(const void *a, const void *b) {
    struct problem *pa = (struct problem *)a;
    struct problem *pb = (struct problem *)b;
    if (pa->biaozhuncha < pb->biaozhuncha)
        return 1;
    else if (pa->biaozhuncha > pb->biaozhuncha)
        return -1;
    else
        return strcmp(pa->name, pb->name);
}

int main(){
    int n,k;
    scanf("%d %d",&n,&k);

    struct problem problems[n];
    for(int i = 0; i < n; i++){
        problems[i].name[0] = '\0';
    }

    for(int i = 0; i < n; i++){
        problems[i].sum = 0;
        scanf("%s",problems[i].name);
        for(int j = 0; j < k; j++){
            scanf("%d", &problems[i].scores[j]);
            problems[i].sum += problems[i].scores[j];
        }
        double aver = problems[i].sum / (double)k;
        double fenzisum = 0; 
        for(int j = 0; j < k; j++){
            fenzisum += (problems[i].scores[j] - aver) * (problems[i].scores[j] - aver);
        }
        problems[i].biaozhuncha = sqrt(fenzisum / (k + 0.0));
    }

    qsort(problems, n, sizeof(struct problem), cmp);

    for(int i = 0; i < 20 && problems[i].name[0] != '\0'; i++){
        printf("%s\n",problems[i].name);
    }

    return 0;
}