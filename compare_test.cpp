#include <iostream>
#include <ctime>

#define MR_PAIRING_SSP
#define AES_SECURITY 80
//#define AES_SECURITY 128
//*************
//compare calculate time
//(g1^r1)*...*(g100^r100)
//(g1^w1)*...*(g100^w100)
//*************
#define NUM 20
#define W 4
#include "pairing_1.h"
using namespace std;

Big gen_exp()
{
    //miracl *mip=get_mip();
    Big x;
    char str[100]={'\0'};
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
    //mip->IOBASE=16;
    x=str;
    return x;
}

int main()
{
    srand((unsigned int)time(NULL));
    PFC pfc(AES_SECURITY);
    miracl *mip=get_mip();
    mip->IOBASE=10;
    G1 g[100];
    Big r[100],w[100];
    int i;
    time_t seed;
    time(&seed);
    irand((long)seed);
    for(i=0;i<100;++i)
    {

        pfc.random(g[i]);
        pfc.random(r[i]);
        w[i]=gen_exp();
    }
    clock_t s,d;
    double time;
    s=clock();
    G1 t1=pfc.mult(g[0],r[0]);
    cout<<r[0]<<endl;
    for(i=1;i<100;++i)
    {
        t1=t1+pfc.mult(g[i],r[i]);
    }
    d=clock();
    time=(double)(d-s)*1000/CLOCKS_PER_SEC;
    cout<<"time:"<<time<<endl;
    clock_t ss,dd;
    ss=clock();
    G1 t2=pfc.mult(g[0],w[0]);
    cout<<w[0]<<endl;
    for(i=1;i<100;++i)
    {
        t2=t2+pfc.mult(g[i],w[i]);
    }
    dd=clock();
    time=(double)(dd-ss)*1000/CLOCKS_PER_SEC;
    cout<<"time:"<<time<<endl;
}