#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

typedef struct {
    int x, y;
    int index; 
} machine;

typedef struct {
    int x, y;
} point;


machine machines[2010];
int machine_count = 0;

int machineindex[2010][2010];

int spawnindices[2010];
int spawn_count = 0;

point hunterpoints[2010];
int hunter_ount = 0;

int main() {
    int n, k, T;
    scanf("%d %d %d", &n, &k, &T);

    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        machines[i].x = x;
        machines[i].y = y;
        machines[i].index = i;
        machineindex[x + 1000][y + 1000] = i; //加1000是为了防止负坐标対数组索引的影响
    }

    for (int i = 0; i < k; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        int index = machineindex[x + 1000][y + 1000];
        spawnindices[spawn_count++] = index;
    }

    for (int i = 0; i < T; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        hunterpoints[i].x = x;
        hunterpoints[i].y = y;
    }

    int ans = 0;

    for (int i = 0; i < T; i++) {
        int max_dist_sq = -1;
        int min_index = n + 1; 

        for (int j = 1; j <= n; j++) {
            int dx = machines[j].x - hunterpoints[i].x;
            int dy = machines[j].y - hunterpoints[i].y;
            int dist_sq = dx * dx + dy * dy;
            if (dist_sq > max_dist_sq) {
                max_dist_sq = dist_sq;
                min_index = machines[j].index;
            } else if (dist_sq == max_dist_sq) {
                if (machines[j].index < min_index) {
                    min_index = machines[j].index;
                }
            }
        }

        for (int s = 0; s < spawn_count; s++) {
            if (spawnindices[s] == min_index) {
                ans++;
                break; 
            }
        }
    }

    printf("%d", ans);

    return 0;
}
