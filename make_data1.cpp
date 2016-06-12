#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;


const int n = 100;
const double a = 0.5; 
const int m = n*n; 
int gx[m],gy[m],gw[m];
int s;
int times = 10;


int main(){
	srand(time(0));
	freopen("1_2.in","w",stdout);
for (int tt =0;tt<times;tt++){
	s = 0;
	for (int i= 1;i<=n;i++)
		for (int j = 1;j<=n;j++)
			if (i!=j){
				double x = rand()/(RAND_MAX*1.0);
			 	if (x<a){
					gx[s] = i;
					gy[s] = j;
					gw[s] = rand()%500;
					s++;
				} 	
			}
	printf("%d %d\n",s,n);
	for (int i= 0;i<s;i++){
		printf("%d %d %d\n",gx[i],gy[i],gw[i]);
	}
}
}
