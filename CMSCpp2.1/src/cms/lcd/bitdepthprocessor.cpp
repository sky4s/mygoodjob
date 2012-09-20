#include <includeall.h>
#pragma hdrstop
#include "bitdepthprocessor.h"

//C╰参ゅン

//C++╰参ゅン

//ㄤ畐繷ゅン

//セ兜ヘず繷ゅン

namespace cms {
    namespace lcd {

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

	const Dep::MaxValue & BitDepthProcessor::getOutputMaxValue(BitDepth bitDepth) {
	    switch (bitDepth) {
	    case b10_10:
		return MaxValue::Int10Bit;
	    case b10_8:
		return MaxValue::Int8Bit;
	    case b8_8:
		return MaxValue::Int8Bit;
	    case b8_6:
		return MaxValue::Int6Bit;
	    case b6_6:
		return MaxValue::Int6Bit;
	    };
	};
	const int BitDepthProcessor::getFRCOnlyBit(BitDepth bitDepth) {
	    switch (bitDepth) {
	    case b10_10:
		return 2;
	    case b10_8:
		return 3;
	    case b8_8:
		return 3;
	    case b8_6:
		return 3;
	    case b6_6:
		return 3;
	    };
	};

      BitDepthProcessor::BitDepthProcessor(int inBit, int lutBit, int outBit, bool tconInput, int tconInputBit):tconInput(tconInput)
	{
	    in = &MaxValue::getByIntegerBit(inBit);
	    lut = &MaxValue::getByIntegerBit(lutBit);
	    out = &MaxValue::getByIntegerBit(outBit);
	    bitDepth = getBitDepth(*in, *out);
	};
	BitDepthProcessor::BitDepthProcessor(int inBit, int lutBit, int outBit,
					     bool tconInput):tconInput(tconInput) {
	    in = &MaxValue::getByIntegerBit(inBit);
	    lut = &MaxValue::getByIntegerBit(lutBit);
	    out = &MaxValue::getByIntegerBit(outBit);
	    bitDepth = getBitDepth(*in, *out);
	};

	BitDepthProcessor::BitDepthProcessor(int inBit, int lutBit, int outBit):tconInput(false) {
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
	    case b6_6:
		return tconInput ? 16 : 4;
	    default:
		throw IllegalStateException("Unsupported bitDepth: " + bitDepth);
	    }
	};

	double BitDepthProcessor::getInputMaxDigitalCount() {
	    switch (bitDepth) {
	    case b10_10:
	    case b10_8:
		return 256;
	    case b8_8:
	    case b8_6:
		return 255;
	    case b6_6:
		return 252;
	    default:
		throw IllegalStateException("Unsupported bitDepth: " + bitDepth);
	    }
	};
	double BitDepthProcessor::getOutputMaxDigitalCount() {
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
	int BitDepthProcessor::getEffectiveInputLevel() {
	    return getInputMaxDigitalCount() + 1;
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
	    if (Unknow == bitDepth) {
		return string_ptr(new string("N/A"));
	    } else if (b8_8 == bitDepth) {
		if (*lut == MaxValue::Int12Bit) {
		    return string_ptr(new string("8+3"));
		} else if (*lut == MaxValue::Int10Bit) {
		    return string_ptr(new string("8+2"));
		}
	    } else {
		const Dep::MaxValue & output = getOutputMaxValue(bitDepth);
		int frcOnlyBit = getFRCOnlyBit(bitDepth);
		string result = _toString(output.bit) + "+" + _toString(frcOnlyBit);
		return string_ptr(new string(result));
	    }

	    /*switch (bitDepth) {
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
	       } */
	};
	const Dep::MaxValue & BitDepthProcessor::getFRCAbilityBit() {
	    if (Unknow == bitDepth) {
		throw IllegalStateException();
	    } else if (b8_8 == bitDepth) {
		if (*lut == MaxValue::Int12Bit) {
		    return MaxValue::Int11Bit;
		} else if (*lut == MaxValue::Int10Bit) {
		    return MaxValue::Int11Bit;
		}
	    } else {
		const Dep::MaxValue & output = getOutputMaxValue(bitDepth);
		int frcOnlyBit = getFRCOnlyBit(bitDepth);
		int totalbit = output.bit + frcOnlyBit;
		return MaxValue::getByIntegerBit(totalbit);
	    }

	    /*switch (bitDepth) {
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
	       } */
	};
	const int BitDepthProcessor::getFRCOnlyBit() {
	    return getFRCOnlyBit(bitDepth);
	};
	const Dep::MaxValue & BitDepthProcessor::getMeasureMaxValue() {
	    const MaxValue & maxValue = isTCONInput()? MaxValue::Int12Bit : MaxValue::Int8Bit;
	    return maxValue;
	};
	//==================================================================

      PanelInfo::PanelInfo(bptr < BitDepthProcessor > bitDepth):bitDepth(bitDepth),
	    tconContrl(bptr < i2c::TCONControl >
		       ((i2c::TCONControl *) null)), tconInput(false) {
	    if (bitDepth->isTCONInput()) {
		throw new IllegalArgumentException("");
	    }
	};
      PanelInfo::PanelInfo(bptr < BitDepthProcessor > bitDepth, bptr < i2c::TCONControl > tconContrl):bitDepth(bitDepth),
	    tconContrl(tconContrl), tconInput(true)
	{
	    if (null == tconContrl || !bitDepth->isTCONInput()) {
		throw new IllegalArgumentException("");
	    }
	};
	void PanelInfo::setPCWithTCONInput(bool enable) {
	    if (enable) {
		if (!tconInput) {
		    throw new IllegalStateException("");
		} else {
		    pcWithTCONInput = true;
		}
	    } else {
		pcWithTCONInput = false;
	    }

	};
    };
};

