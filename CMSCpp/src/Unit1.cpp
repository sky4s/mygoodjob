//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <cms/colorspace/independ.h>
#include <cms/colorspace/depend.h>
#include <cms/colorspace/colorspace.h>
#include <cms/measure/_MeasureWindow.h>
#include <java/lang.h>
#include <iostreamg>
#include <conio.h>
#include <boost/shared_ptr.hpp>
#include <vector>


//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char *argv[])
{
    MeasureWindow = new TMeasureWindow(NULL);
    MeasureWindow->Visible = true;
    getch();
    return 0;
}

//---------------------------------------------------------------------------

