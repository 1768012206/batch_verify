//
// Created by max on 17-2-24.
//

#include <iostream>
#include <ctime>

#define MR_PAIRING_SSP
#define AES_SECURITY 128

#define N 100

#include "pairing_1.h"
using namespace std;
PFC pfc(AES_SECURITY);

double ini_step1_vehicle() {
    clock_t start, end;
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
    G1 tmp1, tmp2;
    tmp1 = si10 + pfc.mult(si11, E);
    tmp2 = tmp1 + pfc.mult(v, oi);
    for(int j = 0; j < N; j++) {
        pfc.hash_and_map(f[j], (char*)"asdfi");
        y[j] = tmp2 + pfc.mult(f[j], ni);
    }
    end = clock();
    double time=(double)(end-start)*1000/CLOCKS_PER_SEC;
    return time;
}

double ini_step1_manager() {
    clock_t start, end;
    double time = 0;
    G1 v, f[N], y[N][N], s0[N], s1[N], ff[N];
    Big o[N], n[N], E[N];
    for(int i = 0; i < N; i++) {
        pfc.random(o[i]);
        pfc.random(n[i]);
        pfc.random(s0[i]);
        pfc.random(s1[i]);
    }
    start = clock();
    pfc.hash_and_map(v, (char*)"asdf");
    for(int i = 0; i < N; i++) {
        E[i] = pfc.hash_to_group((char*)"asdfqwer");
        pfc.hash_and_map(f[i], (char*)"asdf");
    }
    end = clock();
    time = (double)(end-start)*1000/CLOCKS_PER_SEC;
    G1 tmps1[N];
    for(int i = 0; i < N; i++) {
        tmps1[i] = pfc.mult(s1[i], E[i]);
    }
    G1 tmp1, tmp2, tmp3;
    pfc.precomp_for_mult(v);
    for(int i = 0; i < N; i++) {
        pfc.precomp_for_mult(f[i]);
    }
    start = clock();
    for(int i = 0; i < N; i++) {
        tmp1 = s0[i] + tmps1[i];
        tmp2 = tmp1 + pfc.mult(v, o[i]);
        for(int j = 0; j < N; j++) {
            tmp3 = pfc.mult(f[j], n[i]);
            y[j][i] = tmp2 + tmp3;
        }
    }
    end = clock();
    time = time + (double)(end-start)*1000/CLOCKS_PER_SEC;
    return time;
}

double ini_step2() {
    clock_t start, end;
    G1 p0[N], p1[N], gpub, v, b[N], y[N], ai[N], fi;
    pfc.random(gpub);
    pfc.random(v);
    pfc.random(fi);
    for(int i = 0; i < N; i++) {
        pfc.random(b[i]);
        pfc.random(y[i]);
        pfc.random(ai[i]);
    }
    Big El[N];
    start = clock();
    for(int i = 0; i < N; i++) {
        pfc.hash_and_map(p0[i], (char*)"asdf0");
        pfc.hash_and_map(p1[i], (char*)"asdf1");
        El[i] = pfc.hash_to_group((char*)"asasdf");
    }
    G1 tmp0 = ai[0];
    for(int i = 1; i < N; i++) {
        tmp0 = tmp0 + ai[i];
    }
    G1 tmp1 = p0[0] + pfc.mult(p1[0], El[0]), tmp2;
    for(int i = 1; i < N; i++) {
        tmp2 = p0[i] + pfc.mult(p1[i], El[i]);
        tmp1 = tmp1 + tmp2;
    }
    GT pair1 = pfc.pairing(tmp1, gpub);
    G1 tmp3 = b[0];
    for(int i = 1; i < N; i++) {
        tmp3 = tmp3 + b[i];
    }
    GT pair2 = pfc.pairing(v, tmp3);
    GT O = pair1 * pair2;
    G1 tmp4 = y[0];
    for(int i = 1; i < N; i++) {
        tmp4 = tmp4 + y[i];
    }
    GT Li = pfc.pairing(fi, tmp0);
    pfc.pairing(tmp4, gpub);
    GT equ = O * Li;
    end = clock();
    double time=(double)(end-start)*1000/CLOCKS_PER_SEC;
    return time;
}

double join_step1() {
    clock_t start, end;
    Big ni, oi, EI;
    pfc.random(oi);
    pfc.random(ni);
    G1 v, fj[N], sI0, sI1;
    pfc.random(sI0);
    pfc.random(sI1);
    start = clock();
    pfc.hash_and_map(v, (char*)"asdf");
    EI = pfc.hash_to_group((char*)"asdfqer");
    for(int i = 0; i < N; i++) {
        pfc.hash_and_map(fj[i], (char*)"asdfl");
        G1 tmp1 = sI0 + pfc.mult(sI1, EI);
        tmp1 = tmp1 + pfc.mult(v, oi);
        tmp1 = tmp1 + pfc.mult(fj[i], ni);
    }
    end = clock();
    double time=(double)(end-start)*1000/CLOCKS_PER_SEC;
    return time;
}

double join_step2() {
    clock_t start, end;
    G1 pl0, pl1, pi0, pi1, E, al, ai, gpub, bi, bI, v;
    GT O;
    Big El, Ei;
    pfc.random(pi0); pfc.random(pi1); pfc.random(Ei); pfc.random(E); pfc.random(al); pfc.random(ai);
    pfc.random(gpub); pfc.random(bi); pfc.random(bI); pfc.random(v);
    O = pfc.pairing(pl0, pl1);
    start = clock();
    pfc.hash_and_map(pl0, (char*)"asdf0");
    pfc.hash_and_map(pl1, (char*)"asdf1");
    El = pfc.hash_to_group((char*)"asdfqer");
    E = E + al;
    E = E + ai;
    G1 tmp = pl0 + pfc.mult(pl1, Ei);
    tmp = tmp + pi0;
    tmp = tmp + pfc.mult(pi1, Ei);
    GT tmpt = pfc.pairing(tmp, gpub);
    O = O * tmpt;
    G1 tmp2 = bi + bI;
    GT tmpt2 = pfc.pairing(v, tmp2);
    O = O * tmpt2;
    G1 dl = pl0 + pl1;
    dl = dl + pi0;
    for(int i = 0; i < N; i++) {
        G1 ylj = pi0;
    }
    end = clock();
    double time=(double)(end-start)*1000/CLOCKS_PER_SEC;
    return time;
}

int main() {
    //cout<<ini_step1_vehicle()<<endl;
    //cout<<ini_step1_manager();
    //cout<<ini_step2();
    cout<<join_step1();
    //cout<<join_step2();
}