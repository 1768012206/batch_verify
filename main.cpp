#include <iostream>
#include <ctime>

#define MR_PAIRING_SSP
//#define AES_SECURITY 80
#define AES_SECURITY 128

#define STRLEN 10
#define RUNTIMES 100
#define NUM 40
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
    clock_t start,end;
    PFC pfc(AES_SECURITY);
    char* hstr=(char*)"asdfadf";
    G1 H;
    Big a,b;
    pfc.random(a);
    pfc.random(b);
    start=clock();
    a*b;
    end=clock();
    double time=(double)(end-start)*1000/CLOCKS_PER_SEC;
    cout<<"time:"<<time<<endl;
    return 0;
}