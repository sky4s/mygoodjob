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


#pragma argsused
int main(int argc, char *argv[])
{
    using namespace Dep;
    using namespace std;
    bptr < RGBColor > b(new RGBColor);
    typedef int int10[10];
    int10 dd;
    //typedef boost::shared_array < int >barray;
    //typedef boost::shared_ptr < int >TestPtr;



    foreach(const Channel & c, *Channel::RGBChannel) {
	cout << *(c.toString()) << endl;
    };

    typedef boost::array < int, 4 > Array4;
    Array4 s = { 1, 2, 3, 4 };
    for (Array4::iterator p = s.begin(); p != s.end(); ++p) {
	cout << *p << endl;
    }
    foreach(int i, s) {
	cout << i << endl;
    }
    int a[] = { 1, 2, 3, 4 };
    for (int x = 0; x < 4; x++) {
	cout << a[x] << endl;
    }

    foreach(int i, a) {
	cout << i << endl;
    }



    getch();
    return 0;
}

//---------------------------------------------------------------------------

