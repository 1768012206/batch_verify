#include <iostream>
#include <ctime>


#define MR_PAIRING_SSP
#define AES_SECURITY 80
//#define AES_SECURITY 128

#define STRLEN 10
#define RUNTIMES 100
#define NUM 20
#define W 4
#include "pairing_1.h"
using namespace std;

void rand_str(char* str,int len)
{
    int i;
    for(i=0;i<len;++i)
        str[i]='A'+rand()%26;
    str[i]='\0';
}

Big gen_exp()
{
    Big x;
    char str[100]={'\0'};
    //srand(time(NULL));
    int i,j;
    for(i=0;i<NUM*W;i=i+W)
    {
        str[i]='0'+rand()%5*2+1;
        for(j=1;j<=W;j++)
        {
            str[i+j]='0';
        }
    }
    for(i=0;i<NUM*W-W+1;i++)
    {
        str[i]=str[i+W-1];
    }
    //cout<<str<<endl;
    x=str;
    return x;
    //cout<<x<<endl;

}

int main()
{
    clock_t start,end;
    PFC pfc(AES_SECURITY);
    G1 V,P;
    G1 S[RUNTIMES],R[RUNTIMES],SEXP[RUNTIMES],REXP[RUNTIMES],SIG,HAS;
    GT T,U;
    int lsb[RUNTIMES],i;
    Big s,X[RUNTIMES],exp[RUNTIMES];
    time_t seed;
    time(&seed);
    irand((long)seed);
    pfc.random(P);
    pfc.random(s);
    V=pfc.mult(P,s);
    char* str[RUNTIMES];
    char* str2=new char[STRLEN+1];
    srand((unsigned int)time(NULL));
    for(i=0;i<RUNTIMES;++i)
    {
        rand_str(str2,STRLEN);
        str[i]=str2;
        pfc.hash_and_map(R[i],str[i]);
        S[i]=pfc.mult(R[i],s);
        //lsb[i]=S[i].g.get(X[i]);
        //cout<<lsb[i]<<","<<X[i]<<endl;
        //exp[i]=gen_exp();
        //cout<<exp[i]<<endl;
        //SEXP[i]=pfc.mult(S[i],exp[i]);

        //REXP[i]=pfc.mult(R[i],exp[i]);
    }
    delete [] str2;

    start=clock();
    exp[0]=gen_exp();
    SEXP[0]=pfc.mult(S[0],exp[0]);
    SIG=SEXP[0];
    REXP[0]=pfc.mult(R[0],exp[0]);
    HAS=REXP[0];
    for(i=1;i<RUNTIMES;++i)
    {
        exp[i]=gen_exp();
        SEXP[i]=pfc.mult(S[i],exp[i]);
        SIG=SIG+SEXP[i];
        REXP[i]=pfc.mult(R[i],exp[i]);
        HAS=HAS+REXP[i];
    }
    //cout<<SIG.g<<endl;
    T=pfc.pairing(P,SIG);
    //cout<<T.g<<endl;
    U=pfc.pairing(V,HAS);
    //cout<<U.g<<endl;

    if(T==U)
    {
        //cout<<"good"<<endl;
        end=clock();
        double time=(double)(end-start)*1000/CLOCKS_PER_SEC;
        cout<<"time:"<<time/RUNTIMES<<endl;
    }
    return 0;
}