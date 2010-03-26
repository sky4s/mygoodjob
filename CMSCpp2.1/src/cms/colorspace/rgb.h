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

		string_vector_ptr getBandNames();

		void changeMaxValue(const MaxValue & type,
				    bool integerRoundDown);
		void changeMaxValue(const MaxValue & type);
		void addValue(const Channel & channel, double addvalue);
		void addValue(double addvalue);
		double getValue(const Channel & channel);
		double_array getValues(double_array values,
				       const MaxValue & type);
		double_array getValues();
		double_array getValues(double_array values);
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
		 double_array _getValues(double_array values);
		void _setValues(double_array values);
		/*
		   MaxValue和RGBColorSpace採用指標(為何不用smart_ptr)的原因:

		   由於MaxValue和RGBColorSpace原本是設計成java中的enum, 其個數不會改變,
		   所以採用reference就好, reference不能變動, 但是有變動需求,
		   因此只能考慮採用指標.

		   指標可選擇c指標(傳統指標)或者smart_ptr兩種.
		   若採用smart_ptr, 要把原先存在於MaxValue或RGBColorSpace中的const reference
		   以取址運算改變為指標, 再指定給smart_ptr. 但是MaxValue和RGBColorSpace
		   只有在系統結束的時候才會被消滅(他是靜態類別變數, 由系統自動做消滅動作),
		   所以根本沒有smart_ptr存在的必要性. (因為執行期參考計數永遠>=1, 不會被消滅))
		   因此改用c指標, 去除不必要的smart_ptr參考計數effort(雖然effort應該很小)

		 */
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

