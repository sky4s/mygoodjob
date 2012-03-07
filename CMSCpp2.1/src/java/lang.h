#ifndef LANGH
#define LANGH

#include "java_config.h"

//C�t�Τ��

//C++�t�Τ��
#ifdef __BORLANDC__
# pragma pack(push, 8)
#endif
#include <string>
#include <vector>
#include <exception>
#include <map>

//��L�w�Y���
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

#define TNT_LIB

#ifdef TNT_LIB
#include <tnt/tnt_array1d.h>
#include <tnt/tnt_array2d.h>
#include <tnt/tnt_array3d.h>
#endif

#ifdef __BORLANDC__
# pragma pack(pop)
#endif


//�����ؤ��Y���


//==============================================================================
// include template
//==============================================================================
//C�t�Τ��

//C++�t�Τ��

//vcl�w�Y���

//��L�w�Y���

//�����ؤ��Y���

//�����ؤ�gui�Y���
//==============================================================================

//==============================================================================
// change the byte alignment macro
//==============================================================================
#include <vcl.h>
#ifdef __BORLANDC__
# pragma pack(push, 8)
#endif

#ifdef __BORLANDC__
# pragma pack(pop)
#endif
//==============================================================================

//==============================================================================
// �w���ŧi, �i�H���include .h���ݭn
//==============================================================================
namespace java {
    namespace lang {
	class Object;
    };
};

namespace math {
    class Interpolation1DLUT;
    class DoubleArray;
    class FloatArray;
};

namespace i2c {
    class TestRGBBit;
    class i2cControl;
    class TCONParameter;
    class TCONControl;
};


namespace gui {
    namespace util {
	class UIValueSetter;
	class MultiUIBinder;
	class TextFilterIF;
    };
    namespace event {
	class EventListener;
	class WindowListener;
	class WindowAdapter;
	class ChangeListener;
	class ListSelectionListener;
    };
};

//==============================================================================
//==============================================================================
//²��java.lang�ϥΤW������
//==============================================================================
typedef java::lang::Object jObject;
#define null NULL
#define boolean bool
//==============================================================================

//==============================================================================
//²��boost::smart_ptr�ϥΤW������
//==============================================================================
#define bptr boost::shared_ptr
#define barray boost::shared_array
#define bwptr boost::weak_ptr
//scope����smart_ptr
#define bptr_ boost::scoped_ptr

#define Object_ptr bptr < jObject >
typedef bptr < std::string > string_ptr;
typedef bptr < AnsiString > String_ptr;
#define nil_string_ptr string_ptr ((std::string*)NULL)

#define nil_int_vector_ptr int_vector_ptr ((int_vector*)NULL)
#define nil_int_vector nil_int_vector_ptr
typedef std::vector < int >int_vector;
typedef bptr < int_vector > int_vector_ptr;

typedef std::vector < bool > bool_vector;
typedef bptr < bool_vector > bool_vector_ptr;

#define nil_double_vector_ptr double_vector_ptr ((double_vector*)NULL)
#define nil_double_vector nil_double_vector_ptr
typedef std::vector < double >double_vector;
typedef bptr < double_vector > double_vector_ptr;

typedef std::vector < std::string > string_vector;
typedef bptr < string_vector > string_vector_ptr;
typedef std::vector < string_ptr > stringp_vector;
typedef bptr < stringp_vector > stringp_vector_ptr;
typedef std::vector < string_vector_ptr > string_doublevector;
typedef bptr < string_doublevector > string_doublevector_ptr;


typedef barray < double >double_array;
#define nil_double_array double_array ((double*)NULL)
typedef barray < float >float_array;
#define nil_float_array float_array ((float*)NULL)
typedef barray < int >int_array;
#define nil_int_array int_array ((int*)NULL)
typedef barray < short >short_array;
#define nil_short_array short_array ((short*)NULL)
typedef barray < bool > bool_array;

//boost���Ѫ�foreach, �Y�n��vector<int> ivec��foreach, �y�k��: foreach(const int & i, ivec) { ... }
#define foreach BOOST_FOREACH
//==============================================================================

//==============================================================================
//²��tnt�ϥΤW������
//==============================================================================
#ifdef TNT_LIB
typedef TNT::Array1D < long double >longdouble1D;
typedef TNT::Array2D < long double >longdouble2D;
typedef bptr < longdouble2D > longdouble2D_ptr;

//#define _USE_LONG_DOUBLE_

