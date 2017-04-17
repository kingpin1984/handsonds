#ifndef __BIGINT_H
#define __BIGINT_H

#include<iostream>
#include<unistd.h>
#include<string>
//#include<inttypes.h>
#include<errno.h>
#include<cstdlib>

#define int64_t long long

using namespace std;

class BigInteger {
    protected:
        int64_t ll_val;
        string str_val;
        bool islarge;
    public:
        BigInteger();
        BigInteger(const int64_t val);
        BigInteger(const string &val);
        BigInteger(BigInteger &val);
        ~BigInteger(){ };
        BigInteger& operator +(BigInteger &bi_add);
        //BigInteger& operator +(const int64_t &ll_add);
        friend BigInteger &operator +(const int64_t &ll_add, BigInteger &bi);
        BigInteger& operator +(const string &s_add);
        BigInteger& operator -(BigInteger &bi_add);
        BigInteger& operator -(const int64_t &ll_add);
        BigInteger& operator -(const string &s_add);
        BigInteger& operator =(const int64_t &ll_assign);
        BigInteger& operator =(BigInteger &bi_assign);
        BigInteger& operator =(const string &s_assign);

        const char *tostring();
    private:
        string lltostr(const int64_t &addval);
};

#endif
