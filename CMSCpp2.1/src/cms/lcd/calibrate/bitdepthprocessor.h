#ifndef BITDEPTHPROCESSORH
#define BITDEPTHPROCESSORH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include "rgbgammaop.h"

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
		void setInBit(int inBit);
		void setLUTBit(int lutBit);
		void setOutBit(int outBit);
		string_ptr getFRCAbility();
		const Dep::MaxValue & getFRCAbilityBit();
		const Dep::MaxValue & getMeasureMaxValue();

	    };
	};
    };
};
#endif

