#include "depend.h"
#include <limits>

namespace cms {
    namespace colorspace {
	const Channel Channel::R = Channel(1, clRed, "R");
	const Channel Channel::G = Channel(2, clGreen, "G");
	const Channel Channel::B = Channel(3, clBlue, "B");
	const Channel Channel::Y = Channel(4, clYellow, "Y");
	const Channel Channel::M = Channel(5, (TColor) 0xff00ff, "M");
	const Channel Channel::C = Channel(6, (TColor) 0xffff00, "C");
	const Channel Channel::W = Channel(7, clWhite, "W");

	const vector < Channel > &Channel::RGBYMCChannel =
	    *getChannelVector(6, R, G, B, Y, M, C);
	const vector < Channel > &Channel::RGBYMCWChannel =
	    *getChannelVector(7, R, G, B, Y, M, C, W);
	const vector < Channel > &Channel::RGBChannel =
	    *getChannelVector(3, R, G, B);
	const vector < Channel > &Channel::RGBWChannel =
	    *getChannelVector(4, R, G, B, W);
	const vector < Channel > &Channel::WRGBChannel =
	    *getChannelVector(4, W, R, G, B);
	const vector < Channel > &Channel::YMCChannel =
	    *getChannelVector(3, Y, M, C);


	const MaxValue MaxValue::Double1(1.);	//正規化
	const MaxValue MaxValue::Double100(100.);	//正規化
	const MaxValue MaxValue::Int5Bit(31., true, false);	//5bit
	const MaxValue MaxValue::Int6Bit(63., true, false);	//6bit
	const MaxValue MaxValue::Int7Bit(127., true, false);	//7bit
	const MaxValue MaxValue::Int8Bit(255., true, true);	//一般常用的RGB code
	const MaxValue MaxValue::Double255(255.);	//各種bit數的RGB code通用
	const MaxValue MaxValue::Int9Bit(510., true, true);	//9bit
	const MaxValue MaxValue::Double1020(1020, false, true);	//10bit
	const MaxValue MaxValue::Int10Bit(1020, true, true);	//10bit
	const MaxValue MaxValue::Int11Bit(2040, true, true);	//11bit
	const MaxValue MaxValue::Double4080(4080, false, true);	//12bit
	const MaxValue MaxValue::Int12Bit(4080, true, true);	//12bit
	const MaxValue MaxValue::Int13Bit(8160, true, true);	//13bit
	const MaxValue MaxValue::Int14Bit(16320, true, true);	//14bit
	const MaxValue MaxValue::Int15Bit(32640, true, true);	//15bit
	const MaxValue MaxValue::Int16Bit(65280, true, true);	//16bit
	const MaxValue MaxValue::Int20Bit(1044480, true, true);	//20bit
	const MaxValue MaxValue::Int24Bit(16711680, true, true);	//24bit
	const MaxValue MaxValue::Int31Bit(2139095040, true, true);	//31bit
	const MaxValue MaxValue::DoubleUnlimited(std::numeric_limits <
						 double >::max()
	    );			//無限制


    };
};

