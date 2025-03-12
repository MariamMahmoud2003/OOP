#include <iostream>
#include "main.h"
using namespace std;
int main() {
    cout<<"Please enter value to choose which operation you want from 1 to 12 \n";
    int num;
    cin>>num;
    if (num==1) {
        //test1 validity
        BigReal n("15.3512.5");
        cout << n << '\n'; //invalid
    }
//--------------------------------------------------------------------
    else if (num==2) {
        //test2 + (same signs)
        BigReal n1("11.9000000000000000000000000000000001");
        BigReal n2("2333333333339.1134322222222292");
        BigReal n3 = n1 + n2;
        cout << n3 << '\n';
        BigReal n4(0.9);
        n3 = n3 + n4;
    }
//---------------------------------------------------------------------
    else if (num==3) {
        //test 3 + (different signs = minus op.)
        BigReal m1("-1123"), m2("1877");
        BigReal m3 = m1 + m2;
        cout << m3 << '\n';
    }
//----------------------------------------------------------------------
    else if (num==4) {
        //test4 +(both are negative)
        BigReal b1("-444.1"), b2("-887.6"), b3;
        b3 = b1 + b2;
        cout << b3 << '\n';
    }
//----------------------------------------------------------------------
    else if (num==5) {
        //test5 size
        BigReal bi("44.00999987");
        cout << bi.size() << '\n';
    }
//-----------------------------------------------------------------------
    else if (num==6) {
        //test 6 sign
        BigReal s1("-66.8"), s2("88.99");
        cout << s1.sign() << '\n';
        cout << s2.sign() << '\n';
    }
//-----------------------------------------------------------------------
    else if (num==7) {
        //test 7 <
        BigReal b("3.0"), s("3.3");
        if (b < s)
            cout << s << '\n';
    }
//-------------------------------------------------------------------------
    else if (num==8) {
        //test8 - (same signs)
        BigReal x1("-11.9000000000000000000000000000000001");
        BigReal x2("-2333333333339.1134322222222292");
        BigReal x3 = x1 - x2;
        cout << x3 << '\n';
        BigReal x4(0.9);
        x3 = x3 + x4;
    }
//---------------------------------------------------------------------
    else if (num==9) {
        //test 9 - (different signs )
        BigReal y1("-1123"), y2("1877");
        BigReal y3 = y1 - y2;
        cout << y3 << '\n';
    }
//----------------------------------------------------------------------
    else if (num==10) {
        //test10 - (both are negative)
        BigReal w1("-444.1"), w2("-887.6"), w3;
        w3 = w1 - w2;
        cout << w3 << '\n';
    }
//----------------------------------------------------------------------
    else if (num==11) {
        //test 11 >
        BigReal j("6666666.01"), k("34.7");
        if (j > k)
            cout << j << '\n';
    }
//----------------------------------------------------------------------
    else if (num==12) {
        //test 12 ==
        BigReal z("998.4"), q("998.4");
        if (z == q) {
            cout << "equal\n";
        }
    }
}