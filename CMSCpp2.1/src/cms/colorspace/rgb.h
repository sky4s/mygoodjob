#ifndef RGBH
#define RGBH

#include "depend.h"
#define RGBNumberBands 3

namespace cms {
    namespace colorspace {
	namespace depend {
	    class RGBColor:public RGBBase {
	      public:
		double R, G, B;

		 RGBColor();
		 RGBColor(const MaxValue & maxValue);
		 RGBColor(const RGBColorSpace & rgbColorSpace,
			  double_array rgb, const MaxValue & maxValue);
		 RGBColor(int r, int g, int b);
		 RGBColor(double r, double g, double b, const MaxValue & maxValue);
		 RGBColor(double r, double g, double b);
		 RGBColor(const RGBColorSpace & rgbColorSpace, XYZ_ptr XYZ);
		string_vector_ptr getBandNames();

		void changeMaxValue(const MaxValue & type, bool integerRoundDown);
		void changeMaxValue(const MaxValue & type);
		void addValue(const Channel & channel, double addvalue);
		void addValue(double addvalue);
		double getValue(const Channel & channel);
		double getValue(const Channel & channel, const MaxValue & type);
		double_array getValues(double_array values, const MaxValue & type);
		double_array getValues();
		double_array getValues(double_array values);
		void setValue(const Channel & channel, double value);
		const Channel & getMinChannel();
		const Channel & getMaxChannel();
		RGB_ptr clone();
		static const RGB_ptr White;
		static const RGB_ptr Black;
		void quantization(const MaxValue & maxValue);
		void quantization(const MaxValue & maxValue, bool integerRoundDown);
		const MaxValue & getMaxValue();
		double_array getRGBRatio();
		double getHue();
		//double_array getHSVIValues();
		//static RGB_ptr fromHSVValues(double h, double s, double v);
		//static double_array HSV2RGBValues(double h, double s, double v);
		TColor getColor();

		static XYZ_ptr toXYZ(RGB_ptr rgb, const RGBColorSpace & rgbColorSpace);

		static double_array toXYZValues(double_array rgbValues,
						const RGBColorSpace & rgbColorSpace);
		static double_array linearToXYZValues(double_array rgbValues,
						      const RGBColorSpace & rgbColorSpace);
		XYZ_ptr toXYZ();
		static RGB_ptr fromXYZ(XYZ_ptr XYZ, const RGBColorSpace & colorSpace);
		static double_array fromXYZValues(double_array XYZValues,
						  const RGBColorSpace & colorSpace);

		static boolean isLegal(double value, const MaxValue & maxValue);
		boolean isLegal();
	      protected:
		 boolean isLegal(double value);
		double_array _getValues(double_array values);
		void _setValues(double_array values);
		/*
		   MaxValue�MRGBColorSpace�ĥΫ���(���󤣥�smart_ptr)����]:

		   �ѩ�MaxValue�MRGBColorSpace�쥻�O�]�p��java����enum, ��ӼƤ��|����,
		   �ҥH���ĥ�reference�N�n; ��c++�U��reference����re-assign, ��re-assign�ݨD,
		   �]���u��Ҽ{�ĥΫ���.

		   ���Хi���c����(�ǲΫ���)�Ϊ�smart_ptr���.
		   �Y�ĥ�smart_ptr, �n�����s�b��MaxValue��RGBColorSpace����const reference
		   �H���}�B����ܬ�����, �A���w��smart_ptr. ���OMaxValue�MRGBColorSpace
		   �u���b�t�ε������ɭԤ~�|�Q����(�L�O�R�A���O�ܼ�, �Ѩt�Φ۰ʰ������ʧ@),
		   �ҥH�ڥ��S��smart_ptr�s�b�����n��. (�]��������Ѧҭp�ƥû�>=1, ���|�Q����))
		   �]�����c����, �h�������n��smart_ptr�Ѧҭp��effort(���Meffort���ӫܤp)

		 */
		const MaxValue *maxValue;
		const RGBColorSpace *rgbColorSpace;

		static void changeMaxValue(double_array values,
					   const MaxValue & srcType,
					   const MaxValue & destType, bool integerRoundDown);
		static double_array changeIntegerMaxValue(double_array
							  integerValues,
							  const MaxValue &
							  srcType,
							  const MaxValue &
							  destType, bool roundDown);
		static double_array changeMaxValue(double_array normal100,
						   const MaxValue & type, bool integerRoundDown);

		static double_array normalizeTo100(double_array values, const MaxValue & maxValue);
		int getNumberBands();
	    };
	};
    };
};

#endif