#ifdef  _USE_LONG_DOUBLE_
typedef TNT::Array1D < long double >double1D;
typedef TNT::Array2D < long double >double2D;
typedef TNT::Array3D < long double >double3D;
#else
typedef TNT::Array1D < double >double1D;
typedef TNT::Array2D < double >double2D;
typedef TNT::Array3D < double >double3D;
#endif

typedef bptr < double1D > double1D_ptr;
typedef bptr < double2D > double2D_ptr;
typedef bptr < double3D > double3D_ptr;

typedef TNT::Array1D < float >float1D;
typedef TNT::Array2D < float >float2D;
typedef TNT::Array3D < float >float3D;
typedef bptr < float1D > float1D_ptr;
typedef bptr < float2D > float2D_ptr;
typedef bptr < float3D > float3D_ptr;

typedef TNT::Array1D < int >int1D;
typedef TNT::Array2D < int >int2D;
typedef TNT::Array3D < int >int3D;
typedef bptr < int1D > int1D_ptr;
typedef bptr < int2D > int2D_ptr;
typedef bptr < int3D > int3D_ptr;
#endif
//==============================================================================

//==============================================================================
// ²��lexical�ϥΤW������
//==============================================================================
#define _toString boost::lexical_cast < std::string >
#define _toInt boost::lexical_cast < int >
#define _toDouble boost::lexical_cast < double >
#define _toAnsiString(s)\
        AnsiString(s.c_str())
//==============================================================================

//==============================================================================
// ²��stl�ϥΤW������
//==============================================================================
typedef std::map < const std::string, const std::string > StringMap;
typedef bptr < StringMap > StringMap_ptr;
#define nil_StringMap_ptr StringMap_ptr((StringMap *) NULL)

typedef std::map < const std::string, string_vector_ptr > StringVecMap;
typedef bptr < StringVecMap > StringVecMap_ptr;
#define nil_StringVecMap_ptr StringVecMap_ptr((StringVecMap *) NULL)
//==============================================================================

//==============================================================================
// ²��VCL�ϥΤW������
//==============================================================================
typedef std::vector < TControl * >TControl_vector;
typedef bptr < TControl_vector > TControl_vector_ptr;
typedef std::map < TWinControl *, TControl_vector_ptr > TControlVecMap;
typedef bptr < TControlVecMap > TControlVecMap_ptr;
#define nil_TControlVecMap_ptr TControlVecMap_ptr((TControlVecMap *) NULL)
typedef std::vector < TLabel * >TLabel_vector;
typedef bptr < TLabel_vector > TLabel_vector_ptr;
//==============================================================================

