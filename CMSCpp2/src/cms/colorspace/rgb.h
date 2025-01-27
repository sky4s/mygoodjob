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
		 RGBColor(const RGBColorSpace & rgbColorSpace,
			  double_array rgb, const MaxValue & maxValue);
		 RGBColor(int r, int g, int b);
		 RGBColor(double r, double g, double b);
		 RGBColor(const RGBColorSpace & rgbColorSpace,
			  XYZ_ptr XYZ);
		double_array _getValues(double_array values);
		void _setValues(double_array values);
		string_vector_ptr getBandNames();

		void changeMaxValue(const MaxValue & type,
				    bool integerRoundDown);
		void changeMaxValue(const MaxValue & type);
		void addValue(const Channel & channel, double addvalue);
		void addValue(double addvalue);
		double getValue(const Channel & channel);
		void setValue(const Channel & channel, double value);
		const Channel & getMinChannel();
		const Channel & getMaxChannel();
		RGB_ptr clone();
		static const RGB_ptr White;
		static const RGB_ptr Black;
		void quantization(const MaxValue & maxValue);
		void quantization(const MaxValue & maxValue,
				  bool integerRoundDown);
	      protected:
		const MaxValue *maxValue;
		const RGBColorSpace *rgbColorSpace;

		static void changeMaxValue(double_array values,
					   const MaxValue & srcType,
					   const MaxValue & destType,
					   bool integerRoundDown);
		static double_array changeIntegerMaxValue(double_array
							  integerValues,
							  const MaxValue &
							  srcType,
							  const MaxValue &
							  destType,
							  bool roundDown);
		static double_array changeMaxValue(double_array normal100,
						   const MaxValue & type,
						   bool integerRoundDown);

		static double_array normalizeTo100(double_array values,
						   const MaxValue &
						   maxValue);
		int getNumberBands();
	    };
	};
    };
};

#endif

