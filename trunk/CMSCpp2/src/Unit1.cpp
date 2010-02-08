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
#include <algorithm>
#include <iterator>
#include <iterator>
#include <cms/math/Interpolation.h>
#include <cms/math/Searcher.h>
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
    using namespace cms::math;
    double_vector_ptr a(new double_vector);
    double_vector_ptr b(new double_vector);
    a->push_back(1);
    a->push_back(2);
    a->push_back(3);
    a->push_back(4);

    b->push_back(4);
    b->push_back(5);
    b->push_back(6);
    b->push_back(9);
    /*java::lang::System::vectorcopy(a, 1, b, 1, 2);
       foreach(double &v, *b) {
       cout << v << endl;
       }; */


    Interpolation i(a, b);
    cout << i.interpolate(3.5, Linear) << endl;
    //cout << Searcher::leftNearSequentialSearch(a, 3.1) << endl;
    //int_vector_ptr r = Searcher::leftNearSequentialSearchAll(a, 3.1);
    //cout << (*r)[0] << endl;
    //cout << (*r)[1] << endl;

    getch();
    return 0;
}

//---------------------------------------------------------------------------

