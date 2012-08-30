#include <includeall.h>
#pragma hdrstop
#include "dgcodefile.h"
//C系統文件
#include <cstdarg>
//C++系統文件                  
#include <iostream>

//其他庫頭文件

//本項目內頭文件


namespace cms {
    namespace colorformat {
	using namespace std;
	using namespace boost;
	using namespace java::lang;
	using namespace cms::lcd::calibrate;
	using namespace cms::lcd;
	using namespace Indep;
	using namespace Dep;
	using namespace cms::colorspace;
	using namespace cms::util;
	using namespace cms::measure;

	//======================================================================
	// DGLutFile
	//======================================================================
	string_vector_ptr DGLutFile::makeValues(int n, Component_ptr c) {
	    return makeValues(n, c, RGB_ptr((RGBColor *) null), RGB_ptr((RGBColor *) null));
	};
	string_vector_ptr DGLutFile::
	    makeValues(int n, Component_ptr c, RGB_ptr rgbGamma, RGB_ptr rgbGammaFix) {
	    string_vector_ptr values(new string_vector(13));
	     (*values)[0] = _toString(n);
	    xyY_ptr xyY(new CIExyY(c->XYZ));
	     (*values)[1] = _toString(xyY->x);
	     (*values)[2] = _toString(xyY->y);
	     (*values)[3] = _toString(xyY->Y);
	    RGB_ptr intensity = c->intensity;
	     (*values)[4] = _toString(intensity->R);
	     (*values)[5] = _toString(intensity->G);
	     (*values)[6] = _toString(intensity->B);
	    //gamma 0~100
	    if (null != rgbGamma) {
		(*values)[7] = _toString(rgbGamma->R);
		(*values)[8] = _toString(rgbGamma->G);
		(*values)[9] = _toString(rgbGamma->B);
	    }

	    if (null != rgbGammaFix) {
		(*values)[10] = _toString(rgbGammaFix->R);
		(*values)[11] = _toString(rgbGammaFix->G);
		(*values)[12] = _toString(rgbGammaFix->B);
	    }
	    return values;
	};
      DGLutFile::DGLutFile(const std::string & filename, Mode mode):ExcelAccessBase(filename,
			mode),
	    maxValue(Dep::MaxValue::Double255) {
	    init();
	};

	DGLutFile::DGLutFile(const std::string & filename, Mode mode,
			     const Dep::
			     MaxValue & maxValue):ExcelAccessBase(filename,
								  mode), maxValue(maxValue) {
	    init();
	};

	void DGLutFile::init() {
	    initSheet(GammaTable, 4, "Gray Level", "Gamma R", "Gamma G", "Gamma B");
	    initSheet(RawData, 16, "Gray Level", "W_x", "W_y", "W_Y (nit)",
		      "W_R", "W_G", "W_B", "RP", "GP", "BP",
		      "RP_Intensity_Fix", "GP_Intensity_Fix", "BP_Intensity_Fix", "DG_R", "DG_G",
		      "DG_B");
	    initPropertySheet();
	    /*initSheet(Measure, 12, "id", "R", "G", "B", "X", "Y (nit)", "Z", "_x", "_y",
	       "R12", "G12", "B12");
	       measureID = 1; */
	};


	const string & DGLutFile::RawData = "Raw_Data";
	const string & DGLutFile::Target = "Target";
	const string & DGLutFile::MultiGenTarget = "Multi_Gen_Target";
	const string & DGLutFile::LCDTarget = "LCD_Target";
	//const string & DGLutFile::Measure = "Measure";


