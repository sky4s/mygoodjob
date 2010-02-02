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
//---------------------------------------------------------------------------


void f(double_vector_ptr a)
{

};

#pragma argsused
int main(int argc, char *argv[])
{
    using namespace Dep;
    using namespace std;
    RGBColor r(1, 2, 3);
    cout << r.R << endl;
    cout << r.getObjectID() << endl;

    RGBColor a(r);
    cout << a.R << endl;
    cout << a.getObjectID() << endl;
    getch();
    return 0;
}

//---------------------------------------------------------------------------

