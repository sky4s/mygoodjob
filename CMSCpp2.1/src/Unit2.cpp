//---------------------------------------------------------------------------
#include <includeall.h>
#pragma hdrstop
//#include "utilcls.h"
//#include "system.hpp"
//#include "ComObj.hpp"


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
#include <boost/any.hpp>


#include <vcl.h>
#ifdef __BORLANDC__
# pragma pack(push, 8)
#endif
#include <locale>
#ifdef __BORLANDC__
# pragma pack(pop)
#endif


#include <math.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include "inifiles.hpp"
#include <map>
//#include <boost/lexical_cast.hpp>
//#include "gui/3d/T3DMeasurementForm.h"
//#include <boost/tokenizer.hpp>
# include <algo/asa047.H>
#include <iomanip>

using namespace std;

//---------------------------------------------------------------------------
void excel()
{
    using namespace cms::colorformat;
    using namespace cms::util;
    //string_ptr filename(new string("a.xls"));

    string_vector_ptr fieldsNames = StringVector::fromCString(2, "a", "b");

    const string & filename = "a.xls";
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
	db.update("a", 44, fieldsNames, StringVector::fromCString(2, "55", "55"));
    };


    //db.close();
}

void excel2()
{
    using namespace cms::colorformat;
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
	    db.insert(fieldsNames, StringVector::fromString(2, _toString(x), _toString((x + 1))));
	}

	for (int x = 0; x < 1000; x++) {
	    string_vector_ptr values = StringVector::fromString(2, _toString(x),
								_toString((x + 1)));
	    db.update("a", x, fieldsNames, values);
	}


    } else {
	for (int x = 0; x < 1000; x++) {

	    db.execute(" INSERT INTO[tb] ([a],[b]) VALUES(0, 1) ");

	}
    }
}

void lut()
{
    using namespace math;
    double a[] = { 1, 2, 3, 4, 5, 6 };
    double b[] = { 2, 4, 5, 6, 8, 10 };

    double_vector_ptr key(new double_vector(a, a + 6));
    double_vector_ptr val(new double_vector(b, b + 6));
    Interpolation1DLUT lut(key, val);
    //cout << lut.getValue(3) << endl;
    cout << lut.getValue(3.5) << endl;
    //cout << lut.getValue(4) << endl;
}


