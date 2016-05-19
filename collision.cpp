//
// Created by max on 16-5-9.
//

#include <iostream>
#include <cstring>
#include <bitset>
#include "big.h"

#define STRLEN 30
#define BE 256
#define AF 256
#define LEN 20

char* s = (char*) "ejzgylvjzhpeynphxnnlhgjbdkzgls";
char alp[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

void rand_str(char* str,int len)
{
    int i;
    for(i = 0; i < len; ++i)
        str[i] = 'a' + rand()%26;
    str[i] = '\0';
}

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

void str_to_bit(char value[], bitset<LEN> &b)
{
    int char_num = LEN / 8;
    int char_mod = LEN % 8;
    for(int i = 0; i < char_num; ++i)
    {

    }
}

void 

int main()
{
    srand((int)time(0));
    //char* s = (char*) "ejzgylvjzhpeynphxnnlhgjbdkzgls";
    //char* s= new char[STRLEN+1];    //ejzgylvjzhpeynphxnnlhgjbdkzgls
    //rand_str(s, STRLEN);
    //cout<< s << endl;
    char* front[BE];
    for(int i = 0; i < BE; ++i)
    {
        front[i] = new char[STRLEN+1];
        strcpy(front[i], s);
    }
    bitset<8> b[BE];
    for(int i = 0; i < BE; ++i)
    {
        b[i] = i;
        unsigned long long int a = b[i].to_ullong();
        //cout<< (char)a << endl;
        char c[1];
        c[0] = (char)a;
        strcat(front[i], c);
        //cout<< front[i] << endl;
    }
    char value[BE][20];

    for(int i = 0; i < BE; ++i)
    {
        sha_1(value[i], front[i], STRLEN+1);
        b[i] = (int) value[i][0];
        cout<< b[i] << " " << i << endl;
    }

    for(int i = 0; i < 256; ++i)
    {
        for(int j = 1; j < 256; ++j)
        {
            string bi = b[i].to_string();
            string bj = b[j].to_string();
            if(i == j) continue;
            if(bi.compare(bj) == 0)
            {
                cout<< "collision " << i << " " << j << endl;
            }
        }
    }
}