	void DGLutFile::setRawData(Component_vector_ptr componentVector,
				   RGBGamma_ptr initialRGBGamma, RGBGamma_ptr finalRGBGamma) {
	    //==================================================================
	    // 檢查來源資料
	    //==================================================================
	    //int componentSize = componentVector->size();
	    if (null != initialRGBGamma && null != finalRGBGamma
		&& initialRGBGamma->r->size() != finalRGBGamma->r->size()) {
		throw IllegalArgumentException("initialRGBGamma->size() != finalRGBGamma->size()");
	    };

	    //==================================================================
	    //==================================================================
	    // 初始資料設定
	    //==================================================================
	    int part1Size = componentVector->size();
	    int part2Size = null != initialRGBGamma ? initialRGBGamma->r->size() : part1Size;
	    const int headerCount = getHeaderCount(RawData);
	    string_vector_ptr values(new string_vector(headerCount));
	    //==================================================================
	    //==================================================================
	    // 迴圈處理
	    //==================================================================
	    //設定前半部量測的data
	    for (int x = 0; x != part1Size; x++) {
		int n = part2Size - 1 - x;
		Component_ptr c = (*componentVector)[x];
		int w = static_cast < int >(c->rgb->getValue(Channel::W));
		(*values)[0] = _toString(w);

		if (null != c->XYZ) {
		    xyY_ptr xyY(new CIExyY(c->XYZ));
		    (*values)
			[1] = _toString(xyY->x);
		    (*values)
			[2] = _toString(xyY->y);
		    (*values)
			[3] = _toString(xyY->Y);
		} else {
		    StringVector::setContent(values, "0", 3, 1, 2, 3);
		}


		RGB_ptr intensity = c->intensity;
		if (null != intensity) {
		    (*values)
			[4] = _toString(intensity->R);
		    (*values)
			[5] = _toString(intensity->G);
		    (*values)
			[6] = _toString(intensity->B);
		} else {
		    StringVector::setContent(values, "0", 3, 4, 5, 6);
		}

		//gamma 0~100
		if (null != initialRGBGamma) {
		    (*values)[7] = _toString((*initialRGBGamma->r)[n]);
		    (*values)[8] = _toString((*initialRGBGamma->g)[n]);
		    (*values)[9] = _toString((*initialRGBGamma->b)[n]);
		} else {
		    StringVector::setContent(values, "0", 3, 7, 8, 9);
		}

		if (null != finalRGBGamma) {
		    (*values)[10] = _toString((*finalRGBGamma->r)[n]);
		    (*values)[11] = _toString((*finalRGBGamma->g)[n]);
		    (*values)[12] = _toString((*finalRGBGamma->b)[n]);
		} else {
		    StringVector::setContent(values, "0", 3, 10, 11, 12);
		}
		RGB_ptr dg = c->rgb;
		if (null != dg) {
		    (*values)[13] = _toString(dg->R);
		    (*values)[14] = _toString(dg->G);
		    (*values)[15] = _toString(dg->B);
		} else {
		    StringVector::setContent(values, "-1", 3, 13, 14, 15);
		}

		this->insertData(RawData, values, false);
	    }

	    //設定後半部gamma的data
	    for (int x = part1Size; x != part2Size; x++) {
		int n = part2Size - 1 - x;
		StringVector::setContent(values, "-1", 7, 0, 1, 2, 3, 4, 5, 6);

		//gamma 0~100
		if (null != initialRGBGamma) {
		    (*values)[7] = _toString((*initialRGBGamma->r)[n]);
		    (*values)[8] = _toString((*initialRGBGamma->g)[n]);
		    (*values)[9] = _toString((*initialRGBGamma->b)[n]);
		} else {
		    StringVector::setContent(values, "0", 3, 7, 8, 9);
		}

		if (null != finalRGBGamma) {
		    (*values)[10] = _toString((*finalRGBGamma->r)[n]);
		    (*values)[11] = _toString((*finalRGBGamma->g)[n]);
		    (*values)[12] = _toString((*finalRGBGamma->b)[n]);
		} else {
		    StringVector::setContent(values, "0", 3, 10, 11, 12);
		}
		StringVector::setContent(values, "-1", 3, 13, 14, 15);
		this->insertData(RawData, values, false);
	    }

	    //==================================================================
	};

	void DGLutFile::setTargetXYZVector(XYZ_vector_ptr targetXYZVector) {
	    setTargetXYZVector(targetXYZVector, nil_RGB_vector_ptr,
			       bptr < BitDepthProcessor > ((BitDepthProcessor *) null));
	}

	LCDTarget_ptr DGLutFile::getLCDTarget() {
	    if (db->isTableExist(LCDTarget)) {
		/*db->setTableName(LCDTarget);
		   bptr < DBQuery > query = db->selectAll();
		   int index = 0;
		   while (query->hasNext()) {
		   string_vector_ptr result = query->nextResult();
		   }; */
		throw new UnsupportedOperationException();

	    } else {
		return LCDTarget_ptr((cms::lcd::LCDTarget *) null);
	    }
	};

	void DGLutFile::addToLCDTarget(Patch_ptr p) {
	    //const int headerCount = 9;
	    const int headerCount = getHeaderCount(LCDTarget);
	    string_vector_ptr values(new string_vector(headerCount));

	    (*values)[0] = "-1";

	    RGB_ptr rgb = p->getRGB();
	    (*values)[1] = _toString(rgb->R);
	    (*values)[2] = _toString(rgb->G);
	    (*values)[3] = _toString(rgb->B);

	    XYZ_ptr XYZ = p->getXYZ();
	    (*values)[4] = _toString(XYZ->X);
	    (*values)[5] = _toString(XYZ->Y);
	    (*values)[6] = _toString(XYZ->Z);

	    xyY_ptr xyY(new CIExyY(XYZ));
	    (*values)[7] = _toString(xyY->x);
	    (*values)[8] = _toString(xyY->y);

	    this->insertData(LCDTarget, values, true);
	};
	void DGLutFile::setLCDTarget(LCDTarget_ptr lcdTarget) {
	    Patch_vector_ptr patchList = lcdTarget->getPatchList();

	    //==================================================================
	    // 初始資料設定
	    //==================================================================
	    const int headerCount = 9;
	    initSheet(LCDTarget, headerCount, "id", "R", "G", "B", "X", "Y (nit)", "Z", "_x", "_y");

	    int size = patchList->size();
	    string_vector_ptr values(new string_vector(headerCount));
	    //==================================================================
	    int id = 1;
	    foreach(Patch_ptr p, *patchList) {
		(*values)[0] = _toString(id++);

		RGB_ptr rgb = p->getRGB();
		(*values)[1] = _toString(rgb->R);
		(*values)[2] = _toString(rgb->G);
		(*values)[3] = _toString(rgb->B);

		XYZ_ptr XYZ = p->getXYZ();
		(*values)[4] = _toString(XYZ->X);
		(*values)[5] = _toString(XYZ->Y);
		(*values)[6] = _toString(XYZ->Z);

		xyY_ptr xyY(new CIExyY(XYZ));
		(*values)[7] = _toString(xyY->x);
		(*values)[8] = _toString(xyY->y);

		this->insertData(LCDTarget, values, false);
	    }


	};


