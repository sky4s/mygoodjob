//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <conio.h>
#include <java/lang.h>
#include <boost/foreach.hpp>
#include <cstdio>
#include <iostream>
#include <cms/colorspace/rgb.h>
#include <vector>
#include <cstdarg>
#include <boost/array.hpp>
//---------------------------------------------------------------------------
using namespace std;
vector < int >getIntVec()
{
    vector < int >vec;
    vec.push_back(3);
    vec.push_back(4);
    cout << &vec << endl;
    foreach(int &i, vec) {
	cout << &i << endl;
    }

    return vec;
}

vector < jObject > getObjectVec()
{
    vector < jObject > vec;
    jObject a, b;
    vec.push_back(a);
    vec.push_back(b);
    foreach(jObject & i, vec) {
	cout << &i << endl;
    }
    return vec;
}
boost::array < int, 2 > getArray()
{
    boost::array < int, 2 > a;
    cout << &a << endl;
    foreach(int &i, a) {
	cout << &i << endl;
    }
    return a;

};

#pragma argsused
int main(int argc, char *argv[])
{
    using namespace Dep;
    using namespace std;
    bptr < RGBColor > b(new RGBColor);
    typedef int int10[10];
    int10 dd;
    boost::shared_array < int >sa(new int[3]);

    /*vector < int >v = getIntVec();
       cout << &v << endl;
       foreach(int &i, v) {
       cout << &i << endl;
       } */

    /*vector < jObject > v2 = getObjectVec();
       foreach(jObject & i, v2) {
       cout << &i << endl;
       } */

    boost::array < int, 2 > a = getArray();
    cout << &a << endl;
    foreach(int &i, a) {
	cout << &i << endl;
    }
    getch();
    return 0;
}

//---------------------------------------------------------------------------

