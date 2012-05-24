#ifndef COMPONENTH
#define COMPONENTH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include <math/regression.h>
#include "rgbgammaop.h"
#include <gui/event/listener.h>

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace math;
	    class Component:public jObject {
	      public:
		Component(RGB_ptr rgb, RGB_ptr intensity);
		Component(RGB_ptr rgb, RGB_ptr intensity, XYZ_ptr XYZ);
		Component(RGB_ptr rgb, RGB_ptr intensity, XYZ_ptr XYZ, RGB_ptr gamma);
		Component(Component_ptr c);
		Component(Patch_ptr p);
		RGB_ptr rgb;
		RGB_ptr intensity;
		XYZ_ptr XYZ;
		RGB_ptr gamma;
	    };

	    /*
	       ComponentFetcher =  IntensityAnalyzerIF+ BitDepthProcessor
	       �L�hAnalzyer�����w���(CA-2/310) �n���.
	       �{�b�Τ@�εw���...analyzer�s�b���N�q�N���C�F,ComponentFetcher�ѹ����Q��ƤF
	     */
	    class ComponentFetcher:public gui::event::WindowAdapter {
	      private:
		bptr < cms::measure::IntensityAnalyzerIF > firstAnalyzer;
		bptr < cms::measure::IntensityAnalyzerIF > secondAnalyzer;
		bool stop;
		//bptr < cms::lcd::BitDepthProcessor > bitDepth;
		Component_vector_ptr fetchComponent(RGB_vector_ptr rgbMeasureCode);
		XYZ_ptr extraMeasureXYZ;
		RGB_ptr extraMeasureRGB;
	      public:
		 /*ComponentFetcher(bptr <
				  cms::measure::IntensityAnalyzerIF >
				  analyzer, bptr < BitDepthProcessor > bitDepth);*/
		 ComponentFetcher(bptr < cms::measure::IntensityAnalyzerIF > analyzer);
		Component_vector_ptr fetchComponent(bptr < MeasureCondition > measureCondition);

		double_vector_ptr fetchLuminance(bptr < MeasureCondition > measureCondition);

		static void storeToExcel(const std::string & filename,
					 Component_vector_ptr componentVector);
		virtual void windowClosing(TObject * Sender, TCloseAction & Action);
		 bptr < cms::measure::IntensityAnalyzerIF > getAnalyzer();
		static RGB_vector_ptr getRGBVector(Component_vector_ptr componentVector);
		__property RGB_ptr ExtraMeasureRGB = { write = extraMeasureRGB
		};
		__property XYZ_ptr ExtraMeasureXYZ = { read = extraMeasureXYZ
		};
		__property bptr < cms::measure::IntensityAnalyzerIF > SecondAnalyzer = { write =
			secondAnalyzer
		};
		__property bptr < cms::measure::IntensityAnalyzerIF > FirstAnalyzer = { read =
			firstAnalyzer
		};
	    };

	    /*
	       �إ�Component���G�׻PIntensity�����Y��
	     */
	    class ComponentRelationIF {
	      public:
		virtual double getIntensity(double luminance) = 0;
		virtual double getLuminance(double rIntensity,
					    double gIntensity, double bIntensity) = 0;
	    };
	    class ComponentLinearRelation:public ComponentRelationIF {
	      private:
		bptr < PolynomialRegression > regression;
		double a0, a1, a2, a3, c, d;
		void init(double2D_ptr input, double2D_ptr output);
		void init(Component_vector_ptr componentVector);
		Component_vector_ptr componentVector;
	      public:
		 ComponentLinearRelation(double2D_ptr input, double2D_ptr output);
		 ComponentLinearRelation(Component_vector_ptr componentVector);
		double getIntensity(double luminance);
		double getLuminance(double rIntensity, double gIntensity, double bIntensity);
	    };

	    /*
	       �إ�Component���G�׻PIntensity�����Y��
	     */
	    class ComponentPLRelation:public ComponentRelationIF {
	    };

	    /*
	       DGLutGenerator������XDG Code�����d�j��
	       1. ��������ComponentFetcher���X��rgb,������componet,�G��
	       2. �ǥ�regression��Xcomponet�P�G�ת����Y
	       1/2��init���X

	       3. �ѥؼ�gamma curve�g�B�J�G��������component
	       4. ��compomenet�����XDG Code, DG Code���X
	       3/4��produce���X

	     */

	    class ComponentLUT {
	      private:
		Component_vector_ptr componentVector;
		bptr < math::Interpolation1DLUT > rLut;
		bptr < math::Interpolation1DLUT > gLut;
		bptr < math::Interpolation1DLUT > bLut;
		bptr < math::Interpolation1DLUT > YLut;
		double rMax, gMax, bMax, rIntensityMax, gIntensityMax, bIntensityMax;
	      protected:
		void init(Component_vector_ptr componentVector);

	      public:
		 ComponentLUT(Component_vector_ptr componentVector);
		double getIntensity(const Dep::Channel & ch, double code);
		double getCode(const Dep::Channel & ch, double intensity);
		RGB_ptr getCode(double luminance);
		double correctIntensityInRange(const Dep::Channel & ch, double intensity);
		double correctCodeInRange(const Dep::Channel & ch, double code);
		double getMaxBIntensity();
		int getMaxBIntensityRGL();
		bool hasCorrectedInRange(const Dep::Channel & ch);
		void setInverseSearch(bool inverse);
	    };
	};
    };
};
#endif

