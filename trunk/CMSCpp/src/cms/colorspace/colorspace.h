#ifndef COLORSPACEH
#define COLORSPACEH

//C系統文件

//C++系統文件
#include <vector>
//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>

namespace cms {
    namespace colorspace {

	class ColorSpace:public java::lang::Object /*, NameIF, virtual ValuePropertyIF  */  {

	  private:
	    bool setValuesLocked;
	  protected:
	    virtual int getNumberBands() = 0;
	    virtual boost::shared_array <
		double >_getValues(boost::shared_array < double >values) =
		0;
	    virtual void _setValues(boost::shared_array < double >values) =
		0;
	     ColorSpace();
	  public:
	    static boost::shared_array < double >
		cartesian2polarCoordinatesValues(boost::shared_array <
						 double >cartesianValues);
	    static boost::shared_array < double >
		cartesian2polarCoordinatesValues(double x, double y);

	    bool equalsValues(ColorSpace & colorSpace);

	     boost::shared_ptr < std::string > getName();
	     boost::shared_array < double >getValues();
	     boost::shared_array < double >getValues(boost::shared_array <
						     double >values);
	    static boost::shared_array <
		double >polar2cartesianCoordinatesValues(boost::
							 shared_array <
							 double
							 >polarValues);
	    static boost::shared_array <
		double >polar2cartesianCoordinatesValues(double
							 distance, double
							 angle);

	    void setValues(boost::shared_array < double >values);
	    void setValues(double value1, double value2, double value3);
	    virtual vector_string_ptr getBandNames() = 0;
	    void setValuesLock(bool lock);

	};
    };
};
#endif

