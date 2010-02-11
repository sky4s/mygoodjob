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
#include <math/regression.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <jama/jama_svd.h>
//---------------------------------------------------------------------------



#pragma argsused
int main(int argc, char *argv[])
{
    using namespace std;
    using namespace TNT;
    using namespace math;
    using namespace JAMA;



    int count = 10;
    double2D_ptr rgb(new double2D(count, 3));
    double2D_ptr XYZ(new double2D(count, 3));

    for (int x = 0; x < count; x++) {
	for (int y = 0; y < 3; y++) {
	    (*rgb)[x][y] = x + 100 + y;
	    (*XYZ)[x][y] = (*rgb)[x][y] * 10;
	}
    }
    Polynomial::COEF_3 coefsArray[] = {
	Polynomial::COEF_3::BY_3, Polynomial::COEF_3::BY_3C,
	    /*Polynomial::COEF_3::BY_6, Polynomial::COEF_3::BY_6C */ };
    foreach(const Polynomial::COEF_3 & coef, coefsArray) {
	PolynomialRegression regression(rgb, XYZ, coef);

	regression.regress();
	double2D_ptr input(new double2D(1, 3));
	(*input)[0][0] = 150;
	(*input)[0][1] = 151;
	(*input)[0][2] = 152;
	double2D_ptr d =
	    regression.getPredict(input, regression.getCoefs());
	cout << *d << endl;
	//cout << *regression.getCoefs() << endl;
    }
    getch();
}

//---------------------------------------------------------------------------

