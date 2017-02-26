//
// Created by max on 17-2-24.
//

#include <iostream>
#include <ctime>

#define MR_PAIRING_SSP
#define AES_SECURITY 128

#define N 10

#include "pairing_1.h"
using namespace std;

double ini_step1() {
    clock_t start, end;
    PFC pfc(AES_SECURITY);
    Big ni,oi;
    pfc.random(ni);
    pfc.random(oi);
    G1 a, b, v, f[N], y[N], si10, si11;
    Big E;
    pfc.random(si10);
    pfc.random(si11);
    start = clock();
    pfc.hash_and_map(v, (char*)"asdf");
    E = pfc.hash_to_group((char*)"asdfqwre");
    for(int j = 0; j < N; j++) {
        pfc.hash_and_map(f[j], (char*)"asdfi");
        G1 tmp1, tmp2;
        tmp1 = si10 + pfc.mult(si11, E);
        tmp2 = tmp1 + pfc.mult(v, oi);
        y[j] = tmp2 + pfc.mult(f[j], ni);
    }
    end = clock();
    double time=(double)(end-start)*1000/CLOCKS_PER_SEC;

    G1 v2, f2[N], y2[N][N];
    Big oi2[N], ni2[N], E2[N];
    for(int i = 0; i < N; i++) {
        pfc.random(oi2[i]);
        pfc.random(ni2[i]);
    }
    start = clock();
    pfc.hash_and_map(v2, (char*)"asdf");
    for(int i = 0; i < N; i++) {
        E2[i] = pfc.hash_to_group((char*)"asdfqwer");
    }
    for(int j = 0; j < N; j++) {
        pfc.hash_and_map(f2[j], (char*)"asdfi");
    }
    G1 v_tmp[N];
    for(int i = 0; i < N; i++) {
        G1 tmp1, tmp2, tmp3[N][N];
        tmp1 = si10 + pfc.mult(si11, E2[i]);
        tmp2 = tmp1 + pfc.mult(v_tmp[i], oi2[i]);
        for(int j = 0; j < N; j++) {
            pfc.mult(tmp3[j][i], ni2[i]);
            y2[j][i] = tmp2 + tmp3[j][i];
        }
    }
    end = clock();
    time= time + (double)(end-start)*1000/CLOCKS_PER_SEC;
    return time;
}

int main() {
    cout<<ini_step1();
}