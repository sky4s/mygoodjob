#include <includeall.h>
#pragma hdrstop
#include "bitdepthprocessor.h"

//C╰参ゅン

//C++╰参ゅン

//ㄤ畐繷ゅン

//セ兜ヘず繷ゅン

namespace cms {
    namespace lcd {
	namespace calibrate {

	    using namespace Dep;
	    using namespace java::lang;

	    //==================================================================
	    // BitDepthProcessor
	    //==================================================================
	     BitDepthProcessor::BitDepth BitDepthProcessor::
		getBitDepth(const Dep::MaxValue & in, const Dep::MaxValue & out) {
		if (in == MaxValue::Int10Bit && out == MaxValue::Int10Bit) {
		    return b10_10;
		} else if (in == MaxValue::Int10Bit && out == MaxValue::Int8Bit) {
		    return b10_8;
		} else if (in == MaxValue::Int8Bit && out == MaxValue::Int8Bit) {
		    return b8_8;
		} else if (in == MaxValue::Int8Bit && out == MaxValue::Int6Bit) {
		    return b8_6;
		} else if (in == MaxValue::Int6Bit && out == MaxValue::Int6Bit) {
		    return b6_6;
		} else {
		    return Unknow;
		}
	    };


	  BitDepthProcessor::BitDepthProcessor(int inBit, int lutBit, int outBit, bool tconInput):tconInput
		(tconInput)
	    {
		in = &MaxValue::getByIntegerBit(inBit);
		lut = &MaxValue::getByIntegerBit(lutBit);
		out = &MaxValue::getByIntegerBit(outBit);
		bitDepth = getBitDepth(*in, *out);
	    };

	    /*
	       秖代癬翴
	     */
	    int BitDepthProcessor::getMeasureStart() {
		switch (bitDepth) {
		case b10_10:
		    return tconInput ? 4095 : 255;
		case b10_8:
		case b8_8:
		    return tconInput ? 4080 : 255;
		case b8_6:
		case b6_6:
		    return tconInput ? 4032 : 252;
		default:
		    throw IllegalStateException("Unsupported bitDepth: " + bitDepth);
		}
	    };
	    /*
	       秖代沧翴
	     */
	    int BitDepthProcessor::getMeasureEnd() {
		switch (bitDepth) {
		case b10_10:
		case b10_8:
		case b8_8:
		case b8_6:
		case b6_6:
		    return 0;
		default:
		    throw IllegalStateException("Unsupported bitDepth: " + bitDepth);
		}
	    };
	    /*
	       秖代step
	     */
	    int BitDepthProcessor::getMeasureStep() {
		switch (bitDepth) {
		case b10_10:
		    return tconInput ? 16 : 1;
		case b10_8:
		case b8_8:
		    return tconInput ? 16 : 1;
		case b8_6:
		    return tconInput ? 16 : 1;
		case b6_6:
		    return tconInput ? 16 : 4;
		default:
		    throw IllegalStateException("Unsupported bitDepth: " + bitDepth);
		}
	    };

	    int BitDepthProcessor::getMeasureFirstStep() {
		switch (bitDepth) {
		case b10_10:
		    return tconInput ? 15 : 1;
		case b10_8:
		case b8_8:
		    return tconInput ? 16 : 1;
		case b8_6:
		    return tconInput ? 16 : 1;
		case b6_6:
		    return tconInput ? 16 : 4;
		default:
		    throw IllegalStateException("Unsupported bitDepth: " + bitDepth);
		}
	    };
	    /*
	       DG Lut程(in 8Bit)
	     */
	    double BitDepthProcessor::getMaxDigitalCount() {
		switch (bitDepth) {
		case b10_10:
		    return 256;
		case b10_8:
		case b8_8:
		    return 255;
		case b8_6:
		case b6_6:
		    return 252;
		default:
		    throw IllegalStateException("Unsupported bitDepth: " + bitDepth);
		}
	    };

	    int BitDepthProcessor::getLevel() {
		return 257;
	    };
	    int BitDepthProcessor::getLevelInTCon() {
		switch (bitDepth) {
		case b10_10:
		case b10_8:
		    return 257;
		case b8_8:
		case b8_6:
		case b6_6:
		    return 256;
		default:
		    throw IllegalStateException("Unsupported bitDepth: " + bitDepth);
		}
	    };
	    int BitDepthProcessor::getEffectiveLevel() {
		return getMaxDigitalCount() + 1;
	    };
	    bool BitDepthProcessor::is8in8Out() {
		return bitDepth == b8_8;
	    };
	    bool BitDepthProcessor::is8in6Out() {
		return bitDepth == b8_6;
	    };
	    bool BitDepthProcessor::is6in6Out() {
		return bitDepth == b6_6;
	    };
	    bool BitDepthProcessor::is10in8Out() {
		return bitDepth == b10_8;
	    };
	    bool BitDepthProcessor::is10in10Out() {
		return bitDepth == b10_10;
	    };

	    const Dep::MaxValue & BitDepthProcessor::getInputMaxValue() {
		return *in;
	    };
	    const Dep::MaxValue & BitDepthProcessor::getLutMaxValue() {
		return *lut;
	    };
	    const Dep::MaxValue & BitDepthProcessor::getOutputMaxValue() {
		return *out;
	    };

	    bool BitDepthProcessor::isTCONInput() {
		return tconInput;
	    };

	    void BitDepthProcessor::setTCONInput(bool tconInput) {
		this->tconInput = tconInput;
	    };
	    void BitDepthProcessor::setInBit(int inBit) {
		in = &MaxValue::getByIntegerBit(inBit);
		bitDepth = getBitDepth(*in, *out);
	    };
	    void BitDepthProcessor::setLUTBit(int lutBit) {
		lut = &MaxValue::getByIntegerBit(lutBit);
	    };
	    void BitDepthProcessor::setOutBit(int outBit) {
		out = &MaxValue::getByIntegerBit(outBit);
		bitDepth = getBitDepth(*in, *out);
	    };
	    string_ptr BitDepthProcessor::getFRCAbility() {
		switch (bitDepth) {
		case b10_10:
		    return string_ptr(new string("10+2"));
		case b10_8:
		    return string_ptr(new string("8+3"));
		case b8_8:
		    if (*lut == MaxValue::Int12Bit) {
			return string_ptr(new string("8+3"));
		    } else {
			return string_ptr(new string("8+2"));
		    }
		case b8_6:
		case b6_6:
		    return string_ptr(new string("6+3"));
		default:
		    return string_ptr(new string("N/A"));
		}
	    };
	    const Dep::MaxValue & BitDepthProcessor::getFRCAbilityBit() {
		switch (bitDepth) {
		case b10_10:
		    return MaxValue::Int12Bit;
		case b10_8:
		    return MaxValue::Int11Bit;
		case b8_8:
		    if (*lut == MaxValue::Int12Bit) {
			return MaxValue::Int11Bit;
		    } else {
			return MaxValue::Int10Bit;
		    }
		case b8_6:
		case b6_6:
		    return MaxValue::Int9Bit;
		default:
		    throw IllegalStateException();
		}
	    };
	    const Dep::MaxValue & BitDepthProcessor::getMeasureMaxValue() {
		const MaxValue & maxValue = isTCONInput()? MaxValue::Int12Bit : MaxValue::Int8Bit;
		return maxValue;
	    };
	    //==================================================================
	};
    };
};

