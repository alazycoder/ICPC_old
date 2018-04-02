
意义： 表示不超过n且与n互素的正整数的个数
性质： 欧拉函数在正整数n上的值等于对n进行素因子分解后，所有的素数幂上的欧拉函数之积。(积性函数)
欧拉定理： 对于互质的正整数a和n，有a^φ(n) ≡ 1 (mod n)
降幂公式： (A^x) %C =A^ ( x%phi(C)+phi(C) )  %C（x>=phi(C)）
常用公式： ∑ phi(d) = n (d|n) ，即 phi(n) = n - ∑ phi(d) (d|n,d<n)


//复杂度sqrt（n）
int phi(int n)
{
    int rea=n;
    for(int i=2;i*i<=n;i++)
    {
        if(n%i==0)
        {
            rea=rea-rea/i;
            while(n%i==0)
                n/=i;
        }
    }
    if(n>1)
        rea=rea-rea/n;
    return rea ;
}


//递推求前n个数的欧拉函数
//复杂度nlg(n)
for(int i=1;i<MAX;i++)  phi[i]=i;
for(int i=2;i<MAX;i+=2)  phi[i]/=2;
for(int i=3;i<MAX;i+=2)
{
    if(phi[i]==i)
    {
        for(int j=i;j<MAX;j+=i)
            phi[j]=phi[j]/i*(i-1);
    }
}
