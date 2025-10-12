#include<stdio.h>
#include<stdlib.h>


long long min(long long a, long long b) {
    return a < b ? a : b;
}

int main() {
    int T;
    scanf("%d", &T);  


    while (T--) {
        long long n, m;
        scanf("%lld %lld", &n, &m);  
        long long max_tools = 0;

        for (long long sward_count = 0; sward_count <= min(n, m / 2); sward_count++) {
            long long remaining_n = n - sward_count;        
            long long remaining_m = m - sward_count * 2;    

            long long chan_count = min(remaining_m, remaining_n / 2);
            long long remaining_n_after_chan = remaining_n - chan_count * 2;
            long long remaining_m_after_chan = remaining_m - chan_count;

            long long chu_count = min(remaining_m_after_chan / 2, remaining_n_after_chan / 2);

            long long total_tools = sward_count + chan_count + chu_count;
            if (total_tools > max_tools) {
                max_tools = total_tools;
            }
        }

        printf("%lld\n", max_tools);
    }
    
    system("pause");
    return 0;
}

