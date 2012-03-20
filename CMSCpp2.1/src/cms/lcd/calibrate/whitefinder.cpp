#include <includeall.h>
#pragma hdrstop
#include "whitefinder.h"

//C�t�Τ��

//C++�t�Τ��


//��L�w�Y���

//�����ؤ��Y���

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace cms;
	    using namespace cms::measure;
	    using namespace cms::lcd::calibrate::algo;
	    using namespace cms::colorformat;
	    using namespace Dep;
	    using namespace Indep;
	    //==================================================================
	    // WhitePointFinder
	    //==================================================================
	     WhitePointFinder::WhitePointFinder(bptr < MeterMeasurement >
						mm,
						bptr < BitDepthProcessor >
						bitDepth,
						double maxcode):mm(mm),
		stop(false), maxcode(maxcode), bitDepth(bitDepth) {
		aroundAlgo =
		    bptr < ChromaticAroundAlgorithm > (new ChromaticAroundAlgorithm(maxcode));
		nearAlgo =
		    bptr < CIEuv1960NearestAlgorithm >
		    (new CIEuv1960NearestAlgorithm(XYZ_ptr((CIEXYZ *) null), mm));
	    };

	    RGB_ptr WhitePointFinder::findMatchRGB0(xyY_ptr xyY, RGB_ptr initRGB) {
		this->mm;
		RGB_ptr nearestRGB = initRGB;
		bool findNearest = false;
		 stop = false;
		double step = bitDepth->getMeasureStep();

		do {
		    RGB_vector_ptr aroundRGB = aroundAlgo->getAroundRGB(nearestRGB, step);
		    XYZ_ptr center = xyY->toXYZ();
		     bptr < AlgoResult > algoResult = nearAlgo->getNearestRGB(center, aroundRGB);
		    XYZ_vector_ptr aroundXYZ = algoResult->aroundXYZ;
		     nearestRGB = algoResult->nearestRGB;
		     findNearest = MeasuredUtils::isFirstNearestXYZInuvPrime(center, aroundXYZ);
		    //findNearest = true;
		    if (true == stop) {
			stop = false;
			return nil_RGB_ptr;
		    }

		} while (!findNearest);
		return nearestRGB;
	    };

	    RGB_ptr WhitePointFinder::findRGBAround(xyY_ptr xyY) {
		aroundAlgo->setMode(algo::Normal);
		RGB_ptr maxrgb(new RGBColor(maxcode, maxcode, maxcode));
		RGB_ptr result = findMatchRGB0(xyY, maxrgb);
		return result;
	    };

	    /*
	       �H���ץ��᪺��, �ץ���l�D255�����I, �Ϧ�׹F��̱����.
	       1. ���̤j���W�D
	       2. �p��ثexyY�P�ؼЭȤ�delta
	       3.
	     */
	    RGB_ptr WhitePointFinder::findMatchRGB(xyY_ptr xyY, RGB_ptr initRGB) {
		aroundAlgo->setMode(White);
		RGB_ptr result = findMatchRGB0(xyY, initRGB);
		return result;
	    };

	    RGB_ptr WhitePointFinder::fixRGB2TouchMax(RGB_ptr rgb) {
		RGB_ptr clone = rgb->clone();
		//�M��A�վ�White��RGB�䤤�@�I��255.
		const Channel & maxChannel = clone->getMaxChannel();
		double maxChannelValue = clone->getValue(maxChannel);
		double diff = maxcode - maxChannelValue;
		clone->addValue(diff);
		return clone;
	    };

	    /*
	       ���I�M��y�{

	       �ѩ�ʥFmodel�i�H�w���A�����I,
	       1. �]�����HRGB��cube�M�䥿�T���I
	       2. �M��A�վ�White��RGB�䤤�@�I��255.
	       3. �A�H���ץ��᪺��, �ץ���l�D255�����I, �Ϧ�׹F��̱����.
	     */
	    RGB_ptr WhitePointFinder::findRGB(xyY_ptr xyY) {
		RGB_ptr initRGB = findRGBAround(xyY);
		if (null == initRGB) {
		    return initRGB;
		}
		RGB_ptr fixRGB = fixRGB2TouchMax(initRGB);
		RGB_ptr finalRGB = findMatchRGB(xyY, fixRGB);
		return finalRGB;
	    };

	    void WhitePointFinder::windowClosing(TObject * Sender, TCloseAction & Action) {
		stop = true;
	    };

	    //==================================================================
	    //
	    //==================================================================
	    StocktonWhitePointFinder::StocktonWhitePointFinder(bptr < MeterMeasurement > mm,
							       bptr < BitDepthProcessor > bitDepth,
							       RGB_ptr initRGB, double maxcode,
							       bool keepBlue):WhitePointFinder(mm,
											       bitDepth,
											       maxcode),
		initRGB(initRGB), keepBlue(keepBlue) {

	    };


	    RGB_ptr StocktonWhitePointFinder::findRGB(xyY_ptr targetxyY) {
		using java::lang::Math;
		double_array delta;
		RGB_ptr findRGB = initRGB->clone();
		stop = false;
		int adjustStep = bitDepth->getMeasureStep();

		//==============================================================
		BEGIN_STORE("findwhite.xls");
		//==============================================================

		//==============================================================
		// blue���B�z(x/y)
		//==============================================================
		if (!keepBlue) {
		    do {
			Patch_ptr patch = mm->measure(findRGB, findRGB->toString());
			xyY_ptr measurexyY(new CIExyY(patch->getXYZ()));
			delta = measurexyY->getDeltaxy(targetxyY);

			STORE_RGBXY(findRGB, measurexyY);

			/*int adjust = 0;
			   if (Math::abs(delta[0]) > 0.012 && Math::abs(delta[1]) > 0.012) {
			   adjust = 5;
			   } else if (Math::abs(delta[0]) > 0.003 && Math::abs(delta[1]) > 0.003) {
			   adjust = 3;
			   } else {
			   adjust = 1;
			   } */

			if (delta[0] < 0 || delta[1] < 0) {
			    findRGB->B -= adjustStep;
			}

			if (true == stop) {
			    stop = false;
			    return nil_RGB_ptr;
			}
		    }
		    while (!(delta[0] > 0 && delta[1] > 0));
		}
		//==============================================================

		//==============================================================
		// red���B�z(x)
		//==============================================================
		do {
		    Patch_ptr patch = mm->measure(findRGB, findRGB->toString());
		    xyY_ptr measurexyY(new CIExyY(patch->getXYZ()));
		    delta = measurexyY->getDeltaxy(targetxyY);

		    STORE_RGBXY(findRGB, measurexyY);

		    if (delta[0] > 0) {
			findRGB->R -= adjustStep;
		    }
		    if (true == stop) {
			stop = false;
			return nil_RGB_ptr;
		    }
		} while (!(delta[0] < 0));
		//==============================================================

		//==============================================================
		// rgb���B�z
		//==============================================================
		bool stopLoop = false;
		do {
		    Patch_ptr patch = mm->measure(findRGB, findRGB->toString());
		    xyY_ptr measurexyY(new CIExyY(patch->getXYZ()));
		    delta = measurexyY->getDeltaxy(targetxyY);

		    STORE_RGBXY(findRGB, measurexyY);

		    if (delta[1] > 0) {
			//green���B�z
			findRGB->G -= adjustStep;
		    }
		    if (!keepBlue && delta[0] > 0 && findRGB->B < maxcode) {
			//blue���B�z
			findRGB->B += adjustStep;
		    }
		    if (delta[0] > 0 && maxcode == findRGB->B) {
			findRGB->R -= adjustStep;
		    }
		    stopLoop = (delta[0] < 0 && delta[1] < 0)
			|| (maxcode == findRGB->B && delta[1] < 0);

		    if (true == stop) {
			stop = false;
			return nil_RGB_ptr;
		    }
		} while (false == stopLoop);
		//==============================================================

		//==============================================================
		// �̲פ@���վ�
		//==============================================================
		Patch_ptr patch = mm->measure(findRGB, findRGB->toString());
		xyY_ptr measurexyY(new CIExyY(patch->getXYZ()));
		delta = measurexyY->getDeltaxy(targetxyY);

		STORE_RGBXY(findRGB, measurexyY);

		if (findRGB->R < maxcode) {
		    findRGB->R += adjustStep;
		    patch = mm->measure(findRGB, findRGB->toString());
		    measurexyY = xyY_ptr(new CIExyY(patch->getXYZ()));

		    STORE_RGBXY(findRGB, measurexyY);

		    double_array delta2 = measurexyY->getDeltaxy(targetxyY);
		    if (Math::abs(delta2[0]) > Math::abs(delta[0])) {
			findRGB->R -= adjustStep;
		    }
		}
		if (findRGB->G < maxcode) {
		    findRGB->G += adjustStep;
		    patch = mm->measure(findRGB, findRGB->toString());
		    measurexyY = xyY_ptr(new CIExyY(patch->getXYZ()));

		    STORE_RGBXY(findRGB, measurexyY);

		    double_array delta2 = measurexyY->getDeltaxy(targetxyY);
		    if (Math::abs(delta2[1]) > Math::abs(delta[1])) {
			findRGB->G -= adjustStep;
		    }
		}
		//==============================================================
		return findRGB;
	    };
	    //==================================================================

	};
    };
};

