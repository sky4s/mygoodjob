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

void modifed(float_array a)
{
    a[0] = 1;
    a[1] = 2;
};

#pragma argsused
int main(int argc, char *argv[])
{

    float_array a(new float[3]);
    for (int x = 0; x != 3; x++) {
	cout << a[x] << endl;
    };
    modifed(a);
    for (int x = 0; x != 3; x++) {
	cout << a[x] << endl;
    };
    getch();
}

//---------------------------------------------------------------------------

