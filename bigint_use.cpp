#include<BigInteger.hh>

int main() {
    BigInteger b1(1000);
    BigInteger b2("10000000");
    BigInteger b3(b1);

    cout<<"b1:"<<b1.tostring()<<endl;
    cout<<"b2:"<<b2.tostring()<<endl;
    cout<<"b3:"<<b3.tostring()<<endl;
    b3=b2;
    cout<<"b3(assigned BigInteger b1):"<<b3.tostring()<<endl;
    b2=5000;
    cout<<"b2(assigned intval):"<<b2.tostring()<<endl;
    b2=b1+b2;
    cout<<"b2(after sum):"<<b2.tostring()<<endl;
    b1="999999999999999999999999999999999999";
    cout<<"b1(assigned large string):"<<b1.tostring()<<endl;
    b1=b1+1;
    cout<<"b1(after adding uint64_t):"<<b1.tostring()<<endl;
    return 0;
}
