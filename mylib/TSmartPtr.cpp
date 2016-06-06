#include <iostream>
#include <TSmartPtr.hh>

using namespace std;
int main(int argc,char *argv[]) {

    int *ip=NULL;
    ip=new int(10);
    {
    SPtr<int> sp(new int(50));
    cout<<sp.getprintable();
    cout<<*sp<<endl;
    sp=ip;
    cout<<*ip<<"("<<ip<<")"<<endl;
    cout<<sp.getprintable();
    cout<<*sp<<endl;
    }
    return 0;
}
