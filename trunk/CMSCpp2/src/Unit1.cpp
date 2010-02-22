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
//#include <jama/jama_svd.h>
#include <math/interpolation.h>
//#include <boost/assign/std/vector.hpp>
//#include <boost/assign/std/list.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

//---------------------------------------------------------------------------


int lut()
{
    using namespace math;
    using namespace std;
    double a[] = { 1, 2, 3, 4, 5, 6 };
    double b[] = { 2, 4, 5, 6, 8, 10 };

    double_vector_ptr key(new double_vector(a, a + 6));
    double_vector_ptr val(new double_vector(b, b + 6));
    Interpolation1DLUT lut(key, val);
    //cout << lut.getValue(3) << endl;
    cout << lut.getValue(3.5) << endl;
    //cout << lut.getValue(4) << endl;
}


int regress()
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
	    //(*XYZ)[x][y] = pow((*rgb)[x][y] * 10, 1.2);
	    (*XYZ)[x][y] = (*rgb)[x][y] * 10;
	}
    }
    //cout << *rgb << endl;
    //cout << *XYZ << endl;
    /*SVDLib svd(rgb);
       double2D_ptr U = svd.getU();
       double2D_ptr sv = DoubleArray::diagonal(svd.getSingularValues());
       double2D_ptr V = DoubleArray::transpose(svd.getV());
       cout << *DoubleArray::times(DoubleArray::times(U, sv), V) << endl; */

    Polynomial::COEF_3 coefsArray[] = {
    Polynomial::COEF_3::BY_3, Polynomial::COEF_3::BY_3C,
	    Polynomial::COEF_3::BY_6, Polynomial::COEF_3::BY_6C};
    foreach(const Polynomial::COEF_3 & coef, coefsArray) {
	PolynomialRegression regression(rgb, XYZ, coef);

	regression.regress();
	double2D_ptr input(new double2D(1, 3));
	(*input)[0][0] = 105;
	(*input)[0][1] = 106;
	(*input)[0][2] = 107;
	double2D_ptr d = regression.getPredict(input);
	cout << *d << endl;
	cout << *regression.getCoefs() << endl;
    }

}

//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char *argv[])
{
    //regress();
    //lut();
    getch();
}

