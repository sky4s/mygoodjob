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
	    const Dep::MaxValue * in, *lut, *out;	//, *tcon;
	    BitDepth bitDepth;
	    static BitDepth getBitDepth(const Dep::MaxValue & in, const Dep::MaxValue & out);

	    static const Dep::MaxValue & getOutputMaxValue(BitDepth bitDepth);
	    static const int getFRCOnlyBit(BitDepth bitDepth);
	    bool directGamma;

	  public:
	     bool is10BitDirectGamma();
	    bool is10BitInput();
	     BitDepthProcessor(int inBit, int lutBit, int outBit, bool directGamma);
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
	    bool isDirectGamma();
	    void setDirectGamma(bool directGamma);

	    void setInBit(int inBit);
	    void setLUTBit(int lutBit);
	    void setOutBit(int outBit);
	    string_ptr getFRCAbility();
	    const Dep::MaxValue & getFRCAbilityBit();
	    const int getFRCOnlyBit();
	    const Dep::MaxValue & getMeasureMaxValue();

	};

	enum PatternSource {
	    PC, TCON, DGLUT
	};

	/*
	   PanelInfo= BitDepthProcessor+ TCONControl
	   ���BitDepthProcessor�PTCONControl���ӬO��K�j�b�@�_��
	   ���O�ثe������ ...

	   �����O�|���ҥ�
	 */
	class PanelInfo {
	  private:
	    const bool directGamma;
	    bool pcWithDirectGamma;
	    PatternSource patternSource;
	    void setPCWithDirectGamma(bool enable);
	  public:
	    const bptr < BitDepthProcessor > bitDepth;
	    const bptr < i2c::TCONControl > tconContrl;
	     PanelInfo(bptr < BitDepthProcessor > bitDepth);
	     PanelInfo(bptr < BitDepthProcessor > bitDepth, bptr < i2c::TCONControl > tconContrl);
	    __property bool DirectGamma = { read = directGamma };
	    __property bool PCWithDirectGamma = { read = pcWithDirectGamma, write =
		    setPCWithDirectGamma
	    };
	    __property PatternSource PatternSource = { read = patternSource };


	};
    };
};
#endif

