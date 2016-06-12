#include <stdio.h>
#include <string.h>
#include <chrono>
using namespace std;


#define N 1002
#define MAX_INT 2000000

#define min(a, b) ((a) < (b) ? (a) : (b))

int     graph[N][N];
int     h[N];
int     e[N];
int     n;



long long totaltime = 0;


long long getCurrentTime()
{
    using namespace std::chrono;
    milliseconds ms = duration_cast< milliseconds >(
                                                    system_clock::now().time_since_epoch()
                                                    );
    return ms.count();
}


int push_relabel(int s, int t)
{
    int     max_flow, u, v, d, done, relabel, min_height;

   
    h[s] = n+2;
    for (u = 1; u <= t; u++) {
        if (graph[s][u] > 0) {
            e[u] = graph[s][u];
            e[s] -= graph[s][u];
            graph[u][s] = graph[s][u];
            graph[s][u] = 0;
        }
    }

    for (;;) {
        done = 1;
        for (u = s+1; u < t; u++) {
            if (e[u] > 0) {
                done = 0;
                //先假设顶点u需要relabel
                relabel = 1;
                for (v = s; v <= t && e[u] > 0; v++) {  /* 检查能push的顶点 */
                    if (graph[u][v] > 0 && h[u] > h[v]) {
                        //push
                        relabel = 0;
                        d = min(graph[u][v], e[u]);
                        e[u] -= d;
                        e[v] += d;
                        graph[u][v] -= d;
                        graph[v][u] += d;
                    }
                }
                //没有可以push的顶点,执行relabel
                if (relabel) {
                    //relabel
                    min_height = MAX_INT;
                    for (v = s; v <= t; v++) {
                        if (graph[u][v] > 0 && h[v] < min_height) {
                            min_height = h[v];
                        }
                    }
                    h[u] = 1 + min_height;
                }
            }
        }
        if (done) { /* 除源点和汇点外,每个顶点的e[i]都为0 */
            max_flow = 0;
            for (u = s; u <= t; u++) {
                if (graph[t][u] > 0) {
                    max_flow += graph[t][u];
                }
            }
            break;
        }
    }
    return max_flow;
}

int main()
{
    int     np, nc, m, u, v, w;

    while (scanf("%d%d",&m, &n) != EOF) {
        memset(graph, 0, sizeof(graph));
        n+=2;
        while (m--) {
            scanf("%d%d%d", &u, &v, &w);
            graph[u][v] += w;
        }
        graph[0][1] = MAX_INT;
        graph[n-2][n-1] = MAX_INT;
         memset(h, 0, sizeof(h));
        memset(e, 0, sizeof(e));

        long long p1 = getCurrentTime();
        printf("%d\n", push_relabel(0, n-1));

                   long long p2 = getCurrentTime();

        totaltime += (p2-p1);
        
    }
     printf("total time: %.5lf\n",totaltime/1000.0);
    return 0;
}