#include <includeall.h>
#pragma hdrstop
#include "sandbox.h"
#include <debug.h>


//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace cms::measure;
	    using namespace cms::colorformat;
	    using namespace Indep;
	    using namespace Dep;
	    using namespace java::lang;
	    using namespace cms::lcd::calibrate;


	    XYZ_ptr getTargetXYZ(double v1, double v2, double v3,
				 Domain domain) {
		double_array targetValues(new double[3]);
		 targetValues[0] = v1;
		 targetValues[1] = v2;
		 targetValues[2] = v3;
		CIExyY targetxyY;
		switch (domain) {
		case CIExy:
		    targetxyY.setValues(targetValues);
		    break;
		    case CIEuv:targetxyY.setuvYValues(targetValues);
		    break;

		    case CIEuvPrime:targetxyY.
			setuvPrimeYValues(targetValues);
		    break;
		};
		 return targetxyY.toXYZ();
	    };

	    XYZ_ptr getTargetXYZ(double x, double y, double Y) {
		CIExyY targetxyY;
		 targetxyY.x = x;
		 targetxyY.y = y;
		 targetxyY.Y = Y;
		XYZ_ptr XYZ = targetxyY.toXYZ();
		 return XYZ;
	    };

	    //==================================================================
	    // AdvancedDGLutGenerator
	    //==================================================================
	  AdvancedDGLutGenerator::AdvancedDGLutGenerator(Component_vector_ptr componentVector, bptr < cms::lcd::calibrate::ComponentFetcher > fetcher, bptr < IntensityAnalyzerIF > analyzer1, bptr < IntensityAnalyzerIF > analyzer2nd, bptr < BitDepthProcessor > bitDepth, const LCDCalibrator & calibrator):DimDGLutGenerator(componentVector, analyzer1),
		fetcher(fetcher), analyzer2nd(analyzer2nd),
		bitDepth(bitDepth), smoothMode(true), c(calibrator) {
		init();
	    };

	    void AdvancedDGLutGenerator::init() {
		/*rTargetIntensity = -1;
		   gTargetIntensity = -1;
		   bTargetIntensity = -1;
		   autoIntensity = false; */
		stopMeasure = false;
		//multiGen = false;
		this->bitDepth = bitDepth;
		//middleCCTRatio = -1;
		//autoParameter = false;
		rgbGenerateResult = nil_RGBGamma;
		//smoothIntensity = false;
	    };

	    AdvancedDGLutGenerator::
		AdvancedDGLutGenerator(Component_vector_ptr
				       componentVector,
				       bptr < ComponentFetcher > fetcher,
				       bptr < BitDepthProcessor > bitDepth,
				       const LCDCalibrator &
				       calibrator):DimDGLutGenerator
		(componentVector, fetcher->getAnalyzer()),
		fetcher(fetcher), bitDepth(bitDepth), smoothMode(false),
		c(calibrator) {
		init();
	    };
	    /*
	       targetWhite: �ؼХ��I
	       luminanceGammaCurve: �ؼ�gamma curve
	       dimTurn: �C�Ƕ�������I
	       brightTurn: ���Ƕ�������I
	       dimGamma: �C�Ƕ�����Ŧ��ugamma�ܤ�
	       brightGamma: ���Ƕ�����Ŧ��ugamma�ܤ�
	       brightWidth: ���Ƕ�
	     */
	    XYZ_vector_ptr AdvancedDGLutGenerator::
		getTargetXYZVector(XYZ_ptr targetWhite,
				   double_vector_ptr luminanceGammaCurve,
				   int dimTurn, int brightTurn,
				   double dimGamma, double brightGamma,
				   int brightWidth) {
		XYZ_ptr nativeWhite = (*componentVector)[0]->XYZ;
		return getTargetXYZVector(targetWhite, nativeWhite,
					  luminanceGammaCurve, dimTurn,
					  brightTurn, dimGamma,
					  brightGamma, brightWidth);
	    };
	    XYZ_vector_ptr AdvancedDGLutGenerator::
		getTargetXYZVector(XYZ_ptr targetWhite,
				   XYZ_ptr nativeWhite,
				   double_vector_ptr luminanceGammaCurve,
				   int dimTurn, int brightTurn,
				   double dimGamma, double brightGamma,
				   int brightWidth) {
		//==============================================================
		// ��T�ǳ�
		//==============================================================
		XYZ_ptr blackXYZ =
		    (*componentVector)[componentVector->size() - 1]->XYZ;
		XYZ_vector_ptr targetXYZVector;
		this->brightTurn = brightTurn;

		//�D�ؼЭȦ��u

		if (-1 != c.middleCCTRatio) {
		    targetXYZVector =
			getTarget0(blackXYZ, targetWhite, nativeWhite,
				   luminanceGammaCurve, dimTurn,
				   brightTurn, dimGamma, brightGamma,
				   brightWidth, c.middleCCTRatio);
		} else {
		    targetXYZVector =
			getTarget0(blackXYZ, targetWhite, nativeWhite,
				   luminanceGammaCurve, dimTurn,
				   brightTurn, dimGamma, brightGamma,
				   brightWidth);
		}
		//}
		return targetXYZVector;
	    }


	    RGB_vector_ptr AdvancedDGLutGenerator::
		produce(XYZ_vector_ptr targetXYZVector) {
		STORE_XYZXY_VECTOE("1.2_target.xls", targetXYZVector);
		//==============================================================
		/*
		   �Y���Fsmooth target(�򥻤Wadv dg lut�]�u��smooth target���\��)
		   ���Oanalyzer�̪�primary color�ä��Onative white��primary color,
		   �ҥH���X�Ӫ�native target�L�k�p�w���|�O(255,255,255)
		   ���F�ѨM�o�Ӱ��D, �����n�����primary color;
		   �Ĥ@�յ�target white��, �ĤG�յ�native white��.
		   ���D�b��p��V�γo���primary color?

		   ��k1. �H���analyer�����ͤ@��DG, �M��Abright turn��end�o�q, �Hgain�Ȱ������B�z.
		 */
		if (c.multiGen) {
		    /*
		       ��i�������ͤ覡
		       1.�����ͤ@��DG Lut
		       2.��Ӳ�DG���q����@Raw Data
		       3.�A���Ӳհ�Raw Data����DG Lut
		       4.�Y��ǫ׭n��,�N���ư��캡�N����
		     */
		    return produceDGLutMulti(targetXYZVector,
					     componentVector);
		} else {
		    if (smoothMode) {
			/*
			   smooth mode�O�Φb ���I�D��l��� + �nkeep�̤j�G��.
			   ���ɨ�Ӧ�ŭY���P, �n�N��ӵ��G��smooth.
			   ���ثe�ӥ\��bUI�W�å��}��
			 */
			//target white���ͪ����G
			RGB_vector_ptr result1 =
			    produceDGLut(targetXYZVector, componentVector,
					 analyzer, panelRegulator1);
			//native white���ͪ����G
			RGB_vector_ptr result2;
			if (componentVector2 != null) {
			    result2 =
				produceDGLut(targetXYZVector,
					     componentVector2, analyzer2nd,
					     panelRegulator2);
			} else {
			    result2 =
				produceDGLut(targetXYZVector,
					     componentVector, analyzer2nd,
					     panelRegulator1);
			}

			//�N��ӵ��G�α��_��
			return smooth(result1, result2, bitDepth,
				      brightTurn);
		    } else {
			//�j�������O�b��case
			RGB_vector_ptr result =
			    produceDGLut(targetXYZVector, componentVector,
					 analyzer,
					 panelRegulator1);

			//==========================================================================
			// �C�Ƕ��ץ�debug
			//==========================================================================

			//==========================================================================
			return result;
		    }
		}
	    }



	    RGB_vector_ptr AdvancedDGLutGenerator::
		smooth(RGB_vector_ptr result1, RGB_vector_ptr result2,
		       bptr < BitDepthProcessor > bitDepth,
		       int brightTurn) {
		RGB_vector_ptr result = RGBVector::deepClone(result1);

		int level = bitDepth->getLevel();
		int part = level - brightTurn;
		int part13 = part / 3;
		int part13Start = level - part13;
		//int size = result1->size();
		for (int x = brightTurn; x < part13Start; x++) {
		    RGB_ptr rgb = (*result)[x];
		    RGB_ptr rgb1 = (*result1)[x];
		    RGB_ptr rgb2 = (*result2)[x];
		    double gain2 =
			(((double) x) - brightTurn) / (part13Start -
						       brightTurn);
		    double gain = 1. - gain2;
		    rgb->R = gain * rgb1->R + gain2 * rgb2->R;
		    rgb->G = gain * rgb1->G + gain2 * rgb2->G;
		    rgb->B = gain * rgb1->B + gain2 * rgb2->B;
		}
		for (int x = part13Start; x < level; x++) {
		    (*result)[x] = (*result2)[x]->clone();
		}


		return result;
	    };
	    RGB_vector_ptr AdvancedDGLutGenerator::
		produceDGLutMulti(XYZ_vector_ptr targetXYZVector,
				  Component_vector_ptr componentVector) {
		//�����ͪ�B���G
		RGB_vector_ptr initRGBVector =
		    produceDGLut(targetXYZVector, componentVector,
				 analyzer, panelRegulator1);

		/*
		   1. RGB���δ�, ��w255
		   2. RGB���ĥΤW�@����DG Code
		   �Y�O�p��, �@�w�n�D�X��GL��DG�~�i�H�~��U�@��
		 */
		RGB_vector_ptr result = initRGBVector;
		if (null == fetcher) {
		    throw new IllegalStateException("null == fetcher");
		}
		STORE_RGBVECTOR("MultiGen_DG_0.xls", result);

		/*
		   multi gen���L�{���ɶ��O�@���y�u��, ���O���S�ʤ]�i���H�ۮɶ�����
		   ���OtargetXYZVector�ä���, �O���O���i��ɭP���X�Ӫ����G�|��clipping?
		 */
		for (int t = 0; t < c.multiGenTimes; t++) {
		    RGBVector::changeMaxValue(result,
					      bitDepth->
					      getFRCAbilityBit());

		    bptr < MeasureCondition >
			measureCondition(new
					 MeasureCondition(RGBVector::
							  reverse
							  (result)));

		    Component_vector_ptr componentVectorPrime =
			fetcher->fetchComponent(measureCondition);
		    STORE_COMPONENT("MultiGen_Component_" +
				    _toString(t + 1) + ".xls",
				    componentVectorPrime);

		    result =
			produceDGLut(targetXYZVector, componentVectorPrime,
				     analyzer,
				     bptr < PanelRegulator >
				     ((PanelRegulator *) null));
		    STORE_RGBVECTOR("MultiGen_DG_" + _toString(t + 1) +
				    ".xls", result);
		}

		return result;
	    };

	    RGB_ptr AdvancedDGLutGenerator::
		getIdealIntensity(Component_vector_ptr componentVector,
				  bptr <
				  cms::measure::
				  MaxMatrixIntensityAnalyzer > analyzer) {
		Component_vector_ptr newcomponentVector =
		    fetchNewComponent(analyzer, componentVector);
		STORE_COMPONENT("idealIntensity.xls", newcomponentVector);
		DGLutGenerator lutgen(newcomponentVector);
		RGB_ptr refRGB = analyzer->getReferenceRGB();
		RGB_ptr intensity = lutgen.getIntensity(refRGB);
		return intensity;
	    };

	    /*
	       ����DG LUT���t��k�֤߳���
	     */
	    RGB_vector_ptr AdvancedDGLutGenerator::
		produceDGLut(XYZ_vector_ptr targetXYZVector,
			     Component_vector_ptr componentVector,
			     bptr < cms::measure::IntensityAnalyzerIF >
			     analyzer,
			     bptr < PanelRegulator > panelRegulator) {
		/*
		   �B��覡²�z:
		   1.�Q�Τ��_�ܤƪ�target XYZ, �N��|���ܦh��Target White.
		   2.�C�ӦǶ��U���@��Target White, �ҥH�C�ӦǶ����Q�θ�Target White,
		   �p��X�@��Intensity,
		   3.��DG Lut�n�����N�O�C�@��Intensity�̭�, R=G=B=100�B,
		   �]���N���Intensity������DG, ��n�N�OTarget White.
		 */

		int size = targetXYZVector->size();
		RGB_vector_ptr result(new RGB_vector(size));
		//==============================================================
		//primary color�u���target white~
		XYZ_ptr rXYZ =
		    analyzer->getPrimaryColor(Channel::R)->toXYZ();
		XYZ_ptr gXYZ =
		    analyzer->getPrimaryColor(Channel::G)->toXYZ();
		XYZ_ptr bXYZ =
		    analyzer->getPrimaryColor(Channel::B)->toXYZ();
		RGB_ptr refRGB = analyzer->getReferenceRGB();
		//=============================================================
		// debug��
		//=============================================================
#ifdef DEBUG_CCTLUT_NEWMETHOD
		Component_vector_ptr maxComponentVector(new
							Component_vector
							());
#endif				//DEBUG_CCTLUT_NEWMETHOD

#ifdef DEBUG_INTENISITY
		Component_vector_ptr debugComponentVector(new
							  Component_vector
							  ());
#endif
		//=============================================================

		//=============================================================
		//�]�wintensity
		//=============================================================
		double rTargetIntensity = -1;
		double gTargetIntensity = -1;
		double bTargetIntensity = -1;
		if (true == c.autoIntensity) {
		    xyY_ptr refxyY = analyzer->getReferenceColor();
		    XYZ_ptr targetXYZ = refxyY->toXYZ();

		    bptr < MaxMatrixIntensityAnalyzer >
			ma(new MaxMatrixIntensityAnalyzer());
		    ma->setupComponent(Channel::R, rXYZ);
		    ma->setupComponent(Channel::G, gXYZ);
		    ma->setupComponent(Channel::B, bXYZ);
		    ma->setupComponent(Channel::W, targetXYZ);
		    ma->setReferenceRGB(refRGB);
		    ma->enter();

		    idealIntensity =
			getIdealIntensity(componentVector, ma);
		    rTargetIntensity = idealIntensity->R;
		    gTargetIntensity = idealIntensity->G;
		    bTargetIntensity = idealIntensity->B;
		}
		if (rTargetIntensity == -1) {
		    rTargetIntensity = 100;
		};
		if (gTargetIntensity == -1) {
		    gTargetIntensity = 100;
		};
		//B��100��?
		if (bTargetIntensity == -1) {
		    bTargetIntensity = 100;
		};
		double rIntensity = rTargetIntensity;
		double gIntensity = gTargetIntensity;
		double bIntensity = bTargetIntensity;
		//=============================================================

		RGB_vector_ptr rgbGenResultVector(new RGB_vector());
		//=============================================================
		// �j��}�l
		//=============================================================
		for (int x = size - 1; x != -1; x--) {
		    //x = 0;
		    XYZ_ptr targetXYZ = (*targetXYZVector)[x];

		    //���_����Analyzer, �]��Target White�@���ܤ�, �ҥH�Q�ηs��Analyzer, �p��XIntensity
		    bptr < MaxMatrixIntensityAnalyzer >
			ma(new MaxMatrixIntensityAnalyzer());
		    ma->setupComponent(Channel::R, rXYZ);
		    ma->setupComponent(Channel::G, gXYZ);
		    ma->setupComponent(Channel::B, bXYZ);
		    ma->setupComponent(Channel::W, targetXYZ);
		    ma->setReferenceRGB(refRGB);
		    ma->enter();

		    //�Q�ηs��analyzer��X�s��component(�N�Ointensity)
		    Component_vector_ptr newcomponentVector =
			fetchNewComponent(ma, componentVector);

		    {		// debug scope
#ifdef DEBUG_CCTLUT_NEWMETHOD
			if (FileExists(DEBUG_VERBOSE_STEP)) {
			    STORE_COMPONENT(_toString(x) + ".xls",
					    newcomponentVector);
			}
			//��Ĥ@�Ӧs�_��, �Ĥ@�ө����O�̤j��
			RGB_ptr grayLevel(new RGBColor(x, x, x));
			Component_ptr c(new Component(grayLevel,
						      (*newcomponentVector)
						      [0]->intensity,
						      targetXYZ));
			maxComponentVector->push_back(c);
#endif				//DEBUG_CCTLUT_NEWMETHOD
		    }

		    if (true == c.autoIntensity
			&& true == c.smoothIntensity
			&& x >= c.smoothIntensityStart
			&& x <= c.smoothIntensityEnd) {
			rIntensity =
			    Interpolation::linear(c.smoothIntensityStart,
						  c.smoothIntensityEnd,
						  100, rTargetIntensity,
						  x);
			gIntensity =
			    Interpolation::linear(c.smoothIntensityStart,
						  c.smoothIntensityEnd,
						  100, gTargetIntensity,
						  x);
			bIntensity =
			    Interpolation::linear(c.smoothIntensityStart,
						  c.smoothIntensityEnd,
						  100, bTargetIntensity,
						  x);
		    }


		    DGLutGenerator lutgen(newcomponentVector);
		    RGB_ptr rgb = lutgen.getDGCode(rIntensity, gIntensity,
						   bIntensity);
		    bool_array isCorrect =
			lutgen.isCorrectIntensityInRange();
		    (*result)[x] = rgb;

		    //�������ͪ��L�{�O�_�����D
		    RGB_ptr genResult(new RGBColor());
		    genResult->R = (true == isCorrect[0]) ? -1 : 0;
		    genResult->G = (true == isCorrect[1]) ? -1 : 0;
		    genResult->B = (true == isCorrect[2]) ? -1 : 0;
		    rgbGenResultVector->push_back(genResult);

#ifdef DEBUG_INTENISITY
		    {
			Component_ptr c =
			    getFRCAbilityComponent(x, rgb, ma,
						   newcomponentVector);
			c->gamma = genResult;
			debugComponentVector->push_back(c);
		    }
#endif
		}
		rgbGenerateResult =
		    RGBGamma::
		    getReverse(RGBGamma_ptr
			       (new
				RGBGamma(rgbGenResultVector, 0, Unknow)));
		//=============================================================
		// �j�鵲��
		//=============================================================

		if (null != panelRegulator) {
		    //�Y��panelRegulator, �i��remapping (�J��hook�~�ݭn)
		    GammaTestPanelRegulator *gammaTestRegulator =
			dynamic_cast <
			GammaTestPanelRegulator * >(panelRegulator.get());
		    if (null == gammaTestRegulator) {
			//�Y�OGammaTest�򥻤Wcomponent�N��mapping����dg code, �ҥH�L���A�@remapping
			result = panelRegulator->remapping(result);
		    }
		}
#ifdef DEBUG_CCTLUT_NEWMETHOD
		STORE_COMPONENT("1.3_maxIntensity.xls",
				maxComponentVector);
#endif

#ifdef DEBUG_INTENISITY
		//�Q��DG�^��Intenisty�Mwhite point��primart color�w��CIE xy
		STORE_COMPONENT("1.3_debugIntensity.xls",
				debugComponentVector);
#endif

		return result;
	    };

	    Component_ptr AdvancedDGLutGenerator::
		getFRCAbilityComponent(int grayLevel, RGB_ptr rgb,
				       bptr <
				       cms::measure::IntensityAnalyzerIF >
				       analyzer,
				       Component_vector_ptr
				       componentVector) {
		//�o�T�ˤ��ޤ���analyzer���O�̼˪�, �|�ܪ��OtargetXYZ
		XYZ_ptr rXYZ =
		    analyzer->getPrimaryColor(Channel::R)->toXYZ();
		XYZ_ptr gXYZ =
		    analyzer->getPrimaryColor(Channel::G)->toXYZ();
		XYZ_ptr bXYZ =
		    analyzer->getPrimaryColor(Channel::B)->toXYZ();
		RGB_ptr refRGB = analyzer->getReferenceRGB();
		RGB_ptr refR = refRGB->clone();
		refR->reserveValue(Channel::R);
		RGB_ptr refG = refRGB->clone();
		refG->reserveValue(Channel::G);
		RGB_ptr refB = refRGB->clone();
		refB->reserveValue(Channel::B);

		//debug scope
		RGB_ptr clone = rgb->clone();
		//���FRC�i�H�e�{��bit��
		clone->quantization(bitDepth->getFRCAbilityBit());

		DGLutGenerator lutgen2(componentVector);
		RGB_ptr intensity2 = lutgen2.getIntensity(clone);
		/*RGB_ptr remappingDGCode =
		   lutgen2.getDGCode(intensity2->R, intensity2->G, intensity2->B);
		   RGB_ptr intensity3 = lutgen2.getIntensity(remappingDGCode); */
		RGB_ptr intensityR = lutgen2.getIntensity(refR);
		RGB_ptr intensityG = lutgen2.getIntensity(refG);
		RGB_ptr intensityB = lutgen2.getIntensity(refB);

		double_array rXYZValues = rXYZ->getValues();
		double_array gXYZValues = gXYZ->getValues();
		double_array bXYZValues = bXYZ->getValues();
		//�ι�Wtarget primary��intensity����CIEXYZ
		rXYZValues =
		    DoubleArray::times(rXYZValues,
				       intensity2->R / intensityR->R, 3);
		gXYZValues =
		    DoubleArray::times(gXYZValues,
				       intensity2->G / intensityG->G, 3);
		bXYZValues =
		    DoubleArray::times(bXYZValues,
				       intensity2->B / intensityB->B, 3);
		XYZ_ptr rXYZ2(new Indep::CIEXYZ(rXYZValues));
		XYZ_ptr gXYZ2(new Indep::CIEXYZ(gXYZValues));
		XYZ_ptr bXYZ2(new Indep::CIEXYZ(bXYZValues));
		XYZ_ptr rgXYZ2 = CIEXYZ::plus(rXYZ2, gXYZ2);
		XYZ_ptr rgbXYZ2 = CIEXYZ::plus(rgXYZ2, bXYZ2);

		RGB_ptr w(new RGBColor(grayLevel, grayLevel, grayLevel));
		Component_ptr c(new Component(w, intensity2, rgbXYZ2));
		return c;
	    };


	    bool AdvancedDGLutGenerator::isAvoidHook(XYZ_ptr targetXYZ,
						     double offsetK) {
		XYZ_ptr XYZOffset = getXYZ(targetXYZ, offsetK);
		return isDuplicateBlue100(XYZOffset);
	    };
	    XYZ_ptr AdvancedDGLutGenerator::getXYZ(XYZ_ptr XYZ,
						   double offsetK) {
		//==============================================================
		// ���Ʒǳ�
		//==============================================================
		xyY_ptr xyY(new CIExyY(XYZ));
		double cct =
		    CorrelatedColorTemperature::xy2CCTByMcCamyFloat(xyY);
		xyY_ptr xyYOriginal =
		    CorrelatedColorTemperature::CCT2DIlluminantxyY(cct);
		double cctOffset = cct + offsetK;
		xyY_ptr xyYOffset =
		    CorrelatedColorTemperature::
		    CCT2DIlluminantxyY(cctOffset);
		//==============================================================

		//==============================================================
		// shift
		//==============================================================
		double_array dxy = xyY->getDeltaxy(xyYOriginal);
		xyYOffset->x += dxy[0];
		xyYOffset->y += dxy[1];
		//==============================================================

		xyYOffset->Y = XYZ->Y;
		XYZ_ptr XYZOffset = xyYOffset->toXYZ();
		return XYZOffset;
	    };
	    bool AdvancedDGLutGenerator::
		isDuplicateBlue100(XYZ_ptr targetXYZ) {
		xyY_ptr rxyY = analyzer->getPrimaryColor(Channel::R);
		xyY_ptr gxyY = analyzer->getPrimaryColor(Channel::G);
		xyY_ptr bxyY = analyzer->getPrimaryColor(Channel::B);

		bptr < MaxMatrixIntensityAnalyzer >
		    mmia(new MaxMatrixIntensityAnalyzer());
		mmia->setupComponent(Channel::R, rxyY->toXYZ());
		mmia->setupComponent(Channel::G, gxyY->toXYZ());
		mmia->setupComponent(Channel::B, bxyY->toXYZ());
		mmia->setupComponent(Channel::W, targetXYZ);
		mmia->enter();

		Component_vector_ptr newcomponentVector =
		    fetchNewComponent(mmia, componentVector);

		return isDuplicateBlue100(newcomponentVector);
	    };

	    /*
	       ����smooth target�٬O���Ӱ��D, �N�Oluminance.
	       �{�b���@�k�O�έ쥻��Target White���G�רӲ���Luminance(�]�N�O�̤j�G��),
	       ����ڤW���Ƕ���Target White�w�g�Q����, �ҥH�̤j�G�פ]���P�F.
	       �Y�����H���Ƕ���Target White���̤j�G��, �������Ƕ��o�S�L�k���ͬۦP�G�פάۦP��׮y�Ъ�DG
	     */
	    XYZ_vector_ptr AdvancedDGLutGenerator::
		getTarget0(XYZ_ptr startXYZ, XYZ_ptr targetXYZ,
			   XYZ_ptr endXYZ,
			   double_vector_ptr luminanceGammaCurve,
			   int dimTurn, int brightTurn, double dimGamma,
			   double brightGamma, int brightWidth) {
		int size = luminanceGammaCurve->size();
		double_array dimendValues = targetXYZ->getxyValues();
		XYZ_vector_ptr result(new XYZ_vector(size));

		//==============================================================
		// dim�Ϭq
		//==============================================================
		double_vector_ptr dimGammaCurve =
		    DoubleArray::getRangeCopy(luminanceGammaCurve, 0,
					      dimTurn);
		XYZ_vector_ptr dimResult =
		    DimTargetGenerator::getTarget(startXYZ, targetXYZ,
						  dimGammaCurve, dimGamma);

		STORE_XYZXY_VECTOE("1.1_target_dim.xls", dimResult);
		int dimSize = dimResult->size();
		for (int x = 0; x < dimSize; x++) {
		    (*result)[x] = (*dimResult)[x];
		}
		//==============================================================

		//==============================================================
		// �����Ϭq
		//==============================================================
		for (int x = dimTurn; x < brightTurn; x++) {
		    //��Y���ܤ�
		    double Y = (*luminanceGammaCurve)[x];
		    (*result)[x] =
			getTargetXYZ(dimendValues[0], dimendValues[1], Y);
		}
		//==============================================================

		//==============================================================
		// bright�Ϭq
		//==============================================================
		XYZ_vector_ptr brightResult =
		    getBrightGammaTarget(luminanceGammaCurve,
					 targetXYZ,
					 endXYZ, brightGamma,
					 brightTurn, brightWidth,
					 bitDepth);
		int brightSize = brightResult->size();
		for (int x = 0; x < brightSize; x++) {
		    (*result)[x + brightTurn] = (*brightResult)[x];
		}
		//==============================================================
		return result;
	    };

	    XYZ_ptr AdvancedDGLutGenerator::getMiddleXYZ(int middleIndex,
							 double
							 middleCCTRatio,
							 XYZ_ptr targetXYZ)
	    {
		//½�Xmiddle��XYZ
		XYZ_ptr middleBaseXYZ =
		    (*componentVector)[componentVector->size() - 1 -
				       middleIndex]->XYZ;
		xyY_ptr middleBasexyY(new CIExyY(middleBaseXYZ));
		double middleBaseCCT =
		    CorrelatedColorTemperature::
		    xy2CCTByMcCamyFloat(middleBasexyY);

		xyY_ptr targetxyY(new CIExyY(targetXYZ));
		double targetCCT =
		    CorrelatedColorTemperature::
		    xy2CCTByMcCamyFloat(targetxyY);

		//��X���CCT���t��
		double cctDiff = Math::abs(middleBaseCCT - targetCCT);
		//�A���Wratio(?)
		double cct = cctDiff * middleCCTRatio;
		double middleCCT =
		    (targetCCT <
		     middleCCT) ? (targetCCT + cct) : (middleBaseCCT +
						       cct);
		xyY_ptr middlexyY =
		    CorrelatedColorTemperature::
		    CCT2DIlluminantxyY(middleCCT);
		return middlexyY->toXYZ();
	    }

	    /*
	       middleCCTRatio�S�K����, �i�H�q middleXYZ�L�ר� targetXYZ���\��
	     */
	    XYZ_vector_ptr AdvancedDGLutGenerator::
		getTarget0(XYZ_ptr startXYZ, XYZ_ptr targetXYZ,
			   XYZ_ptr endXYZ,
			   double_vector_ptr luminanceGammaCurve,
			   int dimTurn, int brightTurn, double dimGamma,
			   double brightGamma, int brightWidth,
			   double middleCCTRatio) {
		int size = luminanceGammaCurve->size();
		XYZ_ptr middleXYZ =
		    getMiddleXYZ(dimTurn, middleCCTRatio, targetXYZ);
		double_array dimendValues = middleXYZ->getxyValues();
		double_array brightstartValues = targetXYZ->getxyValues();
		XYZ_vector_ptr result(new XYZ_vector(size));
		//==============================================================
		// dim�Ϭq
		//==============================================================
		double_vector_ptr dimGammaCurve =
		    DoubleArray::getRangeCopy(luminanceGammaCurve, 0,
					      dimTurn - 1);
		XYZ_vector_ptr dimResult =
		    DimTargetGenerator::getTarget(startXYZ, targetXYZ,
						  dimGammaCurve, dimGamma);

		int dimSize = dimResult->size();
		for (int x = 0; x < dimSize; x++) {
		    (*result)[x] = (*dimResult)[x];
		}
		//==============================================================

		//==============================================================
		// �����Ϭq
		//==============================================================
		for (int x = dimTurn; x < brightTurn; x++) {
		    //��Y���ܤ�
		    double Y = (*luminanceGammaCurve)[x];
		    double ratio =
			((double) (x - dimTurn)) / (brightTurn - dimTurn);
		    double v1 =
			Interpolation::linear(0, 1, dimendValues[0],
					      brightstartValues[0],
					      ratio);
		    double v2 =
			Interpolation::linear(0, 1, dimendValues[1],
					      brightstartValues[1],
					      ratio);
		    XYZ_ptr XYZ = getTargetXYZ(v1, v2, Y);;
		    (*result)[x] = XYZ;

		}
		//==============================================================

		//==============================================================
		// bright�Ϭq
		//==============================================================
		XYZ_vector_ptr brightResult =
		    getBrightGammaTarget(luminanceGammaCurve, targetXYZ,
					 endXYZ,
					 brightGamma, brightTurn,
					 brightWidth,
					 bitDepth);
		int brightSize = brightResult->size();
		for (int x = 0; x < brightSize; x++) {
		    XYZ_ptr XYZ = (*brightResult)[x];
		    (*result)[x + brightTurn] = XYZ;
		}
		//==============================================================
		return result;
	    };

	    /*
	       luminanceGammaCurve: �ؼ�gamma curve
	       startXYZ: �_�lXYZ
	       endXYZ: ����XYZ
	       brightGamma: ��Ŧ��u��gamma�ܤ�
	       brightTurn: ��Ū�����I
	       brightWidth: ����ܤƪ��e�װ϶�
	       bitDepth: ���O����`��T
	     */
	    XYZ_vector_ptr
		AdvancedDGLutGenerator::
		getBrightGammaTarget(double_vector_ptr
				     luminanceGammaCurve,
				     XYZ_ptr startXYZ,
				     XYZ_ptr endXYZ, double brightGamma,
				     int brightTurn, int brightWidth,
				     bptr < BitDepthProcessor > bitDepth) {
		//==============================================================
		// bright�Ϭq
		//==============================================================
		int size = luminanceGammaCurve->size();
		int brightEnd = brightTurn + brightWidth;
		int resultSize = size - brightTurn;
		XYZ_vector_ptr result(new XYZ_vector(resultSize));
		double_array brightstartValues = startXYZ->getxyValues();
		double_array brightendValues = endXYZ->getxyValues();
		double brightbase = brightEnd - 1 - brightTurn;
		for (int x = brightTurn; x < brightEnd; x++) {
		    double normal = ((double) x - brightTurn) / brightbase;
		    double gamma = Math::pow(normal,
					     brightGamma) * brightbase +
			brightTurn;
		    //�buv'�W�u���ܤ�
		    double u =
			Interpolation::linear(brightTurn, brightEnd - 1,
					      brightstartValues[0],
					      brightendValues[0],
					      gamma);
		    double v =
			Interpolation::linear(brightTurn, brightEnd - 1,
					      brightstartValues[1],
					      brightendValues[1],
					      gamma);
		    double Y = (*luminanceGammaCurve)[x];
		    (*result)[x - brightTurn] = getTargetXYZ(u, v, Y);
		}
		int endIndex = brightEnd - 1 - brightTurn;
		XYZ_ptr XYZ =
		    (-1 == endIndex) ? endXYZ : (*result)[endIndex];
		for (int x = brightEnd; x < size; x++) {
		    (*result)[x - brightTurn] = XYZ;
		}
		return result;
		//==============================================================
	    };
	    /*void AdvancedDGLutGenerator::setUseMaxTargetBIntensity(bool useMaxTargetBIntensity) {
	       this->useMaxTargetBIntensity = useMaxTargetBIntensity;
	       };
	       void AdvancedDGLutGenerator::setRTargetIntensity(double rTargetIntensity) {
	       this->rTargetIntensity = rTargetIntensity;
	       }
	       void AdvancedDGLutGenerator::setGTargetIntensity(double gTargetIntensity) {
	       this->gTargetIntensity = gTargetIntensity;
	       }
	       void AdvancedDGLutGenerator::setBTargetIntensity(double bTargetIntensity) {
	       this->bTargetIntensity = bTargetIntensity;
	       } */
	    /*void AdvancedDGLutGenerator::setTargetIntensity(double_array intensity) {
	       this->rTargetIntensity = intensity[0];
	       this->gTargetIntensity = intensity[1];
	       this->bTargetIntensity = intensity[2];
	       }; */
	    void AdvancedDGLutGenerator::windowClosing(TObject * Sender,
						       TCloseAction &
						       Action) {
		stopMeasure = true;
	    };
	    /*void AdvancedDGLutGenerator::setMultiGen(bool enable, int times) {
	       if (null == fetcher) {
	       throw IllegalStateException("null == fetcher");
	       }
	       this->multiGen = enable;
	       this->multiGenTimes = times;
	       }; */
	    /*XYZ_vector_ptr AdvancedDGLutGenerator::getTargetXYZVector() {
	       return targetXYZVector;
	       }; */

	    bool AdvancedDGLutGenerator::
		isDuplicateBlue100(Component_vector_ptr componentVector) {
		int size = componentVector->size();
		int timesOfB100 = 0;
		for (int x = size - 1; x > 0; x--) {
		    Component_ptr c0 = (*componentVector)[x];
		    Component_ptr c1 = (*componentVector)[x - 1];
		    if (c0->intensity->B > 100 && c1->intensity->B < 100
			|| c0->intensity->B < 100 && c1->intensity->B > 100
			||
			//��n����100, ���ӫ���
			c0->intensity->B == 100 ||
			//�̫�@�ӹG��100, �]����100
			(c0->intensity->B > 99.0 && x == size - 1)) {
			timesOfB100++;
		    }
		}
		return timesOfB100 == 2;
	    };
	    /*void AdvancedDGLutGenerator::setAutoParameter(bool autoParameter) {
	       this->autoParameter = autoParameter;
	       }; */
	    /*
	       ����ʽ�
	     */
	    bool AdvancedDGLutGenerator::
		checkTargetXYZVector(XYZ_vector_ptr targetXYZVector,
				     int start, int end,
				     double deltaabThreshold) {
		int size = targetXYZVector->size();
		XYZ_ptr white = (*targetXYZVector)[size - 1];
		int checkSize = end - start;
		double_vector_ptr checkResult(new
					      double_vector(checkSize));
		for (int x = start + 1; x < end; x++) {
		    XYZ_ptr x0 = (*targetXYZVector)[x - 1];
		    XYZ_ptr x1 = (*targetXYZVector)[x];
		    Lab_ptr lab0(new CIELab(x0, white));
		    Lab_ptr lab1(new CIELab(x1, white));
		    DeltaE de(lab0, lab1);
		    double dab = de.getCIE2000Deltaab();
		    (*checkResult)[x - (start + 1)] = dab;
		}
		double max = Math::max(checkResult);
		return max < deltaabThreshold;
	    };
	    int AdvancedDGLutGenerator::getAutoBrightTurn() {
		return autoBrightTurn;
	    };
	    int AdvancedDGLutGenerator::getAutoBrightWidth() {
		return autoBrightWidth;
	    };
	    /*
	       ���ĤG��componentVector2�MpanelRegulator2, �O�Φbtarget white != native white,
	       ���O�S�Q smooth�L�h�ɨϥ�
	     */
	    void AdvancedDGLutGenerator::
		setComponentVector2(Component_vector_ptr componentVector2,
				    bptr < PanelRegulator >
				    panelRegulator2) {
		this->componentVector2 = componentVector2;
		this->panelRegulator2 = panelRegulator2;
	    };
	    /*
	       �H�w���LDG�����O�Ӳ���DG Lut, �����ٻݭnpanelRegulator��remap.
	       �]�����LDG�����O��Gray Level�w�g����, ����ݭnremap�^���T�����G.
	     */
	    void AdvancedDGLutGenerator::setPanelRegulator(bptr <
							   PanelRegulator >
							   panelRegulator)
	    {
		this->panelRegulator1 = panelRegulator;
	    };
	    /*void AdvancedDGLutGenerator::setMiddleCCTRatio(double ratio) {
	       this->middleCCTRatio = ratio;
	       }; */

	    //==================================================================
	    //==================================================================
	    // DimTargetGenerator.
	    //==================================================================
	    const Domain DimTargetGenerator::UsageColorSpace = CIExy;
	    XYZ_vector_ptr DimTargetGenerator::
		getLinearTarget(XYZ_ptr startXYZ, XYZ_ptr endXYZ,
				double_vector_ptr luminanceGammaCurve) {
		return getLinearTarget(startXYZ, endXYZ,
				       luminanceGammaCurve,
				       UsageColorSpace);
	    };
	    XYZ_vector_ptr DimTargetGenerator::
		getLinearTarget(XYZ_ptr startXYZ, XYZ_ptr endXYZ,
				double_vector_ptr luminanceGammaCurve,
				Domain domain) {
		return getTarget(startXYZ, endXYZ, luminanceGammaCurve,
				 domain, 1);
	    }
	    XYZ_vector_ptr DimTargetGenerator::getTarget(XYZ_ptr startXYZ,
							 XYZ_ptr endXYZ,
							 double_vector_ptr
							 luminanceGammaCurve,
							 double gamma) {
		return getTarget(startXYZ, endXYZ, luminanceGammaCurve,
				 UsageColorSpace, gamma);
	    };

	    XYZ_vector_ptr DimTargetGenerator::
		getTarget(XYZ_ptr startXYZ, XYZ_ptr endXYZ,
			  double_vector_ptr luminanceGammaCurve,
			  Domain domain, double gamma) {
		int size = luminanceGammaCurve->size();
		double_array startuvValues;
		double_array enduvValues;
		switch (domain) {
		case CIExy:
		    startuvValues = startXYZ->getxyValues();
		    enduvValues = endXYZ->getxyValues();
		    break;
		case CIEuv:
		    startuvValues = startXYZ->getuvValues();
		    enduvValues = endXYZ->getuvValues();
		    break;
		case CIEuvPrime:
		    startuvValues = startXYZ->getuvPrimeValues();
		    enduvValues = endXYZ->getuvPrimeValues();
		    break;
		};
		XYZ_vector_ptr result(new XYZ_vector(size));
		for (int x = 0; x < size; x++) {
		    double normal = ((double) x) / (size - 1);
		    double gammanormal = Math::pow(normal, gamma);
		    double gammax = gammanormal * (size - 1);
		    //�buv'�W�u���ܤ�
		    double u = Interpolation::linear(0, size - 1,
						     startuvValues[0],
						     enduvValues[0],
						     gammax);
		    double v = Interpolation::linear(0, size - 1,
						     startuvValues[1],
						     enduvValues[1],
						     gammax);
		    double Y = (*luminanceGammaCurve)[x];

		    (*result)[x] = getTargetXYZ(u, v, Y);
		};
		return result;
	    }

	    //==================================================================
	};
    };
};

