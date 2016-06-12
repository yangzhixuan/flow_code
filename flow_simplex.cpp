// 题目来源：POJ 1273
// 题目大意：求源汇点最大流
// 解决方法：建立线性规划模型，用单纯形求解即可
// 特别注意：设原图有n个点，m条边，则：最大流量约束m，流量平衡约束2*n-4，总约束m+2*n-4；变量m；

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <chrono>
#define eps 0.000001
using namespace std;

double a[11000][11000];
int num[11000];
int n, m;

long long totaltime = 0;


long long getCurrentTime()
{
    using namespace std::chrono;
    milliseconds ms = duration_cast< milliseconds >(
                                                    system_clock::now().time_since_epoch()
                                                    );
    return ms.count();
}

int main( )
{

    while( scanf( "%d%d", &m, &n ) > 0 )
    {
        //memset( a, 0, sizeof( a ) );  // 目标约束矩阵初始化
        int bnd = m + 2*n - 4;  // 设置约束（bound）的数量
        for (int i= 0;i<=m;i++)
			for (int j=0;j<=bnd;j++)
				a[j][i] =0;
		int aa, bb, cc;
        for( int i = 1; i <= m; i++ )
        {
            scanf( "%d%d%d", &aa, &bb, &cc ); // 读取出端点aa，入端点bb，流量限制cc 
            a[i][0] = cc;  
            a[i][i] = -1;  // 约束矩阵加入最大流量限制
            if( aa != 1 ) a[m+aa-1][i] = -1, a[m+n-3+aa][i] = 1;
            if( bb != n ) a[m+bb-1][i] = 1,  a[m+n-3+bb][i] = -1;  // 约束矩阵加入流量平衡限制
            if( aa == 1 ) a[0][i] = 1;  // 矩阵首行加入目标函数
        }
        long long p1 = getCurrentTime();

        while( 1 )
        {
            int line = 0, row = 0;  // line得到进基变量所在列，row得到出基变量所在行
            double delta = 1e30, k;  // 取最紧约束值 
            for( line = 1; line < m+1; line++ )
                if( a[0][line] > eps ) break;  // 在目标函数值中找到进基变量
            if( line == m+1 ) break;  // 无进基变量退出循环
            for( int i = 1; i <= bnd; i++ )
                if( a[i][line] < -eps && a[i][0] / -a[i][line] < delta )
                    delta = a[i][0] / -a[i][line], row = i;  // 找到被进基变量约束得最紧的基变量，标记为出基变量
            k = -a[row][line];  // 取进基变量系数的相反数
            a[row][line] = -1;  // 将出基变量覆盖进基变量完成出基操作
            for( int i = 0; i <= m; i++ )
                a[row][i] /= k;  // 对出基变量所代表的约束执行恒等变换
            for( int i = 0; i <= bnd; i++ )
                if( i != row && a[i][line] != 0 )
                {
                    k = a[i][line], a[i][line] = 0;
                    for( int j = 0; j <= m; j++ )
                        a[i][j] += a[row][j] * k;  // 对所有约束执行消元
                }
        }
        printf( "%.0lf\n", a[0][0] );  // 输出目标函数当前值
                long long p2 = getCurrentTime();

        totaltime += (p2-p1);
    }
        printf("total time: %.5lf\n",totaltime/1000.0);

    return 0;
}
