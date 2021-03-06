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
    /*end = clock();
    double time=(double)(end-start)*1000/CLOCKS_PER_SEC;
    pfc.precomp_for_mult(v);
    for(int i = 0; i < N; i++) {
        pfc.precomp_for_mult(f[i]);
    }
    start = clock();*/
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
    G1 tmp1, tmp2, tmp3;
    G1 si10,si11;
    Big oi,ni;
    pfc.random(si10); pfc.random(si11); pfc.random(oi); pfc.random(ni);
    start = clock();
    pfc.hash_and_map(v, (char*)"asdf");
    for(int i = 0; i < N; i++) {
        E[i] = pfc.hash_to_group((char*)"asdfqwer");
        pfc.hash_and_map(f[i], (char*)"asdf");
    }

    tmp1 = si10 + pfc.mult(si11, E[0]);
    tmp2 = tmp1 + pfc.mult(v, oi);
    for(int j = 0; j < N; j++) {
        pfc.hash_and_map(f[j], (char*)"asdfi");
        y[j][0] = tmp2 + pfc.mult(f[j], ni);
    }
    end = clock();
    time = (double)(end-start)*1000/CLOCKS_PER_SEC;
    G1 tmps1[N];
    for(int i = 0; i < N; i++) {
        tmps1[i] = pfc.mult(s1[i], E[i]);
    }

    pfc.precomp_for_mult(v);
    for(int i = 0; i < N; i++) {
        pfc.precomp_for_mult(f[i]);
    }
    start = clock();
    for(int i = 0; i < N/5; i++) {
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
    G1 tmp1 = sI0 + pfc.mult(sI1, EI);
    tmp1 = tmp1 + pfc.mult(v, oi);
    for(int i = 0; i < N; i++) {
        pfc.hash_and_map(fj[i], (char*)"asdfl");
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
    E = E + pfc.mult(al, -1);
    E = E + ai;
    G1 tmp = pfc.mult(pl0, -1) + pfc.mult(pl1, Ei);
    tmp = tmp + pi0;
    tmp = tmp + pfc.mult(pi1, Ei);
    /*GT tmpt = pfc.pairing(tmp, gpub);
    O = O * tmpt;
    G1 tmp2 = pfc.mult(bi, -1) + bI;
    GT tmpt2 = pfc.pairing(v, tmp2);
    O = O * tmpt2;*/
    G1 tmp2 = pfc.mult(bi, -1) + bI;
    G1 *mu1[2]={&tmp,&gpub},*mu2[2]={&v,&tmp2};
    GT mul_res=pfc.multi_pairing(2,mu1,mu2);
    O=O*mul_res;
    G1 dl = pl0 + pl1;
    dl = dl + pfc.mult(pi0, -1);
    for(int i = 0; i < N; i++) {
        G1 ylj = pi0;
    }
    end = clock();
    double time=(double)(end-start)*1000/CLOCKS_PER_SEC;
    return time;
}

double leaving_case1() {
    clock_t start, end;
    G1 pl0, pl1, pi0, pi1, al, ai, bl, bi, g, v, E, dl, pI;
    Big El, Ei;
    pfc.random(pi0); pfc.random(pi1); pfc.random(Ei); pfc.random(al); pfc.random(ai); pfc.random(pI);
    pfc.random(v); pfc.random(E); pfc.random(g); pfc.random(bl); pfc.random(bi); pfc.random(dl);
    GT O = pfc.pairing(al, ai);
    start = clock();
    pfc.hash_and_map(pl0, (char*)"asdf0");
    pfc.hash_and_map(pl1, (char*)"asdf1");
    El = pfc.hash_to_group((char*)"asdfwq");
    E = E + al; E = E + ai;
    G1 tmp = pl0 ;//+ pfc.mult(pl1, Ei);
    tmp = tmp + pI;
    tmp = tmp + pfc.mult(pI, Ei);
    /*GT gt1 = pfc.pairing(tmp, g);
    O = O * gt1;
    GT gt2 = pfc.pairing(v, bl + pfc.mult(bi, -1));
    O = O * gt2;*/
    G1 tmp2=bl + bi;
    G1 *mu1[2]={&tmp,&v}, *mu2[2]={&g,&tmp2};
    GT mul_res=pfc.multi_pairing(2,mu1,mu2);
    O=O*mul_res;
    dl = dl + pl0;
    dl = dl + pl1;
    end = clock();
    double time=(double)(end-start)*1000/CLOCKS_PER_SEC;
    return time;
}

double leaving_step1() {
    clock_t start, end;
    G1 C, F, P, S, Pub, tmp;
    Big h, x;
    pfc.random(P); pfc.random(x); pfc.random(Pub); pfc.random(S), pfc.random(F), pfc.random(C);
    pfc.random(x);
    start = clock();
    C = pfc.mult(P, x);
    h = pfc.hash_to_group((char*)"asdf");
    F = pfc.mult(S, h) + pfc.mult(Pub, x);
    C = pfc.mult(P, x);
    h = pfc.hash_to_group((char*)"asdf");
    F = pfc.mult(S, h) + pfc.mult(Pub, x);

    h = pfc.hash_to_group((char*)"asdf");
    pfc.pairing(F, P);
    pfc.hash_and_map(tmp, (char*)"asdf");
    G1 tmp2 = pfc.mult(tmp, h);
    tmp2 = C + tmp2;
    pfc.pairing(tmp2, Pub);
    end = clock();
    double time=(double)(end-start)*1000/CLOCKS_PER_SEC;
    return time;
}

double mode1_step1() {
    clock_t start,end;
    G1 P, C, S, Pub, F;
    Big x, h;
    pfc.random(P); pfc.random(x); pfc.random(Pub); pfc.random(S);
    GT gt=pfc.pairing(S,P), t2;
    start = clock();
    //pfc.hash_to_group((char*)"asdf");
    C = pfc.mult(P, x);
    h = pfc.hash_to_group((char*)"asdf");
    F = pfc.mult(S, h) + pfc.mult(Pub, x);

    pfc.mult(P, x);
    pfc.mult(P, x);
    t2=pfc.power(gt,x);
    pfc.hash_to_aes_key(t2);
    end = clock();
    double time=(double)(end-start)*1000/CLOCKS_PER_SEC;
    return time;
}

double mode2_step1() {
    clock_t start,end;
    G1 P, C, S, Pub, F;
    Big x, h;
    pfc.random(P); pfc.random(x); pfc.random(Pub); pfc.random(S);
    GT gt=pfc.pairing(S,P);
    start = clock();
    //pfc.hash_to_group((char*)"asdf");
    C = pfc.mult(P, x);
    h = pfc.hash_to_group((char*)"asdf");
    F = pfc.mult(S, h) + pfc.mult(Pub, x);

    for(int i=0;i<N;i++) {
        pfc.mult(P, x);
        pfc.mult(P, x);
        GT t2=pfc.power(gt,x);
        pfc.hash_to_aes_key(t2);
    }
    end = clock();
    double time=(double)(end-start)*1000/CLOCKS_PER_SEC;
    return time;
}

double mode1_step2() {
    clock_t start, end;
    G1 d, f, A1, A2;
    pfc.random(d); pfc.random(f); pfc.random(A1); pfc.random(A2);

    G1 F, P, C, Pub, Tmp;
    Big h;
    pfc.random(C); pfc.random(Pub); pfc.random(F); pfc.random(P);
    start = clock();
    //pfc.hash_to_group((char*)"asdf");
    /*GT tmp = pfc.pairing(d, A1);
    GT tmp2 = pfc.pairing(pfc.mult(f, -1), A2);
    GT tmp3 = tmp * tmp2;*/
    G1 fg=pfc.mult(f, -1);
    G1 *mu1[2]={&d,&fg}, *mu2[2]={&A1,&A2};
    GT tmp3=pfc.multi_pairing(2,mu1,mu2);
    pfc.hash_to_aes_key(tmp3);

    h = pfc.hash_to_group((char*)"asdf");
    pfc.pairing(F, P);
    pfc.hash_and_map(Tmp, (char*)"asdf");
    G1 Tmp2 = pfc.mult(Tmp, h);
    Tmp2 = C + Tmp2;
    pfc.pairing(Tmp2, Pub);
    end = clock();
    double time=(double)(end-start)*1000/CLOCKS_PER_SEC;
    return time;
}

double verify() {
    clock_t start, end;
    G1 F, P, C, Pub, tmp;
    Big h;
    pfc.random(C); pfc.random(Pub); pfc.random(F); pfc.random(P);
    start = clock();
    h = pfc.hash_to_group((char*)"asdf");
    pfc.pairing(F, P);
    pfc.hash_and_map(tmp, (char*)"asdf");
    G1 tmp2 = pfc.mult(tmp, h);
    tmp2 = C + tmp2;
    pfc.pairing(tmp2, Pub);
    end = clock();
    double time=(double)(end-start)*1000/CLOCKS_PER_SEC;
    return time;
}

double batch_verify() {
    clock_t start, end;
    G1 F, P, C, Pub, tmp3;
    Big r[N], h;
    pfc.random(C); pfc.random(Pub); pfc.random(F); pfc.random(P);
    for(int i = 0; i < N; i++) {
        pfc.random(r[i]);
    }
    start = clock();
    G1 tmp = pfc.mult(F, r[0]);
    for(int i = 1; i < N; i++) {
        tmp = tmp + pfc.mult(F, r[i]);
    }
    pfc.pairing(tmp, P);
    pfc.hash_and_map(tmp3, (char*)"asdf");
    tmp3 = pfc.mult(tmp3, h);
    G1 tmp4 = pfc.mult(tmp3, r[0]);
    G1 tmp2 = pfc.mult(C, r[0]);
    for(int i = 1; i < N; i++) {
        tmp2 = tmp2 + pfc.mult(C, r[i]);
        tmp4 = pfc.mult(tmp3, r[i]);
    }
    pfc.pairing(tmp2+tmp4, Pub);
    end = clock();
    double time=(double)(end-start)*1000/CLOCKS_PER_SEC;
    return time;
}

double mode3_step2() {
    clock_t start, end;
    G1 d, f, A1, A2;
    pfc.random(d); pfc.random(f); pfc.random(A1); pfc.random(A2);

    G1 F, P, C, Pub, Tmp;
    Big h;
    pfc.random(C); pfc.random(Pub); pfc.random(F); pfc.random(P);
    start = clock();
    pfc.hash_to_group((char*)"asdf");
    /*GT tmp = pfc.pairing(d, A1);
    GT tmp2 = pfc.pairing(pfc.mult(f, -1), A2);
    GT tmp3 = tmp * tmp2;*/
    G1 fg=pfc.mult(f, -1);
    G1 *mu1[2]={&d,&fg}, *mu2[2]={&A1,&A1};
    GT tmp3=pfc.multi_pairing(2,mu1,mu2);
    pfc.hash_to_aes_key(tmp3);

    h = pfc.hash_to_group((char*)"asdf");
    pfc.pairing(F, P);
    pfc.hash_and_map(Tmp, (char*)"asdf");
    G1 Tmp2 = pfc.mult(Tmp, h);
    Tmp2 = C + Tmp2;
    pfc.pairing(Tmp2, Pub);
    end = clock();
    double time=(double)(end-start)*1000/CLOCKS_PER_SEC;
    return time;
}

void rand_str(char* str,int len)
{
    int i;
    for(i=0;i<len;++i)
        str[i]='A'+rand()%26;
    str[i]='\0';
}

double myhash() {
    clock_t start, end;
    G1 f;
    start = clock();
    pfc.hash_and_map(f, (char*)"asdf");
    end = clock();
    double time=(double)(end-start)*1000/CLOCKS_PER_SEC;
    return time;
}

double pair4() {
    clock_t start, end;
    G1 a ,b;
    pfc.random(a); pfc.random(b);
    start = clock();
    pfc.pairing(a, b); pfc.pairing(a, b); pfc.pairing(a, b); pfc.pairing(a, b);
    end = clock();
    double time=(double)(end-start)*1000/CLOCKS_PER_SEC;
    return time;
}

int main() {
    time_t seed;
    time(&seed);
    irand((long)seed);

    /*G1 d, g, a, b, e, f;
    pfc.random(d); pfc.random(g); pfc.random(a); pfc.random(b); pfc.random(e); pfc.random(f);
    GT o = pfc.pairing(a, b);


    //G1 P,Pub,C,S,F;
    //Big h, x;
    //pfc.random(P); pfc.random(x); pfc.random(Pub); pfc.random(S),pfc.random(F);
    clock_t start, end;
    start = clock();
    pfc.pairing(d, g);
    GT l = pfc.pairing(e, f);
    o*l;
    //C = pfc.mult(P, x);
    //h = pfc.hash_to_group((char*)"asdf");
    //F = pfc.mult(S, h) + pfc.mult(Pub, x);
    end = clock();
    double time=(double)(end-start)*1000/CLOCKS_PER_SEC;
    cout<<time;*/
    cout << pair4() << endl;
}