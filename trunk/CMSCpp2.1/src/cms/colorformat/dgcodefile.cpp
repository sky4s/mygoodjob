#include <includeall.h>
#pragma hdrstop
#include "dgcodefile.h"
//C系統文件
#include <cstdarg>
//C++系統文件                  
#include <iostream>

//其他庫頭文件

//本項目內頭文件

//不做初使化(其實沒有初始化的必要了)
//#define LAZY_EXCEL true
//將多筆sql合併成一句執行(excel似乎不能這樣玩)
//#define CACHE_SQL

namespace cms {
    namespace colorformat {
	using namespace std;
	using namespace boost;
	using namespace java::lang;
	using namespace cms::lcd::calibrate;
	using namespace Indep;
	using namespace Dep;
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
			mode) {
	    initSheet(GammaTable, 4, "Gray Level", "Gamma R", "Gamma G", "Gamma B");
	    initSheet(RawData, 13, "Gray Level", "W_x", "W_y",
		      "W_Y (nit)", "W_R", "W_G", "W_B", "RP", "GP", "BP",
		      "RP_Intensity_Fix", "GP_Intensity_Fix", "BP_Intensity_Fix");
	    initPropertySheet();
	};

	const string & DGLutFile::GammaTable = "Gamma_Table";
	const string & DGLutFile::RawData = "Raw_Data";

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
	    //db->setTableName(RawData);
	    //int size = componentVector->size();
	    //string_vector_ptr headerNames = getHeaderNames(RawData);
	    const int headerCount = getHeaderCount(RawData);
	    string_vector_ptr values(new string_vector(headerCount));
	    //==================================================================
	    //==================================================================
	    // 迴圈處理
	    //==================================================================
	    for (int x = 0; x != part1Size; x++) {
		int n = part2Size - 1 - x;
		Component_ptr c = (*componentVector)[x];
		int w = static_cast < int >(c->rgb->getValue(Channel::W));
		(*values)[0] = _toString(w);
		xyY_ptr xyY(new CIExyY(c->XYZ));
		(*values)
		    [1] = _toString(xyY->x);
		(*values)
		    [2] = _toString(xyY->y);
		(*values)
		    [3] = _toString(xyY->Y);
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
#ifdef CACHE_SQL
	    db->excuteCache();
#endif
	    //==================================================================
	};

