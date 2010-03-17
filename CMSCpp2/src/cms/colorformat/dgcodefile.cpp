#include <includeall.h>
#pragma hdrstop
#include "dgcodefile.h"
//C系統文件

//C++系統文件                  
#include <iostream>

//其他庫頭文件

//本項目內頭文件

//不做初使化(其實沒有初始化的必要了)
#define LAZY_EXCEL false
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

	//======================================================================
	// DGLutFile
	//======================================================================
	const std::string DGLutFile::GammaHeader[4] =
	    { "Gray Level", "Gamma R", "Gamma G", "Gamma B" };
	const std::string DGLutFile::RawHeader[13] =
	    { "Gray Level", "W_x", "W_y", "W_Y (nit)", "W_R", "W_G", "W_B",
	    "RP", "GP", "BP", "RP_Intensity_Fix", "GP_Intensity_Fix",
	    "BP_Intensity_Fix"
	};
	const std::string DGLutFile::PropertiesHeader[2] =
	    { "Key", "Value" };
	const string & DGLutFile::GammaTable = "Gamma_Table";
	const string & DGLutFile::RawData = "Raw_Data";
	const string & DGLutFile::Properties = "Properties";

	string_vector_ptr DGLutFile::getFieldNames(const string *
						   fieldNames, int n) {
	    string_vector_ptr result(new string_vector(n));
	    for (int x = 0; x < n; x++) {
		(*result)[x] = fieldNames[x];
	    } return result;
	};

	void DGLutFile::initDefaultData(string_vector_ptr fieldNames,
					const string & tableName, int n,
					bool reverse) {
	    db->createTable(tableName, fieldNames);
	    if (!lazyMode) {
		int start = !reverse ? 0 : n - 1;
		int end = !reverse ? n : -1;
		int step = !reverse ? 1 : -1;

		for (int x = start; x != end; x += step) {
		    string_vector_ptr value =
			ExcelFileDB::makes(1, lexical_cast < string > (x));
		    string_vector_ptr fieldName =
			ExcelFileDB::makes(1, (*fieldNames)[0]);

		    db->insert(fieldName, value);
		}
#ifdef CACHE_SQL
		db->excuteCache();
#endif

	    }
	};

	void DGLutFile::initDefaultData(string_vector_ptr fieldNames,
					const std::string & tableName,
					int_vector_ptr nvector,
					bool reverse) {
	    db->createTable(tableName, fieldNames);
	    if (!lazyMode) {
		int size = nvector->size();

		int start = !reverse ? 0 : size - 1;
		int end = !reverse ? size : -1;
		int step = !reverse ? 1 : -1;


		for (int x = start; x != end; x += step) {
		    int n = (*nvector)[x];
		    string_vector_ptr value
			=
			ExcelFileDB::makes(1, lexical_cast < string > (n));
		    string_vector_ptr fieldName =
			ExcelFileDB::makes(1, (*fieldNames)[0]);
		    db->insert(fieldName, value);
		}
#ifdef CACHE_SQL
		db->excuteCache();
#endif
	    }
	};
	void
	 DGLutFile::init() {
	    if (null == GammaFieldNames) {
		GammaFieldNames = getFieldNames(GammaHeader, 4);
	    }
	    if (null == RawFieldNames) {
		RawFieldNames = getFieldNames(RawHeader, 13);
	    }
	    if (null == PropertiesFieldNames) {
		PropertiesFieldNames = getFieldNames(PropertiesHeader, 2);
	    }
	    if (Create == mode) {
		if (FileExists(filename.c_str())) {
		    throw IllegalStateException("File " + filename +
						" exists.");
		}

		db.reset(new ExcelFileDB(filename, Create));
#ifdef CACHE_SQL
		db->setCacheMode(true);
#endif
		//若為lazy mode 等到set時期再init field name
		if (n != -1) {
		    initDefaultData(GammaFieldNames, GammaTable, n, false);
		    initDefaultData(RawFieldNames, RawData, n, true);
		} else {
		    initDefaultData(GammaFieldNames, GammaTable,
				    nvector, false);
		    initDefaultData(RawFieldNames, RawData, nvector, true);
		};
		//==============================================================
		// property不用管lazy mode
		//==============================================================
		string_vector_ptr fieldType(new string_vector(2));
		(*fieldType)[0] = "Text";
		(*fieldType)[1] = "Text";
		db->createTable(Properties, PropertiesFieldNames,
				fieldType);
		//==============================================================
	    } else {
		db.reset(new ExcelFileDB(filename, mode));
	    }
	};
	DGLutFile::DGLutFile(const string & filename, int
			     n):filename(filename), n(n), mode(Create),
	    lazyMode(LAZY_EXCEL) {
	    init();
	};

	DGLutFile::DGLutFile(const std::string & filename,
			     int_vector_ptr nvector):filename(filename),
	    nvector(nvector), n(-1), mode(Create), lazyMode(LAZY_EXCEL) {
	    init();
	};

	DGLutFile::
	    DGLutFile(const std::string & filename):filename(filename),
	    n(-1), mode(ReadOnly), lazyMode(LAZY_EXCEL) {
	    init();
	};
	void
	 DGLutFile::addProperty(const
				string & key, const
				string & value) {
	    db->setTableName(Properties);
	    string_vector_ptr values(new string_vector(2));
	    (*values)
		[0] = key;
	    (*values)
		[1] = value;
	    db->setCacheMode(false);
	    db->insert(PropertiesFieldNames, values, true);
#ifdef CACHE_SQL
	    db->setCacheMode(true);
#endif
	};
	void
	 DGLutFile::addProperty(const
				std::string & key, const
				double
				value) {
	    addProperty(key, lexical_cast < string > (value));
	};
	/*void
	   DGLutFile::setRawData(Component_vector_ptr componentVector) {
	   setRawData(componentVector, nil_RGBGamma, nil_RGBGamma);
	   };

	   void
	   DGLutFile::
	   setRawData
	   (Component_vector_ptr componentVector, RGBGamma_ptr rgbgamma) {
	   setRawData(componentVector, rgbgamma, nil_RGBGamma);
	   }; */

	void DGLutFile::setRawData(Component_vector_ptr componentVector,
				   RGBGamma_ptr initialRGBGamma,
				   RGBGamma_ptr finalRGBGamma) {
	    //==================================================================
	    // 檢查來源資料
	    //==================================================================
	    if (null != initialRGBGamma
		&& componentVector->size() != initialRGBGamma->r->size()) {
		throw
		    IllegalArgumentException
		    ("componentVector->size() != initialRGBGamma->r->size()");
	    };
	    if (null != finalRGBGamma
		&& componentVector->size() != finalRGBGamma->r->size()) {
		throw
		    IllegalArgumentException
		    ("componentVector->size() != finalRGBGamma->r->size()");
	    };
	    //==================================================================
	    //==================================================================
	    // 初始資料設定
	    //==================================================================
	    db->setTableName(RawData);
	    int
	     size = componentVector->size();
	    string_vector_ptr values(new string_vector(13));
	    //==================================================================
	    //==================================================================
	    // 迴圈處理
	    //==================================================================
	    for (int x = 0; x != size; x++) {
		int n = size - 1 - x;
		Component_ptr c = (*componentVector)
		    [x];
		int w = static_cast < int
		    >(c->rgb->getValue(Channel::W));
		(*values)
		    [0] = lexical_cast < string > (w);
		xyY_ptr xyY(new CIExyY(c->XYZ));
		(*values)
		    [1] = lexical_cast < string > (xyY->x);
		(*values)
		    [2] = lexical_cast < string > (xyY->y);
		(*values)
		    [3] = lexical_cast < string > (xyY->Y);
		RGB_ptr intensity = c->intensity;
		(*values)
		    [4] = lexical_cast < string > (intensity->R);
		(*values)
		    [5] = lexical_cast < string > (intensity->G);
		(*values)
		    [6] = lexical_cast < string > (intensity->B);

		//gamma 0~100
		if (null != initialRGBGamma) {
		    (*values)[7] = _toString((*initialRGBGamma->r)[n]);
		    (*values)[8] = _toString((*initialRGBGamma->g)[n]);
		    (*values)[9] = _toString((*initialRGBGamma->b)[n]);
		} else {
		    (*values)[7] = "0";
		    (*values)[8] = "0";
		    (*values)[9] = "0";
		}

		if (null != finalRGBGamma) {
		    (*values)[10] = _toString((*finalRGBGamma->r)[n]);
		    (*values)[11] = _toString((*finalRGBGamma->g)[n]);
		    (*values)[12] = _toString((*finalRGBGamma->b)[n]);
		} else {
		    (*values)[10] = "0";
		    (*values)[11] = "0";
		    (*values)[12] = "0";
		}

		if (!lazyMode) {
		    db->update(RawHeader[0], w, RawFieldNames, values,
			       false);
		} else {
		    db->insert(RawFieldNames, values, false);
		}
	    }
#ifdef CACHE_SQL
	    db->excuteCache();
#endif
	    //==================================================================
	};

	void
	 DGLutFile::setGammaTable(RGB_vector_ptr dglut) {
	    //==================================================================
	    // 檢查來源資料
	    //==================================================================
	    /*if (compositionVector->size() != rgbgamma->r->size()) {
	       throw
	       IllegalArgumentException
	       ("compositionVector->size() != rgbgamma->r->size()");
	       }; */
	    //==================================================================

	    //==================================================================
	    // 初始資料設定
	    //==================================================================
	    db->setTableName(GammaTable);
	    int
	     size = dglut->size();
	    string_vector_ptr values(new string_vector(4));
	    //==================================================================
	    //==================================================================
	    // 迴圈處理
	    //==================================================================
	    for (int x = 0; x != size; x++) {
		//int n = size - 1 - x;
		//Composition_ptr c = (*compositionVector)[x];

		RGB_ptr rgb = (*dglut)[x];
		//int w = static_cast < int >(rgb->getValue(Channel::W));
		(*values)[0] = lexical_cast < string > (x);
		(*values)
		    [1] = lexical_cast < string > (rgb->R);
		(*values)
		    [2] = lexical_cast < string > (rgb->G);
		(*values)
		    [3] = lexical_cast < string > (rgb->B);
		if (!lazyMode) {
		    db->update(GammaHeader
			       [0], x, GammaFieldNames, values, false);
		} else {
		    db->insert(GammaFieldNames, values, false);
		}
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
		int
		 gray = lexical_cast < int >((*result)[0]);
		double x = lexical_cast < double >((*result)[1]);
		double y = lexical_cast < double >((*result)[2]);
		double Y = lexical_cast < double >((*result)[3]);
		double R = lexical_cast < double >((*result)[4]);
		double G = lexical_cast < double >((*result)[5]);
		double B = lexical_cast < double >((*result)[6]);
		double r = lexical_cast < double >((*result)[7]);
		double g = lexical_cast < double >((*result)[8]);
		double b = lexical_cast < double >((*result)[9]);
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
	string_vector_ptr DGLutFile::makeValues(int n, Component_ptr c) {
	    return
		makeValues(n, c,
			   RGB_ptr((RGBColor *) null),
			   RGB_ptr((RGBColor *) null));
	};
	string_vector_ptr DGLutFile::
	    makeValues(int n, Component_ptr c, RGB_ptr rgbGamma,
		       RGB_ptr rgbGammaFix) {
	    string_vector_ptr values(new string_vector(13));
	    (*values)
		[0] = lexical_cast < string > (n);
	    xyY_ptr xyY(new CIExyY(c->XYZ));
	    (*values)
		[1] = lexical_cast < string > (xyY->x);
	    (*values)
		[2] = lexical_cast < string > (xyY->y);
	    (*values)
		[3] = lexical_cast < string > (xyY->Y);
	    RGB_ptr intensity = c->intensity;
	    (*values)
		[4] = lexical_cast < string > (intensity->R);
	    (*values)
		[5] = lexical_cast < string > (intensity->G);
	    (*values)
		[6] = lexical_cast < string > (intensity->B);
	    //gamma 0~100
	    if (null != rgbGamma) {
		(*values)[7] = lexical_cast < string > (rgbGamma->R);
		(*values)[8] = lexical_cast < string > (rgbGamma->G);
		(*values)[9] = lexical_cast < string > (rgbGamma->B);
	    }

	    if (null != rgbGammaFix) {
		(*values)[10] = lexical_cast < string > (rgbGammaFix->R);
		(*values)[11] = lexical_cast < string > (rgbGammaFix->G);
		(*values)[12] = lexical_cast < string > (rgbGammaFix->B);
	    }
	    return values;
	};
	string_vector_ptr DGLutFile::GammaFieldNames;
	string_vector_ptr DGLutFile::RawFieldNames;
	string_vector_ptr DGLutFile::PropertiesFieldNames;
	void
	 DGLutFile::setProperty(const
				DGLutProperty & property) {
	    property.store(*this);
	};
	//======================================================================
	//======================================================================
	// DGLutProperty
	//======================================================================
	const
	string DGLutProperty::Start = "start";
	const
	string DGLutProperty::End = "end";
	const
	string DGLutProperty::Step = "step";
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
	const string DGLutProperty::On = "On";
	const string DGLutProperty::Off = "Off";
	void
	 DGLutProperty::store(DGLutFile & dgcode) const {
	    dgcode.addProperty(Start, c.start);
	    dgcode.addProperty(End, c.end);
	    dgcode.addProperty(Step, c.step);
	    dgcode.addProperty(DimCorrect,
			       (c.correct == 1) ? "P1P2" :
			       (c.correct == 2) ?
			       "RBInterpolation" : "None");
	    dgcode.addProperty(P1, c.p1);
	    dgcode.addProperty(P2, c.p2);
	    dgcode.addProperty(RBUnder, c.rbInterpUnder);
	    dgcode.addProperty(In, *c.in.toString());
	    dgcode.addProperty(LUT, *c.lut.toString());
	    dgcode.addProperty(Out, *c.out.toString());
	    dgcode.addProperty(Gamma, c.gamma);
	    dgcode.addProperty(GByPass, c.gByPass ? On : Off);
	    dgcode.addProperty(BGain, c.bIntensityGain);
	    dgcode.addProperty(BMax, c.bMax ? On : Off);
	    dgcode.addProperty(Gamma256, c.gamma256 ? On : Off);
	    dgcode.addProperty(FRC_NR, c.avoidFRCNoise ? On : Off);
	};
	DGLutProperty::DGLutProperty(const
				     LCDCalibrator & c):c(c) {
	};
	//======================================================================
    };
};

