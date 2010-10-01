#ifndef CMFH
#define CMFH
//C系統文件

//C++系統文件

//其他庫頭文件
//#include <vcl.h>
//本項目內頭文件

//#define USE_QUERY

namespace cms {
    namespace colorformat {

	class Parser {
	  private:
	    bptr < TStringList > strList;

	  public:
	    Parser(const string & filename);
	    int getCount();
	    string_vector_ptr getTokenize(int index);
	    //virtual void parsing() = 0;
	};
	class ColorMatchingFunctionFile:public Parser {
	  private:
	    double2D_ptr CMF;
	    double2D_ptr filterCMFnTranspose(double2D_ptr cmf);
	  public:
	     ColorMatchingFunctionFile(const string & filename);
	    CMF_ptr getColorMatchingFunction();
	    Spectra_vector_ptr getSpectraVector();
	    void parsing();
	};
    };
};
#endif