	void
	 DGLutFile::setGammaTable(RGB_vector_ptr dglut) {
	    //==================================================================
	    // 初始資料設定
	    //==================================================================
	    //db->setTableName(GammaTable);
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
#ifdef CACHE_SQL
	    db->excuteCache();
#endif
	    //==================================================================
	};
	Component_vector_ptr DGLutFile::getComponentVector() {
	    Component_vector_ptr vector(new Component_vector());
	    db->setTableName(RawData);
	    bptr < DBQuery > query = db->selectAll();
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
		RGB_ptr rgb(new RGBColor(gray, gray, gray));
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
		int R = _toInt((*result)[1]);
		int G = _toInt((*result)[2]);
		int B = _toInt((*result)[3]);

		RGB_ptr rgb(new RGBColor(R, G, B));
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

	void
	 DGLutProperty::store(DGLutFile & dgcode) const {
	    dgcode.addProperty("Version", "3.2");

	    bptr < MeasureCondition > mc = c->measureCondition;
	    switch (mc->type) {
	    case MeasureCondition::Normal:
		dgcode.addProperty("start", mc->start);
		dgcode.addProperty("end", mc->end);
		dgcode.addProperty("step", mc->step);
		break;
		case MeasureCondition::Extend:dgcode.addProperty("high level start", mc->highStart);
		dgcode.addProperty("high level end", mc->highEnd);
		dgcode.addProperty("high level step", mc->highStep);
		dgcode.addProperty("low level start", mc->lowStart);
		dgcode.addProperty("low level end", mc->lowEnd);
		dgcode.addProperty("low level step", mc->lowStep);
		break;
		//case MeasureCondition::Plain:break;
	    }
	    //==================================================================// low level correct//==================================================================
		string correctstr;
	    switch (c->correct) {
	    case Correct::P1P2:
		correctstr = "P1P2";
		break;
	    case Correct::RBInterpolation:
		correctstr = "RBInterpolation";
		break;
	    case Correct::None:
		correctstr = "None";
		break;
	    }
	    dgcode.addProperty("low level correct", correctstr);
	    if (Correct::P1P2 == c->correct) {
		dgcode.addProperty("p1", c->p1);
		dgcode.addProperty("p2", c->p2);
	    } else if (Correct::RBInterpolation == c->correct) {
		dgcode.addProperty("rb under", c->under);
	    }
	    //==================================================================

	    dgcode.addProperty("New Method", c->newMethod ? On : Off);
	    bptr < BitDepthProcessor > bitDepth = c->bitDepth;
	    dgcode.addProperty("in", *bitDepth->getInputMaxValue().toString());
	    dgcode.addProperty("lut", *bitDepth->getLutMaxValue().toString());
	    dgcode.addProperty("out", *bitDepth->getOutputMaxValue().toString());
	    dgcode.addProperty("gamma", c->gamma);
	    dgcode.addProperty("gamma curve", c->useGammaCurve ? On : Off);
	    dgcode.addProperty("g bypass", c->gByPass ? On : Off);
	    dgcode.addProperty("b gain", c->bIntensityGain);
	    dgcode.addProperty("b max", c->bMax ? On : Off);
	    dgcode.addProperty("avoid FRC noise", c->avoidFRCNoise ? On : Off);
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
	    dgcode.addProperty("keep max luminance", keepstr);
	    if (c->keepMaxLuminance == KeepMaxLuminance::NativeWhiteAdvanced) {
		dgcode.addProperty("keep max lumi adv over", c->keepMaxLumiOver);
		dgcode.addProperty("keep max lumi adv gamma", c->keepMaxLumiGamma);
	    }
	    //==================================================================

	    //==================================================================
	    // target color
	    //==================================================================
	    bptr < IntensityAnalyzerIF > analyzer = c->fetcher->getAnalyzer();
	    if (null != analyzer) {
		//紀錄ref color
		xyY_ptr refWhitexyY = analyzer->getReferenceColor();
		if (null != refWhitexyY) {
		    xyY_ptr refRxyY = analyzer->getPrimaryColor(Channel::R);
		    xyY_ptr refGxyY = analyzer->getPrimaryColor(Channel::G);
		    xyY_ptr refBxyY = analyzer->getPrimaryColor(Channel::B);
		    dgcode.addProperty("reference white", *refWhitexyY->toString());
		    string_ptr comment = analyzer->getReferenceColorComment();
		    if (null != comment) {
			dgcode.addProperty("reference white comment", *comment);
		    }
		    dgcode.addProperty("primary R", *refRxyY->toString());
		    dgcode.addProperty("primary G", *refGxyY->toString());
		    dgcode.addProperty("primary B", *refBxyY->toString());
		}
		//紀錄target white用的rgb
		RGB_ptr refRGB = analyzer->getReferenceRGB();
		if (null != refRGB) {
		    dgcode.addProperty("reference white RGB", *refRGB->toString());
		}
	    }
	    //==================================================================
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
      DGLutProperty::DGLutProperty(bptr < DGLutFile > d):c((LCDCalibrator *) null), d(d) {
	    if (false == initProperty(d)) {
		throw IllegalStateException("init Property failed.");
	    }
	};
      DGLutProperty::DGLutProperty(DGLutFile * d):c((LCDCalibrator *) null), d2(d) {
	    if (false == initProperty(d)) {
		throw IllegalStateException("init Property failed.");
	    }
	};
	string_ptr DGLutProperty::getProperty(const std::string key) {
	    return propertyMap[key];
	};
	xyY_ptr DGLutProperty::getReferenceColor(const Channel & ch) {
	    string_ptr value;
	    switch (ch.chindex) {
	    case ChannelIndex::R:
		value = getProperty("primary R");
		break;
	    case ChannelIndex::G:
		value = getProperty("primary G");
		break;
	    case ChannelIndex::B:
		value = getProperty("primary B");
		break;
	    case ChannelIndex::W:
		value = getProperty("reference white");
		break;
	    default:
		throw IllegalArgumentException("Unsupported Channel: " + *ch.toString());
	    }
	    if (null != value) {
		xyY_ptr xyY(new CIExyY(CIExyY::getValuesFromString(value)));
		return xyY;
	    } else {
		return xyY_ptr((CIExyY *) null);
	    }
	};
	//======================================================================
    };
};

