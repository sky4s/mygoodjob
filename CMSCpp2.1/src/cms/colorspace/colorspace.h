#ifndef COLORSPACEH
#define COLORSPACEH

//C�t�Τ��

//C++�t�Τ��
#ifdef __BORLANDC__
# pragma pack(push, 8)
#endif
#include <vector>
#ifdef __BORLANDC__
# pragma pack(pop)
#endif
//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>
#include <cms/cms.h>

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
	    static double_array getValuesArray(double value1, double value2, double value3);
	  public:
	    static double_array cartesian2polarCoordinatesValues(double_array cartesianValues);
	    static double_array cartesian2polarCoordinatesValues(double x, double y);

	    bool equalsValues(ColorSpace & colorSpace);
	    bool equalsValues(ColorSpace_ptr colorSpace);

	    string_ptr getName();
	    double_array getValues();
	    double_array getValues(double_array values);
	    static double_array polar2cartesianCoordinatesValues(double_array polarValues);
	    static double_array polar2cartesianCoordinatesValues(double
								 distance, double
								 angle);

	    void setValues(double_array values);
	    void setValues(double value1, double value2, double value3);
	    virtual string_vector_ptr getBandNames() = 0;
	    void setValuesLock(bool lock);
	    const string_ptr toString();
	    static double_array getValuesFromString(const string_ptr string);
	};
    };
};
#endif

