#ifndef BITDEPTHPROCESSORH
#define BITDEPTHPROCESSORH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
//#include "rgbgammaop.h"

namespace cms {
    namespace lcd {
	class BitDepthProcessor {

	    enum BitDepth {
		b10_10, b10_8, b8_8, b8_6, b6_6, Unknow
	    };
	  private:
	    const Dep::MaxValue * in, *lut, *out;
	    BitDepth bitDepth;
	    static BitDepth getBitDepth(const Dep::MaxValue & in, const Dep::MaxValue & out);
	    bool tconInput;
	    //bptr < i2c::TCONControl > tconContrl;
	  public:
	     BitDepthProcessor(int inBit, int lutBit, int outBit, bool tconinput);
	     BitDepthProcessor(int inBit, int lutBit, int outBit);

	    /*
	       �q���_�l�I
	     */
	    int getMeasureStart();
	    /*
	       �q���פ��I
	     */
	    int getMeasureEnd();
	    /*
	       �q�����j
	     */
	    int getMeasureStep();
	    /*
	       �q���Ĥ@�����j(�i��P��L���j���P)
	     */
	    int getMeasureFirstStep();
	    /*
	       �̤j��DG��(�o��)
	     */
	    //double getMaxDigitalCount();

	    /*
	       ��J�ݳ̤j��DG(�T��)
	     */
	    double getInputMaxDigitalCount();
	    /*
	       ��X�ݳ̤j��DG(to Panel)
	     */
	    double getOutputMaxDigitalCount();

	    /*
	       DG���`���� (�@�߬O257:0~256)
	     */
	    int getLevel();
	    /*
	       TCon�U�����DG�`����
	     */
	    int getLevelInTCon();
	    /*
	       �i�e�{�X�t��������
	     */
	    int getEffectiveInputLevel();

	    bool is8in8Out();
	    bool is8in6Out();
	    bool is6in6Out();
	    bool is10in8Out();
	    bool is10in10Out();
	    const Dep::MaxValue & getInputMaxValue();
	    const Dep::MaxValue & getLutMaxValue();
	    const Dep::MaxValue & getOutputMaxValue();
	    bool isTCONInput();

	    void setTCONInput(bool tconInput);
	    //void setTCONInput(bptr < i2c::TCONControl > tconContrl);
	    //bptr < i2c::TCONControl > getTCONControl();
	    void setInBit(int inBit);
	    void setLUTBit(int lutBit);
	    void setOutBit(int outBit);
	    string_ptr getFRCAbility();
	    const Dep::MaxValue & getFRCAbilityBit();
	    const Dep::MaxValue & getMeasureMaxValue();

	};

	enum PatternSource {
	    PC, TCON, DGLUT
	};

	/*
	   PanelInfo= BitDepthProcessor+ TCONControl
           ���BitDepthProcessor�PTCONControl���ӬO��K�j�b�@�_��
           ���O�ثe������
	 */
	class PanelInfo {
	  private:
	    const bool tconInput;
	    bool pcWithTCONInput;
	    PatternSource patternSource;
	    void setPCWithTCONInput(bool enable);
	  public:
	    const bptr < BitDepthProcessor > bitDepth;
	    const bptr < i2c::TCONControl > tconContrl;
	     PanelInfo(bptr < BitDepthProcessor > bitDepth);
	     PanelInfo(bptr < BitDepthProcessor > bitDepth, bptr < i2c::TCONControl > tconContrl);
	    __property bool TCONInput = { read = tconInput };
	    __property bool PCWithTCONInput = { read = pcWithTCONInput, write = setPCWithTCONInput
	    };
	    __property PatternSource PatternSource = { read = patternSource };


	};
    };
};
#endif