	void DGLutFile::
	    setTargetXYZVector(XYZ_vector_ptr targetXYZVector,
			       RGB_vector_ptr dglut, bptr < BitDepthProcessor > bitDepth) {
	    setTargetXYZVector(Target, targetXYZVector, dglut, bitDepth);
	};
	void DGLutFile::
	    setMultiGenTargetXYZVector(XYZ_vector_ptr targetXYZVector,
				       RGB_vector_ptr dglut, bptr < BitDepthProcessor > bitDepth) {
	    setTargetXYZVector(MultiGenTarget, targetXYZVector, dglut, bitDepth);
	};

	void DGLutFile::
	    setTargetXYZVector(const std::string & targetName, XYZ_vector_ptr targetXYZVector,
			       RGB_vector_ptr dglut, bptr < BitDepthProcessor > bitDepth) {
	    //==================================================================
	    // 初始資料設定
	    //==================================================================
	    const int headerCount = 16;
	    //const int headerCount = getHeaderCount(targetName);
	    string_vector_ptr values(new string_vector(headerCount));

	    initSheet(targetName, headerCount, "Gray Level", "X",
		      "Y (nit)", "Z", "_x", "_y", "dx", "dy",
		      // 8~13, 由Gamma Table R/G/B/找到對應的Intensity,
		      //再由Intensity及Target White/Primary Color推算出XYZ, 得到Gamma X/Y/Z
		      "Gamma R", "Gamma G", "Gamma B", "Sim X",
		      "Sim Y", "Sim Z", "Sim _x", "Sim _y");

	    int size = targetXYZVector->size();
	    //string_vector_ptr values(new string_vector(headerCount));
	    //==================================================================
	    Component_vector_ptr componentVector = nil_Component_vector_ptr;
	    bptr < ComponentLUT > componentLUT;
	    bptr < DGLutProperty > property;
	    XYZ_ptr rXYZ, gXYZ, bXYZ;
	    double_array targetWhiteRatio;
	    if (null != dglut) {
		int max = 255;
		if (null != bitDepth && bitDepth->isTCONInput()) {
		    max = bitDepth->getLutMaxValue().max;
		}
		//從檔案回讀componentVector
		componentVector = getComponentVector(false, max);
		componentLUT = bptr < ComponentLUT > (new ComponentLUT(componentVector));
		property = getProperty();
		xyY_ptr rxyY = property->getTargetReferenceColor(Channel::R);
		xyY_ptr gxyY = property->getTargetReferenceColor(Channel::G);
		xyY_ptr bxyY = property->getTargetReferenceColor(Channel::B);
		rXYZ = rxyY->toXYZ();
		gXYZ = gxyY->toXYZ();
		bXYZ = bxyY->toXYZ();
		targetWhiteRatio = property->getTargetWhiteRatio();
	    }
	    //==================================================================
	    // 迴圈處理
	    //==================================================================

	    for (int x = 0; x != size; x++) {
		XYZ_ptr XYZ = (*targetXYZVector)[x];

		(*values)[0] = _toString(x);
		(*values)
		    [1] = _toString(XYZ->X);
		(*values)
		    [2] = _toString(XYZ->Y);
		(*values)
		    [3] = _toString(XYZ->Z);
		xyY_ptr xyY(new CIExyY(XYZ));
		(*values)
		    [4] = _toString(xyY->x);
		(*values)
		    [5] = _toString(xyY->y);

		if (x == 0) {
		    StringVector::setContent(values, "0", 2, 6, 7);	//dx dy=0
		} else {
		    XYZ_ptr XYZ0 = (*targetXYZVector)[x - 1];
		    xyY_ptr xyY0(new CIExyY(XYZ0));
		    double dx = xyY->x - xyY0->x;
		    double dy = xyY->y - xyY0->y;
		    if (Math::abs(dx) < 0.00001 || Math::abs(dy) < 0.00001) {
			StringVector::setContent(values, "0", 2, 6, 7);
		    } else {
			(*values)[6] = _toString(dx);
			(*values)[7] = _toString(dy);
		    }

		}

		if (null != dglut) {
		    RGB_ptr rgb = (*dglut)[x];
		    (*values)[8] = _toString(rgb->R);
		    (*values)[9] = _toString(rgb->G);
		    (*values)[10] = _toString(rgb->B);
		    double r = rgb->getValue(Channel::R, MaxValue::Double255);
		    double g = rgb->getValue(Channel::G, MaxValue::Double255);
		    double b = rgb->getValue(Channel::B, MaxValue::Double255);


		    r = componentLUT->correctCodeInRange(Channel::R, r);
		    double rIntensity =
			componentLUT->
			hasCorrectedInRange(Channel::
					    R) ? -1 : componentLUT->getIntensity(Channel::R,
										 r) *
			targetWhiteRatio[0];
		    g = componentLUT->correctCodeInRange(Channel::G, g);
		    double gIntensity =
			componentLUT->
			hasCorrectedInRange(Channel::
					    G) ? -1 : componentLUT->getIntensity(Channel::G,
										 g) *
			targetWhiteRatio[1];
		    b = componentLUT->correctCodeInRange(Channel::B, b);
		    double bIntensity =
			componentLUT->
			hasCorrectedInRange(Channel::
					    B) ? -1 : componentLUT->getIntensity(Channel::B,
										 b) *
			targetWhiteRatio[2];

		    if (-1 == rIntensity || -1 == gIntensity || -1 == bIntensity) {
			rIntensity = gIntensity = bIntensity = -1;
		    }
		    double X =
			rXYZ->X * rIntensity / 100 +
			gXYZ->X * gIntensity / 100 + bXYZ->X * bIntensity / 100;
		    double Y =
			rXYZ->Y * rIntensity / 100 +
			gXYZ->Y * gIntensity / 100 + bXYZ->Y * bIntensity / 100;
		    double Z =
			rXYZ->Z * rIntensity / 100 +
			gXYZ->Z * gIntensity / 100 + bXYZ->Z * bIntensity / 100;

		    double targetx = Y != 0 ? X / (X + Y + Z) : 0;
		    double targety = Y != 0 ? Y / (X + Y + Z) : 0;
		    (*values)[11] = _toString(X);
		    (*values)[12] = _toString(Y);
		    (*values)[13] = _toString(Z);
		    (*values)[14] = _toString(targetx);
		    (*values)[15] = _toString(targety);
		} else {
		    StringVector::setContent(values, "-1", 6, 8, 9, 10, 11, 12, 13, 14, 15);	//dx dy=0
		}

		this->insertData(targetName, values, false);
	    }
	};
	Component_vector_ptr DGLutFile::getComponentVector(bool rgbFromGammaTable, int max) {
	    Component_vector_ptr vector(new Component_vector());
	    db->setTableName(RawData);
	    bptr < DBQuery > query = db->selectAll();
	    RGB_vector_ptr gammaTable = RGBVector::reverse(getGammaTable());
	    int index = 0;
	    while (query->hasNext()) {
		string_vector_ptr result = query->nextResult();
		int gray = _toInt((*result)[0]);
		double x = _toDouble((*result)[1]);
		double y = _toDouble((*result)[2]);
		double Y = _toDouble((*result)[3]);
		if (gray == -1 || Y == 0) {
		    break;
		}
		double R = _toDouble((*result)[4]);
		double G = _toDouble((*result)[5]);
		double B = _toDouble((*result)[6]);
		double r = _toDouble((*result)[7]);
		double g = _toDouble((*result)[8]);
		double b = _toDouble((*result)[9]);
		RGB_ptr rgb;
		if (true == rgbFromGammaTable && gammaTable->size() != 0) {
		    //RGB_ptr gamma = (*gammaTable)[index++];
		    rgb = (*gammaTable)[index++];
		} else {
		    int c = Math::round(((double) gray) / max * 255);
		    rgb = RGB_ptr(new RGBColor(c, c, c));
		}

		RGB_ptr intensity(new RGBColor(R, G, B));
		xyY_ptr xyY(new CIExyY(x, y, Y));
		XYZ_ptr XYZ(xyY->toXYZ());
		RGB_ptr gamma(new RGBColor(r, g, b));
		bptr < Component > component(new Component(rgb, intensity, XYZ, gamma));
		vector->push_back(component);
	    };
	    return vector;
	};