double2D_ptr inverse()
{
    using namespace math;

    double2D_ptr m = DoubleArray::toDouble2D(3, 9, 0.5767309, 0.1855540, 0.1881852,
					     0.2973769, 0.6273491, 0.0752741,
					     0.0270343, 0.0706872, 0.9911085);
    double2D_ptr inv = DoubleArray::inverse(m);
    cout << *DoubleArray::toString(m) << endl;
    cout << *DoubleArray::toString(inv) << endl;



    return m;
    //double_array a = DoubleArray::toDoubleArray(3, 1.1, 2.2, 3.3);
    //cout << *DoubleArray::toString(a,3) << endl;
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


void gammaCurve()
{
    using namespace cms::lcd::calibrate;
    using namespace math;
    //int n = 256;

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
    dgcode.setRawData(compositionVec, nil_RGBGamma, nil_RGBGamma);
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
    /*RGBColor rgb(RGBColorSpace::unknowRGB,
       DoubleArray::toDoubleArray(3, 0.25, 0.5, 0.75), MaxValue::Double255);
       cout << *rgb.toString() << endl;
       rgb.changeMaxValue(MaxValue::Int10Bit);
       cout << *rgb.toString() << endl; */
    RGBColor rgb;
    rgb.setValue(Channel::R, .5);
    double_array d(new double[3]);
    rgb.getValues(d, MaxValue::Int8Bit);
    cout << *rgb.toString() << endl;
    cout << *DoubleArray::toString(d, 3) << endl;
};
void doubleArrayTry()
{
    using namespace math;
    double2D_ptr array(new double2D(2, 2));
    (*array)[0][0] = 1;
    (*array)[0][1] = 2;
    (*array)[1][0] = 3;
    (*array)[1][1] = 4;

    double_array result = DoubleArray::toDoubleArray(array);
    cout << *DoubleArray::toString(result, 4);
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
    bptr < CA210IntensityAnalyzer > analyzer(new CA210IntensityAnalyzer(ca210, mm));
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

void strTry()
{
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

void byteOpTry()
{
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

};
void bufferTry()
{
    using namespace cms::util;
    ByteBuffer buffer(3);
};
void rgbGammaTry()
{
    using namespace cms::lcd::calibrate;
    RGBGamma_ptr rgbgamma = RGBGamma::loadFromDesiredGamma("DesiredGamma.xls");
    double_vector_ptr r = rgbgamma->r;
    foreach(const double v, *r) {
	cout << v << endl;
    };
};

void measureConditionTry()
{
    using namespace cms::lcd::calibrate;
    //MeasureCondition mc(64, 0, 8, 255, 64, 16);
    /*int_vector_ptr code = mc.getMeasureCode();
       foreach(const int &c, *code) {
       cout << c << endl;
       } */
};
void vectorTry()
{

    vector < int >v;
    int a = 3;
    int b = 4;
    v.push_back(a);
    v.push_back(b);
    cout << v[0] << endl;
    cout << v[1] << endl;
};

void ca210Try()
{
    using namespace ca210api;
    CA210API ca;
    ca.setChannelNO(0);
    ca.copyFromFile("a.dat");

};

void floatArrayTry()
{
    using namespace math;
    float2D_ptr f = FloatArray::toFloat2D(3, 3, 1.1, 2.2f, 3.3f);
    cout << *(FloatArray::toString(f)) << endl;
};

void inverseTry()
{
    using namespace std;
    using namespace math;
    double2D_ptr m = DoubleArray::toDouble2D(3, 9, 0.9649, 0.9572, 0.1419, 0.1576,
					     0.4854,
					     0.4218, 0.9706, 0.8003, 0.9157);


    double2D_ptr invm = DoubleArray::inverse(m);
    double2D_ptr mm = DoubleArray::times(m, invm);

    cout << *(DoubleArray::toString(m)) << endl;
    cout << *(DoubleArray::toString(invm)) << endl;
    cout << *(DoubleArray::toString(mm)) << endl;
    cout << "==" << endl;

    double2D m_ = *m;
    double2D invm_ = DoubleArray::inverse(m_);
    double2D mm_ = DoubleArray::times(m_, invm_);

    cout << DoubleArray::toString(m_) << endl;
    cout << DoubleArray::toString(invm_) << endl;
    cout << DoubleArray::toString(mm_) << endl;
};

void ddLutFileReadTry()
{
    using namespace cms::colorformat;
    DGLutFile file("debug.xls", ReadOnly);

    Component_vector_ptr cv = file.getComponentVector();
    foreach(Component_ptr c, *cv) {
	cout << *c->rgb->toString() << endl;
    }
};

void newCCTAlgoTry()
{
    using namespace cms::colorformat;
    using namespace cms::lcd::calibrate;

    DGLutFile file("debug.xls", ReadOnly);
    Component_vector_ptr vector = file.getComponentVector();
    ComponentLUT lut(vector);
    int size = vector->size();

    for (int x = size - 1; x >= 0; x--) {
	const Component_ptr c = (*vector)[x];
	RGB_ptr intensity = c->intensity;
	double rintensity = intensity->G - (intensity->B - intensity->G);
	rintensity = lut.correctIntensityInRange(Dep::Channel::R, rintensity);
	double rcode = lut.getCode(Dep::Channel::R, rintensity);
	double g = c->rgb->G;
	cout << java::lang::Math::roundTo(rcode * 16) << " " << g * 16 << " " << g * 16 << endl;
    }
}


void readTextTester()
{


    using namespace cms::colorformat;
    Parser parser("ciexyz31_1.txt");
    //for(int x=0;x<parser.
    for (int x = 0; x < parser.getCount(); x++) {
	string_vector_ptr tokenize = parser.getTokenize(x);
	foreach(const string & s, *tokenize) {
	    //cout << s << endl;
	    double d = _toDouble(s);
	    cout << d << endl;
	}
    }
}

void cmfTester()
{
    using namespace cms;
    const ColorMatchingFunction & cmf = *ColorMatchingFunction::CIE_1931_2DEG_XYZ;
    cout << cmf.getStart() << endl;
    cout << cmf.getInterval() << endl;
    cout << cmf.getEnd() << endl;
    cout << cmf.getSpectra(0)->getXYZ() << endl;
};

void targetTester()
{
    using namespace cms::lcd::calibrate;
    using namespace cms;
    using namespace Indep;
    cout << _toString("123") << endl;
    xyY_ptr xyY = CorrelatedColorTemperature::CCT2DIlluminantxyY(20000);
    bool result = CorrelatedColorTemperature::isCCTMeaningful(xyY);
    cout << result << endl;
    XYZ_ptr black = xyY->toXYZ();
    cout << *black->toString() << endl;
    /*XYZ_ptr targetWhite =
       CorrelatedColorTemperature::CCT2DIlluminantxyY(6500)->toXYZ();
       XYZ_ptr nativeWhite =
       CorrelatedColorTemperature::CCT2DIlluminantxyY(8000)->toXYZ();
       double_vector_ptr gamaCurve =
       LCDCalibrator::getGammaCurveVector(2.2, 256, 256);
       for (int x = 0; x < 256; x++) {
       (*gamaCurve)[x] += 0.1;
       }
       XYZ_vector_ptr result =
       AdvancedDGLutGenerator::getTarget(black, targetWhite, nativeWhite,
       gamaCurve, 30, 240, 2.2, 3);
       foreach(XYZ_ptr XYZ, *result) {
       xyY_ptr xyY(new CIExyY(XYZ));
       //cout << *xyY->toString() << endl;
       cout << CorrelatedColorTemperature::
       xy2CCTByMcCamyFloat(xyY) << endl;
       }; */
};

void directGammaTester()
{
    using namespace i2c;
    bptr < cms::util::ByteBuffer > buf =
	TCONControl::getRGBByteBuffer(513, 2052, 0, TestRGBBit::DependentInstance);
    int size = buf->getSize();
    for (int x = 0; x < size; x++) {
	byte b = (*buf)[x];
	cout << (int) b << endl;
    }
};

void hookTester()
{
    string filename = "debug.xls";
    using namespace cms::measure::meter;
    using namespace cms::measure;
    using namespace cms::colorformat;
    using namespace cms::lcd::calibrate;
    using namespace Indep;
    using namespace Dep;
    bptr < DGLutFile > dgcode(new DGLutFile(filename, ReadOnly));
    bptr < Meter > meter = bptr < Meter > (new DGLutFileMeter(dgcode));
    bptr < MeterMeasurement > mm = bptr < MeterMeasurement > (new MeterMeasurement(meter, false));
    mm->setFakeMeasure(true);

    bptr < MaxMatrixIntensityAnayzer > matrixAnalyzer(new MaxMatrixIntensityAnayzer(mm));

    bptr < MaxMatrixIntensityAnayzer > analyzer = matrixAnalyzer;
    //fetcher = bptr < ComponentFetcher > ((ComponentFetcher *) null);

    bptr < DGLutProperty > property = dgcode->getProperty();
    xyY_ptr wxyY = property->getTargetReferenceColor(Channel::W);
    if (null != wxyY) {
	xyY_ptr rxyY = property->getTargetReferenceColor(Channel::R);
	xyY_ptr gxyY = property->getTargetReferenceColor(Channel::G);
	xyY_ptr bxyY = property->getTargetReferenceColor(Channel::B);

	matrixAnalyzer->setupComponent(Channel::W, wxyY->toXYZ());
	matrixAnalyzer->setupComponent(Channel::R, rxyY->toXYZ());
	matrixAnalyzer->setupComponent(Channel::G, gxyY->toXYZ());
	matrixAnalyzer->setupComponent(Channel::B, bxyY->toXYZ());
	matrixAnalyzer->enter();
    }
    Component_vector_ptr componentVector = dgcode->getComponentVector();


    DimDGLutGenerator generator(componentVector, analyzer);

    Component_vector_ptr newcomponentVector =
	generator.fetchNewComponent(analyzer, componentVector);
    foreach(Component_ptr p, *newcomponentVector) {
	cout << p->intensity->B << endl;
    }
    //STORE_COMPONENT(_toString(x++) + ".xls", newcomponentVector);
    //DGLutGenerator lutgen(newcomponentVector);
    //±Ä100¶Ü?
    //RGB_ptr rgb = lutgen.getDGCode(100, 100, 100);

    //result->push_back(rgb);

};

void odTester()
{

};

void txtTester()
{
    TStringList *ClickList = new TStringList;
    ClickList->Add("131213");	//add a string to the list

    ClickList->SaveToFile(ChangeFileExt(Application->ExeName, ".LOG"));	//Save the list
    delete ClickList;

};




class PropTest {
  public:
    PropTest() {
	Count.setContainer(this);
	Count.setter(&PropTest::setCount);
	Count.getter(&PropTest::getCount);
    } int getCount() {
	return m_nCount;
    }
    void setCount(int nCount) {
	m_nCount = nCount;
    }
    Property < PropTest, int, READ_WRITE > Count;


  private:
    int m_nCount;
};

void propTester()
{
    int i = 5, j;
    PropTest test;
    test.Count = i;		//-- call the set method --
    j = test.Count;		//-- call the get method --

}

void excelTester()
{
    //OleInitialize(NULL);
    CoInitialize(NULL);
    Variant EXCEL, WORKbooks, WORKbook, WORKsheets, WORKsheet, CELL;
    EXCEL = CreateOleObject("Excel.Application");
    EXCEL.OlePropertySet("Visible", true);
    WORKbooks = EXCEL.OlePropertyGet("Workbooks");
    WORKbook = WORKbooks.OleFunction("Add");
    WORKsheets = WORKbook.OlePropertyGet("Worksheets");
    WORKsheet = WORKsheets.OlePropertyGet("Item", 1);
    CELL = WORKsheet.OlePropertyGet("Cells", 1, 1);
    CELL.OlePropertySet("Value", "MY DATA");
    OleUninitialize();
}

void iniTester()
{
    bptr_ < TIniFile > ini(new TIniFile(ExtractFilePath(Application->ExeName) + "tcon.ini"));
    ini->WriteInteger("I2C", "Card", 0);
    ini->WriteInteger("I2C2", "Card", 0);
    ini->WriteInteger("I2C3", "Card", 0);
    bptr_ < TStringList > sections(new TStringList());
    ini->ReadSections(sections.get());
    for (int x = 0; x < sections->Count; x++) {
	cout << (*sections)[x] << endl;
    }
    /*foreach(AnsiString s,  sections) {
       } */
}

void byteTester()
{
    unsigned char data = 53;
    unsigned char mask = ~(1 << 2);
    cout << (int) mask << endl;
    data = data & mask;
    cout << (int) data << endl;
    unsigned char dg = false << 2;
    cout << (int) dg << endl;
    int remainder = 257 % 2;
    cout << remainder << endl;
}

void produceTCONINIFile()
{
    bptr_ < TIniFile > ini(new TIniFile(ExtractFilePath(Application->ExeName) + "tcon.ini"));

    ini->WriteInteger("11306", "AddressingSize", 5);

    ini->WriteString("11306", "DigitalGammaEnableAddress", "28");
    ini->WriteInteger("11306", "DigitalGammaEnableBit", 0);
    ini->WriteString("11306", "DigitalGammaLUTAddress", "3C0");
    ini->WriteInteger("11306", "DigitalGammaLUTType", 10);

    ini->WriteBool("11306", "GammaTestFunc", false);
    //=========================================================================
    ini->WriteInteger("12306", "AddressingSize", 5);

    ini->WriteString("12306", "DigitalGammaEnableAddress", "28");
    ini->WriteInteger("12306", "DigitalGammaEnableBit", 0);
    ini->WriteString("12306", "DigitalGammaLUTAddress", "302");
    ini->WriteInteger("12306", "DigitalGammaLUTType", 12);

    ini->WriteBool("12306", "GammaTestFunc", true);
    ini->WriteString("12306", "GammaTestEnableAddress", "29");
    ini->WriteInteger("12306", "GammaTestEnableBit", 0);
    ini->WriteString("12306", "GammaTestAddress", "154");
    ini->WriteBool("12306", "IndepRGB", true);
    //=========================================================================
}

void stringTester()
{
    String s = "1234";
    String s1 = s.sprintf("%0.4f", 123456.1234567);
    String s2 = s.sprintf("%0.4f", 123456.2234567);
    String s3 = s.sprintf("%0.4f", 123456.3234567);
    cout << s << endl;
    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;
}

void maxValueTry()
{
    using namespace Dep;
    const Dep::MaxValue & m = Dep::MaxValue::Int6Bit;
    cout << m.max << endl;
}

void linearRGBTry()
{
    using namespace cms::lcd::calibrate;
    bptr < BitDepthProcessor > bitDepth(new BitDepthProcessor(8, 12, 8, false));
    RGB_vector_ptr vec = RGBVector::getLinearRGBVector(bitDepth, .5);

    int size = vec->size();
    for (int x = 0; x < size; x++) {
	cout << x << " ";
	cout << *(*vec)[x]->toString() << endl;
    }

}

void smoothTry()
{
    using namespace cms::lcd::calibrate;
    using namespace cms::util;
    bptr < BitDepthProcessor > bitDepth(new BitDepthProcessor(8, 10, 6, false));
    RGB_vector_ptr vector1 = RGBVector::getLinearRGBVector(bitDepth, 0.5);
    RGB_vector_ptr vector2 = RGBVector::getLinearRGBVector(bitDepth, 1);
    /*foreach(RGB_ptr rgb, *vector1) {
       cout << *rgb->toString() << endl;
       }
       foreach(RGB_ptr rgb, *vector2) {
       cout << *rgb->toString() << endl;
       } */
    RGB_vector_ptr result = AdvancedDGLutGenerator::smooth(vector1, vector2, bitDepth, 230);
    /*foreach(RGB_ptr rgb, *result) {
       cout << *rgb->toString() << endl;
       } */
    for (int x = 200; x < vector1->size(); x++) {
	cout << *(*vector1)[x]->toString() << endl;
    }
    for (int x = 200; x < vector1->size(); x++) {
	cout << *(*vector2)[x]->toString() << endl;
    }
    for (int x = 200; x < vector1->size(); x++) {
	cout << *(*result)[x]->toString() << endl;
    }
}

void cloneTry()
{
    using namespace cms::lcd::calibrate;
    using namespace cms::util;
    bptr < BitDepthProcessor > bitDepth(new BitDepthProcessor(8, 10, 6, false));

    RGB_vector_ptr vector2 = RGBVector::getLinearRGBVector(bitDepth, 1);
    RGB_vector_ptr result = RGBVector::deepClone(vector2);
    cout << (*vector2)[0]->R << endl;
    (*result)[0]->R = 100;
    cout << (*vector2)[0]->R << endl;
};

void deltaETry()
{
    using namespace cms;
    using namespace Indep;
    Lab_ptr a(new CIELab(50, 3, 10));
    Lab_ptr b(new CIELab(51, 4, 12));
    DeltaE de(a, b);
    cout << de.getCIE2000DeltaE() << endl;
    cout << de.getCIE2000Deltaab() << endl;
}

void scurve()
{
    using namespace cms::util;
    SCurve scurve(-6, 6);
    for (double d = 0; d <= 1; d += 0.05) {
	cout << d << " " << scurve.getValue(d) << endl;
    }
}

void domap()
{
    using namespace std;


    multimap < int, int >map;
    typedef multimap < int, int >::iterator Iter;
    map.insert(make_pair(1, 2));
    map.insert(make_pair(1, 3));
    map.insert(make_pair(1, 4));

    pair < Iter, Iter > range = map.equal_range(1);
    for (Iter i = range.first; i != range.second; ++i) {
	//cout << i->first << endl;
	cout << i->second << endl;
    }
}

class A {
  public:
    void some_function() {
	std::cout << "A::some_function()\n";
    };
};
class B {
  public:
    void some_function() {
	std::cout << "B::some_function()\n";
    };
};

void print_any(boost::any & a)
{
    if (A * pA = boost::any_cast < A > (&a)) {
	pA->some_function();
    } else if (B * pB = boost::any_cast < B > (&a)) {
	pB->some_function();
    } else {
	try {
	    std::cout << boost::any_cast < std::string > (a) << '\n';
	}
	catch(boost::bad_any_cast &) {
	    std::cout << "Oops!\n";
	}
    }
}


void anyTest()
{
    std::cout << "Example of using any.\n\n";
    std::vector < boost::any > store_anything;
    store_anything.push_back(A());
    store_anything.push_back(B());
    // §Ú­Ì¦A¨Ó¡A¦A¥[¤@¨Ç§OªºªF¦è  
    store_anything.push_back(std::string("This is fantastic! "));
    store_anything.push_back(3);
    store_anything.push_back(std::make_pair(true, 7.92));
    std::for_each(store_anything.begin(), store_anything.end(), print_any);


    std::cout << "Example of using any member functions\n\n";
    boost::any a1(100);
    boost::any a2(std::string("200"));
    boost::any a3;
    std::cout << "a3 is ";
    if (!a3.empty()) {
	std::cout << "not empty\n ";
    }
    std::cout << "empty\n";
    a1.swap(a2);
    try {
	std::string s = boost::any_cast < std::string > (a1);
	std::cout << "a1 contains a string: " << s << "\n";
    }
    catch(boost::bad_any_cast & e) {
	std::cout << "I guess a1 doesn't contain a string!\n";
    }
    if (int *p = boost::any_cast < int >(&a2)) {
	std::cout << "a2 seems to have swapped contents with a1: " << *p << "\n";
    } else {
	std::cout << "Nope, no int in a2\n";
    }
    if (typeid(int) == a2.type()) {
	std::cout << "a2's type_info equals the type_info of int\n";
    }

}

class property {
    boost::any value_;
    std::string name_;
  public:
    property(const std::string & name, const boost::any & value):name_(name), value_(value) {
    } std::string name() const {
	return name_;
    } boost::any & value() {
	return value_;
    }
    friend bool operator<(const property & lhs, const property & rhs) {
	return lhs.name_ < rhs.name_;
    }
};
void print_names(const property & p)
{
    std::cout << p.name() << "\n";
}

void propertyTest()
{
    std::cout << "Example of using any for storing properties.\n";
    std::vector < property > properties;
    properties.push_back(property("B", 30));
    properties.push_back(property("A", std::string("Thirty something")));
    properties.push_back(property("C", 3.1415));
    std::sort(properties.begin(), properties.end());
    std::for_each(properties.begin(), properties.end(), print_names);
    std::cout << "\n";
    std::cout << boost::any_cast < std::string > (properties[0].value()) << "\n";
    std::cout << boost::any_cast < int >(properties[1].value()) << "\n";
    std::cout << boost::any_cast < double >(properties[2].value()) << "\n";
}

void hsvTest()
{
    using namespace Dep;
    /*RGB_ptr rgb(new RGBColor(192, 80, 80));
       cout << rgb->getHue() << endl;
       double_array hsvi = rgb->getHSVIValues();
       cout << *math::DoubleArray::toString(hsvi, 4) << endl;
       double_array rgbValues = RGBColor::HSV2RGBValues(hsvi[0], hsvi[1], hsvi[2]);
       cout << *math::DoubleArray::toString(rgbValues, 3) << endl; */
}

class AA {
  public:
    virtual a() = 0;
    AA() {
	//a();
}};

class BB:public AA {
  public:
    BB() {
	a();
    } virtual a() {
	cout << "a()" << endl;
    }
};

void virtualTry()
{
    BB b;
}

void lcdTargetTry()
{
    using namespace cms::lcd;
    using namespace Dep;
    string_ptr filename(new string("ramp257(6bit).xls"));
    LCDTarget_ptr target = LCDTarget::Instance::getFromAUORampXLS(filename);
    /*for (int x = 0; x < target->size(); x++) {
       Patch_ptr p = target->getPatch(x);
       cout << *p->toString() << endl;
       } */
    LCDTargetInterpolator interpolator(target);
    Patch_ptr p = interpolator.getPatch(Channel::W, 253);
    cout << *p->toString() << endl;


}

void lcdModelTry()
{
    using namespace cms::lcd;
    using namespace Dep;
    using namespace cms::devicemodel;

    string_ptr rampfilename(new string("ramp257(6bit).xls"));
    //string_ptr rampfilename(new string("ramp257(6bit)_cal.xls"));
    LCDTarget_ptr ramp = LCDTarget::Instance::getFromAUORampXLS(rampfilename);
    Patch_ptr whitePatch = ramp->getBrightestPatch();
    XYZ_ptr whitePoint = whitePatch->getXYZ();
    ramp->calculatePatchLab(whitePoint);

    string_ptr auo729(new string("auo-729.xls"));
    //string_ptr auo729(new string("auo-729_cal.xls"));
    LCDTarget_ptr target729 = LCDTarget::Instance::getFromAlteredLogoXLS(auo729);
    target729->calculatePatchLab(whitePoint);
    Patch_vector_ptr patchList = target729->getPatchList();

    MultiMatrixModel model(ramp);
    model.setTargetWhitePoint(whitePoint);
    bptr < DeltaEReport > report = model.testForwardModel(patchList);
    report->storeToExcel("report.xls");
}

double rosenbrock(double x[2])
//****************************************************************************80
//
//  Purpose:
//
//    ROSENBROCK evaluates the Rosenbrock parabolic value function.
//
//  Modified:
//
//    27 February 2008
//
//  Author:
//
//    John Burkardt
//
//  Reference:
//
//    R ONeill,
//    Algorithm AS 47:
//    Function Minimization Using a Simplex Procedure,
//    Applied Statistics,
//    Volume 20, Number 3, 1971, pages 338-345.
//
//  Parameters:
//
//    Input, double X[2], the argument.
//
//    Output, double ROSENBROCK, the value of the function.
//
{
    double fx;
    double fx1;
    double fx2;

    fx1 = x[1] - x[0] * x[0];
    fx2 = 1.0 - x[0];

    fx = 100.0 * fx1 * fx1 + fx2 * fx2;

    return fx;
}

void test01()
//****************************************************************************80
//
//  Purpose:
//
//    TEST01 demonstrates the use of NELMIN on ROSENBROCK.
//
//  Modified:
//
//    27 February 2008
//
//  Author:
//
//    John Burkardt
//
{
    using namespace std;
    int i;
    int icount;
    int ifault;
    int kcount;
    int konvge;
    int n;
    int numres;
    double reqmin;
    double *start;
    double *step;
    double *xmin;
    double ynewlo;

    n = 2;

    start = new double[n];
    step = new double[n];
    xmin = new double[n];

    cout << "\n";
    cout << "TEST01\n";
    cout << "  Apply NELMIN to ROSENBROCK function.\n";

    start[0] = -1.2;
    start[1] = 1.0;

    reqmin = 1.0E-08;

    step[0] = 1.0;
    step[1] = 1.0;

    konvge = 10;
    kcount = 500;

    cout << "\n";
    cout << "  Starting point X:\n";
    cout << "\n";
    for (i = 0; i < n; i++) {
	cout << "  " << setw(14) << start[i] << "\n";
    }

    ynewlo = rosenbrock(start);

    cout << "\n";
    cout << "  F(X) = " << ynewlo << "\n";

    nelmin(rosenbrock, n, start, xmin, &ynewlo, reqmin, step,
	   konvge, kcount, &icount, &numres, &ifault);

    cout << "\n";
    cout << "  Return code IFAULT = " << ifault << "\n";
    cout << "\n";
    cout << "  Estimate of minimizing value X*:\n";
    cout << "\n";
    for (i = 0; i < n; i++) {
	cout << "  " << setw(14) << xmin[i] << "\n";
    }

    cout << "\n";
    cout << "  F(X*) = " << ynewlo << "\n";

    cout << "\n";
    cout << "  Number of iterations = " << icount << "\n";
    cout << "  Number of restarts =   " << numres << "\n";

    delete[]start;
    delete[]step;
    delete[]xmin;

    return;
}

class Rosenbrock:public algo::MinimisationFunction {
  public:
    double function(double_vector_ptr x) {

	double fx;
	double fx1;
	double fx2;

	fx1 = (*x)[1] - (*x)[0] * (*x)[0];
	fx2 = 1.0 - (*x)[0];

	fx = 100.0 * fx1 * fx1 + fx2 * fx2;

	return fx;

    };
};

void test01_()
{
    using namespace std;
    using namespace algo;
    int i;
    //int icount;
    //int ifault;
    int kcount;
    int konvge;
    int n;
    //int numres;
    double reqmin;
    //double *start;
    //double *step;
    //double *xmin;
    double ynewlo;

    n = 2;

    //start = new double[n];
    //step = new double[n];
    //xmin = new double[n];
    double_vector_ptr start(new double_vector(n));
    double_vector_ptr step(new double_vector(n));

    Minimisation mini;
    Rosenbrock rosenbrockfunc;


    cout << "\n";
    cout << "TEST01\n";
    cout << "  Apply NELMIN to ROSENBROCK function.\n";

    (*start)[0] = -1.2;
    (*start)[1] = 1.0;

    reqmin = 1.0E-08;

    (*step)[0] = 1.0;
    (*step)[1] = 1.0;

    konvge = 10;
    kcount = 500;

    cout << "\n";
    cout << "  Starting point X:\n";
    cout << "\n";
    for (i = 0; i < n; i++) {
	cout << "  " << setw(14) << (*start)[i] << "\n";
    }

    //ynewlo = rosenbrock(start);
    ynewlo = rosenbrockfunc.function(start);

    cout << "\n";
    cout << "  F(X) = " << ynewlo << "\n";

    bptr < MinimisationFunction > minifun(&rosenbrockfunc);
    mini.setNrestartsMax(10);
    mini.nelderMead(minifun, start, step, reqmin, kcount);

    /*nelmin(rosenbrock, n, start, xmin, &ynewlo, reqmin, step,
       konvge, kcount, &icount, &numres, &ifault); */

    cout << "\n";
    algo::Error err = mini.getError();
    cout << "  Return code IFAULT = " << err << "\n";
    cout << "\n";
    cout << "  Estimate of minimizing value X*:\n";
    cout << "\n";
    double_vector_ptr xmin = mini.getParamValues();
    for (i = 0; i < n; i++) {
	cout << "  " << setw(14) << (*xmin)[i] << "\n";
    }

    cout << "\n";
    ynewlo = mini.getMinimum();
    cout << "  F(X*) = " << ynewlo << "\n";

    cout << "\n";

    cout << "  Number of iterations = " << mini.getNiter() << "\n";
    cout << "  Number of restarts =   " << mini.getNmax() << "\n";

    //delete[]start;
    //delete[]step;
    //delete[]xmin;
    return;
}

void vectorop(double_vector v)
{
    v[0]++;
}


void vectorop2(double_vector_ptr v)
{
    (*v)[0]++;
}

void vectorTest()
{
    double_vector vec(5);
    cout << sizeof(vec) << endl;
    double_vector vec2(10);
    cout << sizeof(vec2) << endl;

    double_vector_ptr vecp(new double_vector(5));
    cout << sizeof(vecp) << endl;
    cout << sizeof(*vecp) << endl;

    vec[0] = 10;
    cout << vec[0] << endl;
    vectorop(vec);
    cout << vec[0] << endl;

    (*vecp)[0] = 10;
    cout << (*vecp)[0] << endl;
    vectorop2(vecp);
    cout << (*vecp)[0] << endl;
}




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

    //double2D_ptr m = inverse();
    //cout << *math::DoubleArray::toString(m) << endl;

    //rgbTry();
    //mathTry();
    //doubleArrayTry();
    //rgbop();
    //templateTry();
    //forTry();
    //namespaceTry();
    //lcdcalibratorTry();
    //channelTry();
    //strTry();
    //measureFileTry();
    //maxValueTry();
    //using namespace cms::colorformat;
    //DGLutFile dg(" test.xls ",256);
    //cout << RoundTo(94.5, 0) << endl;
    //cout << java::lang::Math::roundTo(94.5) << endl;
    //byteOpTry();
    //castTry();
    //rgbGammaTry();
    //bufferTry();
    //measureConditionTry();
    //vectorTry();
    //ca210Try();
    //floatArrayTry();
    //inverseTry();

    //persistence();
    //ddLutFileReadTry();
    //newCCTAlgoTry();
    //token();
    //readTextTester();
    //cmfTester();
    //cout<<_toDouble("123");
    //ShellExecute(null, null, "target.xls", null, null, SW_SHOW);
    //ShellExecute(null, null, "target.xls", null, null, SW_HIDE);
    //targetTester();
    //directGammaTester();
    //hookTester();
    //odTester();
    //txtTester();
    //propTester();
    //excelTester();
    //iniTester();
    //byteTester();
    //produceTCONINIFile();
    //stringTester();
    //maxValueTry();
    //linearRGBTry();
    //smoothTry();
    //deltaETry();
    //cloneTry();
    //scurve();
    //domap();
    //anyTest();
    //propertyTest();
    //hsvTest();
    //cout << IntToHex(10,2) << endl;
    //virtualTry();
    //lcdTargetTry();
    //lcdModelTry();
    test01();
    test01_();
    //vectorTest();

    //cout << 5 / 4 / 3. << endl;
    //cout << _toString("123") << endl;
    cout << "end" << endl;
    getch();
}

