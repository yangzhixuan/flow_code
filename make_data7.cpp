#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;


const int n = 10000;
const double a = 0.5; 
const int m = n*n; 
int gx[m],gy[m],gw[m];
int s;
int times = 1;


void add(int x ,int y,int z){
	gx[s] = x;
	gy[s] = y;
	gw[s] = z;
	s++;
	
}



int main(){
	srand(time(0));
	freopen("7.in","w",stdout);
for (int tt =0;tt<times;tt++){
	s = 0;
	for (int i= 1;i<n;i++)
		add(i,n,1);
	for (int i=1;i<n-1;i++)
		add(i,i+1,n);
	printf("%d %d\n",s,n);
	for (int i= 0;i<s;i++){
		printf("%d %d %d\n",gx[i],gy[i],gw[i]);
	}
}
}
