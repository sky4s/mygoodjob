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


#pragma argsused
int main(int argc, char *argv[])
{
    using namespace Dep;
    using namespace std;

    foreach(const Channel & c, *Channel::RGBChannel) {
	cout << *(c.toString()) << endl;
    };
    RGB_ptr r(new RGBColor);
    Object_ptr o(new RGBColor);


    getch();
    return 0;
}

//---------------------------------------------------------------------------

