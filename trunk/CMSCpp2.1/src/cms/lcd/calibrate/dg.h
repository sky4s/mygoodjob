#ifndef dgH
#define dgH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "common.h"

namespace cms {
    namespace lcd {
	namespace calibrate {
	    /*
	       根據量測結果, 產生需求的DG Lut
	     */
	    class DGLutGenerator {
	      private:
		enum Mode {
		    Component, WLumi, RGBLumi,
		};
		KeepMaxLuminance keepMaxLuminance;
		bool rCorrect, gCorrect, bCorrect;
	      protected:
		 Mode mode;
		Component_vector_ptr componentVector;
		double_vector_ptr luminanceVector;
		double_vector_ptr rLuminanceVector, gLuminanceVector, bLuminanceVector;
		double minLuminance, maxLuminance;
		 bptr < ComponentLUT > lut;
		 bptr < ComponentLinearRelation > componentRelation;
		 bptr < Interpolation1DLUT > wlut;
		double getMaximumIntensity();
		void initComponent(Component_vector_ptr componentVector,
				   bool keepTargetWhiteMaxLuminance);
	      public:
		 DGLutGenerator(Component_vector_ptr componentVector);
		 DGLutGenerator(Component_vector_ptr componentVector,
				KeepMaxLuminance keepMaxLuminance);
		 DGLutGenerator(double_vector_ptr luminanceVector);
		RGB_ptr getDGCode(double rIntensity, double gIntensity, double bIntensity);
		RGB_ptr getDGCode(double rIntensity, double gIntensity,
				  double bIntensity, bool correctInRange);
		RGB_vector_ptr getCCTDGLut(RGBGamma_ptr normalRGBGammaCurve);
		RGB_vector_ptr getGammaDGLut(double_vector_ptr normalGammaCurve);

		//由gamma curve轉rgb intensity
		RGBGamma_ptr getRGBGamma(double_vector_ptr normalGammaCurve);
		double_vector_ptr getLuminanceGammaCurve(double_vector_ptr normalGammaCurve);

		double getMaxBIntensity();
		double_vector_ptr getIntensityVector(const Dep::
						     Channel & ch, RGB_vector_ptr rgbVector);
		RGB_ptr getIntensity(RGB_ptr dgcode);
		RGB_ptr getIntensity(RGB_ptr dgcode, bool correctInRange);
		bool_array isCorrectIntensityInRange();
		__property double MaxLuminance = { write = maxLuminance };
		__property bool RCorrect = { read = rCorrect };
		__property bool GCorrect = { read = gCorrect };
		__property bool BCorrect = { read = bCorrect };
	    };
	};
    };
};

#endif

