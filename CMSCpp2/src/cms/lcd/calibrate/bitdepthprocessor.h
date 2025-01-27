#ifndef BITDEPTHPROCESSORH
#define BITDEPTHPROCESSORH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
#include "rgbgamma.h"

namespace cms {
    namespace lcd {
	namespace calibrate {
	    class BitDepthProcessor {

		enum BitDepth {
		    b10_10, b10_8, b8_8, b8_6, b6_6
		};
	      private:
		const Dep::MaxValue * in, *lut, *out;
		BitDepth bitDepth;
		static BitDepth getBitDepth(const Dep::MaxValue & in,
					    const Dep::MaxValue & out);
		bool gamma256;
		bool tconInput;
		int getMaxDigitalCountIndex();
		int getMaxEffectiveDigitalCountIndex();
	      public:
		 BitDepthProcessor(int inBit, int lutBit, int outBit,
				   bool gamma256, bool tconinput);

		int getMeasureStart();
		int getMeasureEnd();
		int getMeasureStep();
		int getMeasureFirstStep();
		int getMeasureLevel();
		double getMaxDigitalCount();

		int getLevel();

		int getEffectiveLevel();
		int getFRCBitDepth();
		const Dep::MaxValue & getFRCMaxValue();
		bool is8in6Out();
		bool is6in6Out();
		bool is10in8Out();
		const Dep::MaxValue & getInputMaxValue();
		const Dep::MaxValue & getLutMaxValue();
		const Dep::MaxValue & getOutputMaxValue();
		bool isGamma256();
		bool isTCONInput();

		void setGamma256(bool gamam256);
		void setTCONInput(bool tconInput);
		void setInBit(int inBit);
		void setLUTBit(int lutBit);
		void setOutBit(int outBit);

	    };
	};
    };
};
#endif

