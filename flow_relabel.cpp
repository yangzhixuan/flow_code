#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <chrono>
#include<queue>



using namespace std;
#define INF 99999999

const int maxn =20000;
const int maxm =2500000;
const int  oo = 0x7fffffff;


long long totaltime = 0;


long long getCurrentTime()
{
    using namespace std::chrono;
    milliseconds ms = duration_cast< milliseconds >(
                                                    system_clock::now().time_since_epoch()
                                                    );
    return ms.count();
}



struct list
{
    int x;
    int h;
    bool friend operator <(const list &a,const list &b){
        return a.h<b.h;
    }
}q;


  int h[maxn];//高度
    int ef[maxn];//余流
    int n;//点数
    int max_flow;//最大流
    priority_queue<list>que;
    int u,v,p,i;
    int vis[maxn]; 
    int gx[maxm] , gy[maxm] , gw[maxm],ne[maxm] ,op[maxm] , fir[maxn];
    int sum;

struct push_relablel//最高标号预流推进算法，时间复杂度O(n*n*sqrt（m）)
{
  
	
	void init(int x){
        n=x;
		sum = 0;
		memset(fir,0,sizeof(fir));
        memset(h,0,sizeof(h));
        memset(ef,0,sizeof(ef));
    }
    void add(int u,int v,int w){
        gx[++sum]  = u; gy[sum]=v; gw[sum] = w; ne[sum] =fir[u]; fir[u] = sum;   op[sum] = sum+1;
		gx[++sum] =  v; gy[sum]=u; gw[sum] = 0; ne[sum] =fir[v]; fir[v] = sum;	 op[sum] = sum-1;
  	}

    int ans(int s,int t){
        max_flow=0;
        h[s]=n;
        ef[s]=oo;ef[t]=-oo;
        while(!que.empty())que.pop();
        q.x=s;
        q.h=h[s];
        que.push(q);
        while(!que.empty())
        {
            q=que.top();
            que.pop();
            u=q.x;
			for (int tt=fir[u];tt!=0;tt=ne[tt])
            {  
                v=gy[tt];
                if(gw[tt]<ef[u])p=gw[tt];
                else p=ef[u];
                if(p>0&&(u==s||h[u]==h[v]+1))
                {
                    gw[tt]-=p;
					gw[op[tt]]+=p;
				    if(v==t)max_flow+=p;
                    ef[u]-=p;ef[v]+=p;
                    if(v!=s&&v!=t)
                    {
                        q.x=v;
                        q.h=h[v];
                        que.push(q);
                    }
                }
            }
            if(u!=s&&u!=t&&ef[u]>0)
            {
                h[u]++;
                q.x=u;
                q.h=h[u];
                que.push(q);
            }
        }
        return max_flow;
    }
}G;

int main()
{
    int m,n,u,v,w;
    while(~scanf("%d%d",&m,&n))
    {
        G.init(n);
        while(m--)
        {
            scanf("%d%d%d",&u,&v,&w);
            G.add(u,v,w);
        }
        long long p1 = getCurrentTime();

        cout<<G.ans(1,n)<<endl;
        long long p2 = getCurrentTime();

        totaltime += (p2-p1);
    }
        printf("total time: %.5lf\n",totaltime/1000.0);

    return 0;
}











