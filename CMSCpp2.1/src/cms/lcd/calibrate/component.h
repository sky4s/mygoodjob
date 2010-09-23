#ifndef COMPONENTH
#define COMPONENTH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <math/regression.h>
#include "rgbgammaop.h"

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace math;
	    class Component:public jObject {
	      public:
		Component(RGB_ptr rgb, RGB_ptr intensity);
		Component(RGB_ptr rgb, RGB_ptr intensity, XYZ_ptr XYZ);
		Component(RGB_ptr rgb, RGB_ptr intensity, XYZ_ptr XYZ, RGB_ptr gamma);
		RGB_ptr rgb;
		RGB_ptr intensity;
		XYZ_ptr XYZ;
		RGB_ptr gamma;
	    };
	    class ComponentFetcher:public gui::event::WindowAdapter {
	      private:
		bptr < cms::measure::IntensityAnalyzerIF > analyzer;
		bool stop;
		 bptr < cms::lcd::calibrate::BitDepthProcessor > bitDepth;
		Component_vector_ptr fetchComponent(RGB_vector_ptr rgbMeasureCode);
	      public:
		 ComponentFetcher(bptr <
				  cms::measure::IntensityAnalyzerIF >
				  analyzer, bptr < BitDepthProcessor > bitDepth);
		Component_vector_ptr fetchComponent(bptr < MeasureCondition > measureCondition);
		double_vector_ptr fetchLuminance(bptr < MeasureCondition > measureCondition);

		static void storeToExcel(const std::string & filename,
					 Component_vector_ptr componentVector);
		virtual void windowClosing(TObject * Sender, TCloseAction & Action);
		 bptr < cms::measure::IntensityAnalyzerIF > getAnalyzer();
	    };

	    /*
	       建立Component內亮度與Intensity的關係式
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
	       建立Component內亮度與Intensity的關係式
	     */
	    class ComponentPLRelation:public ComponentRelationIF {
	    };

	    /*
	       DGLutGenerator擔任產出DG Code的重責大任
	       1. 首先接手ComponentFetcher產出的rgb,對應的componet,亮度
	       2. 藉由regression找出componet與亮度的關係
	       1/2由init產出

	       3. 由目標gamma curve經步驟二找到對應的component
	       4. 由compomenet對應出DG Code, DG Code產出
	       3/4由produce產出

	     */

	    class ComponentLUT {
	      private:
		Component_vector_ptr componentVector;
		bptr < math::Interpolation1DLUT > rLut;
		bptr < math::Interpolation1DLUT > gLut;
		bptr < math::Interpolation1DLUT > bLut;
		bptr < math::Interpolation1DLUT > YLut;
	      protected:
		void init(Component_vector_ptr componentVector);

	      public:
		 ComponentLUT(Component_vector_ptr componentVector);
		double getIntensity(const Dep::Channel & ch, double code);
		double getCode(const Dep::Channel & ch, double intensity);
		RGB_ptr getCode(double luminance);
		double correctIntensityInRange(const Dep::Channel & ch, double intensity);
		double getMaxBIntensity();
	    };
	};
    };
};
#endif

