#ifndef FEEDBACKH
#define FEEDBACKH

//C╰参ゅン

//C++╰参ゅン

//ㄤ畐繷ゅン

//セ兜ヘず繷ゅン
#include "component.h"
namespace cms {
    namespace lcd {
	namespace calibrate {
	    class ChromaticityAdjustEstimatorIF {
	      public:
		virtual double_array getdxdy(const Dep::Channel & ch, int grayLevel) = 0;
		virtual double_array getRdxGdy(int componentIndex) = 0;
	    };

	    /*
	       ︹秸俱碩箇代, 硓筁intensity
	     */
	    class IntensityEstimator:public ChromaticityAdjustEstimatorIF {
	      private:
		Component_vector_ptr componentVector;
		bptr < DGLutGenerator > dgLutGenerator;
		bptr < cms::measure::IntensityAnalyzerIF > analyzer;
		XYZ_ptr rXYZ, gXYZ, bXYZ;
		xyY_ptr getxyY(RGB_ptr intensity);
		 bptr < BitDepthProcessor > bitDepth;
	      public:
		 IntensityEstimator(Component_vector_ptr componentVector,
				    bptr < cms::measure::IntensityAnalyzerIF > analyzer,
				    bptr < BitDepthProcessor > bitDepth);
		virtual double_array getdxdy(const Dep::Channel & ch, int grayLevel);
		virtual double_array getRdxGdy(int componentIndex);
	    };

	    /*
	       ︹秸俱碩箇代, 硓筁秖代
	     */
	    class MeasureEstimator:public ChromaticityAdjustEstimatorIF {
	      private:
		bptr < cms::measure::MeterMeasurement > mm;
		Component_vector_ptr componentVector;
		Component_vector_ptr storeComponentVector;
		RGB_vector_ptr dglut;
		 bptr < BitDepthProcessor > bitDepth;
		void init();
		int storeIndex;
		double_array getdxdy(XYZ_ptr XYZ0, XYZ_ptr XYZ1);
		const int size;
		RGB_ptr getMeasureBaseRGB(int index);
		bool useComponentVector;
		XYZ_ptr baseXYZ;
		XYZ_ptr measure(RGB_ptr rgb);
		bool measureRdxGdy;
		int_vector_ptr constrained;
	      public:
		 MeasureEstimator(Component_vector_ptr componentVector,
				  bptr < cms::measure::MeterMeasurement > mm,
				  bptr < BitDepthProcessor > bitDepth);
		 MeasureEstimator(Component_vector_ptr componentVector,
				  bptr < cms::measure::IntensityAnalyzerIF > analyzer,
				  bptr < BitDepthProcessor > bitDepth);
		 MeasureEstimator(RGB_vector_ptr dglut,
				  bptr < cms::measure::IntensityAnalyzerIF > analyzer,
				  bptr < BitDepthProcessor > bitDepth);
		virtual double_array getdxdy(const Dep::Channel & ch, int componentIndex);
		virtual double_array getRdxGdy(int componentIndex);
		~MeasureEstimator();
		void measure(int startIndex, int endIndex);

		void resetMeasure();
		int getMeasureCount();

		double_vector_ptr dxofRVector;
		double_vector_ptr dyofGVector;
		double_vector_ptr dxofBase;
		double_vector_ptr dyofBase;
		__property bool MeasureRdxGdy = { write = measureRdxGdy };
		__property int_vector_ptr Constrained = { write = constrained };
		double_array getMaxMeasureError();
	    };

	    class FeedbackListener {
	      public:
		virtual void doFeedback(int defectCount, int feedbackCount) = 0;
	    };
	    class FeedbackFixer {
	      public:
		FeedbackFixer(int dimFixEnd, double dimFixThreshold,
			      bptr < cms::measure::IntensityAnalyzerIF > analyzer,
			      bptr < BitDepthProcessor > bitDepth);
		void fixReverseByFeedback(RGB_vector_ptr dglut);

		__property int FeedbackFixCount = { read = feedbackFixCount };
		__property bptr < FeedbackListener > Listener = { write = feedbackListener
		};
		__property double AverageDistance = { write = averageDistance };
		double_array getMaxMeasureError() {
		    return maxMeasureError;
		};

	      private:
		int checkReverse(double_vector_ptr deltaVector);
		int checkLoose(double_vector_ptr deltaVector);
		int checkReverse(double_vector_ptr deltaVector, int start, int end);
		int checkLoose(double_vector_ptr deltaVector, int start, int end);
		int_vector_ptr getReverseIndexVector(double_vector_ptr deltaVector,
						     int start, int end);

		int_vector_ptr getMustMeasureZoneIndexVector(double_vector_ptr dxofBase,
							     double_vector_ptr dyofBase, int start,
							     int end);
		int_vector_ptr getLooseIndexVector(double_vector_ptr deltaVector,
						   int start, int end);
		void pushBackNumber(int_vector_ptr result, int number);
		double_vector_ptr selectDelta(double_vector_ptr dxofBase,
					      double_vector_ptr dyofBase, Dep::Channel & ch);

		int feedbackFixCount;
		int dimFixEnd;
		double dimFixThreshold;
		double averageDistance;
		double_array maxMeasureError;
		 bptr < cms::measure::IntensityAnalyzerIF > analyzer;
		 bptr < BitDepthProcessor > bitDepth;
		 bptr < FeedbackListener > feedbackListener;

	    };

	};
    };
};

#endif

