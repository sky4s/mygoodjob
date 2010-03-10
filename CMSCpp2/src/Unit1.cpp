//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <conio.h>


#include <cmath>
#include <sstream>
#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <cstdarg>
#include <algorithm>
#include <iterator>

#include <boost/foreach.hpp>
#include <boost/array.hpp>

#include <jama/jama_svd.h>

#include <math/Searcher.h>
#include <math/doublearray.h>
#include <math/regression.h>
#include <math/interpolation.h>
#include <java/lang.h>
#include <cms/colorspace/rgb.h>
#include <cms/colorformat/excelfiletester.h>
#include <cms/colorformat/excelfile.h>
#include <cms/colorformat/dgcodefile.h>
//#include <policybased.h>
#include <locale>
#include <cms/lcd/calibrate/rgbvectorop.h>
#include <cms/lcd/calibrate/lcdcalibrator.h>
#include <cms/util/rgbarray.h>

//---------------------------------------------------------------------------


void excel()
{
    using namespace cms::colorformat;
    //string_ptr filename(new string("a.xls"));

    string_vector_ptr fieldsNames(new string_vector());
    fieldsNames->push_back("a");
    fieldsNames->push_back("b");

    ExcelFileDB db("a.xls", Create);

    //string_ptr tbname(new string("tb"));

    bool newfile = true;

    if (newfile) {
	db.createTable("tb", fieldsNames);
	string_vector_ptr values(new string_vector());
	values->push_back("11");
	values->push_back("22");
	db.insert(fieldsNames, values);
    } else {
    };


    //db.close();
}

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

void inverse()
{
    using namespace math;
    double d[] = { 1, 6, 2, 1, 7, 3, 7, 9, 4 };
    double2D_ptr m(new double2D(3, 3, d));
    double2D_ptr inv = DoubleArray::inverse(m);
    cout << *DoubleArray::toString(m) << endl;
    cout << *DoubleArray::toString(inv) << endl;
    //cout << *DoubleArray::toString(DoubleArray::identity(3,4)) << endl;

};


void wstringtest()
{
    char *test = "我是測試字串";
    wchar_t *wchar = new wchar_t[260];
    size_t ret = mbstowcs(wchar, test, 13);
    if (ret != NULL) {
	cout << "success" << endl;
	//wcout << wchar << endl;
	//wcout << L"我我我我" << endl;
	wcout << L"some english string";

    } else {
	cout << "Error" << endl;
    }
    delete[]wchar;

}

void stringfunc(string a)
{
    cout << &a << ": " << a << endl;
}

void stringfuncref(string & a)
{
    cout << &a << ": " << a << endl;
}

void stringfuncpointer(string * a)
{
    cout << a << ": " << *a << endl;
}



void stringtest()
{
    string a = "abc";
    cout << &a << endl;
    stringfunc(a);
    stringfuncref(a);
    stringfuncpointer(&a);

}

//---------------------------------------------------------------------------

void rgbVectorOp()
{
    using namespace cms::util;
    using namespace cms::lcd::calibrate;
    RGB_vector_ptr linearVector = RGBVector::getLinearRGBVector(256);
    bptr < MinusOp > minus1(new MinusOp(1));
    bptr < MinusOp > minus3(new MinusOp(1));
    bptr < LinearOp > linear(new LinearOp());
    minus1->setSource(linearVector);
    minus1->addOp(minus3);
    minus1->addOp(linear);
    RGB_vector_ptr result = minus1->createInstance();
    //cout << *RGBVector::toString(linearVector);
    cout << *RGBVector::toString(result);
};

void sizeCompare()
{
    double darray[4];
    double *dpointer = new double[4];
    double_array dvalues(dpointer);
    double_vector dvector(4);
    using namespace std;

    cout << "array: " << sizeof(darray) << endl;
    cout << "double: " << sizeof(double) << endl;
    cout << "double*: " << sizeof(dpointer) << endl;

    cout << "bptr: " << sizeof(dvalues) << endl;
    //cout << "*bptr: " << sizeof(*dvalues) << endl;

    cout << "vector: " << sizeof(dvector) << endl;
    cout << "vec capacity:" << dvector.capacity() << endl;

    //cout << dvector.size() << endl;


}

class A {
};

void gammaCurve()
{
    using namespace cms::lcd::calibrate;
    using namespace math;
    int n = 256;
    double_array curve = LCDCalibrator::getGammaCurve(2.2, n);
    cout << *DoubleArray::toString(curve, n);
};


void dgcodefile()
{
    using namespace cms::colorformat;
    //string_ptr filename(new string("test.xls"));
    DGCodeFile dgcode("test.xls", 257);
    //dgcode.setProperty("a", "b");
    //dgcode.setProperty("b", "bbb");

};



#pragma argsused
int main(int argc, char *argv[])
{
    wstringtest();
    //stringtest();


    /*string s;
       cout << ("" == s) << endl; */

    //regress();
    //lut();
    //excel();
    //inverse();
    //rgbVectorOp();
    //sizeCompare();
    //gammaCurve();
    //header();
    //dgcodefile();
    getch();
}

