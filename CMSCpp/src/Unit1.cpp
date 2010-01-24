//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <cms/colorspace/independ.h>
#include <cms/colorspace/colorspace.h>
#include <java/lang.h>
#include <iostreamg>
#include <conio.h>
#include <boost/shared_ptr.hpp>
#include <vector>


//---------------------------------------------------------------------------

//typedef std::vector < double >vector_double;
double *get()
{
    double a[] = { 1, 2, 3 };
    return a;
};

#pragma argsused
int main(int argc, char *argv[])
{
    using namespace cms::colorspace;
    using namespace java::lang;
    using namespace std;
    //CIEXYZ XYZ;
    //double *a = get();

    getch();
    return 0;
}

//---------------------------------------------------------------------------

