#include <stdio.h>
#include <string.h>
#include <chrono>
using namespace std;


#define N 1005
#define MAX_INT 2000000
#define maxm 2500000
#define min(a, b) ((a) < (b) ? (a) : (b))


int     h[N];
int     e[N];
int     n;
int gx[maxm] , gy[maxm] , gw[maxm],ne[maxm] ,op[maxm] , fir[N];
int sum;



long long totaltime = 0;


long long getCurrentTime()
{
    using namespace std::chrono;
    milliseconds ms = duration_cast< milliseconds >(
                                                    system_clock::now().time_since_epoch()
                                                    );
    return ms.count();
}

void add(int u,int v,int w){
    gx[++sum]  = u; gy[sum]=v; gw[sum] = w; ne[sum] =fir[u]; fir[u] = sum;   op[sum] = sum+1;
    gx[++sum] =  v; gy[sum]=u; gw[sum] = 0; ne[sum] =fir[v]; fir[v] = sum;	 op[sum] = sum-1;
}




int push_relabel(int s, int t)
{
    int     max_flow, u, v, d, done, relabel, min_height;

   
    h[s] = n+2;
    for (int tt=fir[s]; tt!=0; tt = ne[tt]) {
        if (gw[tt] > 0) {
            u = gy[tt];
            e[u] = gw[tt];
            e[s] -= gw[tt];
            gw[op[tt]] = gw[tt];
            gw[tt] = 0;
        }
    }

    for (;;) {
        done = 1;
        for (u = s+1; u < t; u++) {
            if (e[u] > 0) {
                done = 0;
                //先假设顶点u需要relabel
                relabel = 1;
                for (int tt=fir[u];tt!=0&&e[u]>0;tt=ne[tt]){
                    v = gy[tt];
                
                //for (v = s; v <= t && e[u] > 0; v++) {  /* 检查能push的顶点 */
                    if (gw[tt] > 0 && h[u] > h[v]) {
                        //push
                        relabel = 0;
                        d = min(gw[tt], e[u]);
                        e[u] -= d;
                        e[v] += d;
                        gw[tt] -= d;
                        gw[op[tt]] += d;
                    }
                }
                //没有可以push的顶点,执行relabel
                if (relabel) {
                    //relabel
                    min_height = MAX_INT;
                    for (int tt=fir[u];tt!=0;tt=ne[tt]){
                        v = gy[tt];
                        if (gw[tt]> 0 && h[v] < min_height) {
                            min_height = h[v];
                        }
                    }
                    h[u] = 1 + min_height;
                }
            }
        }
        if (done) { /* 除源点和汇点外,每个顶点的e[i]都为0 */
            max_flow = 0;
            for (int tt =fir[t];tt!=0;tt=ne[tt]){
                if (gw[tt] > 0) {
                    max_flow += gw[tt];
                }
            }
            break;
        }
    }
    return max_flow;
}



int main()
{
    int      m, u, v, w;

    while (scanf("%d%d",&m, &n) != EOF) {
        memset(fir,0,sizeof(fir));
        sum = 0;
        n+=2;
        while (m--) {
            scanf("%d%d%d", &u, &v, &w);
            //graph[u][v] += w;
            add(u,v,w);
        }
        add(0,1,MAX_INT);
        add(n-2,n-1,MAX_INT);
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