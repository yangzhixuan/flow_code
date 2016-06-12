#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
#define MAXN 402
int s, t;
int n, np, nc, m;
int c[MAXN][MAXN];
int f[MAXN][MAXN];
int e[MAXN];
int h[MAXN];


long long totaltime = 0;


long long getCurrentTime()
{
    using namespace std::chrono;
    milliseconds ms = duration_cast< milliseconds >(
                                                    system_clock::now().time_since_epoch()
                                                    );
    return ms.count();
}

void push(int u, int v)
{
    int d = min(e[u], c[u][v] - f[u][v]);
    f[u][v] += d;
    f[v][u] = -f[u][v];
    e[u] -= d;
    e[v] += d;
}
bool relabel(int u)
{
    int mh = INT_MAX;
    for(int i=0; i<n+2; i++)
    {
        if(c[u][i] > f[u][i])
            mh = min(mh, h[i]);
    }
    if(mh == INT_MAX)
        return false; //残留网络中无从u出发的路
    h[u] = mh + 1;
    for(int i=0; i<n+2; i++)
    {
        if(e[u] == 0) //已无余流，不需再次push
            break;
        if(h[i] == mh && c[u][i] > f[u][i]) //push的条件
            push(u, i);
    }
    return true;
}
void init_preflow()
{
    memset(h, 0, sizeof(h));
    memset(e, 0, sizeof(e));
    h[s] = n+2;
    for(int i=0; i<n+2; i++)
    {
        if(c[s][i] == 0)
            continue;
        f[s][i] = c[s][i];
        f[i][s] = -f[s][i];
        e[i] = c[s][i];
        e[s] -= c[s][i];
    }
}
void push_relabel()
{
    init_preflow();
    bool flag = true; //表示是否还有relabel操作
    while(flag)
    {
        flag = false;
        for(int i=0; i<n; i++)
            if(e[i] > 0)
                flag = flag || relabel(i);
    }
}
int main()
{
    while(scanf("%d%d", &m,  &n) != EOF)
    {
        s = 1; t = n;
        memset(c, 0, sizeof(c));
        memset(f, 0, sizeof(f));
        while(m--)
        {
            int u,v,z;
            scanf("%d%d%d", &u, &v, &z);
            c[u][v] += z;
        }
        memset(h, 0, sizeof(h));
        memset(e, 0, sizeof(e));
        long long p1 = getCurrentTime();

        push_relabel();
                 long long p2 = getCurrentTime();

        totaltime += (p2-p1);
        printf("%d\n", e[t]);
    }
     printf("total time: %.5lf\n",totaltime/1000.0);

}