//==============================================================================
// ²��binder�ϥΤW������
//==============================================================================
typedef bptr < gui::util::UIValueSetter > uiset_ptr;
typedef bptr < gui::util::MultiUIBinder > mbinder_ptr;
typedef bptr < gui::util::TextFilterIF > TextFilterIF_ptr;
#define nil_TextFilterIF_ptr TextFilterIF_ptr((TextFilterIF *) NULL)
typedef String(*FilterFunction) (const int value);
typedef void __fastcall(__closure * OnChangeFunction) (TObject * sender);
typedef void __fastcall(__closure * OnKeyPressFunction) (TObject * sender, char &Key);
//==============================================================================
/*
 java->C++�ഫ��h

 *override+overload���D
 c++�ʥFjava��interface, ���M�i�Hpure virtual func�N��,
 ���O�|�J��override+overload�H��hide�����D. �B�ϥΤF�h���~��, �|�ޤJ�����~�Ӫ����D.
 �ҥH�b���P���O��overload�ݨD�ɺɶq�קK, �H��W�ѨM; ���L�n�O���j�q��W���ݭn,
 ���ܪ����b�l���O��Qhide��func�I�s�^��.

 *�T��ϥΫ��ФΰѦ�
 �קK�ѰOdelete�����D, �Hsmart_ptr���N����.
 �ҥ~���O, string��@�`�ƪ����p�U, �i�Hconst string &�ϥ�.

 *���󧹥��ĥ�smart_ptr
 �Ѧҷ|���L�k��NULL�����p, �]�����ĥ�smart_ptr, �@������gc���ĪG.
 NULL��smart_ptr���ͤ�k�� shared_array < double >p(NULL);

 *��ͫ��O�}�C�ĥ� ���שT�w: shared_ptr(shared_array)
                   ���פ��w: shared_ptr< vector<> >
 �º�ĥ�vector����, ���M�i�H�F������java array���S��, ���O�@��local vector����
 ��@ref or ptr�Q�ǥX�h, �_�h�i��|���V�@�ӥ������Ŷ�.

 �ҥH�@��O��ĳ�ĥ�shared_ptr< vector<> >, ���O�o�ا@�k�|��indent(�{���X�榡�ƾ�) �X��!
 �]���{�b�Ϊ�indent�Oc�M�ݪ�, �L�ݤ���template��<< >>...�|��@shift�B��l.
 �X�g���դ��U, ���ӨM�w��define�N�i�H�ױ�indent�����D!
 ���O�����O����...�n�@�����_����(*)[]�h���� (�����->[] �o�ةǻy�k..), �ӳ·ФF,
 �ҥH�^�Y��shared_array.

 �V�|���O, shared_array�S��k���D�ۤv������!
 �]��java����double[]�ɶq�Hshared_ptr< vector<> >���N.
 ��List<>�]�wvector<>���N, �]��java���Ϊ�List<>�O�HArrayList��@,
 ��S�ʨ��������STL��vector.

 *�O�_�٭n�ϥΰ}�C?(�Y��ӻ��O���V�ƼƤ���������)
 �ĥ�share_array��i�H���κ޲z�}�C������(��ꤣ�O�}�C, �Y��ӻ��O����).
 ���Oshare_array�ʥF���׸�T, �ݭn�ۤv���@����, share_array����8byte.
 �ĥ�vector+bptr��, ���κ޲z�귽�B���D����, ���Ovector��������24byte.
 double���Ц���4byte�̤�, ���O�\��̳h�F.
 
 �n�O�����֦��O�|���j�q���鲣��, ���share_array.
 �n�O���餣�h, �h���vector+bptr.
 �Y�����D����h��, ��ΫO�I��vector+bptr.

 ��ɿ��share_array: ���פ��ܰ�, ���פw��, �|���j�q����, ������
 ��ɿ��vector+bptr: ���׷|�ܰ�, ���ץ���, ���|���j�q����

 *enum �P Enumeration
 enum�Oc++����, �\��ܮz, �򥻤W�u�O�@�ӱ`�ƥN���Ӥw.
 ���p�G���ݽ������\��, ���enum���F.
 �n�Oenum�ݭn��class�ϥΪ��ɭ�, ��ĳ�ĥ��X�R����Enumeration().
 �w�q��k��: Enumeration(enum_name)
              item1=value, item2=value, ...
             EnumerationEnd();
 �i�H Enumeration::item1�ϥ�, ���n����.
*/

/*
 UI�P����Object�p�������

 UI�W���ﶵ�]�w��, ���w�ݭn�ǰe�줺��Object, �]�w��Object����property(�S�x)
 �]��UI���w�|�I�sObject��setXXX(), ��o�ǰѼƶǰe��Object
 �ҥH�C�h�@���Ѽ�, UI�N�n�I�sObject, Object�]�o�}�۹�M��setXXX() method, �~�i�H�����o���u�@.
 �ѹ����ܺ��H=.=

 ���S����k�i�H�۰ʤƬƦܥb�۰ʤƧ����o��Ʊ��O?
 �γ\�u��z�LsetProperty(propertyName, propertyValue); �o�˪��禡�a!

 __property�o����r�ٺ⤣�����F��! �u�n�bheader�ŧi�N�n! �K�h.cpp�w�qsetXXX���·�!
 �]�n!
*/
namespace java {
    namespace lang {
	class Object;

	class Class {
	  private:

	    friend class Object;
	    const std::type_info & info;
	    Object & object;
	    Class(Object & object);
	  public:
	    const string_ptr getSimpleName() const;
	    const string_ptr getName() const;
	};

	class Object /*:public TObject */  {
	  private:
	    //�Ψӭp�q���ͪ������
	    static int globalID;
	    //�ΨӰO���ثe����ID
	    const int objectID;
	    bool null_;
	    const Class c;
	    string_ptr name;
	  public:
	    const bool equals(Object_ptr obj);
	    const Class & getClass() const;
	    const int hashCode();
	    const string_ptr toString() const;
	    const bool isNull();
	    Object(bool _null_);
	    Object();
	    const int getObjectID();

	  protected:
	    Object_ptr clone();
	    void finalize();
	};

	class Math {
	  public:
	    static double abs(double a);
	    static double sqrt(double a);
	    static double pow(double a, double b);
	    static double atan2(double y, double x);
	    static const double PI;
	    static const double E;
	    static double cos(double x);
	    static double acos(double x);
	    static double sin(double x);
	    static double sqr(double v);
	    static double round(double v);
	    static double floor(double v);
	    static double roundTo(double v);
	    static double log(double v);
	    static double fmod(double x, double y);

