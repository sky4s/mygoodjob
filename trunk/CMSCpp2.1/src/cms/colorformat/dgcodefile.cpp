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



	//======================================================================
	// DGLutFile
	//======================================================================
	string_vector_ptr DGLutFile::makeValues(int n, Component_ptr c) {
	    return
		makeValues(n, c, RGB_ptr((RGBColor *) null),
			   RGB_ptr((RGBColor *) null));
	};
	string_vector_ptr DGLutFile::
	    makeValues(int n, Component_ptr c, RGB_ptr rgbGamma,
		       RGB_ptr rgbGammaFix) {
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
			mode)
	{
	    initSheet(GammaTable, 4, "Gray Level", "Gamma R", "Gamma G",
		      "Gamma B");
	    initSheet(RawData, 13, "Gray Level", "W_x", "W_y",
		      "W_Y (nit)", "W_R", "W_G", "W_B", "RP", "GP", "BP",
		      "RP_Intensity_Fix", "GP_Intensity_Fix",
		      "BP_Intensity_Fix");
	    initPropertySheet();
	};

	const string & DGLutFile::GammaTable = "Gamma_Table";
	const string & DGLutFile::RawData = "Raw_Data";

	void DGLutFile::setRawData(Component_vector_ptr componentVector,
				   RGBGamma_ptr initialRGBGamma,
				   RGBGamma_ptr finalRGBGamma) {
	    //==================================================================
	    // 檢查來源資料
	    //==================================================================
	    int componentSize = componentVector->size();
	    if (null != initialRGBGamma && null != finalRGBGamma
		&& initialRGBGamma->r->size() !=
		finalRGBGamma->r->size()) {
		throw
		    IllegalArgumentException
		    ("initialRGBGamma->size() != finalRGBGamma->size()");
	    };

	    //==================================================================
	    //==================================================================
	    // 初始資料設定
	    //==================================================================
	    int part1Size = componentVector->size();
	    int part2Size =
		null !=
		initialRGBGamma ? initialRGBGamma->r->size() : part1Size;
	    //db->setTableName(RawData);
	    int size = componentVector->size();
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

		/*if (!lazyMode) {
		   db->update((*headerNames)[0], w, headerNames, values,
		   false);
		   } else { */
		//db->insert(headerNames, values, false);
		this->insertData(RawData, values, false);
		//}
	    }

	    for (int x = part1Size; x != part2Size; x++) {
		int n = part2Size - 1 - x;
		StringVector::setContent(values, "0", 7, 0, 1, 2, 3, 4, 5,
					 6);

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

		/*if (!lazyMode) {
		   db->update((*headerNames)[0], 0, headerNames, values,
		   false);
		   } else { */
		//db->insert(headerNames, values, false);
		this->insertData(RawData, values, false);
		//}
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
		/*if (!lazyMode) {
		   db->update((*headerNames)[0], x, headerNames, values,
		   false);
		   } else { */
		//db->insert(headerNames, values, false);
		this->insertData(GammaTable, values, false);
		//}
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
		bptr < Component >
		    component(new Component(rgb, intensity, XYZ, gamma));
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
	//======================================================================

	//======================================================================
	// DGLutProperty
	//======================================================================
	/*const
	   string DGLutProperty::Start = "start";
	   const
	   string DGLutProperty::End = "end";
	   const
	   string DGLutProperty::Step = "step";
	   const
	   string DGLutProperty::HighStart = "high level start";
	   const
	   string DGLutProperty::HighEnd = "high level end";
	   const
	   string DGLutProperty::HighStep = "high level step";
	   const
	   string DGLutProperty::LowStart = "low level start";
	   const
	   string DGLutProperty::LowEnd = "low level end";
	   const
	   string DGLutProperty::LowStep = "low level step";
	   const
	   string DGLutProperty::P1P2 = "p1p2";
	   const
	   string DGLutProperty::P1 = "p1";
	   const
	   string DGLutProperty::P2 = "p2";
	   const
	   string DGLutProperty::RB = "rb interpolation";
	   const
	   string DGLutProperty::RBUnder = "rb under";
	   const
	   string DGLutProperty::In = "in";
	   const
	   string DGLutProperty::LUT = "lut";
	   const
	   string DGLutProperty::FRC = "FRC";
	   const
	   string DGLutProperty::Out = "out";
	   const
	   string DGLutProperty::Gamma = "gamma";
	   const
	   string DGLutProperty::RGamma = "r gamma";
	   const
	   string DGLutProperty::GGamma = "g gamma";
	   const
	   string DGLutProperty::BGamma = "b gamma";
	   const
	   string DGLutProperty::GammaCurve = "gamma curve";
	   const
	   string DGLutProperty::GByPass = "g bypass";
	   const
	   string DGLutProperty::BGain = "b gain";
	   const
	   string DGLutProperty::BMax = "b max";
	   const
	   string DGLutProperty::Gamma256 = "gamma 256";
	   const
	   string DGLutProperty::FRC_NR = "avoid FRC noise";
	   const
	   string DGLutProperty::DimCorrect = "low level correct";

	   const string DGLutProperty::KeepMaxLumi = "keep max luminance"; */
	const string DGLutProperty::On = "On";
	const string DGLutProperty::Off = "Off";

	void
	 DGLutProperty::store(DGLutFile & dgcode) const {

	    bptr < MeasureCondition > mc = c.measureCondition;
	    if (mc->normalCondition) {
		dgcode.addProperty("start", mc->start);
		dgcode.addProperty("end", mc->end);
		dgcode.addProperty("step", mc->step);
	    } else {
		dgcode.addProperty("high level start", mc->highStart);
		dgcode.addProperty("high level end", mc->highEnd);
		dgcode.addProperty("high level step", mc->highStep);
		dgcode.addProperty("low level start", mc->lowStart);
		dgcode.addProperty("low level end", mc->lowEnd);
		dgcode.addProperty("low level step", mc->lowStep);
	    }
	    string correctstr;
	    switch (c.correct) {
	    case cms::lcd::calibrate::P1P2:
		correctstr = "P1P2";
		break;
	    case cms::lcd::calibrate::RBInterpolation:
		correctstr = "RBInterpolation";
		break;
	    case cms::lcd::calibrate::None:
		correctstr = "None";
		break;
	    case cms::lcd::calibrate::New:
		correctstr = "new";
		break;
	    }
	    dgcode.addProperty("low level correct", correctstr);

	    dgcode.addProperty("p1", c.p1);
	    dgcode.addProperty("p2", c.p2);
	    dgcode.addProperty("rb under", c.under);
	    bptr < BitDepthProcessor > bitDepth = c.bitDepth;
	    dgcode.addProperty("in",
			       *bitDepth->getInputMaxValue().toString());
	    dgcode.addProperty("lut",
			       *bitDepth->getLutMaxValue().toString());
	    dgcode.addProperty("out",
			       *bitDepth->getOutputMaxValue().toString());

	    dgcode.addProperty("gamma", c.gamma);
	    dgcode.addProperty("gamma curve", c.useGammaCurve ? On : Off);
	    dgcode.addProperty("g bypass", c.gByPass ? On : Off);
	    dgcode.addProperty("b gain", c.bIntensityGain);
	    dgcode.addProperty("b max", c.bMax ? On : Off);

	    dgcode.addProperty("avoid FRC noise",
			       c.avoidFRCNoise ? On : Off);
	    dgcode.addProperty("keep max luminance",
			       c.keepMaxLuminance ? On : Off);
	};
	DGLutProperty::DGLutProperty(const
				     LCDCalibrator & c):c(c) {
	};
	//======================================================================
    };
};

