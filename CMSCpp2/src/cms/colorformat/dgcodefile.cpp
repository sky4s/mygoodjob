#include <includeall.h>
#pragma hdrstop
#include "dgcodefile.h"
//C系統文件

//C++系統文件
#include <iostream>

//其他庫頭文件

//本項目內頭文件

#define LAZY_EXCEL true

namespace cms {
    namespace colorformat {
	using namespace std;
	using namespace boost;
	using namespace java::lang;
	using namespace cms::lcd::calibrate;
	using namespace Indep;
	using namespace Dep;

	//======================================================================
	// DGCodeFile
	//======================================================================
	const std::string DGCodeFile::GammaHeader[4] =
	    { "Gray Level", "Gamma R", "Gamma G", "Gamma B" };
	const std::string DGCodeFile::RawHeader[13] =
	    { "Gray Level", "W_x", "W_y", "W_Y (nit)", "W_R", "W_G", "W_B",
	    "RP", "GP", "BP", "RP_Intensity_Fix", "GP_Intensity_Fix",
	    "BP_Intensity_Fix"
	};
	const std::string DGCodeFile::PropertiesHeader[2] =
	    { "Key", "Value" };
	//const string & DGCodeFile::GammaTable = "Gamma Table";
	//const string & DGCodeFile::RawData = "Raw Data";
	const string & DGCodeFile::GammaTable = "Gamma_Table";
	const string & DGCodeFile::RawData = "Raw_Data";
	const string & DGCodeFile::Properties = "Properties";

	string_vector_ptr DGCodeFile::getFieldNames(const string *
						    fieldNames, int n) {
	    string_vector_ptr result(new string_vector(n));
	    for (int x = 0; x < n; x++) {
		(*result)[x] = fieldNames[x];
	    } return result;
	};

	void DGCodeFile::initDefaultData(string_vector_ptr fieldNames,
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
	    }
	};

