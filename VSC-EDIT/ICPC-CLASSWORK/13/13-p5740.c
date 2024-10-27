#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

struct scoure{
    char name[9];
    int chinese;
    int math;
    int eng;
};


int main(){
    int n;
    scanf("%d",&n);
    int max = 0,pos;

    struct scoure scoures[n];

    for(int i = 0; i < n; i++){
        scanf("%s %d %d %d",scoures[i].name, &scoures[i].chinese, &scoures[i].math, &scoures[i].eng);
    }

    for(int i = 0; i < n; i++){
        if((scoures[i].chinese + scoures[i].math + scoures[i].eng) > max){
            max = (scoures[i].chinese + scoures[i].math + scoures[i].eng);
            pos = i;
        }
    }
    if(max == 0){
        printf("%s %d %d %d",scoures[0].name, scoures[0].chinese, scoures[0].math, scoures[0].eng);
    }else{
        printf("%s %d %d %d",scoures[pos].name, scoures[pos].chinese, scoures[pos].math, scoures[pos].eng);
    }


    return 0;
}