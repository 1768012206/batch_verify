//
// Created by School_lin on 16-4-17.
//

#include <iostream>
#include <ctime>

#define MR_PAIRING_SSP
//#define AES_SECURITY 80
#define AES_SECURITY 128

#define NS 100
#define LEN 200
#define RUNTIMES 100
#define NUM 20
#define W 4
#include "pairing_1.h"
using namespace std;

char* gen_exp(char* str)
{
    int i,j;
    for(i=0;i<NUM*W;i=i+W)
    {
        str[i]='0'+rand()%2;
        for(j=1;j<=W;j++)
        {
            str[i+j]='0';
        }
    }
    for(i=0;i<NUM*W-W+1;i++)
    {
        str[i]=str[i+W-1];
    }
    return str;
}

int main()
{
    srand((unsigned int)time(NULL));
    clock_t start,end;
    PFC pfc(AES_SECURITY);
    miracl *mip=get_mip();
    int i;
    char str[NS][LEN]={'\0'};
    char* vstr[NS];
    for(i=0;i<NS;++i)
    {
        vstr[i]=gen_exp(str[i]);
    }
    Big v[NS];  //V1,V2...Vns
    mip->IOBASE=2;
    for(i=0;i<NS;++i)
    {
        v[i]=vstr[i];
        //pfc.random(v[i]);
    }
    mip->IOBASE=16;
    time_t seed;
    time(&seed);
    irand((long)seed);

    G1 z[NS],g,y,r,h[NS];
    for(i=0;i<NS;++i)
    {
        pfc.random(z[i]);
        pfc.random(h[i]);
    }
    pfc.random(g);
    pfc.random(y);
    pfc.random(r);
    Big c;
    Big p=get_modulus();
    pfc.random(c);
    char* hstr=(char*)"asdfadf";
    G1 H1,H2;
    Big V;
    start=clock();

    G1 Z=pfc.mult(z[0],v[0]);
    for(i=1;i<NS;++i)
    {
        Z=Z+pfc.mult(z[i],v[i]);
    }
    pfc.pairing(Z,g);

    V=v[0];
    for(i=1;i<6;++i)
    {
        V=V*v[i];
        V%=65537;
    }
    //cout<<bits(V)<<endl;
    //cout<<bits(get_modulus())<<endl;
    //pfc.random(V);
    pfc.hash_and_map(H1,hstr);
    pfc.hash_and_map(H2,hstr);
    G1 H3=pfc.mult(H2,c);
    G1 H=H1+H3;
    G1 HH=pfc.mult(H,V);
    pfc.pairing(HH,y);

    G1 HL=pfc.mult(h[0],v[0]);
    for(i=1;i<NS;++i)
    {
        HL=HL+pfc.mult(h[i],v[i]);
    }
    pfc.pairing(HL,r);

    end=clock();

    double time=(double)(end-start)*1000/CLOCKS_PER_SEC;
    cout<<"time:"<<time<<endl;
    return 0;
}