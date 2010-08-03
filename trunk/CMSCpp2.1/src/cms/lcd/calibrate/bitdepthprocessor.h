#ifndef BITDEPTHPROCESSORH
#define BITDEPTHPROCESSORH

//C╰参ゅン

//C++╰参ゅン

//ㄤ畐繷ゅン

//セ兜ヘず繷ゅン
#include "rgbgamma.h"

namespace cms {
    namespace lcd {
	namespace calibrate {
	    class BitDepthProcessor {

		enum BitDepth {
		    b10_10, b10_8, b8_8, b8_6, b6_6, Unknow
		};
	      private:
		const Dep::MaxValue * in, *lut, *out;
		BitDepth bitDepth;
		static BitDepth getBitDepth(const Dep::MaxValue & in, const Dep::MaxValue & out);
		bool tconInput;
	      public:
		 BitDepthProcessor(int inBit, int lutBit, int outBit, bool tconinput);

		/*
		   秖代癬﹍翴
		 */
		int getMeasureStart();
		/*
		   秖代沧ゎ翴
		 */
		int getMeasureEnd();
		/*
		   秖代丁筳
		 */
		int getMeasureStep();
		/*
		   秖代材Ω丁筳(籔ㄤ丁筳ぃ)
		 */
		int getMeasureFirstStep();
		/*
		   程DG
		 */
		double getMaxDigitalCount();
		/*
		   DG羆顶计 (琌257:0~256)
		 */
		int getLevel();
		/*
		   瞷畉钵顶计
		 */
		int getEffectiveLevel();

		bool is8in6Out();
		bool is6in6Out();
		bool is10in8Out();
		bool is10in10Out();
		const Dep::MaxValue & getInputMaxValue();
		const Dep::MaxValue & getLutMaxValue();
		const Dep::MaxValue & getOutputMaxValue();
		bool isTCONInput();

		void setTCONInput(bool tconInput);
		void setInBit(int inBit);
		void setLUTBit(int lutBit);
		void setOutBit(int outBit);
		string_ptr getFRCAbility();
		const Dep::MaxValue & getMeasureMaxValue();

	    };
	};
    };
};
#endif