	/*
	   把存在xls檔案裡的資訊轉成ComponentVector (debug用)
	 */
	Component_vector_ptr DGLutFile::getComponentVector() {
	    return getComponentVector(true, 255);
	};

	void DGLutFile::setProperty(const
				    DGLutProperty & property) {
	    property.store(*this);
	};
	bptr < DGLutProperty > DGLutFile::getProperty() {
	    try {
		bptr < DGLutProperty > property(new DGLutProperty(this));
		return property;
	    }
	    catch(IllegalStateException & ex) {
		return bptr < DGLutProperty > ((DGLutProperty *) null);
	    }
	};
	RGB_vector_ptr DGLutFile::getGammaTable() {
	    return ExcelAccessBase::getGammaTable(maxValue);
	};

	//======================================================================


	//======================================================================
	// DGLutProperty
	//======================================================================
	const string DGLutProperty::On = "On";
	const string DGLutProperty::Off = "Off";
	const string DGLutProperty::Native = "native";
	const string DGLutProperty::Target = "target";
	const string DGLutProperty::Second = "second";
	const string DGLutProperty::WhiteRatio = "WhiteRatio";
	const string DGLutProperty::TargetWhiteRatio = "TargetWhiteRatio";
	void DGLutProperty::store(ExcelAccessBase & dgfile) const {

	    //==================================================================
	    // application status
	    //==================================================================
	    int_array versionInfo = Util::fetchVersionInfo();
	    string version =
		"3.4 (build " + _toString(versionInfo[2]) + "." + _toString(versionInfo[3]) + ")";
	     dgfile.addProperty("cct product version", version);
	     dgfile.addProperty("status", c->ExcuteStatus);
	    bool isCCTMode = "CCTDGLut" == c->ExcuteStatus;
	    //==================================================================


	    //==================================================================
	    // MeasureCondition
	    //==================================================================
	     bptr < MeasureCondition > mc = c->measureCondition;
	    switch (mc->type) {
	    case MeasureCondition::Normal:{
		    dgfile.addProperty("start", mc->start);
		    dgfile.addProperty("end", mc->end);
		    dgfile.addProperty("step", mc->step);
		};
		break;
	    case MeasureCondition::Extend:{
		    dgfile.addProperty("high level start", mc->highStart);
		    dgfile.addProperty("high level end", mc->highEnd);
		    dgfile.addProperty("high level step", mc->highStep);
		    dgfile.addProperty("low level start", mc->lowStart);
		    dgfile.addProperty("low level end", mc->lowEnd);
		    dgfile.addProperty("low level step", mc->lowStep);
		};
		break;
	    };
	    bptr < BitDepthProcessor > bitDepth = c->bitDepth;
	    dgfile.addProperty("t-con input", bitDepth->isTCONInput()? On : Off);
	    dgfile.addProperty("in", *bitDepth->getInputMaxValue().toString());
	    dgfile.addProperty("lut", *bitDepth->getLutMaxValue().toString());
	    dgfile.addProperty("out", *bitDepth->getOutputMaxValue().toString());
	    //dgfile.addProperty("out", *bitDepth->getOutputMaxValue().toString());

	    //==================================================================

	    //==================================================================
	    //low level correct
	    //==================================================================
	    if (isCCTMode) {
		string lowLevelCorrect = "low level correct";
		switch (c->correct) {
		case DimCorrect::P1P2:
		    dgfile.addProperty(lowLevelCorrect, "P1P2");
		    dgfile.addProperty("p1", c->p1);
		    dgfile.addProperty("p2", c->p2);
		    break;
		case DimCorrect::RBInterpolation:
		    dgfile.addProperty(lowLevelCorrect, "RBInterpolation");
		    dgfile.addProperty("rb under", c->under);
		    break;
		case DimCorrect::None:
		    dgfile.addProperty(lowLevelCorrect, "None");
		    break;
		case DimCorrect::DefinedDim:
		    dgfile.addProperty(lowLevelCorrect, "DefinedDim");
		    dgfile.addProperty("defined dim under", c->under);
		    dgfile.addProperty("defined dim strength", c->dimStrength);
		    /*if (true == c->dimFix) {
		       dgfile.addProperty("defined dim - fix", On);
		       } */
		    /*if (true == c->feedbackFix) {
		       dgfile.addProperty("defined dim - feedback fix", On);
		       if( null != maxMeasureError ) {
		       dgfile.
		       addProperty
		       ("defined dim - feedback fix init defect", c->initDefectCount);
		       dgfile.addProperty("defined dim - feedback fix count", c->feedbackFixCount);
		       dgfile.addProperty("max measure dx", c->maxMeasureError[0]);
		       dgfile.addProperty("max measure dy", c->maxMeasureError[1]);
		       }
		       } */
		    /*if (true == c->dimFix || true == c->feedbackFix) {
		       dgfile.addProperty("defined dim - fix threshold", c->dimFixThreshold);
		       } */

		    XYZ_ptr blackXYZ =
			(*c->originalComponentVector)[c->originalComponentVector->size() - 1]->XYZ;
		    xyY_ptr blackxyY(new CIExyY(blackXYZ));
		    dgfile.addProperty("defined dim black", *blackxyY->toString());
		    break;
		}
		dgfile.addProperty("keep dark level", c->KeepDarkLevel ? On : Off);
	    }
	    //==================================================================

	    //==================================================================
	    // others
	    //==================================================================
	    if (isCCTMode) {
		dgfile.addProperty("New Method", c->useNewMethod ? On : Off);
		if (c->useNewMethod && c->multiGen) {
		    dgfile.addProperty("multi-gen", c->multiGenTimes);
		    dgfile.addProperty("keep max Y in multi-gen", c->keepMaxYInMultiGen ? On : Off);
		}
	    }
	    //==================================================================
	    // gamma
	    //==================================================================
	    dgfile.addProperty("gamma",
			       c->originalGamma ? "Original Gamma" : _toString(c->gamma).c_str());
	    if (-1 != c->dimGamma) {
		dgfile.addProperty("dim gamma", _toString(c->dimGamma));
		dgfile.addProperty("dim gamma end", _toString(c->dimGammaEnd));
	    }
	    dgfile.addProperty("gamma curve", c->useGammaCurve ? On : Off);
	    if (true == c->absoluteGamma) {
		dgfile.addProperty("absolute gamma", c->absoluteGamma ? On : Off);
		dgfile.addProperty("keep absolute gamma start", _toString(c->absoluteGammaStart));
		dgfile.addProperty("keep absolute gamma as",
				   _toString(c->absGammaStartGLAboveGamma));
	    }
	    //dgfile.addProperty("highlight gamma fix", c->highlightGammaFix ? On : Off);
	    //==================================================================

	    //==================================================================
	    // others 2
	    //==================================================================
	    if (isCCTMode) {
		dgfile.addProperty("g bypass", c->gByPass ? On : Off);
		dgfile.addProperty("b gain", c->bIntensityGain);
		dgfile.addProperty("b max",
				   c->bMax ? "B Max" : (c->bMax2 ? "B Max Smooth" : "Off"));
		if (c->bMax2) {
		    dgfile.addProperty("b max begin", c->bMax2Begin);
		    dgfile.addProperty("b max strength", c->bMax2Gamma);
		}
	    }
	    dgfile.addProperty("avoid FRC noise", c->avoidFRCNoise ? On : Off);
	    if (c->remapped) {
		dgfile.addProperty("panel regulator remapping", On);
	    }
	    bptr < MeterMeasurement > mm = c->getMeterMeasurement();
	    if (null != mm) {
		int waitTimes = mm->WaitTimes;
		dgfile.addProperty("wait times", waitTimes);
		int averageTimes = mm->AverageTimes;
		dgfile.addProperty("average times", averageTimes);

	    }
	    //==================================================================

	    //==================================================================
	    // KeepMaxLuminance
	    //==================================================================
	    string keepstr;
	    switch (c->keepMaxLuminance) {
	    case KeepMaxLuminance::TargetLuminance:
		keepstr = "Target Luminance(Align Luminance Only)";
		break;
	    case KeepMaxLuminance::TargetWhite:{
		    keepstr = "Target White";
		    string smoothIntensity = c->smoothIntensity ? On : Off;
		    dgfile.addProperty("Smooth Intensity", smoothIntensity);
		}
		break;
	    case KeepMaxLuminance::NativeWhite:
		keepstr = "Native White";
		break;
	    case KeepMaxLuminance::Smooth2NativeWhite:
		keepstr = "Native White(CCT Smoothing)";
		break;
	    case KeepMaxLuminance::None:
		keepstr = "None process";
		break;
	    }
	    dgfile.addProperty("keep max luminance", keepstr);
	    if (c->keepMaxLuminance == KeepMaxLuminance::Smooth2NativeWhite) {
		if (true == c->autoKeepMaxLumiParameter) {
		    dgfile.addProperty("auto keep max lumi adv parameter", On);
		}
		dgfile.addProperty("keep max lumi adv over", c->keepMaxLumiOver);
	    }


	    if (None == c->DeHookMode) {
		dgfile.addProperty("dehook mode", "None");
	    } else {
		string dehookmode;
		switch (c->DeHookMode) {
		case KeepCCT:
		    dehookmode = "Keep CCT";
		    break;
		case SecondWithBGap1st:
		    dehookmode = "DeHook2 With BGap first";
		    break;
		case SecondWithGamma1st:
		    dehookmode = "DeHook2 With Gamma first";
		    break;
		}

		dgfile.addProperty("dehook mode", dehookmode);
		dgfile.addProperty("max B intensity RGL", c->maxBRawGrayLevel);
		if (SecondWithBGap1st == c->DeHookMode) {
		    dgfile.addProperty("max B at DG GL", c->maxBDGGrayLevel);
		    dgfile.addProperty("best gamma at max B DG GL",
				       c->bestGammaAtGammaBoundGrayLevel);
		    dgfile.addProperty("alter gamma curve@DeHook2",
				       c->alterGammaCurveAtDeHook2 ? On : Off);
		}
	    }

	    if (c->keepMaxLuminance == KeepMaxLuminance::Smooth2NativeWhite) {
		if (true == c->autoKeepMaxLumiParameter) {
		    dgfile.addProperty("auto keep max lumi adv parameter", On);
		}
		dgfile.addProperty("keep max lumi adv over", c->keepMaxLumiOver);
	    }
	    if (true == c->autoIntensity) {
		RGB_ptr idealIntensity = c->idealIntensity;
		if (null != idealIntensity) {
		    dgfile.addProperty("target intensity", *idealIntensity->toString());
		}
	    }
	    //==================================================================

	    //==================================================================
	    // analyzer
	    //==================================================================
	    if (null != c->fetcher->FirstAnalyzer) {
		storeAnalyzer(dgfile, c->fetcher->FirstAnalyzer, Target);
	    }
	    if (null != c->secondWhiteAnalyzer) {
		storeAnalyzer(dgfile, c->secondWhiteAnalyzer, Second);
	    }
	    //==================================================================
	};

