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
	    initSheet(GammaTable, 4, "Gray Level", "Gamma R", "Gamma G", "Gamma B");
	    initSheet(RawData, 13, "Gray Level", "W_x", "W_y",
		      "W_Y (nit)", "W_R", "W_G", "W_B", "RP", "GP", "BP",
		      "RP_Intensity_Fix", "GP_Intensity_Fix", "BP_Intensity_Fix");
	    initPropertySheet();
	};

	DGLutFile::DGLutFile(const std::string & filename, Mode mode,
			     const Dep::MaxValue & maxValue):ExcelAccessBase(filename, mode),
	    maxValue(maxValue) {
	    initSheet(GammaTable, 4, "Gray Level", "Gamma R", "Gamma G", "Gamma B");
	    initSheet(RawData, 13, "Gray Level", "W_x", "W_y",
		      "W_Y (nit)", "W_R", "W_G", "W_B", "RP", "GP", "BP",
		      "RP_Intensity_Fix", "GP_Intensity_Fix", "BP_Intensity_Fix");
	    initPropertySheet();
	};

	const string & DGLutFile::GammaTable = "Gamma_Table";
	const string & DGLutFile::RawData = "Raw_Data";
	const string & DGLutFile::Target = "Target";

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
		(*values)
		    [4] = _toString(intensity->R);
		(*values)
		    [5] = _toString(intensity->G);
		(*values)
		    [6] = _toString(intensity->B);

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

		this->insertData(RawData, values, false);
	    }

	    //==================================================================
	};

	void
	 DGLutFile::setGammaTable(RGB_vector_ptr dglut) {
	    //==================================================================
	    // 初始資料設定
	    //==================================================================
	    int
	     size = dglut->size();
	    string_vector_ptr values(new string_vector(4));
	    //string_vector_ptr headerNames = getHeaderNames(GammaTable);
	    //==================================================================
	    //==================================================================
	    // 迴圈處理
	    //==================================================================
	    for (int x = 0; x != size; x++) {

		RGB_ptr rgb = (*dglut)[x];
		(*values)[0] = _toString(x);
		(*values)
		    [1] = _toString(rgb->R);
		(*values)
		    [2] = _toString(rgb->G);
		(*values)
		    [3] = _toString(rgb->B);
		this->insertData(GammaTable, values, false);
	    }

	    //==================================================================
	};
	void DGLutFile::setTargetXYZVector(XYZ_vector_ptr targetXYZVector) {
	    //==================================================================
	    // 初始資料設定
	    //==================================================================
	    initSheet(Target, 6, "Gray Level", "X", "Y (nit)", "Z", "_x", "_y");

	    int size = targetXYZVector->size();
	    const int headerCount = getHeaderCount(Target);
	    string_vector_ptr values(new string_vector(headerCount));
	    //==================================================================
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

		this->insertData(Target, values, false);
	    }
	};
	Component_vector_ptr DGLutFile::getComponentVector() {
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
		if (gammaTable->size() != 0) {
		    RGB_ptr gamma = (*gammaTable)[index++];
		    rgb = gamma;
		} else {
		    rgb = RGB_ptr(new RGBColor(gray, gray, gray));
		}

		//RGB_ptr rgb(new RGBColor(gray, gray, gray));
		RGB_ptr intensity(new RGBColor(R, G, B));
		xyY_ptr xyY(new CIExyY(x, y, Y));
		XYZ_ptr XYZ(xyY->toXYZ());
		RGB_ptr gamma(new RGBColor(r, g, b));
		bptr < Component > component(new Component(rgb, intensity, XYZ, gamma));

		vector->push_back(component);
	    };
	    return vector;
	};

	RGB_vector_ptr DGLutFile::getGammaTable() {
	    db->setTableName(GammaTable);
	    RGB_vector_ptr vector(new RGB_vector());

	    bptr < DBQuery > query = db->selectAll();
	    while (query->hasNext()) {
		string_vector_ptr result = query->nextResult();
		double R = _toDouble((*result)[1]);
		double G = _toDouble((*result)[2]);
		double B = _toDouble((*result)[3]);

		RGB_ptr rgb(new RGBColor(R, G, B, maxValue));
		vector->push_back(rgb);
	    };
	    return vector;
	};
	void
	 DGLutFile::setProperty(const
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
	//======================================================================

	//======================================================================
	// DGLutProperty
	//======================================================================
	const string DGLutProperty::On = "On";
	const string DGLutProperty::Off = "Off";
	const string DGLutProperty::Native = "native";
	const string DGLutProperty::Target = "target";
	void
	 DGLutProperty::store(DGLutFile & dgfile) const {
	    dgfile.addProperty("cct product version", "3.2");

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
		//case MeasureCondition::Plain:break;
	    };
	    //==================================================================

	    //==================================================================
	    //low level correct
	    //==================================================================
	    string lowLevelCorrect = "low level correct";
	    switch (c->correct) {
	    case Correct::P1P2:
		dgfile.addProperty(lowLevelCorrect, "P1P2");
		dgfile.addProperty("p1", c->p1);
		dgfile.addProperty("p2", c->p2);
		break;
	    case Correct::RBInterpolation:
		dgfile.addProperty(lowLevelCorrect, "RBInterpolation");
		dgfile.addProperty("rb under", c->under);
		break;
	    case Correct::None:
		dgfile.addProperty(lowLevelCorrect, "None");
		break;
	    case Correct::DefinedDim:
		dgfile.addProperty(lowLevelCorrect, "DefinedDim");
		dgfile.addProperty("defined dim under", c->under);
		dgfile.addProperty("defined dim gamma", c->dimGamma);

		XYZ_ptr blackXYZ = (*c->componentVector)[c->componentVector->size() - 1]->XYZ;
		xyY_ptr blackxyY(new CIExyY(blackXYZ));
		dgfile.addProperty("defined dim black", *blackxyY->toString());
		break;
	    }
	    //==================================================================

	    //==================================================================
	    // others
	    //==================================================================
	    dgfile.addProperty("New Method", c->useNewMethod ? On : Off);
	    if (c->useNewMethod && c->multiGen) {
		dgfile.addProperty("Multi-Gen", c->multiGenTimes);
	    }

	    bptr < BitDepthProcessor > bitDepth = c->bitDepth;
	    dgfile.addProperty("in", *bitDepth->getInputMaxValue().toString());
	    dgfile.addProperty("lut", *bitDepth->getLutMaxValue().toString());
	    dgfile.addProperty("out", *bitDepth->getOutputMaxValue().toString());
	    dgfile.addProperty("gamma",
			       c->originalGamma ? "Original Gamma" : _toString(c->gamma).c_str());
	    dgfile.addProperty("gamma curve", c->useGammaCurve ? On : Off);
	    dgfile.addProperty("g bypass", c->gByPass ? On : Off);
	    dgfile.addProperty("b gain", c->bIntensityGain);
	    dgfile.addProperty("b max", c->bMax ? "B Max" : (c->bMax2 ? "B Max Smooth" : "Off"));
	    if (c->bMax2) {
		dgfile.addProperty("b max begin", c->bMax2Begin);
		dgfile.addProperty("b max strength", c->bMax2Gamma);
	    }
	    dgfile.addProperty("avoid FRC noise", c->avoidFRCNoise ? On : Off);
	    if (c->remapped) {
		dgfile.addProperty("panel regulator remapping", On);
	    }
	    //==================================================================

	    //==================================================================
	    // KeepMaxLuminance
	    //==================================================================
	    string keepstr;
	    switch (c->keepMaxLuminance) {
	    case KeepMaxLuminance::None:
		keepstr = "None";
		break;
	    case KeepMaxLuminance::TargetWhite:
		keepstr = "Target White";
		break;
	    case KeepMaxLuminance::NativeWhite:
		keepstr = "Native White";
		break;
	    case KeepMaxLuminance::NativeWhiteAdvanced:
		keepstr = "Native White Advanced";
		break;
	    }
	    dgfile.addProperty("keep max luminance", keepstr);
	    if (c->keepMaxLuminance == KeepMaxLuminance::NativeWhiteAdvanced) {
		if (true == c->autoKeepMaxLumiParameter) {
		    dgfile.addProperty("auto keep max lumi adv parameter", On);
		}
		dgfile.addProperty("keep max lumi adv over", c->keepMaxLumiOver);
		dgfile.addProperty("keep max lumi adv gamma", c->keepMaxLumiGamma);
		dgfile.addProperty("skip inverse b", c->skipInverseB ? On : Off);
		if (true == c->skipInverseB) {
		    dgfile.addProperty("maxZ dg code", c->maxZDGCode);
		}
	    }
	    //==================================================================

	    //==================================================================
	    // analyzer
	    //==================================================================
	    bptr < IntensityAnalyzerIF > analyzer = c->fetcher->getAnalyzer();
	    if (null != analyzer) {
		storeAnalyzer(dgfile, analyzer, Target);
	    }
	    if (null != c->nativeWhiteAnalyzer) {
		storeAnalyzer(dgfile, c->nativeWhiteAnalyzer, Native);
	    }
	    //==================================================================
	};
	void DGLutProperty::storeAnalyzer(DGLutFile & dgfile,
					  bptr < cms::measure::IntensityAnalyzerIF >
					  analyzer, const string & prestring) const {
	    //紀錄ref color
	    xyY_ptr refWhitexyY = analyzer->getReferenceColor();
	    if (null != refWhitexyY) {
		xyY_ptr refRxyY = analyzer->getPrimaryColor(Channel::R);
		xyY_ptr refGxyY = analyzer->getPrimaryColor(Channel::G);
		xyY_ptr refBxyY = analyzer->getPrimaryColor(Channel::B);
		 dgfile.addProperty(prestring + " reference white", *refWhitexyY->toString());
		string_ptr comment = analyzer->getReferenceColorComment();
		if (null != comment) {
		    dgfile.addProperty("reference white comment", *comment);
		}
		dgfile.addProperty(prestring + " primary R", *refRxyY->toString());
		dgfile.addProperty(prestring + " primary G", *refGxyY->toString());
		dgfile.addProperty(prestring + " primary B", *refBxyY->toString());
	    }
	    //紀錄target white用的rgb
	    RGB_ptr refRGB = analyzer->getReferenceRGB();
	    if (null != refRGB) {
		dgfile.addProperty(prestring + " reference white RGB", *refRGB->toString());
	    }

	    MaxMatrixIntensityAnalyzer *ma =
		dynamic_cast < MaxMatrixIntensityAnalyzer * >(analyzer.get());
	    if (null != ma) {
		double2D_ptr ratio = ma->getTargetRatio();
		dgfile.addProperty("Target Ratio", *DoubleArray::toString(ratio));
		//ShowMessage("Set \"Target White \"first.");
	    }

	};
	void DGLutProperty::addProperty(const std::string key, string_ptr value) {
	    propertyMap.insert(make_pair(key, value));
	};
	void DGLutProperty::addProperty(const std::string key, const std::string value) {
	    propertyMap.insert(make_pair(key, string_ptr(new string(value))));
	};
      DGLutProperty::DGLutProperty(cms::lcd::calibrate::LCDCalibrator * c):c(c),
	    d(bptr < DGLutFile >
	      ((DGLutFile *) null)) {

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
	//=====================================================================
	// 擷取app的檔案資訊, 很難寫, 所以尚未完成, 還不能用   
	//=====================================================================
	void DGLutProperty::fetchVersionInfo() {
	    const AnsiString InfoStr[10] = {
		"CompanyName", "FileDescription", "FileVersion", "InternalName", "LegalCopyright",
		"LegalTradeMarks", "OriginalFileName", "ProductName", "ProductVersion",
		"Comments"
	    };
	    char *ExeName = Application->ExeName.c_str();
	    DWORD n = GetFileVersionInfoSize(ExeName, null);

	    if (n > 0) {
		char *pBuf = (char *) malloc(n);
		AnsiString temp = "VersionInfoSize = ";

		GetFileVersionInfo(ExeName, 0, n, pBuf);
		for (int i = 0; i < 10; i++) {
		    char *pValue;
		    DWORD Len;
		    temp = "StringFileInfo\\040904E4\\";
		    temp = temp + InfoStr[i];
		    /*if (VerQueryValue(pBuf, temp.c_str(), pValue, &Len)) {

		       } */
		}
		free(pBuf);
	    }
	};
	//=====================================================================
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

	bptr < BitDepthProcessor > DGLutProperty::getBitDepthProcessor() {
	    const MaxValue & in = MaxValue::valueOf(getProperty("in"));
	    const MaxValue & lut = MaxValue::valueOf(getProperty("lut"));
	    const MaxValue & out = MaxValue::valueOf(getProperty("out"));
	    bptr < BitDepthProcessor >
		bitDepth(new BitDepthProcessor(in.bit, lut.bit, out.bit, false));
	    return bitDepth;
	}
	//======================================================================
    };
};

