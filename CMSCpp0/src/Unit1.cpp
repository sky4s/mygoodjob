//---------------------------------------------------------------------------
#pragma hdrstop
#include <vcl.h>
#include <conio.h>
#include "cms/colorspace/independ.h"
#include "java/lang.h"
#include <iostream>

//---------------------------------------------------------------------------
#pragma argsused
int main(int argc, char *argv[])
{
    using cms::colorspace::CIExyY;
    using namespace std;
    using java::lang::Math;
    //using namespace cms;
    //CIExyY xyY;
    //cout << xyY.isNull();
    cout << Math::sqrt(3);
    getch();
    return 0;
}

//---------------------------------------------------------------------------