	void DGLutProperty::storeFeedbackInfo(ExcelAccessBase & dgfile) const {
	    if (DimCorrect::DefinedDim == c->correct && true == c->feedbackFix) {
		dgfile.addProperty("defined dim - feedback fix", On);
		if (null != c->maxMeasureError) {
		    dgfile.addProperty
			("defined dim - feedback fix init defect", c->initDefectCount);
		    dgfile.addProperty("defined dim - feedback fix count", c->feedbackFixCount);
		    dgfile.addProperty("max measure dx", c->maxMeasureError[0]);
		    dgfile.addProperty("max measure dy", c->maxMeasureError[1]);
		}

	    }

	};
	void DGLutProperty::storeAnalyzer(ExcelAccessBase & dgfile,
					  bptr <
					  cms::measure::
					  IntensityAnalyzerIF > analyzer, const string & prestring)
	    const {
	    //紀錄ref color
	    xyY_ptr refWhitexyY = analyzer->getReferenceColor();
	    if (null != refWhitexyY) {
		string_ptr comment = analyzer->getReferenceColorComment();
		if (null != comment) {
		    dgfile.addProperty("reference white comment", *comment);
		}

		xyY_ptr refRxyY = analyzer->getPrimaryColor(Channel::R);
		xyY_ptr refGxyY = analyzer->getPrimaryColor(Channel::G);
		xyY_ptr refBxyY = analyzer->getPrimaryColor(Channel::B);
		dgfile.addProperty(prestring + " reference white", *refWhitexyY->toString());
		dgfile.addProperty(prestring + " primary R", *refRxyY->toString());
		dgfile.addProperty(prestring + " primary G", *refGxyY->toString());
		dgfile.addProperty(prestring + " primary B", *refBxyY->toString());
	    }
	    //紀錄target white用的rgb
	    RGB_ptr refRGB = analyzer->getReferenceRGB();
	    if (null != refRGB) {
		dgfile.addProperty(prestring + " reference white RGB", *refRGB->toString());

		bptr < BitDepthProcessor > bitDepth = c->bitDepth;
		const Dep::MaxValue & lutBit = bitDepth->getLutMaxValue();
		RGB_ptr lutRefRGB = refRGB->clone();
		lutRefRGB->changeMaxValue(lutBit);
		dgfile.addProperty(prestring +
				   " reference white RGB(LUT Bit)", *lutRefRGB->toString());
	    }

	    MaxMatrixIntensityAnalyzer *ma =
		dynamic_cast < MaxMatrixIntensityAnalyzer * >(analyzer.get());
	    if (null != ma && null != ma->getWhiteRatio()) {
		double2D_ptr ratio = ma->getWhiteRatio();
		string title = prestring + " " + WhiteRatio;
		dgfile.addProperty(title, *DoubleArray::toString(ratio));
	    }

	};
	void DGLutProperty::addProperty(const std::string key, string_ptr value) {
	    propertyMap.insert(make_pair(key, value));
	};
	void DGLutProperty::addProperty(const std::string key, const std::string value) {
	    propertyMap.insert(make_pair(key, string_ptr(new string(value))));
	};

