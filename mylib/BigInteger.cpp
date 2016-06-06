#include "BigInteger.hh"
#include <sstream>
#include <list>

#define _FORTIFY_SOURCE
using namespace std;

#define absval(num) (num-'0')

BigInteger::BigInteger() {
    ll_val=0;
    str_val="0";
    islarge=false;
}

BigInteger::BigInteger(const int64_t val) {
    ll_val=val;
    std::stringstream oss;
    oss<<val;
    str_val=oss.str();
    islarge=false;
}
BigInteger::BigInteger(const string &val) {
    char **nptr=NULL;
    errno=0;
    ll_val=strtoll(val.c_str(), nptr, 0);
    if(nptr != NULL|| errno==EINVAL) {
        cout<<"Invalid value passed"<<endl;
        exit(1);
    }
    if(errno==ERANGE) {
        ll_val=-1;
        islarge=true;
    }
    str_val=val;
}
BigInteger::BigInteger(BigInteger &val) {
    str_val=val.str_val;
    ll_val=val.ll_val;
    islarge=val.islarge;
}
BigInteger &BigInteger::operator=(BigInteger &bi_assign) {
    this->ll_val=bi_assign.ll_val;
    this->islarge=bi_assign.islarge;
    this->str_val=bi_assign.str_val;
    return *this;
}
BigInteger &BigInteger::operator=(const string &s_assign) {
    char **nptr=NULL;
    errno=0;
    this->ll_val=strtoll(s_assign.c_str(), nptr, 0);
    if(nptr != NULL || errno==EINVAL) {
        cout<<"Invalid value passed"<<endl;
        exit(1);
    }
    if(errno==ERANGE) {
        this->ll_val=-1;
        this->islarge=true;
    }
    else this->islarge=false;
    this->str_val=s_assign;
    return *this;
}

BigInteger &BigInteger::operator=(const int64_t &ll_assign) {
    this->ll_val=ll_assign;
    this->islarge=false;
    this->str_val=lltostr(ll_assign);
    return *this;
}

string BigInteger::lltostr(const int64_t &conv) {
    std::stringstream oss;
    oss<<conv;
    return oss.str();
}

BigInteger &BigInteger::operator+(BigInteger &bi_add) {
    if(this->str_val[0]=='-' || bi_add.str_val[0]=='-') {
        *this=*this - bi_add;
        return *this;
    }
    if(this->islarge == false && bi_add.islarge == false) {
        int64_t sum=this->ll_val+bi_add.ll_val;
        if(sum-bi_add.ll_val == this->ll_val) {
            this->ll_val=sum;
            this->str_val=lltostr(sum);
            return *this;
        }
    }
    int itd=this->str_val.size()-1;
    int its=bi_add.str_val.size()-1;
    int carry=0;
    const char *sstr=bi_add.str_val.c_str();
    const char *dstr=this->str_val.c_str();
    list<char> outnum;
    for(;itd>=0 && its>=0;) {
        int sumdigit=(absval(sstr[its--])+absval(dstr[itd--])+carry);
        carry=0;
        if(sumdigit>9) {
            carry=1;
            outnum.push_front((sumdigit-10+'0'));
        }
        else 
            outnum.push_front((sumdigit+'0'));
    }
    while(itd>=0) {
        int sumdigit=(absval(dstr[itd--])+carry);
        carry=0;
        if(sumdigit>9) {
            carry=1;
            outnum.push_front((sumdigit-10+'0'));
        }
        else 
            outnum.push_front((sumdigit+'0'));
    }
    while(its>=0) {
        int sumdigit=(absval(sstr[its--])+carry);
        carry=0;
        if(sumdigit>9) {
            carry=1;
            outnum.push_front((sumdigit-10+'0'));
        }
        else 
            outnum.push_front((sumdigit+'0'));
    }
    if(carry)
        outnum.push_front('1');
    string out;
    for(list<char>::iterator it=outnum.begin();it!=outnum.end();it++)
        out+=*it;
    this->str_val=out;
    return *this;
}
BigInteger &BigInteger::operator+(const string &s_add) {
    BigInteger b_add(s_add);
    *this=*this+b_add;
    return *this;
}
BigInteger &BigInteger::operator+(const int64_t &ll_add) {
    BigInteger b_add(ll_add);
    *this=*this+b_add;
    return *this;
}

BigInteger &BigInteger::operator-(BigInteger &bi_add) {
    this->ll_val=bi_add.ll_val;
    this->islarge=bi_add.islarge;
    this->str_val=bi_add.str_val;
    return *this;
}
BigInteger &BigInteger::operator-(const string &s_add) {
    char **nptr=NULL;
    this->ll_val=strtoll(s_add.c_str(), nptr, 0);
    if(nptr != NULL) {
        cout<<"Invalid value passed"<<endl;
        exit(1);
    }
    if(errno==ERANGE) {
        this->ll_val=-1;
        this->islarge=true;
    }
    this->str_val=s_add;
    return *this;
}
BigInteger &BigInteger::operator-(const int64_t &ll_add) {
    this->ll_val=ll_add;
    this->islarge=false;
    std::stringstream oss;
    oss<<ll_add;
    this->str_val=oss.str();
    return *this;
}
const char* BigInteger::tostring() {
    return str_val.c_str();
}
