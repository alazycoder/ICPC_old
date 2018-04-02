1.  n<=5000
//递推关系式C [n][ m ]= C[ n ][m-1 ] + C[ n-1][m-1 ]
//复杂度O(n^2)
int c[5005][5005];
void init(int n)
{
    memset(c,0,sizeof(c));
    for(int i=0;i<n;i++)
        c[i][0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=i;j++)
        {
            c[i][j]= c[i-1][j]+c[i-1][j-1];
            if(c[i][j]>=mod)  c[i][j]-=mod;
        }
    }
}