	void DGCodeFile::initDefaultData(string_vector_ptr fieldNames,
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
	    }
	};
	void
	 DGCodeFile::init() {
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
	DGCodeFile::DGCodeFile(const string & filename, int
			       n):filename(filename), n(n), mode(Create),
	    lazyMode(LAZY_EXCEL) {
	    init();
	};

	DGCodeFile::DGCodeFile(const std::string & filename,
			       int_vector_ptr nvector):filename(filename),
	    nvector(nvector), n(-1), mode(Create), lazyMode(LAZY_EXCEL) {
	    init();
	};

	DGCodeFile::
	    DGCodeFile(const std::string & filename):filename(filename),
	    n(-1), mode(ReadOnly), lazyMode(LAZY_EXCEL) {
	    init();
	};
	void
	 DGCodeFile::addProperty(const
				 string & key, const
				 string & value) {
	    db->setTableName(Properties);
	    string_vector_ptr values(new string_vector(2));
	    (*values)
		[0] = key;
	    (*values)
		[1] = value;
	    db->insert(PropertiesFieldNames, values, true);
	};
	void
	 DGCodeFile::addProperty(const
				 std::string & key, const
				 double
				 value) {
	    addProperty(key, lexical_cast < string > (value));
	};
	void
	 DGCodeFile::setRawData(Composition_vector_ptr compositionVector) {
	    db->setTableName(RawData);
	    int
	     size = compositionVector->size();
	    string_vector_ptr values(new string_vector(13));
	    for (int x = 0; x != size; x++) {
		Composition_ptr c = (*compositionVector)
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
		RGB_ptr component = c->component;
		(*values)
		    [4] = lexical_cast < string > (component->R);
		(*values)
		    [5] = lexical_cast < string > (component->G);
		(*values)
		    [6] = lexical_cast < string > (component->B);
		//gamma 0~100
		(*values)[7] = "0";
		(*values)
		    [8] = "0";
		(*values)
		    [9] = "0";
		(*values)
		    [10] = "0";
		(*values)
		    [11] = "0";
		(*values)
		    [12] = "0";

		if (!lazyMode) {
		    db->update(RawHeader[0], w, RawFieldNames, values,
			       false);
		} else {
		    db->insert(RawFieldNames, values, false);
		}
	    }
	};
	void
	 DGCodeFile::
	    setRawData
	    (Composition_vector_ptr
	     compositionVector, RGBGamma_ptr rgbgamma) {
	    int a = compositionVector->size();
	    int b = rgbgamma->r->size();
	    //==================================================================
	    // 檢查來源資料
	    //==================================================================
	    if (compositionVector->size() != rgbgamma->r->size()) {
		throw
		    IllegalArgumentException
		    ("compositionVector->size() != rgbgamma->r->size()");
	    };
	    //==================================================================
	    //==================================================================
	    // 初始資料設定
	    //==================================================================
	    db->setTableName(RawData);
	    int
	     size = compositionVector->size();
	    string_vector_ptr values(new string_vector(13));
	    //==================================================================
	    //==================================================================
	    // 迴圈處理
	    //==================================================================
	    for (int x = 0; x != size; x++) {
		int n = size - 1 - x;
		Composition_ptr c = (*compositionVector)
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
		RGB_ptr component = c->component;
		(*values)
		    [4] = lexical_cast < string > (component->R);
		(*values)
		    [5] = lexical_cast < string > (component->G);
		(*values)
		    [6] = lexical_cast < string > (component->B);
		//gamma 0~100
		(*values)[7] = _toString((*rgbgamma->r)[n] * 100);
		(*values)[8] = _toString((*rgbgamma->g)[n] * 100);
		(*values)[9] = _toString((*rgbgamma->b)[n] * 100);
		(*values)[10] = (*values)[7];
		(*values)[11] = (*values)[8];
		(*values)[12] = (*values)[9];

		if (!lazyMode) {
		    db->update(RawHeader[0], w, RawFieldNames, values,
			       false);
		} else {
		    db->insert(RawFieldNames, values, false);
		}
	    }
	    //==================================================================
	};
	void
	 DGCodeFile::setGammaTable(RGB_vector_ptr dgcode) {
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
	     size = dgcode->size();
	    string_vector_ptr values(new string_vector(4));
	    //==================================================================
	    //==================================================================
	    // 迴圈處理
	    //==================================================================
	    for (int x = 0; x != size; x++) {
		//int n = size - 1 - x;
		//Composition_ptr c = (*compositionVector)[x];

		RGB_ptr rgb = (*dgcode)
		    [x];
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
	    //==================================================================
	};
	Composition_vector_ptr DGCodeFile::getCompositionVector() {
	    Composition_vector_ptr vector(new Composition_vector());
	    db->setTableName(RawData);
	    bptr < DBQuery > query = db->selectAll();
	    while (query->hasNext()) {
		string_vector_ptr result = query->nextResult();
		int
		 gray = lexical_cast < int
		    >((*result)[0]);
		double x = lexical_cast < double
		    >((*result)[1]);
		double y = lexical_cast < double
		    >((*result)[2]);
		double Y = lexical_cast < double
		    >((*result)[3]);
		double R = lexical_cast < double
		    >((*result)[4]);
		double G = lexical_cast < double
		    >((*result)[5]);
		double B = lexical_cast < double
		    >((*result)[6]);
		double r = lexical_cast < double
		    >((*result)[7]);
		double g = lexical_cast < double
		    >((*result)[8]);
		double b = lexical_cast < double
		    >((*result)[9]);
		RGB_ptr rgb(new RGBColor(gray, gray, gray));
		RGB_ptr component(new RGBColor(R, G, B));
		xyY_ptr xyY(new CIExyY(x, y, Y));
		XYZ_ptr XYZ(xyY->toXYZ());
		RGB_ptr gamma(new RGBColor(r, g, b));
		bptr <
		    Composition >
		    composition(new
				Composition(rgb, component, XYZ, gamma));
		vector->push_back(composition);
	    };
	    return vector;
	};
	string_vector_ptr DGCodeFile::makeValues(int n, Composition_ptr c) {
	    return
		makeValues(n, c,
			   RGB_ptr((RGBColor *) null),
			   RGB_ptr((RGBColor *) null));
	};
	string_vector_ptr
	    DGCodeFile::
	    makeValues(int n,
		       Composition_ptr
		       c, RGB_ptr rgbGamma, RGB_ptr rgbGammaFix) {
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
	    RGB_ptr component = c->component;
	    (*values)
		[4] = lexical_cast < string > (component->R);
	    (*values)
		[5] = lexical_cast < string > (component->G);
	    (*values)
		[6] = lexical_cast < string > (component->B);
	    //gamma 0~100
	    if (null != rgbGamma) {
		(*values)[7] = lexical_cast < string > (rgbGamma->R);
		(*values)
		    [8] = lexical_cast < string > (rgbGamma->G);
		(*values)
		    [9] = lexical_cast < string > (rgbGamma->B);
	    }

	    if (null != rgbGammaFix) {
		(*values)[10] = lexical_cast < string > (rgbGammaFix->R);
		(*values)
		    [11] = lexical_cast < string > (rgbGammaFix->G);
		(*values)
		    [12] = lexical_cast < string > (rgbGammaFix->B);
	    }
	    return values;
	};
	string_vector_ptr DGCodeFile::GammaFieldNames;
	string_vector_ptr DGCodeFile::RawFieldNames;
	string_vector_ptr DGCodeFile::PropertiesFieldNames;
	void
	 DGCodeFile::setProperty(const
				 DGCodeProperty & property) {
	    property.store(*this);
	};
	//======================================================================
	//======================================================================
	// DGCodeProperty
	//======================================================================
	const
	string DGCodeProperty::Start = "start";
	const
	string DGCodeProperty::End = "end";
	const
	string DGCodeProperty::Step = "step";
	const
	string DGCodeProperty::P1P2 = "p1p2";
	const
	string DGCodeProperty::P1 = "p1";
	const
	string DGCodeProperty::P2 = "p2";
	const
	string DGCodeProperty::RB = "rb interpolation";
	const
	string DGCodeProperty::RBUnder = "rb under";
	const
	string DGCodeProperty::In = "in";
	const
	string DGCodeProperty::LUT = "lut";
	const
	string DGCodeProperty::Out = "out";
	const
	string DGCodeProperty::Gamma = "gamma";
	const
	string DGCodeProperty::RGamma = "r gamma";
	const
	string DGCodeProperty::GGamma = "g gamma";
	const
	string DGCodeProperty::BGamma = "b gamma";
	const
	string DGCodeProperty::GammaCurve = "gamma curve";
	const
	string DGCodeProperty::GByPass = "g bypass";
	const
	string DGCodeProperty::BGain = "b gain";
	const
	string DGCodeProperty::BMax = "b max";
	const
	string DGCodeProperty::Gamma256 = "gamma 256";
	const
	string DGCodeProperty::FRC_NR = "avoid FRC noise";
	void
	 DGCodeProperty::store(DGCodeFile & dgcode) const {
	    dgcode.addProperty(Start, c.start);
	    dgcode.addProperty(End, c.end);
	    dgcode.addProperty(Step, c.step);
	    dgcode.addProperty(P1P2, c.p1p2);
	    dgcode.addProperty(P1, c.p1);
	    dgcode.addProperty(P2, c.p2);
	    dgcode.addProperty(RB, !c.p1p2);
	    dgcode.addProperty(RBUnder, c.rbInterpUnder);
	    dgcode.addProperty(In, c.in);
	    dgcode.addProperty(LUT, c.lut);
	    dgcode.addProperty(Out, c.out);
	    dgcode.addProperty(Gamma, c.gamma);
	    dgcode.addProperty(GByPass, c.gByPass);
	    dgcode.addProperty(BGain, c.bIntensityGain);
	    dgcode.addProperty(BMax, c.bMax);
	    dgcode.addProperty(Gamma256, c.gamma256);
	    dgcode.addProperty(FRC_NR, c.avoidFRCNoise);
	};
	DGCodeProperty::DGCodeProperty(const
				       LCDCalibrator & c):c(c) {
	};
	//======================================================================
    };
};

