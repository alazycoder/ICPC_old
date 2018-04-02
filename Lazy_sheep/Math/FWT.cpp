快速沃尔什变换：

//C[i $ j] + = A[i] * B[j]
//C=fwt( fwt(A,1)*fwt(B,1),0 )
const int MOD = (int)1e9 + 7;
const int inv2 = MOD + 1 >> 1;
int A[1 << 20];
void fwt(int A[],int n,int inv)
{
    for (int l = 1; l << 1 <= n; l <<= 1)
    {
        for (int s = 0; s < n; ++ s)
        {
            if (~s & l)
            {
                int a = A[s];
                int b = A[s ^ l];
                if (inv == 1)
                {
                    ///xor
                    A[s]=(a-b+MOD)%MOD;
                    A[s^l]=(a+b)%MOD;
                    ///and
//                    A[s]=b;
//                    A[s^l]=(a+b)%MOD;
                    ///or
//                    A[s]=(a+b)%MOD;
//                    A[s^l]=a;
                }
                else
                {
                    ///xor
                    A[s]=(a+b)*1ll*inv2%MOD;
                    A[s^l]=(b-a+MOD)*1ll*inv2%MOD;
                    ///and
//                    A[s]=(b-a+MOD)%MOD;
//                    A[s^l]=a
                    ///or
//                    A[s]=b;
//                    A[s^l]=(a-b+MOD)%MOD;
                }
            }
        }
    }
}
