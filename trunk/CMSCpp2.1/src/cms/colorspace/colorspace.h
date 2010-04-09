#ifndef COLORSPACEH
#define COLORSPACEH

//C系統文件

//C++系統文件
#ifdef __BORLANDC__
# pragma pack(push, 8)
#endif
#include <vector>
#ifdef __BORLANDC__
# pragma pack(pop)
#endif
//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>

namespace cms {
    namespace colorspace {

	class ColorSpace:public jObject /*, NameIF, virtual ValuePropertyIF  */  {

	  private:
	    bool setValuesLocked;
	  protected:
	    virtual int getNumberBands() = 0;
	    virtual double_array _getValues(double_array values) = 0;
	    virtual void _setValues(double_array values) = 0;
	     ColorSpace();
	  public:
	    static double_array
		cartesian2polarCoordinatesValues(double_array
						 cartesianValues);
	    static double_array cartesian2polarCoordinatesValues(double x,
								 double y);

	    bool equalsValues(ColorSpace & colorSpace);

	    string_ptr getName();
	    double_array getValues();
	    double_array getValues(double_array values);
	    static double_array
		polar2cartesianCoordinatesValues(double_array polarValues);
	    static double_array polar2cartesianCoordinatesValues(double
								 distance, double
								 angle);

	    void setValues(double_array values);
	    void setValues(double value1, double value2, double value3);
	    virtual string_vector_ptr getBandNames() = 0;
	    void setValuesLock(bool lock);
	    const string_ptr toString();
	};
    };
};
#endif

