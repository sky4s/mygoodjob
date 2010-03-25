//---------------------------------------------------------------------------
#include <includeall.h>
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

#include <boost/array.hpp>
//#include <jama/jama_svd.h>

#include <locale>
#include <cms/util/rgbarray.h>
#include <cms/util/util.h>
#include <ca210api/CA210API.h>

#include <math.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/lexical_cast.hpp>


//---------------------------------------------------------------------------
void excel()
{
    using namespace cms::colorformat;
    using namespace std;
    using namespace cms::util;
    //string_ptr filename(new string("a.xls"));

    /*string_vector_ptr fieldsNames(new string_vector());
       fieldsNames->push_back("a");
       fieldsNames->push_back("b"); */
    string_vector_ptr fieldsNames = StringVector::fromCString(2, "a", "b");

    const string & filename = "a.xls";
    //DGLutFile::deleteExist( filename);
    ExcelFileDB db(filename, Create);

    //string_ptr tbname(new string("tb"));

    bool newfile = true;

    if (newfile) {
	db.createTable("tb", fieldsNames);

	db.insert(fieldsNames, StringVector::fromCString(2, "11", "22"));
	db.insert(fieldsNames, StringVector::fromCString(2, "33", "44"));
	db.insert(fieldsNames, StringVector::fromCString(2, "55", "66"));
    } else {
	db.setTableName("tb");
	db.update("a", 11, "b", 99);
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
	//string_vector_ptr fieldsNames = ExcelFileDB::make(2, "99", "9");
	db.update("a", 44, fieldsNames,
		  StringVector::fromCString(2, "55", "55"));
    };


    //db.close();
}

void excel2()
{
    using namespace cms::colorformat;
    using namespace std;
    using namespace cms::util;
    string_vector_ptr fieldsNames = StringVector::fromCString(2, "a", "b");

    const string & filename = "a.xls";
    Util::deleteExist(filename);
    //DGLutFile::deleteExist( filename);
    ExcelFileDB db(filename, Create);

    db.createTable("tb", fieldsNames);
    bool update = false;

    if (update) {
	//¨â­¿®É¶¡
	for (int x = 0; x < 1000; x++) {
	    db.insert(fieldsNames,
		      StringVector::fromString(2, _toString(x),
					       _toString((x + 1))));
	}

	for (int x = 0; x < 1000; x++) {
	    string_vector_ptr values =
		StringVector::fromString(2, _toString(x),
					 _toString((x + 1)));
	    db.update("a", x, fieldsNames, values);
	}


    } else {
	for (int x = 0; x < 1000; x++) {
	    /*db.insert(fieldsNames,
	       ExcelFileDB::makes(2, _toString(x),
	       _toString((x + 1)))); */
	    //string a = "INSERT INTO [tb] ([a],[b]) VALUES (";
	    //string sql = a + _toString(x)+", "+_toString(x+1)+") ";
	    db.execute(" INSERT INTO[tb] ([a],[b]) VALUES(0, 1) ");
	    //db.execute(sql);
	    /*
	       ¤£ºÞ¦³¥Î¨ì¦r¦ê³B²zÁÙ¬O¨S¦³³£¤@¼ËºC, ©Ò¥H¥Î¤£µÛ¤@¤f®ð±Nªì¨Ï¤Æ©Mupdate
	       °µ¦b¤@°_¤F, ¦]¬°ÁÙ¬O¤@¼ËºC
	     */
	}
    }
}

void lut()
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


/*void regress()
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

}*/

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
    string a = " 12345 ";
    cout << a.size() << endl;
    char *test = "";
    wchar_t *wchar = new wchar_t[260];
    size_t ret = mbstowcs(wchar, test, 13);
    if (ret != NULL) {
	cout << " success " << endl;
	//wcout << wchar << endl;
	//wcout << L" § Ú§Ú§Ú§Ú" << endl;
	cout << wchar << endl;
	wcout << wchar << endl;
	wcout << L" some english string ";

    } else {
	cout << " Error " << endl;
    }
    delete[]wchar;

}

void stringfunc(string a)
{
    cout << &a << ":" << a << endl;
}

void stringfuncref(string & a)
{
    cout << &a << ":" << a << endl;
}

void stringfuncpointer(string * a)
{
    cout << a << ":" << *a << endl;
}



void stringtest()
{
    string a = " abc ";
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

    cout << " array:" << sizeof(darray) << endl;
    cout << " double:" << sizeof(double) << endl;
    cout << " double *:" << sizeof(dpointer) << endl;

    cout << " bptr:" << sizeof(dvalues) << endl;
    //cout << " * bptr:" << sizeof(*dvalues) << endl;

    cout << " vector:" << sizeof(dvector) << endl;
    cout << " vec capacity:" << dvector.capacity() << endl;

    //cout << dvector.size() << endl;


}

class A {
};

void gammaCurve()
{
    using namespace cms::lcd::calibrate;
    using namespace math;
    //int n = 256;
    /*double_array curve = LCDCalibrator::getGammaCurve(2.2, n);
       cout << *DoubleArray::toString(curve, n); */
};


void dgcodefile()
{
    using namespace cms::colorformat;
    using namespace cms::lcd::calibrate;
    using namespace Dep;
    using namespace Indep;
    using namespace cms::util;
    const string & filename = "test.xls";
    //string_ptr filename(new string(" test.xls "));
    Util::deleteExist(filename);
    DGLutFile dgcode(filename, Create);
    //dgcode.setProperty(" a ", " b ");
    //dgcode.setProperty(" b ", " bbb ");
    //dgcode.setRawData()
    Component_vector_ptr compositionVec(new Component_vector());
    RGB_ptr rgb(new RGBColor(1, 2, 3));
    XYZ_ptr XYZ(new Indep::CIEXYZ(4, 5, 6));
    Component_ptr c(new Component(rgb, rgb, XYZ));
    compositionVec->push_back(c);
    compositionVec->push_back(c);
    //dgcode.setRawData(compositionVec);

};

