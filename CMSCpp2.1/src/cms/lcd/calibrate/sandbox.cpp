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


	    XYZ_ptr getTargetXYZ(double v1, double v2, double v3, Domain domain) {
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

		    case CIEuvPrime:targetxyY.setuvPrimeYValues(targetValues);
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
	    /* WhiteSmooth�M��
	       componentVector: �q���o�쪺���O�S��
	       fetcher: �ΨӶq�����O�S�ʪ�����
	       analyzer1:
	       analyzer2nd:
	       bitDepth: ���O��bit�S��
	       calibrator:
	     */
	  AdvancedDGLutGenerator::AdvancedDGLutGenerator(Component_vector_ptr componentVector, bptr < cms::lcd::calibrate::ComponentFetcher > fetcher, bptr < IntensityAnalyzerIF > analyzer1, bptr < IntensityAnalyzerIF > analyzer2nd, bptr < BitDepthProcessor > bitDepth, const LCDCalibrator & calibrator):DimDGLutGenerator(componentVector, analyzer1),
		fetcher(fetcher), analyzer2nd(analyzer2nd),
		bitDepth(bitDepth), mode(WhiteSmooth), c(calibrator) {
		init();
	    };
	    /* �DWhiteSmooth�ҥi��
	       componentVector: �q���o�쪺���O�S��
	       fetcher: �ΨӶq�����O�S�ʪ�����
	       bitDepth: ���O��bit�S��
	       calibrator:
	     */
	    AdvancedDGLutGenerator::
		AdvancedDGLutGenerator(Component_vector_ptr
				       componentVector,
				       bptr < ComponentFetcher > fetcher,
				       bptr < BitDepthProcessor > bitDepth,
				       const LCDCalibrator &
				       calibrator):DimDGLutGenerator
		(componentVector, fetcher->getAnalyzer()),
		fetcher(fetcher), bitDepth(bitDepth), mode(Normal), c(calibrator) {
		init();
	    };

	    void AdvancedDGLutGenerator::init() {
		stopMeasure = false;
		//this->bitDepth = bitDepth;
		rgbGenerateResult = nil_RGBGamma;
		useMaxBIntensityZone = 30;
	    };


	    /*
	       targetWhite: �ؼХ��I
	       nativeWhite: ��l���I
	       luminanceGammaCurve: �ؼ�gamma curve
	       dimTurn: �C�Ƕ�������I
	       brightTurn: ���Ƕ�������I
	       dimGamma: �C�Ƕ�����Ŧ��ugamma�ܤ�
	       brightGamma: ���Ƕ�����Ŧ��ugamma�ܤ�
	       brightWidth: ���Ƕ����Ƕ��e��
	     */
	    void AdvancedDGLutGenerator::
		setTarget(XYZ_ptr targetWhite,
			  XYZ_ptr nativeWhite,
			  double_vector_ptr luminanceGammaCurve,
			  int dimTurn, int brightTurn,
			  double dimGamma, double brightGamma, int effectiveInputLevel) {
		//==============================================================
		// ��T�ǳ�
		//==============================================================
		this->effectiveInputLevel = effectiveInputLevel;
		int brightWidth = bitDepth->getEffectiveInputLevel() - brightTurn;
		XYZ_ptr blackXYZ = (*componentVector)[componentVector->size() - 1]->XYZ;
		this->brightTurn = brightTurn;

		this->targetXYZVector = getTarget0(blackXYZ, targetWhite, nativeWhite,	//start target end
						   luminanceGammaCurve, dimTurn,
						   brightTurn, dimGamma, brightGamma, brightWidth);
	    }

	    RGB_vector_ptr AdvancedDGLutGenerator::produce() {
		if (null == targetXYZVector) {
		    return nil_RGB_vector_ptr;
		}
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
		    try {
			return produceDGLutMulti(targetXYZVector, componentVector);
		    }
		    catch(IllegalStateException & ex) {
			return nil_RGB_vector_ptr;
		    }
		} else {
		    switch (mode) {
		    case WhiteSmooth:{
			    /*
			       smooth mode�O�Φb ���I�D��l��� + �nkeep�̤j�G��.
			       ���ɨ�Ӧ�ŭY���P, �n�N��ӵ��G��smooth.
			     */
			    //target white���ͪ����G
			    RGB_vector_ptr result1 = produceDGLut(targetXYZVector,
								  componentVector,
								  analyzer, panelRegulator1);
			    //native white���ͪ����G
			    RGB_vector_ptr result2;
			    if (componentVector2 != null) {
				result2 =
				    produceDGLut(targetXYZVector,
						 componentVector2, analyzer2nd, panelRegulator2);
			    } else {
				result2 =
				    produceDGLut(targetXYZVector,
						 componentVector, analyzer2nd, panelRegulator1);
			    }

			    //�N��ӵ��G�α��_��
			    return smooth(result1, result2, bitDepth, brightTurn);
			}
		    case Normal:
		    case BIntensitySmooth:
			{
			    //�j�������O�b��case
			    RGB_vector_ptr result = produceDGLut(targetXYZVector,
								 componentVector,
								 analyzer, panelRegulator1);

			    //==========================================================================
			    // �C�Ƕ��ץ�debug
			    //==========================================================================

			    //==========================================================================
			    return result;
			}
		    default:
			return nil_RGB_vector_ptr;

		    }
		}
	    }



	    RGB_vector_ptr AdvancedDGLutGenerator::
		smooth(RGB_vector_ptr result1, RGB_vector_ptr result2,
		       bptr < BitDepthProcessor > bitDepth, int brightTurn) {
		RGB_vector_ptr result = RGBVector::deepClone(result1);

		int level = bitDepth->getLevel();
		int part = level - brightTurn;
		int part13 = part / 3;
		int part13Start = level - part13;
		for (int x = brightTurn; x < part13Start; x++) {
		    RGB_ptr rgb = (*result)[x];
		    RGB_ptr rgb1 = (*result1)[x];
		    RGB_ptr rgb2 = (*result2)[x];
		    double gain2 = (((double) x) - brightTurn) / (part13Start - brightTurn);
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
		RGB_vector_ptr initRGBVector = produceDGLut(targetXYZVector, componentVector,
							    analyzer, panelRegulator1);
		int whiteLevel = bitDepth->getEffectiveInputLevel();
		bool keepMaxLumiInMulti = c.keepMaxYInMultiGen;
		//(KeepMaxLuminance::NativeWhite == c.keepMaxLuminance);
		if (keepMaxLumiInMulti) {
		    RGB_ptr whiteRGB = (*initRGBVector)[whiteLevel - 1];
		    whiteRGB->R = whiteRGB->G = whiteRGB->B = bitDepth->getOutputMaxDigitalCount();
		}

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
		    RGBVector::changeMaxValue(result, bitDepth->getFRCAbilityBit());

		    bptr < MeasureCondition >
			measureCondition(new MeasureCondition(RGBVector::reverse(result)));

		    Component_vector_ptr componentVectorPrime =
			fetcher->fetchComponent(measureCondition);
		    STORE_COMPONENT("MultiGen_Component_" +
				    _toString(t + 1) + ".xls", componentVectorPrime);
		    /*if (c.HighlightGammaFix) {        //old gamma correct test scopr
		       Component_ptr c = (*componentVectorPrime)[0];
		       double maxLuminance = c->XYZ->Y;
		       XYZ_ptr targetWhite = (*targetXYZVector)[effectiveInputLevel - 1];
		       XYZ_ptr secondWhite = (*targetXYZVector)[effectiveInputLevel - 2];
		       if (secondWhite->Y > maxLuminance) {
		       throw new IllegalStateException("secondWhite->Y > maxLuminance");
		       }
		       targetWhite->scaleY(maxLuminance);
		       } */

		    result =
			produceDGLut(targetXYZVector, componentVectorPrime,
				     analyzer, bptr < PanelRegulator > ((PanelRegulator *) null));
		    if (keepMaxLumiInMulti) {
			RGB_ptr whiteRGB = (*result)[whiteLevel - 1];
			whiteRGB->R = whiteRGB->G = whiteRGB->B =
			    bitDepth->getOutputMaxDigitalCount();
		    }
		    STORE_RGBVECTOR("MultiGen_DG_" + _toString(t + 1) + ".xls", result);
		}

		return result;
	    };

	    RGB_ptr AdvancedDGLutGenerator::
		getIdealIntensity(Component_vector_ptr componentVector,
				  bptr < cms::measure::MaxMatrixIntensityAnalyzer > analyzer) {
		Component_vector_ptr newcomponentVector =
		    fetchNewComponent(analyzer, componentVector);
		STORE_COMPONENT("idealIntensity.xls", newcomponentVector);
		DGLutGenerator lutgen(newcomponentVector);
		RGB_ptr refRGB = analyzer->getReferenceRGB();
		RGB_ptr intensity = lutgen.getIntensity(refRGB);
		return intensity;
	    };
	    double_array AdvancedDGLutGenerator::
		getSmoothIntensity(double rTargetIntensity,
				   double gTargetIntensity,
				   double bTargetIntensity, int grayLevel) {
		if (true == c.autoIntensity && true == c.smoothIntensity
		    && grayLevel >= c.smoothIntensityStart && grayLevel <= c.smoothIntensityEnd) {
		    double rIntensity = Interpolation::linear(c.smoothIntensityStart,
							      c.smoothIntensityEnd, 100,
							      rTargetIntensity, grayLevel);
		    double gIntensity = Interpolation::linear(c.smoothIntensityStart,
							      c.smoothIntensityEnd, 100,
							      gTargetIntensity, grayLevel);
		    double bIntensity = Interpolation::linear(c.smoothIntensityStart,
							      c.smoothIntensityEnd, 100,
							      bTargetIntensity, grayLevel);
		    double_array result(new double[3]);
		    result[0] = rIntensity;
		    result[1] = gIntensity;
		    result[2] = bIntensity;
		    return result;
		} else {
		    return nil_double_array;
		}
	    };
	    //class MaxBIntensityInfo;
	    MaxBIntensityInfo AdvancedDGLutGenerator::
		getMaxBIntensityInfo(XYZ_vector_ptr targetXYZVector,
				     Component_vector_ptr componentVector,
				     bptr < cms::measure::IntensityAnalyzerIF > analyzer) {
		ComponentLUT lut(componentVector);
		//���̤jB Intensity���Ƕ�
		//int maxBIntenstyRGL = lut.getMaxBIntensityRGL();
		int halfSmoothZone = useMaxBIntensityZone / 2;
		//�n��̤jB Intensity������DG��b:
		//int size = targetXYZVector->size();
		int maxBGrayLevel = effectiveInputLevel - 1 - halfSmoothZone;

		//���̤jB Intensity���ؼ�XYZ
		XYZ_ptr bmaxtargetXYZ = (*targetXYZVector)[maxBGrayLevel];
		//�̤jB Intensity�ؼ�XYZ�����X�Ӫ�anlyzer
		bptr < MaxMatrixIntensityAnalyzer > bmaxma = MaxMatrixIntensityAnalyzer::getReadyAnalyzer(analyzer, bmaxtargetXYZ);	//�ǤJ XYZ x3
		RGB_ptr refRGB = analyzer->getReferenceRGB();
		bmaxma->setReferenceRGB(refRGB);

		//�Q�ηs��analyzer��X�s��component(�N�Ointensity)
		Component_vector_ptr bmaxComponentVector =
		    fetchNewComponent(bmaxma, componentVector);
		ComponentLUT bmaxlut(bmaxComponentVector);
		//��X�W�z�ؼ�XYZ�����X�Ӫ��̤jB Intensity
		double maxBIntensity = bmaxlut.getMaxBIntensity();
		return MaxBIntensityInfo(maxBGrayLevel, maxBIntensity);
	    };
	    //======================================================================================
	    //����DG LUT���t��k�֤߳���
	    //======================================================================================
	    RGB_vector_ptr AdvancedDGLutGenerator::
		produceDGLut(XYZ_vector_ptr targetXYZVector,
			     Component_vector_ptr componentVector,
			     bptr < cms::measure::IntensityAnalyzerIF >
			     analyzer, bptr < PanelRegulator > panelRegulator) {
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
		RGB_ptr refRGB = analyzer->getReferenceRGB();
		//=============================================================
		// debug��
		//=============================================================
#ifdef DEBUG_CCTLUT_NEWMETHOD
		Component_vector_ptr maxComponentVector(new Component_vector());
#endif				//DEBUG_CCTLUT_NEWMETHOD

#ifdef DEBUG_INTENISITY
		Component_vector_ptr debugComponentVector(new Component_vector());
#endif
		//=============================================================

		//=============================================================
		//�]�wintensity
		//=============================================================
		double rTargetIntensity = -1;
		double gTargetIntensity = -1;
		double bTargetIntensity = -1;
		if (true == c.autoIntensity) {
		    //autoIntensity�q��U�q�쪺componentVector����̾A��target intensity
		    xyY_ptr refxyY = analyzer->getReferenceColor();
		    XYZ_ptr targetXYZ = refxyY->toXYZ();

		    bptr < MaxMatrixIntensityAnalyzer > ma =
			MaxMatrixIntensityAnalyzer::getReadyAnalyzer(analyzer, targetXYZ);
		    ma->setReferenceRGB(refRGB);

		    idealIntensity = getIdealIntensity(componentVector, ma);
		    rTargetIntensity = idealIntensity->R;
		    gTargetIntensity = idealIntensity->G;
		    bTargetIntensity = idealIntensity->B;
		}

		rTargetIntensity = (-1 == rTargetIntensity) ? 100 : rTargetIntensity;
		gTargetIntensity = (-1 == gTargetIntensity) ? 100 : gTargetIntensity;
		//B��100��?
		bTargetIntensity = (-1 == bTargetIntensity) ? 100 : bTargetIntensity;
		double_array intensity(new double[3]);
		intensity[0] = rTargetIntensity;
		intensity[1] = gTargetIntensity;
		intensity[2] = bTargetIntensity;
		//=============================================================

		//=============================================================
		// BIntensitySmooth init (NG)
		//=============================================================
		double maxBIntensity = -1;
		int maxBGrayLevel = -1;
		if (mode == BIntensitySmooth) {
		    MaxBIntensityInfo maxBIntensityInfo = getMaxBIntensityInfo(targetXYZVector,
									       componentVector,
									       analyzer);
		    maxBIntensity = maxBIntensityInfo.maxBIntensity;
		    maxBGrayLevel = maxBIntensityInfo.maxBGrayLevel;
		}
		//=============================================================

		RGB_vector_ptr rgbGenResultVector(new RGB_vector());
#ifdef DEBUG_CCTLUT_NEWMETHOD
		bptr < IntensityMatrixFile > intensityMatrixFile;
		if (FileExists(DEBUG_VERBOSE_STEP)) {
		    MAKE_DEBUG_DIR();
		    Util::deleteExist(debug_dir + "/intensityMatrix.xls");
		    intensityMatrixFile =
			bptr < IntensityMatrixFile >
			(new IntensityMatrixFile(debug_dir + "/intensityMatrix.xls"));
		}
#endif
		//=============================================================
		// �j��}�l
		//=============================================================
		for (int x = size - 1; x != -1; x--) {
		    Application->ProcessMessages();
		    XYZ_ptr targetXYZ = (*targetXYZVector)[x];	//�ǤJ(XYZ)

		    //���_����Analyzer, �]��Target White�@���ܤ�, �ҥH�Q�ηs��Analyzer, �p��XIntensity
		    bptr < MaxMatrixIntensityAnalyzer > ma = MaxMatrixIntensityAnalyzer::getReadyAnalyzer(analyzer, targetXYZ);	//�ǤJ XYZ x3
		    ma->setReferenceRGB(refRGB);

		    //�Q�ηs��analyzer��X�s��component(�N�Ointensity)
		    Component_vector_ptr newcomponentVector =
			fetchNewComponent(ma, componentVector);
		    Application->ProcessMessages();

		    {		// debug scope
#ifdef DEBUG_CCTLUT_NEWMETHOD
			if (FileExists(DEBUG_VERBOSE_STEP)) {
			    intensityMatrixFile->addIntensityVector(newcomponentVector);
			}
			//��Ĥ@�Ӧs�_��, �Ĥ@�ө����O�̤j��
			RGB_ptr grayLevel(new RGBColor(x, x, x));

			RGB_ptr maxIntensity(new RGBColor());
			ComponentLUT lut(newcomponentVector);
			double rcode = lut.correctCodeInRange(Channel::R, 255);
			double gcode = lut.correctCodeInRange(Channel::G, 255);
			maxIntensity->R = lut.getIntensity(Channel::R, rcode);
			maxIntensity->G = lut.getIntensity(Channel::G, gcode);
			int maxBIntensityRGL = lut.getMaxBIntensityRGL();
			maxIntensity->B = lut.getIntensity(Channel::B, maxBIntensityRGL);

			Component_ptr c(new Component(grayLevel, (*newcomponentVector)
						      [0]->intensity, targetXYZ, maxIntensity));
			maxComponentVector->push_back(c);	//�ǥX(vector)
#endif				//DEBUG_CCTLUT_NEWMETHOD
		    }

		    DGLutGenerator lutgen(newcomponentVector);
		    //=============================================================
		    // intensity smooth(����)
		    // target white�U�~�|�ҥ�
		    //=============================================================
		    if (true == c.autoIntensity
			&& true == c.smoothIntensity
			&& x >= c.smoothIntensityStart && x <= c.smoothIntensityEnd) {

			//�p�G�ҥ�auto intensity, �|�۰ʧ���100%��A�X��intensity
			//���O���|�|�y���C�Ƕ����ץ��X���D, �]���C�Ƕ����ؼ�intensity���A�O100%
			//�X�G���|�y���t�Ƕ��䤣����|���ܦ��\�h0... �ҥH�����ݭn�q1XX%�L�צ^100%
			double_array smoothIntensity = getSmoothIntensity(rTargetIntensity,
									  gTargetIntensity,
									  bTargetIntensity, x);
			intensity = smoothIntensity;
		    }
		    //=============================================================
		    //=============================================================
		    // BIntensitySmooth
		    // native white advance+de-hook�U�~�|�ҥ�
		    //=============================================================
		    //intensity smooth���ت��N�O�n��blue intensity�i�H�ĥX100, �M��Ssmooth�^100
		    //��T�Ӱ϶� 0~(zone start)~(zone middle/max b intensity)~255
		    //250 252 255
		    else if (mode == BIntensitySmooth) {
			//intensity smooth���ت��N�O�n��blue intensity�i�H�ĥX100, �M��Ssmooth�^100
			if (x <= (effectiveInputLevel - 1)
			    && x > maxBGrayLevel) {
			    //252~255
			    intensity[2] =
				Interpolation::linear(maxBGrayLevel,
						      (effectiveInputLevel
						       - 1), maxBIntensity, bTargetIntensity, x);
			    lutgen.setInverseSearch(true);
			} else if (x <= maxBGrayLevel
				   && x > (effectiveInputLevel - 1 - useMaxBIntensityZone)) {
			    //250~252
			    intensity[2] =
				Interpolation::
				linear((effectiveInputLevel - 1 -
					useMaxBIntensityZone),
				       maxBGrayLevel, bTargetIntensity, maxBIntensity, x);
			} else {
			    //0~250
			    intensity[2] = bTargetIntensity;
			}
		    }
		    //=============================================================

		    //double rIntensity = intensity[0];
		    //double gIntensity = intensity[1];
		    //double bIntensity = intensity[2];
		    RGB_ptr rgb = lutgen.getDGCode(intensity[0], intensity[1], intensity[2]);	//�ǥX(�D�n)
		    (*result)[x] = rgb;

		    //�������ͪ��L�{�O�_�����D
		    bool_array isCorrect = lutgen.isCorrectIntensityInRange();
		    RGB_ptr genResult(new
				      RGBColor((true ==
						isCorrect[0]) ? -1 : 0,
					       (true ==
						isCorrect[1]) ? -1 : 0,
					       (true == isCorrect[2]) ? -1 : 0));
		    rgbGenResultVector->push_back(genResult);	//�ǥX(vecotr)

#ifdef DEBUG_INTENISITY
		    {		//debug scope
			Component_ptr c = getFRCAbilityComponent(x, rgb, ma,
								 newcomponentVector);
			c->gamma = genResult;	//�ǥX(vector)
			debugComponentVector->push_back(c);
		    }
#endif
		}
		//=============================================================
		// �j�鵲��
		//=============================================================

		rgbGenerateResult =
		    RGBGamma::getReverse(RGBGamma_ptr(new RGBGamma(rgbGenResultVector, 0, Unknow)));


		if (null != panelRegulator) {
#ifdef DEBUG_REMAP_NEW
		    //�Y��panelRegulator, �i��remapping (�J��hook�~�ݭn)
		    GammaTestPanelRegulator *gammaTestRegulator =
			dynamic_cast < GammaTestPanelRegulator * >(panelRegulator.get());
		    if (null == gammaTestRegulator) {
			//�Y�OGammaTest(direct gamma)�򥻤Wcomponent�N��mapping����dg code, �ҥH�L���A�@remapping
			//�ݭnremapping�O�]���ĥμg�Jdg lut���覡���ܭ��O�S��
			result = panelRegulator->remapping(result);
		    }
#else
		    result = panelRegulator->remapping(result);
#endif
		}
		//=============================================================
		// debug scope
		//=============================================================
#ifdef DEBUG_CCTLUT_NEWMETHOD
		STORE_COMPONENT("1.3_maxIntensity.xls", maxComponentVector);
#endif
#ifdef DEBUG_INTENISITY
		//�Q��DG�^��Intenisty�Mwhite point��primart color�w��CIE xy
		STORE_COMPONENT("1.3_debugIntensity.xls", debugComponentVector);
#endif
		//=============================================================

		return result;
	    };

	    //======================================================================================

	    Component_ptr AdvancedDGLutGenerator::
		getFRCAbilityComponent(int grayLevel, RGB_ptr rgb,
				       bptr <
				       cms::measure::IntensityAnalyzerIF >
				       analyzer, Component_vector_ptr componentVector) {
		//�o�T�ˤ��ޤ���analyzer���O�̼˪�, �|�ܪ��OtargetXYZ
		XYZ_ptr rXYZ = analyzer->getPrimaryColor(Channel::R)->toXYZ();
		XYZ_ptr gXYZ = analyzer->getPrimaryColor(Channel::G)->toXYZ();
		XYZ_ptr bXYZ = analyzer->getPrimaryColor(Channel::B)->toXYZ();
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
		RGB_ptr intensityR = lutgen2.getIntensity(refR);
		RGB_ptr intensityG = lutgen2.getIntensity(refG);
		RGB_ptr intensityB = lutgen2.getIntensity(refB);

		double_array rXYZValues = rXYZ->getValues();
		double_array gXYZValues = gXYZ->getValues();
		double_array bXYZValues = bXYZ->getValues();
		//�ι�Wtarget primary��intensity����CIEXYZ
		rXYZValues = DoubleArray::times(rXYZValues, intensity2->R / intensityR->R, 3);
		gXYZValues = DoubleArray::times(gXYZValues, intensity2->G / intensityG->G, 3);
		bXYZValues = DoubleArray::times(bXYZValues, intensity2->B / intensityB->B, 3);
		XYZ_ptr rXYZ2(new Indep::CIEXYZ(rXYZValues));	//r
		XYZ_ptr gXYZ2(new Indep::CIEXYZ(gXYZValues));	//g
		XYZ_ptr bXYZ2(new Indep::CIEXYZ(bXYZValues));	//b
		//r+g
		XYZ_ptr rgXYZ2 = CIEXYZ::plus(rXYZ2, gXYZ2);
		//r+g+b
		XYZ_ptr rgbXYZ2 = CIEXYZ::plus(rgXYZ2, bXYZ2);

		RGB_ptr w(new RGBColor(grayLevel, grayLevel, grayLevel));
		Component_ptr c(new Component(w, intensity2, rgbXYZ2));
		return c;
	    };


	    /*bool AdvancedDGLutGenerator::isAvoidHook(XYZ_ptr targetXYZ, double offsetK) {
	       XYZ_ptr XYZOffset = getXYZ(targetXYZ, offsetK);
	       return isDuplicateBlue100(XYZOffset);
	       }; */
	    XYZ_ptr AdvancedDGLutGenerator::getXYZ(XYZ_ptr XYZ, double offsetK) {
		//==============================================================
		// ���Ʒǳ�
		//==============================================================
		xyY_ptr xyY(new CIExyY(XYZ));
		double cct = CorrelatedColorTemperature::xy2CCTByMcCamyFloat(xyY);
		xyY_ptr xyYOriginal = CorrelatedColorTemperature::CCT2DIlluminantxyY(cct);
		double cctOffset = cct + offsetK;
		xyY_ptr xyYOffset = CorrelatedColorTemperature::CCT2DIlluminantxyY(cctOffset);
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
	    /*bool AdvancedDGLutGenerator::isDuplicateBlue100(XYZ_ptr targetXYZ) {
	       xyY_ptr rxyY = analyzer->getPrimaryColor(Channel::R);
	       xyY_ptr gxyY = analyzer->getPrimaryColor(Channel::G);
	       xyY_ptr bxyY = analyzer->getPrimaryColor(Channel::B);

	       bptr < MaxMatrixIntensityAnalyzer > mmia =
	       MaxMatrixIntensityAnalyzer::getReadyAnalyzer(rxyY->toXYZ(), gxyY->toXYZ(),
	       bxyY->toXYZ(), targetXYZ);

	       Component_vector_ptr newcomponentVector = fetchNewComponent(mmia, componentVector);

	       return isDuplicateBlue100(newcomponentVector);
	       }; */

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
		if (dimTurn != 0) {
		    double_vector_ptr dimGammaCurve =
			DoubleArray::getRangeCopy(luminanceGammaCurve, 0,
						  dimTurn);
		    XYZ_vector_ptr dimResult = DimTargetGenerator::getTarget(startXYZ, targetXYZ,
									     dimGammaCurve,
									     dimGamma);

		    STORE_XYZXY_VECTOE("1.1_target_dim.xls", dimResult);
		    int dimSize = dimResult->size();
		    for (int x = 0; x < dimSize; x++) {
			(*result)[x] = (*dimResult)[x];
		    }
		}
		//==============================================================

		//==============================================================
		// �����Ϭq
		//==============================================================
		for (int x = dimTurn; x < brightTurn; x++) {
		    //��Y���ܤ�
		    double Y = (*luminanceGammaCurve)[x];
		    (*result)[x] = getTargetXYZ(dimendValues[0], dimendValues[1], Y);	//targetXYZ
		}
		//==============================================================

		//==============================================================
		// bright�Ϭq
		//==============================================================
		XYZ_vector_ptr brightResult = getBrightGammaTarget(luminanceGammaCurve,
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




	    /*
	       luminanceGammaCurve: �ؼ�gamma curve
	       startXYZ: �_�lXYZ
	       endXYZ: ����XYZ
	       brightGamma: ��Ŧ��u��gamma�ܤ�
	       brightTurn: ��Ū�����I
	       brightWidth: ����ܤƪ��e�װ϶�
	       bitDepth: ���O����`��T
	       static
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
					     brightGamma) * brightbase + brightTurn;
		    //�buv'�W�u���ܤ�
		    double u = Interpolation::linear(brightTurn, brightEnd - 1,
						     brightstartValues[0],
						     brightendValues[0], gamma);
		    double v = Interpolation::linear(brightTurn, brightEnd - 1,
						     brightstartValues[1],
						     brightendValues[1], gamma);
		    double Y = (*luminanceGammaCurve)[x];
		    (*result)[x - brightTurn] = getTargetXYZ(u, v, Y);
		}
		int endIndex = brightEnd - 1 - brightTurn;
		XYZ_ptr XYZ = (-1 == endIndex) ? endXYZ : (*result)[endIndex];
		for (int x = brightEnd; x < size; x++) {
		    (*result)[x - brightTurn] = XYZ;
		}
		return result;
		//==============================================================
	    };

	    void AdvancedDGLutGenerator::windowClosing(TObject * Sender, TCloseAction & Action) {
		stopMeasure = true;
	    };

	    /*bool AdvancedDGLutGenerator::isDuplicateBlue100(Component_vector_ptr componentVector) {
	       int size = componentVector->size();
	       int timesOfB100 = 0;
	       for (int x = size - 1; x > 0; x--) {
	       Component_ptr c0 = (*componentVector)[x];
	       Component_ptr c1 = (*componentVector)[x - 1];
	       if (c0->intensity->B > 100 && c1->intensity->B < 100
	       || c0->intensity->B < 100 && c1->intensity->B > 100 ||
	       //��n����100, ���ӫ���
	       c0->intensity->B == 100 ||
	       //�̫�@�ӹG��100, �]����100
	       (c0->intensity->B > 99.0 && x == size - 1)) {
	       timesOfB100++;
	       }
	       }
	       return timesOfB100 == 2;
	       }; */

	    /*
	       ����ʽ�
	     */
	    bool AdvancedDGLutGenerator::
		checkTargetXYZVector(XYZ_vector_ptr targetXYZVector,
				     int start, int end, double deltaabThreshold) {
		int size = targetXYZVector->size();
		XYZ_ptr white = (*targetXYZVector)[size - 1];
		int checkSize = end - start;
		double_vector_ptr checkResult(new double_vector(checkSize));
		for (int x = start + 1; x < end; x++) {
		    XYZ_ptr x0 = (*targetXYZVector)[x - 1];
		    XYZ_ptr x1 = (*targetXYZVector)[x];
		    Lab_ptr lab0(new CIELab(x0, white));
		    Lab_ptr lab1(new CIELab(x1, white));
		    DeltaE de(lab0, lab1);
		    double dab = de.getCIE2000Deltaab();
		    (*checkResult)[x - (start + 1)] = dab;
		} double max = Math::max(checkResult);
		return max < deltaabThreshold;
	    };
	    /*int AdvancedDGLutGenerator::getAutoBrightTurn() {
	       return autoBrightTurn;
	       };
	       int AdvancedDGLutGenerator::getAutoBrightWidth() {
	       return autoBrightWidth;
	       }; */
	    /*
	       ���ĤG��componentVector2�MpanelRegulator2, �O�Φbtarget white != native white,
	       ���O�S�Q smooth�L�h�ɨϥ�
	     */
	    void AdvancedDGLutGenerator::
		setComponentVector2(Component_vector_ptr componentVector2,
				    bptr < PanelRegulator > panelRegulator2) {
		this->componentVector2 = componentVector2;
		this->panelRegulator2 = panelRegulator2;
	    };
	    /*
	       �H�w���LDG�����O�Ӳ���DG Lut, �����ٻݭnpanelRegulator��remap.
	       �]�����LDG�����O��Gray Level�w�g����, ����ݭnremap�^���T�����G.
	     */
	    void AdvancedDGLutGenerator::setPanelRegulator(bptr < PanelRegulator > panelRegulator) {
		this->panelRegulator1 = panelRegulator;
	    };
	    void AdvancedDGLutGenerator::setUseMaxBIntensityZone(int zone) {
		this->useMaxBIntensityZone = zone;
		mode = BIntensitySmooth;
	    };

	    //==================================================================
	    //==================================================================
	    // DimTargetGenerator.
	    //==================================================================
	    const Domain DimTargetGenerator::UsageColorSpace = CIExy;
	    XYZ_vector_ptr DimTargetGenerator::
		getLinearTarget(XYZ_ptr startXYZ, XYZ_ptr endXYZ,
				double_vector_ptr luminanceGammaCurve) {
		return getLinearTarget(startXYZ, endXYZ, luminanceGammaCurve, UsageColorSpace);
	    };
	    XYZ_vector_ptr DimTargetGenerator::
		getLinearTarget(XYZ_ptr startXYZ, XYZ_ptr endXYZ,
				double_vector_ptr luminanceGammaCurve, Domain domain) {
		return getTarget(startXYZ, endXYZ, luminanceGammaCurve, domain, 1);
	    }
	    XYZ_vector_ptr DimTargetGenerator::getTarget(XYZ_ptr startXYZ,
							 XYZ_ptr endXYZ,
							 double_vector_ptr
							 luminanceGammaCurve, double gamma) {
		return getTarget(startXYZ, endXYZ, luminanceGammaCurve, UsageColorSpace, gamma);
	    };

	    XYZ_vector_ptr DimTargetGenerator::
		getTarget(XYZ_ptr startXYZ, XYZ_ptr endXYZ,
			  double_vector_ptr luminanceGammaCurve, Domain domain, double gamma) {
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
	    };

	    //==================================================================

	  DeHookProcessor::DeHookProcessor(const LCDCalibrator & calibrator):c(calibrator), bestGamma(-1)
	    {
	    };

	    int DeHookProcessor::getMaxBIntensityRawGrayLevel() {
		if (null != c.originalComponentVector) {
		    //�Y�n���Linverse B, �h�n���q����B�b���̤���
		    //�M��]�wb�̤j�u�Ψ�����I
		    ComponentLUT lut(c.originalComponentVector);
		    //���̤jB Intensity���Ƕ�
		    return lut.getMaxBIntensityRGL();
		} else {
		    /*bptr < cms::measure::IntensityAnalyzerIF > analyzer = c.fetcher->FirstAnalyzer;
		       bptr < MeterMeasurement > mm = analyzer->getMeterMeasurement(); */
		    bptr < MeterMeasurement > mm = c.getMeterMeasurement();
		    return MeasureTool::getMaxBIntensityRawGrayLevel(mm, c.bitDepth);
		}
	    };
	    SecondWhite DeHookProcessor::getSecondWhite(KeepMaxLuminance keepMaxLuminance,
							DeHook deHook) {
		if (keepMaxLuminance == KeepMaxLuminance::Smooth2NativeWhite) {
		    return SecondWhite::MaxRGB;
		} else if (deHook == KeepCCT) {
		    return SecondWhite::DeHook;
		} else if (deHook == SecondWithBGap1st || deHook == SecondWithGamma1st) {
		    return SecondWhite::DeHook2;
		} else {
		    return SecondWhite::None;
		}
	    };

	    bptr < cms::devicemodel::LCDModel >
		DeHookProcessor::getLCDModelForDeHook(int blueMaxGrayLevel) {
		bptr < MeterMeasurement > mm = c.getMeterMeasurement();
		int max = c.bitDepth->getOutputMaxDigitalCount();


		//�q�� R:B~255 G:B~255 B:blueMaxGrayLevel K
		Patch_vector_ptr patchList(new Patch_vector());
		Patch_ptr blackPatch = mm->measure(0, 0, 0, nil_string_ptr);
		patchList->push_back(blackPatch);
		//int measureStep = c.bitDepth->getMeasureStep();

		//�¦�@�w�n�����q�L
		for (int r = max; r >= blueMaxGrayLevel; r--) {
		    Patch_ptr p = mm->measure(r, 0, 0, nil_string_ptr);
		    patchList->push_back(p);
		}
		for (int g = max; g >= blueMaxGrayLevel; g--) {
		    Patch_ptr p = mm->measure(0, g, 0, nil_string_ptr);
		    patchList->push_back(p);
		}
		//�Ŧ�]����ѤF, ���M�u�n�q2��
		Patch_ptr b1p = mm->measure(0, 0, max, nil_string_ptr);
		patchList->push_back(b1p);
		Patch_ptr b0p = mm->measure(0, 0, blueMaxGrayLevel, nil_string_ptr);
		patchList->push_back(b0p);

		mm->setMeasureWindowsVisible(false);


		LCDTarget_ptr lcdTarget = LCDTarget::Instance::get(patchList);
		bptr < cms::devicemodel::DeHook2LCDModel >
		    model(new cms::devicemodel::DeHook2LCDModel(lcdTarget));
		return model;
	    };

	    /*
	       �Q��model�w������O, �bRG: blueMaxGrayLevel~255���d��, ���Ҧ��ŦXdeltaxySpec
	       ��RGB��XYZ�ꦨPatch
	     */
	    Patch_vector_ptr DeHookProcessor::getReasonableChromaticityPatchVector(bptr <
										   cms::
										   devicemodel::
										   LCDModel > model,
										   int
										   blueMaxGrayLevel,
										   double
										   deltaxySpec) {
		using namespace Dep;
		bptr < BitDepthProcessor > bitDepth = c.bitDepth;
		//int initstep = bitDepth->getMeasureStep();
		int frcOnlyBit = bitDepth->getFRCOnlyBit();
		double step = 1 / Math::pow(2, frcOnlyBit);

		XYZ_ptr whiteXYZ = model->getXYZ(RGBColor::White, false);
		xyY_ptr whitexyY(new CIExyY(whiteXYZ));

		Patch_vector_ptr result(new Patch_vector());

		for (double g = blueMaxGrayLevel + step; g < 255; g += step) {
		    for (double r = g + step; r < 255; r += step) {
			RGB_ptr rgb(new RGBColor(r, g, (double) blueMaxGrayLevel));
			XYZ_ptr XYZ = model->getXYZ(rgb, false);
			xyY_ptr xyY(new CIExyY(XYZ));
			double_array dxy = xyY->getDeltaxy(whitexyY);
			if (Math::abs(dxy[0]) < deltaxySpec && Math::abs(dxy[1]) < deltaxySpec) {
			    string_ptr name = rgb->toString();
			    XYZ_ptr normalizedXYZ = XYZ->clone();
			    normalizedXYZ->normalize(whiteXYZ);
			    Patch_ptr patch(new Patch(name, XYZ, normalizedXYZ, rgb));
			    result->push_back(patch);
			}
		    }
		}
		return result;
	    };

	    /*
	       �qpatchVector�̭����G��, ���ŦXgammaDWLimit~gammaUPLimit���̧C�Ƕ�
	       �]�N�O��, �^�ǭȪ�gray level�f�t��patchVector, �ܤ֦��@��patch��gamma���bgammaDWLimit~gammaUPLimit
	     */
	    int DeHookProcessor::getReasonableGammaGrayLevel(Patch_vector_ptr patchVector,
							     double gammaDWLimit,
							     double gammaUPLimit) {
		bptr < BitDepthProcessor > bitDepth = c.bitDepth;
		int maxcount = bitDepth->getInputMaxDigitalCount();
		bool hadGammaOk = false;

		for (int targetGrayLevel = maxcount - 1; targetGrayLevel > maxcount - 10;
		     targetGrayLevel--) {
		    double normalInput = ((double) targetGrayLevel) / maxcount;
		    bool gammaOk = false;
		    foreach(Patch_ptr p, *patchVector) {
			XYZ_ptr XYZ = p->getNormalizedXYZ();
			double gamma = GammaFinder::getGammaExponential(normalInput, XYZ->Y);
			if (gamma > gammaDWLimit && gamma < gammaUPLimit) {
			    gammaOk = true;
			    hadGammaOk = true;
			}
		    }
		    if (true == hadGammaOk && false == gammaOk) {
			return targetGrayLevel + 1;
		    }
		}
		return -1;
	    };
	    double DeHookProcessor::getNormalInput(int targetGrayLevel) {
		bptr < BitDepthProcessor > bitDepth = c.bitDepth;
		int maxcount = bitDepth->getInputMaxDigitalCount();
		double normalInput = ((double) targetGrayLevel) / maxcount;
		return normalInput;
	    }
	    /*
	       �qpatchVector�̭�, ����patch��btargetGrayLevel��, �̱���targetGamma������patch
	     */
	    Patch_ptr DeHookProcessor::getBestGammaPatch(Patch_vector_ptr patchVector,
							 double targetGamma, int targetGrayLevel) {

		int size = patchVector->size();
		if (0 == size) {
		    return nil_Patch_ptr;
		}
		double normalInput = getNormalInput(targetGrayLevel);

		int minDeltaIndex = -1;
		double minDeltaGamma = std::numeric_limits < double >::max();

		for (int x = 0; x < size; x++) {
		    Patch_ptr p = (*patchVector)[x];
		    double normalOutput = p->getNormalizedXYZ()->Y;
		    double gamma = GammaFinder::getGammaExponential(normalInput, normalOutput);
		    double deltaGamma = Math::abs(gamma - targetGamma);
		    if (deltaGamma < minDeltaGamma) {
			minDeltaGamma = deltaGamma;
			minDeltaIndex = x;
			bestGamma = gamma;
		    }
		}
		if (-1 == minDeltaIndex) {
		    return nil_Patch_ptr;
		}

		Patch_ptr p = (*patchVector)[minDeltaIndex];
		return p;
	    };

	    /*
	       �Q�ζq������k, �HbasePatch����¦���̲ŦXSPEC��patch
	     */
	    Patch_ptr DeHookProcessor::getBestGammaPatchByMeasure(Patch_ptr basePatch,
								  double targetGamma,
								  int targetGrayLevel,
								  double deltaxySpec) {
		RGB_ptr center = basePatch->getRGB();
		Patch_ptr bestPatch = basePatch;

		//����̦h�q256��
		for (int x = 0; x < 256; x++) {
		    Patch_ptr patch =
			getBestGammaPatchByMeasureLoop(bestPatch, targetGamma, targetGrayLevel,
						       deltaxySpec);
		    RGB_ptr newcenter = patch->getRGB();
		    if (newcenter->equalsValues(center)) {

			bestGamma = getGammaExponentialFromMeasure(patch, targetGrayLevel);
			return patch;
		    }
		    bestPatch = patch;
		    center = bestPatch->getRGB();
		}

		return nil_Patch_ptr;
	    };

	    double DeHookProcessor::getGammaExponentialFromMeasure(Patch_ptr patch,
								   int targetGrayLevel) {
		XYZ_ptr XYZ = patch->getXYZ();
		Patch_ptr white = measure(RGBColor::White);
		XYZ_ptr whiteXYZ = white->getXYZ();
		double normalInput = getNormalInput(targetGrayLevel);
		double normalizedY = XYZ->Y / whiteXYZ->Y;
		double gamma = GammaFinder::getGammaExponential(normalInput, normalizedY);
		return gamma;
	    };

	    /*
	       �j�馡���N���̨θ�
	     */
	    Patch_ptr DeHookProcessor::getBestGammaPatchByMeasureLoop(Patch_ptr basePatch,
								      double targetGamma,
								      int targetGrayLevel,
								      double deltaxySpec) {
		RGB_ptr center = basePatch->getRGB();
		bptr < BitDepthProcessor > bitDepth = c.bitDepth;
		int frcOnlyBit = bitDepth->getFRCOnlyBit();
		double step = 1 / Math::pow(2, frcOnlyBit);
		RGB_vector_ptr aroundRGBVector = getAroudRGBVector(center, step);

		Patch_ptr white = measure(RGBColor::White);
		XYZ_ptr whiteXYZ = white->getXYZ();
		xyY_ptr whitexyY(new CIExyY(whiteXYZ));
		Patch_vector_ptr patchVector(new Patch_vector());

		//����ŦX��ת�������X��
		foreach(RGB_ptr rgb, *aroundRGBVector) {
		    Patch_ptr patch = measure(rgb);
		    XYZ_ptr XYZ = patch->getXYZ();
		    xyY_ptr xyY(new CIExyY(XYZ));
		    double_array dxy = xyY->getDeltaxy(whitexyY);
		    if (Math::abs(dxy[0]) < deltaxySpec && Math::abs(dxy[1]) < deltaxySpec) {
			patchVector->push_back(patch);
		    }
		}

		Patch_ptr minDeltaGammaPatch = nil_Patch_ptr;
		double minDeltaGamma = std::numeric_limits < double >::max();

		//�A���̱���target gamma�����
		foreach(Patch_ptr p, *patchVector) {
		    XYZ_ptr XYZ = p->getXYZ();
		    double gamma = getGammaExponentialFromMeasure(p, targetGrayLevel);
		    double deltaGamma = Math::abs(targetGamma - gamma);
		    if (deltaGamma < minDeltaGamma) {
			minDeltaGamma = deltaGamma;
			minDeltaGammaPatch = p;
		    }
		}
		return minDeltaGammaPatch;
	    };

	    Patch_ptr DeHookProcessor::measure(RGB_ptr rgb) {
		if (null == rgbPatchMap) {
		    rgbPatchMap = RGBPatchMap_ptr(new RGBPatchMap());
		}
		Patch_ptr p = (*rgbPatchMap)[rgb];
		bptr < MeterMeasurement > mm = c.getMeterMeasurement();
		if (null == p) {
		    p = mm->measure(rgb, nil_string_ptr);
		    (*rgbPatchMap)[rgb] = p;
		}
		Patch_ptr whitepatch = (*rgbPatchMap)[RGBColor::White];
		if (null == whitepatch) {
		    whitepatch = mm->measure(RGBColor::White, nil_string_ptr);
		    (*rgbPatchMap)[RGBColor::White] = whitepatch;
		}
		XYZ_ptr whiteXYZ = whitepatch->getXYZ();
		XYZ_ptr XYZ = p->getXYZ();
		XYZ_ptr normalizedXYZ = XYZ->clone();
		normalizedXYZ->normalize(whiteXYZ);
		Patch::Operator::setNormalizedXYZ(p, normalizedXYZ);
		return p;
	    };

	    RGB_vector_ptr DeHookProcessor::getAroudRGBVector(RGB_ptr center, double step) {
		RGB_vector_ptr result(new RGB_vector());


		for (int baseR = -1; baseR <= 1; baseR++) {
		    for (int baseG = -1; baseG <= 1; baseG++) {
			double r = center->R + step * baseR;
			double g = center->G + step * baseG;
			if (r > g && g > center->B) {
			    RGB_ptr clone = center->clone();
			    clone->R = r;
			    clone->G = g;
			    result->push_back(clone);
			}
		    }
		}
		return result;
	    };

	    double_vector_ptr DeHookProcessor::alterGammaCurve(double_vector_ptr gammaCurve,
							       int alterStart, int alterEnd,
							       int maxDigitalCount,
							       double alterEndTargetGamma) {
		double_vector_ptr result = DoubleArray::copy(gammaCurve);
		double startInput = ((double) alterStart) / maxDigitalCount;
		double startOutput = (*gammaCurve)[alterStart];
		double startGamma = GammaFinder::getGammaExponential(startInput, startOutput);

		for (int x = alterStart + 1; x <= alterEnd; x++) {
		    double normal = ((double) x) / maxDigitalCount;
		    double gamma = Interpolation::linear(alterStart, alterEnd, startGamma,
							 alterEndTargetGamma,
							 x);
		    double output = GammaFinder::gamma(normal, gamma);
		    (*result)[x] = output;
		}

		return result;
	    };
	};
    };

};

