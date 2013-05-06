#ifndef FEEDBACKH
#define FEEDBACKH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
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
	       色度調整幅度的預測, 透過intensity
	       目前並無使用到此類別
	       deprecated
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
	       色度調整幅度的預測, 透過量測
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
		//bool success;
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
		bool measure(int startIndex, int endIndex);

		void resetMeasure();
		int getMeasureCount();

		double_vector_ptr dxofRVector;
		double_vector_ptr dyofGVector;
		double_vector_ptr dxofBase;
		double_vector_ptr dyofBase;
		__property bool MeasureRdxGdy = { write = measureRdxGdy };
		__property int_vector_ptr Constrained = { write = constrained };
		double_array getMaxMeasureError();
		//__property bool Success = { read = success };
	    };

	    class FeedbackListener {
	      public:
		virtual void doFeedback(int defectCount, int feedbackCount) = 0;
		virtual void doFeedback(string msg) = 0;
	    };
	    class FeedbackFixer {
	      public:
		FeedbackFixer(int dimFixEnd, double dimFixThreshold,
			      bptr < cms::measure::IntensityAnalyzerIF > analyzer,
			      bptr < BitDepthProcessor > bitDepth);
		void fixReverseByFeedback(RGB_vector_ptr dglut);

		__property int FeedbackFixCount = { read = feedbackFixCount };
		__property int InitDefectCount = { read = initDefectCount };
		__property FeedbackListener *Listener = { write = feedbackListener
		};
		__property double_array AverageDistance = { write = averageDistance };
		__property bool Stop = { write = stop };
		double_array getMaxMeasureError() {
		    return maxMeasureError;
		};

	      private:
		int checkReverse(double_vector_ptr deltaVector);
		int checkLoose(double_vector_ptr deltaVector, double average);
		int checkReverse(double_vector_ptr deltaVector, int start, int end);
		int checkLoose(double_vector_ptr deltaVector, int start, int end, double average);
		int_vector_ptr getReverseIndexVector(double_vector_ptr deltaVector,
						     int start, int end);

		int_vector_ptr getMustMeasureZoneIndexVector(double_vector_ptr dxofBase,
							     double_vector_ptr dyofBase, int start,
							     int end);
		int_vector_ptr getLooseIndexVector(double_vector_ptr deltaVector,
						   int start, int end, double average);
		void pushBackNumber(int_vector_ptr result, int number);
		double_vector_ptr selectDelta(double_vector_ptr dxofBase,
					      double_vector_ptr dyofBase, Dep::Channel & ch);

		int feedbackFixCount;
		int initDefectCount;
		int dimFixEnd;
		double dimFixThreshold;
		double_array averageDistance;
		double_array maxMeasureError;
		 bptr < cms::measure::IntensityAnalyzerIF > analyzer;
		 bptr < BitDepthProcessor > bitDepth;
		FeedbackListener *feedbackListener;
		bool stop;

	    };

	};
    };
};

#endif

