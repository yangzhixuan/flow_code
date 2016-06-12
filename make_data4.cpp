#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;


const int n = 100;
const double a = 0.5; 
const int m = n*n+100; 
int gx[m],gy[m],gw[m];
int s;
int times = 100;


int main(){
	srand(time(0));
	freopen("4_2.in","w",stdout);
for (int tt =0;tt<times;tt++){
	s = 0;
	for (int i=2 ;i<n;i+=2)
	{
		gx[s] = 1;
		gy[s] = i;
		gw[s] = rand()%500;
		s++;
	}
	for (int i=3; i<=n;i+=2){
		gx[s] = i;
		gy[s] = n;
		gw[s] = rand()%500;
		s++;

	}

	for (int i=2;i<n;i+=2)
		for (int j =3;j<=n;j+=2){
	
			double x = rand()%2;
			if (x == 0){
				gx[s] = i;
				gy[s] = j;
				gw[s] = rand()%500;
				s++;
			}	

			x = rand()%2;
			if (x==0){
				gx[s] = j;
				gy[s] = i;
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
