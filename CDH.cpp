//
// Created by max on 16-5-29.
//
#include <iostream>
#include <ctime>

#define MR_PAIRING_SSP
#define AES_SECURITY 80

#define GAMA 2000
#define RUNTIMES 10

#include "pairing_1.h"
using namespace std;
PFC pfc(AES_SECURITY);

int main()
{
    clock_t start, end;
    //miracl *mip = get_mip();
    //mip->IOBASE = 10;
    Big r, t, a;
    G1 g, g1, g2;
    time_t seed;
    time(&seed);
    irand((long)seed);
    start = clock();
    for(int j = 0; j < RUNTIMES; ++j)
    {
        pfc.random(r);
        pfc.random(t);
        a = t % GAMA + r;
        pfc.random(g);
        g1 = pfc.mult(g, a);
        for(int i = 0; i < GAMA; ++i)
        {
            g2 = pfc.mult(g, r + i);
            if(g1 == g2) break;
        }
    }
    end = clock();
    double time=(double)(end-start)*1000/CLOCKS_PER_SEC;
    cout<<"time:"<<time/RUNTIMES<<endl;
    return 0;
}