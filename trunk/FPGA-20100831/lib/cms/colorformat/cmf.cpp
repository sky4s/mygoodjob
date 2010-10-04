#include <includeall.h>
#pragma hdrstop
#include "cmf.h"

//C系統文件

//C++系統文件
//#include <boost/lexical_cast.hpp>
//其他庫頭文件

//本項目內頭文件

namespace cms {
    namespace colorformat {
	using namespace std;
	using namespace boost;
	using namespace java::lang;
	using namespace lcd::calibrate;
	using namespace Indep;
	using namespace Dep;
	using namespace cms::util;
	using namespace math;

	//======================================================================
	// Parser
	//======================================================================
	 Parser::Parser(const string & filename):strList(bptr < TStringList > (new TStringList())) {
	    strList->LoadFromFile(_toAnsiString(filename));
	};
	int Parser::getCount() {
	    return strList->Count;
	};
	string_vector_ptr Parser::getTokenize(int index) {
	    AnsiString str = strList->Strings[index];
	    string stlstring(str.c_str());
	    string_vector_ptr result = StringVector::tokenize(stlstring, " ,");
	    return result;
	};
	//======================================================================

	//======================================================================
	// Parser
	//======================================================================
	double2D_ptr ColorMatchingFunctionFile::filterCMFnTranspose(double2D_ptr cmf) {
	    int size = cmf->dim1();
	    //double[][] filtered = new double[size][3];
	    double2D_ptr filtered(new double2D(size, 3));
	    for (int x = 0; x < size; x++) {
		//System.arraycopy(cmf[x], 1, filtered[x], 0, 3);
	    }
	    return DoubleArray::transpose(filtered);
	};
      ColorMatchingFunctionFile::ColorMatchingFunctionFile(const string & filename):Parser(filename)
	{
	};
	CMF_ptr ColorMatchingFunctionFile::getColorMatchingFunction() {
	    this->parsing();
	    CMF_ptr cmf(new ColorMatchingFunction(getSpectraVector()));
	    //ColorMatchingFunction cmf(getSpectraVector());
	    return cmf;
	};
	Spectra_vector_ptr ColorMatchingFunctionFile::getSpectraVector() {
	    int cmfSize = CMF->dim1();
	    int start = (int) (*CMF)[0][0];
	    int end = (int) (*CMF)[cmfSize - 1][0];
	    int interval = (int) ((*CMF)[1][0] - (*CMF)[0][0]);
	    double2D_ptr data = filterCMFnTranspose(CMF);
	    int width = data->dim2();
	    //double1D_ptr(new double1D(

	    Spectra_vector_ptr spectraVector(new Spectra_vector(3));
	    (*spectraVector)[0] =
		Spectra_ptr(new Spectra("CIE X", start, end, interval,
					double1D_ptr(new double1D(width, (*data)
								  [0]))));
	    (*spectraVector)[1] =
		Spectra_ptr(new Spectra("CIE Y", start, end, interval,
					double1D_ptr(new double1D(width, (*data)
								  [1]))));
	    (*spectraVector)[2] =
		Spectra_ptr(new Spectra("CIE Z", start, end, interval,
					double1D_ptr(new double1D(width, (*data)
								  [2]))));
	    return spectraVector;
	};
	void ColorMatchingFunctionFile::parsing() {
	    int count = getCount();
	    CMF = double2D_ptr(new double2D(count, 4));
	    for (int x = 0; x < count; x++) {
		string_vector_ptr tokenize = getTokenize(x);
		if (tokenize->size() != 4) {
		}
		for (int y = 0; y < 4; y++) {
		    string s = (*tokenize)[y];
		    (*CMF)[x][y] = atof(s.c_str());
		    //(*CMF)[x][y] = _toDouble(s);
		}
	    }

	};
	//======================================================================
    };
};

