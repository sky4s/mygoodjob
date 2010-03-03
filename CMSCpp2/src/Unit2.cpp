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

//#include <policybased.h>
#include <locale>

#include <cms/colorspace/rgb.h>
#include <cms/colorspace/ciexyz.h>
#include <cms/colorformat/excelfile.h>

#include <cms/lcd/calibrate/rgbvectorop.h>
#include <cms/lcd/calibrate/lcdcalibrator.h>
#include <cms/lcd/calibrate/rgbop.h>
#include <cms/lcd/calibrate/rgbgamma.h>
#include <cms/util/rgbarray.h>
#include <cms/measure/analyzer.h>
#include <cms/measure/meter.h>

//---------------------------------------------------------------------------


void excel()
{
    using namespace cms::colorformat;
    using namespace std;
    //string_ptr filename(new string("a.xls"));

    /*string_vector_ptr fieldsNames(new string_vector());
       fieldsNames->push_back("a");
       fieldsNames->push_back("b"); */
    string_vector_ptr fieldsNames = ExcelFileDB::make(2, "a", "b");

    ExcelFileDB db("a.xls", Create);

    //string_ptr tbname(new string("tb"));

    bool newfile = false;

    if (newfile) {
	db.createTable("tb", fieldsNames);

	db.insert(fieldsNames, ExcelFileDB::make(2, "11", "22"));
	db.insert(fieldsNames, ExcelFileDB::make(2, "33", "44"));
	db.insert(fieldsNames, ExcelFileDB::make(2, "55", "66"));
    } else {
	db.setTableName("tb");
	//db.select("a", 11);
	bptr < DBQuery > query = db.selectAll();
	while (query->hasNext()) {
	    foreach(string & s, *query->nextResult()) {
		cout << s << " ";
	    }
	    cout << endl;
	};

	cout << *query->get(1, 1) << endl;
	//query->set(1, 1, "333");

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
    double d[] = { 0.5767309, 0.1855540, 0.1881852,
	0.2973769, 0.6273491, 0.0752741,
	0.0270343, 0.0706872, 0.9911085
    };
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

void dgcode()
{
    using namespace cms::lcd::calibrate;
    using namespace Dep;
    //using namespace Indep;
    int n = 256;
    Composition_vector_ptr vector(new Composition_vector(n));
    for (int x = 0; x != n; x++) {
	RGB_ptr rgb(new RGBColor(x, x, x));
	RGB_ptr component(new RGBColor(x * .3, x * .6, x * .1));
	XYZ_ptr XYZ(new Indep::CIEXYZ(0, x, 0));
	Composition_ptr composition(new Composition(rgb, component, XYZ));
	(*vector)[x] = composition;
    };
    DGCodeProducer producer(vector);
};

void rgbTry()
{
    using namespace Dep;
    using namespace math;

    RGBColor rgb(RGBColorSpace::unknowRGB,
		 DoubleArray::toDoubleArray(3, 0.25, 0.5, 0.75),
		 MaxValue::Double255);
    cout << *rgb.toString() << endl;
    rgb.quantization(MaxValue::Int8Bit);
    //rgb.changeMaxValue(MaxValue::Int10Bit);
    cout << *rgb.toString() << endl;
};

void doubleArrayTry()
{
    using namespace math;
    double_array a = DoubleArray::toDoubleArray(3, 1.1, 2.1, 3.1);
    cout << *DoubleArray::toString(a, 3) << endl;
    double bb[] = { 4, 5, 6 };
    double_array b = DoubleArray::toDoubleArray(bb, 3);
    cout << *DoubleArray::toString(b, 3) << endl;
};

void mathTry()
{
    using namespace java::lang;
    cout << std::ceil(0.25) << endl;
    cout << std::ceil(0.5) << endl;
    cout << std::ceil(0.9) << endl;
    //cout << std::round(1.0) << endl;
    cout << Math::round(0.5) << endl;
    cout << Math::round(0.4) << endl;
};

void rgbop()
{
    using namespace cms::lcd::calibrate;
    //RGBOp < RGBGamma_ptr > rgbgammaop;
};

class AA {
};
class BB {
};
template < class T > class TA {
  public:
    virtual double get() {
    };

};

template <> double TA < AA >::get()
{
    return 1;
};

template <> double TA < BB >::get()
{
    return 2;
};

class TB:public TA < double > {
  public:
    double get() {
	return 100;
    };
};

void templateTry()
{
    using namespace std;
    TA < AA > aa;
    TA < BB > bb;
    //TA < double >cc;
    TB dd;
    cout << aa.get() << endl;
    cout << bb.get() << endl;
    //cout << cc.get() << endl;
    cout << dd.get() << endl;
};

void forTry()
{
    for (int x = 0; x < 100; x++) {
	cout << x << endl;
	if (x == 50) {
	    break;
	}
    }
};

namespace a {
    namespace b {
	double x = 1;
	double y = b::x;
    };
};
namespace b {
    double x = 2;
};

void namespaceTry()
{
    cout << a::b::x << endl;
    cout << a::b::y << endl;
    cout << b::x << endl;
};



void pointerEample()
{
    vector < int >*a = new vector < int >(3);
    (*a)[0] = 3;
};

void lcdcalibratorTry()
{
    using namespace cms::measure::meter;
    using namespace cms::measure;
    using namespace cms::lcd::calibrate;
    bptr < CA210 > ca210(new CA210());
    bptr < CA210ComponentAnalyzer >
	analyzer(new CA210ComponentAnalyzer(ca210));
    LCDCalibrator cal(analyzer);
    cal.setGamma(2.2, 256);
    cal.getDGCode(255, 0, 1);
};

void channelTry()
{
    using namespace Dep;

    cout << ChannelIndex::R << endl;
    //cout << R_ << endl;
    cout << Channel::R.chindex << endl;
    cout << Channel::G.chindex << endl;
    //cout << ChannelIndex::_G << endl;
    //cout << ChannelIndex::_B << endl;
    RGB_ptr rgb(new RGBColor(1, 3, 5));
    foreach(const Channel & ch, *(Channel::RGBChannel)) {
	cout << *ch.toString() << " " << ch.chindex << endl;
	cout << rgb->getValue(ch) << endl;
	//cout << ch << endl;
    }


};

#pragma argsused
int main(int argc, char *argv[])
{
    //wstringtest();
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
    //dgcode();
    //inverse();
    //rgbTry();
    //mathTry();
    //doubleArrayTry();
    //rgbop();
    //templateTry();
    //forTry();
    //namespaceTry();
    //lcdcalibratorTry();
    channelTry();
    getch();
}