	    static double min(double a, double b);
	    static double max(double a, double b);
#ifdef TNT_LIB
	    static double max(double1D_ptr values);
#endif

	    static int maxIndex(short_array values, int n);
	    static short max(short_array values, int n);
	    static int minIndex(short_array values, int n);
	    static short min(short_array values, int n);

	    static int maxIndex(double_array values, int n);
	    static double max(double_array values, int n);
	    static int minIndex(double_array values, int n);
	    static double min(double_array values, int n);
	    static int maxIndex(double_vector_ptr values);
	    static int minIndex(double_vector_ptr values);
	    static double max(double_vector_ptr values);
	    static double min(double_vector_ptr values);



	    static double_vector_ptr normalize(double_vector_ptr original, double normal);
	    static double cubeRoot(double x);
	    static double exp(double x);
	    static double atan2deg(double b, double a);
	};

	/*
	 *�ҥ~��t
	 ������sjava�ҥ~��t, Exception���̤W�h���O, �䩳�U��RuntimeException.
	 ��RuntimeException�U�S���̱`�Ϊ��X�بҥ~.
	 */
	class Exception:public Object, std::exception {
	  public:
	    Exception();
	    Exception(std::string message);
	    std::string & toString();
	  private:
	    std::string message;
	};


	class RuntimeException:public Exception /*, std::runtime_error */  {
	  public:
	    RuntimeException();
	    RuntimeException(std::string message);
	};
	class IllegalStateException:public RuntimeException {
	  public:
	    IllegalStateException();
	    IllegalStateException(std::string message);
	};

	class IllegalArgumentException:public RuntimeException	/*,
								   std::invalid_argument */  {
	  public:
	    IllegalArgumentException();
	    IllegalArgumentException(std::string message);
	};
	class UnsupportedOperationException:public RuntimeException {
	  public:
	    UnsupportedOperationException();
	    UnsupportedOperationException(std::string message);
	};
	class IndexOutOfBoundsException:public RuntimeException	/*,
								   std::range_error */  {
	  public:
	    IndexOutOfBoundsException();
	    IndexOutOfBoundsException(std::string message);
	};
    };
};

//==============================================================================
// �X�R��enum, ���n��Enumeration�ܦ� &!
//==============================================================================
#define Enumeration(E) \
struct E \
{ \
public: \
     E(int value = 0) : _value((__Enum)value) { \
     } \
     E& operator=(int value) { \
         this->_value = (__Enum)value; \
         return *this; \
     } \
     operator int() const { \
         return this->_value; \
     } \
\
     enum __Enum {

#define EnumerationEnd() \
     }; \
\
private: \
     __Enum _value; \
};
//==============================================================================

//==============================================================================
// Property���O
// http://www.codeguru.com/cpp/cpp/cpp_mfc/article.php/c4031/
//==============================================================================
#define READ_ONLY 1
#define WRITE_ONLY 2
#define READ_WRITE 3

template < typename Container, typename ValueType, int nPropType > class Property {
  public:
    Property() {
	m_cObject = NULL;
	Set = NULL;
	Get = NULL;
    }
//-- This to set a pointer to the class that contain the//   property --
	void setContainer(Container * cObject) {
	m_cObject = cObject;
    }
//-- Set the set member function that will change the value --
    void setter(void (Container::*pSet) (ValueType value)) {
	if ((nPropType == WRITE_ONLY) || (nPropType == READ_WRITE))
	    Set = pSet;
	else
	    Set = NULL;
    }
//-- Set the get member function that will retrieve the value --
    void getter(ValueType(Container::*pGet) ()) {
	if ((nPropType == READ_ONLY) || (nPropType == READ_WRITE))
	    Get = pGet;
	else
	    Get = NULL;
    }
//-- Overload the '=' sign to set the value using the set
//   member --
    ValueType operator =(const ValueType & value) {
	assert(m_cObject != NULL);
	assert(Set != NULL);
	(m_cObject->*Set) (value);
	return value;
    }
//-- To make possible to cast the property class to the
//   internal type --
    operator                                                                         ValueType() {
	assert(m_cObject != NULL);
	assert(Get != NULL);
	return (m_cObject->*Get) ();
    }
  private:
    Container * m_cObject;	//-- Pointer to the module that
    //   contains the property --
    void (Container::*Set) (ValueType value);
    //-- Pointer to set member function --
    ValueType(Container::*Get) ();
    //-- Pointer to get member function --
};

//==============================================================================

#endif