	bool DGLutProperty::initProperty(bptr < DGLutFile > d) {
	    bptr < DBQuery > query = d->retrieve(DGLutFile::Properties);
	    if (query != null) {
		while (query->hasNext()) {
		    string_vector_ptr result = query->nextResult();
		    addProperty((*result)[0], (*result)[1]);
		}
		return true;
	    } else {
		return false;
	    }
	};
	bool DGLutProperty::initProperty(DGLutFile * d) {
	    bptr < DBQuery > query = d->retrieve(DGLutFile::Properties);
	    if (query != null) {
		while (query->hasNext()) {
		    string_vector_ptr result = query->nextResult();
		    addProperty((*result)[0], (*result)[1]);
		}
		return true;
	    } else {
		return false;
	    }
	};
      DGLutProperty::DGLutProperty(cms::lcd::calibrate::LCDCalibrator * c):c(c),
	    d(bptr < DGLutFile >
	      ((DGLutFile *) null)) {

	};
      DGLutProperty::DGLutProperty(bptr < DGLutFile > d):c((LCDCalibrator *) null), d(d) {
	    if (false == initProperty(d)) {
		throw IllegalStateException(" init Property failed.");
	    }
	};
      DGLutProperty::DGLutProperty(DGLutFile * d):c((LCDCalibrator *) null) {
	    if (false == initProperty(d)) {
		throw IllegalStateException(" init Property failed.");
	    }
	};
	string_ptr DGLutProperty::getProperty(const std::string key) {
	    return propertyMap[key];
	};
	xyY_ptr DGLutProperty::getReferenceColor(const string & prestring, const Channel & ch) {
	    string_ptr value;
	    switch (ch.chindex) {
	    case ChannelIndex::R:
		value = getProperty(prestring + " primary R");
		if (null == value && Target == prestring) {
		    value = getProperty("primary R");
		}
		break;
	    case ChannelIndex::G:
		value = getProperty(prestring + " primary G");
		if (null == value && Target == prestring) {
		    value = getProperty("primary G");
		}
		break;
	    case ChannelIndex::B:
		value = getProperty(prestring + " primary B");
		if (null == value && Target == prestring) {
		    value = getProperty("primary B");
		}
		break;
	    case ChannelIndex::W:
		value = getProperty(prestring + " reference white");
		if (null == value && Target == prestring) {
		    value = getProperty("reference white");
		}
		break;
	    default:
		throw IllegalArgumentException("Unsupported Channel : " + *ch.toString());
	    }
	    if (null != value) {
		xyY_ptr xyY(new CIExyY(ColorSpace::getValuesFromString(value)));
		return xyY;
	    } else {
		return xyY_ptr((CIExyY *) null);
	    }
	};
	xyY_ptr DGLutProperty::getTargetReferenceColor(const Dep::Channel & ch) {
	    return getReferenceColor(Target, ch);
	};
	xyY_ptr DGLutProperty::getNativeReferenceColor(const Dep::Channel & ch) {
	    return getReferenceColor(Native, ch);
	};
	xyY_ptr DGLutProperty::getSecondReferenceColor(const Dep::Channel & ch) {
	    return getReferenceColor(Second, ch);
	};
	RGB_ptr DGLutProperty::getReferenceRGB(const string & prestring) {
	    string_ptr value = getProperty(prestring + " reference white RGB");
	    double_array rgbValues = ColorSpace::getValuesFromString(value);
	    RGB_ptr rgb(new RGBColor(rgbValues[0], rgbValues[1], rgbValues[2]));
	    return rgb;
	};
	RGB_ptr DGLutProperty::getTargetReferenceRGB() {
	    return getReferenceRGB(Target);
	};
	RGB_ptr DGLutProperty::getNativeReferenceRGB() {
	    return getReferenceRGB(Native);
	};
	RGB_ptr DGLutProperty::getSecondReferenceRGB() {
	    return getReferenceRGB(Second);
	};
	bptr < BitDepthProcessor > DGLutProperty::getBitDepthProcessor() {
	    const MaxValue & in = MaxValue::valueOf(getProperty("in"));
	    const MaxValue & lut = MaxValue::valueOf(getProperty("lut"));
	    const MaxValue & out = MaxValue::valueOf(getProperty("out"));
	    bptr < BitDepthProcessor > bitDepth(new BitDepthProcessor(in.bit, lut.bit, out.bit));
	    return bitDepth;
	}
	double_array DGLutProperty::getTargetWhiteRatio() {
	    string title = Target + " " + WhiteRatio;
	    string_ptr value = getProperty(title);
	    if (null == value) {
		//*為了相容舊的儲存方式
		//原先是存 TargetWhiteRatio, 但是當有兩個analyzer的時候會搞混
		//所以改成 target WhiteRatio跟native WhiteRatio
		//如果新版的找不到, 就會回去找舊版的TargetWhiteRatio關鍵字
		value = getProperty(TargetWhiteRatio);
	    }
	    double_array targetWhiteRatio = DoubleArray::fromString(*value);
	    return targetWhiteRatio;
	};
	/*double_array DGLutProperty::getTargetWhiteRatio(const string & prestring) {
	   string title = prestring + " " + TargetWhiteRatio;
	   string_ptr value = getProperty(title);
	   double_array targetWhiteRatio = DoubleArray::fromString(*value);
	   return targetWhiteRatio;
	   }; */
	//======================================================================
    };
};