void dgcode()
{
    using namespace cms::lcd::calibrate;
    using namespace Dep;
    //using namespace Indep;
    int n = 256;
    Component_vector_ptr vector(new Component_vector(n));
    for (int x = 0; x != n; x++) {
	RGB_ptr rgb(new RGBColor(x, x, x));
	RGB_ptr component(new RGBColor(x * .3, x * .6, x * .1));
	XYZ_ptr XYZ(new Indep::CIEXYZ(0, x, 0));
	Component_ptr composition(new Component(rgb, component, XYZ));
	(*vector)[x] = composition;
    };
    //DGLutGenerator generator(vector);
};

void rgbTry()
{
    using namespace Dep;
    using namespace math;

    RGBColor rgb(RGBColorSpace::unknowRGB,
		 DoubleArray::toDoubleArray(3, 0.25, 0.5, 0.75),
		 MaxValue::Double255);
    cout << *rgb.toString() << endl;
    //rgb.quantization(MaxValue::Int8Bit);
    rgb.changeMaxValue(MaxValue::Int10Bit);
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
    /*using namespace java::lang;
       c*out << std::ceil(0.25) << endl;
       cout << std::ceil(0.5) << endl;
       cout << std::ceil(0.9) << endl;
       //cout << std::round(1.0) << endl;
       cout << Math::round(0.5) << endl;
       cout << Math::round(0.4) << endl; */
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
    Application->Initialize();
    Application->CreateForm(__classid(TMeasureWindow), &MeasureWindow);

    using namespace cms::measure::meter;
    using namespace cms::measure;
    using namespace cms::lcd::calibrate;
    bptr < CA210 > ca210(new CA210());
    //bptr < CA210 > ca2102(new CA210());
    bptr < MeterMeasurement > mm(new MeterMeasurement(ca210, false));
    bptr < CA210IntensityAnalyzer >
	analyzer(new CA210IntensityAnalyzer(ca210, mm));

    mm->measure(0, 0, 128, " test ");


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

void ca210()
{
    ca210api::CA210API ca210;
    /*ca210.setChannelNO(0);
       ca210.resetLvxyCalMode();
       ca210.resetAnalyzerCalMode();
       ca210.setChannelNO(1);
       ca210.resetLvxyCalMode();
       ca210.resetAnalyzerCalMode(); */
    ca210.triggerMeasurement();
};


void strTry()
{
    using namespace std;
    string a = " 1 ";
    string b = " 2 ";
    string c = a + b;
    cout << c << endl;
    string str = " 12345 ";
    str.replace(3, 1, " 90 ");
    cout << str << endl;

};

void measureFileTry()
{
    using namespace cms::colorformat;
    using namespace std;

    const string & filename = "ramp.xls";
    ExcelFileDB db(filename, ReadOnly);
    db.setTableName("Sheet1");
    bptr < DBQuery > query = db.selectAll();
    while (query->hasNext()) {
	string_vector_ptr result = query->nextResult();
	double_vector_ptr doubleresult = query->toDoubleVector(result);
	foreach(const double d, *doubleresult) {
	    cout << d << " ";
	}
	cout << endl;
    };

};

void maxValueTry()
{
    /*using namespace Dep;
       using namespace std;
       const MaxValue & m = MaxValue::getByBit(5);
       const MaxValue & n = MaxValue::getByBit(8);
       cout << *m.toString() << endl;
       cout << *n.toString() << endl; */

};

void byteOpTry()
{
    using namespace std;
    int i = 259;
    int i1 = i & 255;
    int i2 = i >> 8 & 255;
    cout << i1 << " " << i2 << endl;
};

void castTry()
{
    using boost::numeric_cast;

    using boost::numeric::bad_numeric_cast;
    using boost::numeric::positive_overflow;
    using boost::numeric::negative_overflow;

    using namespace std;
    float ff = -42.1234;

    int ii = numeric_cast < int >(ff);
    cout << ii << endl;

    //try {
    //float f = -42.1234;

    // This will cause a boost::numeric::negative_overflow exception to be thrown
    //unsigned int i = numeric_cast < unsigned int >(f);
    /*}
       catch(bad_numeric_cast & e) {
       std::cout << e.what();
       } */


};

void bufferTry()
{
    using namespace cms::i2c;
    ByteBuffer buffer(3);
};

void rgbGammaTry()
{
    using namespace cms::lcd::calibrate;
    using namespace std;
    RGBGamma_ptr rgbgamma =
	RGBGamma::loadFromDesiredGamma("DesiredGamma.xls");
    double_vector_ptr r = rgbgamma->r;
    foreach(const double v, *r) {
	cout << v << endl;
    };
};

#pragma argsused
int main(int argc, char *argv[])
{
    //wstringtest();
    //stringtest();


    /*string s;
       cout << (" " == s) << endl; */

    //regress();
    //lut();
    //excel();
    //excel2();
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
    //channelTry();
    //ca210();

    //strTry();
    //measureFileTry();
    //maxValueTry();

    //using namespace cms::colorformat;
    //DGLutFile dg(" test.xls ",256);
    //cout << RoundTo(94.5, 0) << endl;
    //cout << java::lang::Math::roundTo(94.5) << endl;
    //byteOpTry();
    //castTry();
    rgbGammaTry();
    //bufferTry();
    getch();
}

