//
// Created by max on 16-5-18.
//
#include <iostream>
#include <vector>
#include <cstring>
#include <bitset>
#include "big.h"

#define HASH_LEN 20 //sha-1 hash value 160bit
#define SELECT_LEN 12  //the selected length(bit) of hash value to find collision
#define HASH_MAX 1000000 //the max number of hash values
#define FIR_LEN 30  //first part of hash input length
#define MAX_FIND_LEN 30 //max length to find collision

char* s = (char*) "ikkdtauyzhmknmwbwbjfrvwvttjvqd"; //first part of hash input
//char val[HASH_MAX][20]; //restore hash value
bitset<SELECT_LEN> bs[HASH_MAX];
int bit_num = 0;
int bit_num_now = 0;
int find_if = -1;   // -1 means haven't find collision

void sha_1(char* value, char* input, int len)
{
    sha sh;
    shs_init(&sh);
    for(int i = 0; i < len; ++i)
    {
        shs_process(&sh, input[i]);
    }
    shs_hash(&sh, value);
}

void val_to_bit(char value[], bitset<SELECT_LEN> &b)
{
    int char_num = SELECT_LEN / 8;
    int char_mod = SELECT_LEN % 8;
    bitset<8> tmp;
    string str;
    for(int i = 0; i < char_num + 1; ++i)
    {
        tmp = (int) value[i];
        str = str + tmp.to_string();
    }
    bitset<SELECT_LEN> tmp2(str, 0, SELECT_LEN);
    b = tmp2;
}

int find_collsion(int num, bitset<SELECT_LEN> b)
{
    string bi = b.to_string();
    //cout<<bi<<endl;
    for(int j = 0; j < num; ++j)
    {
        string bj = bs[j].to_string();
        //cout<<bj<<endl;
        if(bi.compare(bj) == 0)
        {
            cout<< "collision " << j << " " << num << endl;
            //cout<< bi << endl;
            //cout<< bj << endl;
            return num;
        }
    }
    return -1;
}

void sort(vector<char> data, vector<char> target, int num)
{
    if(find_if != -1) return;
    if(target.size() == num)
    {
        char* ss = new char[FIR_LEN+num];
        strcpy(ss, s);
        char cc[num];
        for(int i = 0; i < num; ++i)
        {
            cc[i] = target[i];
        }
        strcat(ss, cc);
        ss[FIR_LEN+num] = '\0';
        //cout<< ss << endl;
        char val[20];
        sha_1(val, ss, FIR_LEN+num);
        delete[] ss;
        val_to_bit(val, bs[bit_num]);
        bit_num_now = bit_num;
        bit_num++;
        find_if = find_collsion(bit_num_now, bs[bit_num_now]);
        return;
    }
    for(int i = 0; i < data.size(); ++i)
    {
        vector<char> newdata(data);
        vector<char> newtarget(target);
        newtarget.push_back(newdata[i]);
        sort(newdata, newtarget, num);
    }
}

int main()
{
    clock_t start, end;
    vector<char> alp;   //alphabet
    bitset<8> byt[256];
    for(int i = 1; i < 256; ++i)
    {
        byt[i] = i;
        unsigned long long int a = byt[i].to_ullong();
        alp.push_back((char)a);
    }
    /*for(int i = 0; i < 26; ++i)
    {
        alp.push_back((char) ('a' + i));
    }*/
    start = clock();
    for (int i = 0; i < MAX_FIND_LEN; ++i) {
        vector<char> b;
        sort(alp, b, i);
        if (find_if != -1) break;
    }
    end = clock();
    double time=(double)(end-start)*1000/CLOCKS_PER_SEC;
    cout<<"time:"<<time<<endl;
    return 0;
}