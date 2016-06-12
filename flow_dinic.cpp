#include <cstdio>
#include <cstring>
#include <chrono>
int n,m,t,s[12000],f[12000],x[2500000],y[2500000],z[2500000],b[12000],T(2),ANS;

long long totaltime = 0;


long long getCurrentTime()
{
    using namespace std::chrono;
    milliseconds ms = duration_cast< milliseconds >(
                                                    system_clock::now().time_since_epoch()
                                                    );
    return ms.count();
}

void IN(int a,int b,int c,int d)
{	x[T]=f[a];y[T]=b;z[T]=c;f[a]=T++;
	x[T]=f[b];y[T]=a;z[T]=d;f[b]=T++;
}

int DFS(int l,int m)
{	if(l==t)return m;
	int j,r(0);
	for(;s[l];s[l]=x[s[l]])
	if(z[s[l]]&&b[y[s[l]]]+1==b[l])
	{	j=DFS(y[s[l]],m<z[s[l]]?m:z[s[l]]);
		z[s[l]]-=j;
		z[s[l]^1]+=j;
		m-=j;
		r+=j;
		if(!m)return r;
	}
	return r;
}

int main(){
while (scanf("%d%d",&m,&n)!=-1){
	memset(f,0,sizeof(f));
	T = 2;
	ANS = 0;
	int i,j,k;
	for (int i=0;i<m;i++){
		int xx,yy,zz;
		scanf("%d%d%d",&xx,&yy,&zz);
		IN(xx-1,yy-1,zz,0);
	}
	t = n-1;
	

	long long p1 = getCurrentTime();
	for(;;ANS+=DFS(0,65536000))
	{	memset(b,0,sizeof b);
		for(b[s[i=0]=t]=j=1;!b[0]&&i<j;i++)
			for(k=f[s[i]];k;k=x[k])
				if(z[k^1]&&!b[y[k]])b[s[j++]=y[k]]=b[s[i]]+1;
	//	for(i=0;i<j;i++)printf("%d ",s[i]);printf("\n%d\n",ANS);
		if(!b[0])break;
		memcpy(s,f,sizeof f);
	}
	long long p2 = getCurrentTime();

	printf("%d\n",ANS);
	totaltime += (p2-p1);
	

}

	printf("total time: %.5lf\n",totaltime/1000.0);
}
