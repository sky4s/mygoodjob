#ifndef TCONCONTROLH
#define TCONCONTROLH
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
//nclude <cms/colorformat/excelfile.h>

namespace i2c {
    class TCONControl {
      private:
	bptr < TCONParameter > parameter;
	bptr < i2cControl > control;
	bptr < i2cControl > control2;
	const bool dualTCON;

      public:
	 TCONControl(bptr < TCONParameter > parameter, bptr < i2cControl > control);
	 TCONControl(bptr < TCONParameter > parameter,
		     bptr < i2cControl > control1, bptr < i2cControl > control2);
	static bptr < cms::util::ByteBuffer > getRGBByteBuffer(int r, int g, int b, const
							       TestRGBBit & testRGBBit);
	void setGammaTestRGB(RGB_ptr rgb);
	void setGammaTestRGB(int r, int g, int b);
	void setGammaTest(bool enable);

	const Dep::MaxValue & getLUTBit();
	void setDGLut(RGB_vector_ptr rgbVector);
	RGB_vector_ptr getDGLut();
	void setDG(bool enable);
	bool isDG();
	unsigned char readByte(int dataAddress);
	void writeByte(int dataAddress, unsigned char data);
	bool isGammaTestEnable();
      private:

	void write(int dataAddress, bptr < cms::util::ByteBuffer > data);
	static int_array getLMHData(int data);

	void setBitData(int dataAddress, unsigned char bit, bool data);
	bool getBitData(int dataAddress, unsigned char bit);
      public:
	static bptr < cms::util::ByteBuffer > getDGLut10BitByteBuffer(RGB_vector_ptr rgbVector);
	static bptr < cms::util::ByteBuffer >
	    getDGLut10BitByteBufferType2(RGB_vector_ptr rgbVector);
	static bptr < cms::util::ByteBuffer > getDGLut12BitByteBuffer(RGB_vector_ptr rgbVector);
    };
};

#endif

