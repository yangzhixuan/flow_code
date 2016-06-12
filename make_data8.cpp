#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;


const int n = 100;
const int sqn= 10;
double a ;
const int m = n*n; 
int gx[m],gy[m],gw[m];
int s;
int times = 100;


void add(int x ,int y,int z){
	gx[s] = x;
	gy[s] = y;
	gw[s] = z;
	s++;
	
}



int main(){
	srand(time(0));
	freopen("8_1.in","w",stdout);
for (int tt =0;tt<times;tt++){
	s = 0;
	
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++){
            if (i==j) a=0;
            else
            if (i/sqn == j/sqn) a =0.7;
            else a = 0.1;
           
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
