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
#include <math/Interpolation.h>
#include <math/Searcher.h>
//#include <boost/multi_array.hpp>
#include <jama/jama_svd.h>
#include <math/doublearray.h>
#include <cmath>
//---------------------------------------------------------------------------
using namespace std;
using namespace TNT;
using namespace math;


#pragma argsused
int main(int argc, char *argv[])
{

    double a[] = { 1, 2, 3, 4, 5, 6 };
    double2D_ptr b(new double2D(2, 3, a));
    //double1D_ptr c = DoubleArray::getDouble1D(b, 1);
    double1D_ptr c = DoubleArray::getDouble1DCopy(b, 1);    
    cout << *b << endl;
    (*c)[0] = 0;
    cout << *b << endl;

    getch();
}

//---------------------------------------------------------------------------

