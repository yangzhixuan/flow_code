

#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;






#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

const int n = 10000;
const int nn = 100;
const int nm = 100;
const double a = 0.5; 
const int m = n*10; 
int gx[m],gy[m],gw[m];
int s;
int times = 100;
int xx[3] = {0,1,1};
int yy[3] = {1,0,1};

void add(int x ,int y,int z){
	gx[s] = x;
	gy[s] = y;
	gw[s] = z;
	s++;
	
}

int main(){
	srand(time(0));
	freopen("6.in","w",stdout);
for (int tt =0;tt<times;tt++){
	s = 0;

	for (int i=0;i<nn;i++)
		for (int j=0;j<nm;j++){
			for (int k = 0;k<3;k++){
				int nx = i+xx[k];
				int ny = j+yy[k];
				if (nx<nn&&ny<nm){
					add(i*nm+j+1,nx*nm+ny+1,rand()%500);
				}
			}
		}




	printf("%d %d\n",s,nn*nm);
	for (int i= 0;i<s;i++){
		printf("%d %d %d\n",gx[i],gy[i],gw[i]);
	}
}
}

