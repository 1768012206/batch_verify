//
// Created by max on 16-5-18.
//
#include <iostream>
#include <vector>
#include <cstring>
#include <bitset>
#include "big.h"

#define HASH_LEN 20 //sha-1 hash value 160bit
#define SELECT_LEN 8    //the selected length(bit) of hash value
#define HASH_MAX 10000 //the number of hash values
#define FIR_LEN //first part of hash input length

char alp[26];   //alphabet
char* s = (char*) "ikkdtabyzhmknmwbwbkfrvwvttjvqd"; //first part of hash input
char val[HASH_MAX][20]; //restore hash value

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

void sort(vector<char> data, vector<char> target, int num)
{
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

        //cout<< ss << endl;
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
    for(int i = 0; i < 26; ++i)
    {
        alp[i] = (char) ('a' + i);
    }


}