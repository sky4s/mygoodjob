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
//#include <policybased.h>
#include <locale>

//---------------------------------------------------------------------------
 

void excel()
{
    using namespace cms::colorformat;
    string_ptr filename(new string("a.xls"));

    string_vector_ptr columnNames(new string_vector());
    columnNames->push_back("a");
    columnNames->push_back("b");
    ExcelFileDB db(filename, Create);

    string_ptr tbname(new string("tb"));
    db.setTableName(tbname);
    //db.createTable(tbname, columnNames);
    string_vector_ptr names = db.getFieldNames(tbname);
    /*foreach(string s, *names) {
       cout << s << endl;
       } */
    //db.insert(columnNames,columnNames);
    string_vector_ptr updateField(new string_vector());
    string_vector_ptr updateValue(new string_vector());
    updateField->push_back("b");
    updateValue->push_back("3");
    /*db.update("a",1,updateField, updateValue);
       db.update("a",2,"b", "bb");
       db.update("a",3,"b", 9999); */
    db.setKeyField("a");
    db.setTableName("tb");

    string_vector_ptr updateValue2(new string_vector());
    updateValue->push_back("99");
    updateValue->push_back("999");
    //db.update(6,updateValue);
    db.select("", 1);

    db.close();
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

#pragma argsused
int main(int argc, char *argv[])
{
    //wstringtest();
    //stringtest();


    /*string s;
       cout << ("" == s) << endl; */

    //regress();
    //lut();
    excel();
    //inverse();
    getch();
}

