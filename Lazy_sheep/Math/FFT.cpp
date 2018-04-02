快速傅里叶变换：

//from maopao
const double PI = acos(-1.0);
struct Complex
{
    double real, image;
    Complex(double _real, double _image)
    {
        real = _real;
        image = _image;
    }
    Complex() {}
    Complex operator + (const Complex &c1)
    {
        return Complex(real + c1.real, image + c1.image);
    }
    Complex operator - (const Complex &c1)
    {
        return Complex(real - c1.real, image - c1.image);
    }
    Complex operator * (const Complex &c1)
    {
        return Complex(real*c1.real - image*c1.image, real*c1.image + image*c1.real);
    }

};
int rev(int id, int len)
{
    int ret = 0;
    for(int i = 0; (1 << i) < len; i++)
    {
        ret <<= 1;
        if(id & (1 << i)) ret |= 1;
    }
    return ret;
}
Complex A[1<<20];
//len必须是2^x的形式，DFT为1，逆DFT为-1
void FFT(Complex* a, int len, int DFT)//对a进行DFT或者逆DFT, 结果存在a当中
{
    //Complex* A = new Complex[len]; 这么写会爆栈
    for(int i = 0; i < len; i++)
        A[rev(i, len)] = a[i];
    for(int s = 1; (1 << s) <= len; s++)
    {
        int m = (1 << s);
        Complex wm = Complex(cos(DFT*2*PI/m), sin(DFT*2*PI/m));
        for(int k = 0; k < len; k += m)
        {
            Complex w = Complex(1, 0);
            for(int j = 0; j < (m >> 1); j++)
            {
                Complex t = w*A[k + j + (m >> 1)];
                Complex u = A[k + j];
                A[k + j] = u + t;
                A[k + j + (m >> 1)] = u - t;
                w = w*wm;
            }
        }
    }
    if(DFT == -1) for(int i = 0; i < len; i++) A[i].real /= len, A[i].image /= len;
    for(int i = 0; i < len; i++) a[i] = A[i];
    return;
}

例：
已知多项式一有n项，（最高次项为n-1次），多项式二有m项（最高次项为m-1次）。求两个多项式乘积的各项的次数。

Complex a[1<<20],b[1<<20];
int  numa[100005],numb[100005];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)  scanf("%d",&numa[i]); //多项式系数从0次到n-1次
    for(int i=0;i<m;i++)  scanf("%d",&numb[i]); //多项式系数从0次到m-1次
    //乘积的最高次项为n+m,求出大于等于n+m的第一个2的整数幂
    int len=1;
    while(len<2*max(n,m)) len<<=1;
    //一定要将这len长的数全清零
    memset(a,0,sizeof(*a)*len);
    memset(b,0,sizeof(*b)*len);
    for(int i=0;i<n;i++)  a[i].real=numa[i];
    for(int i=0;i<m;i++)  b[i].real=numb[i];
    //通过DFT将多项式的系数向量表示转换成点值表示
    FFT(a,len,1);
    FFT(b,len,1);
    //点值表示相乘，存在a中
    for(int i=0; i<len; i++)
        a[i]=a[i]*b[i];
    //将a的点值表示通过逆DFT转换成系数向量表示
    FFT(a,len,-1);
    for(int i=0;i<=n+m-2; i++)
        printf("%d\n",int(a[i].real+0.5));
    return 0;
}
