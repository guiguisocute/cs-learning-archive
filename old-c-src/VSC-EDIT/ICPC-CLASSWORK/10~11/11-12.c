#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
//核心：统计每组相应位置上出现次数最多的字母，并且把每个子串不是该字母的字母改成它

int main(){
    int k;
    char s[100005];
    scanf("%d",&k);
    scanf("%s",s);

    int len = strlen(s);
    if(len % k != 0){
        printf("-1");
        return 0;
    }

    int sublen = len / k;
    int ans = 0;

    for(int i = 0; i < sublen; i++){
        int alphabet[26] = {0};
        int max = 0;

        for(int j = 0; j < k; j++){
            int pos = i + j * sublen;
            char c = s[pos];
            alphabet[c - 'a']++;
            if(alphabet[c - 'a'] > max){
                max = alphabet[c - 'a'];
            }
        }
        ans += k - max;
        
    }
    printf("%d",ans);
    return 0;
}