#include <includeall.h>
#pragma hdrstop
#include "measurefile.h"
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

//EXCEL寫入值有格式限定(ex: 數字/字串分別)，但BCB會轉成String 給excel
//若excel為數字格式，BCB String中只能放入數字
//此外，數字格式也無法給空白值(請Assign  0/-1)
namespace cms {
    namespace colorformat {
	using namespace Dep;
	using namespace Indep;
	using namespace java::lang;
	using namespace cms::util;
	const std::string & RampMeasureFile::Sheet1 = "xyY";
	const std::string & RampMeasureFile::Sheet2 = "XYZ";
	//const std::string & RampMeasureFile::GammaTable = "Gamma_Tab;e";
	//const std::string & RampMeasureFile::Deltaxy = "dxdy";

	 RampMeasureFile::RampMeasureFile(const std::string & fileName,
					  const Mode mode):ExcelAccessBase(fileName, mode) {
	    initSheet(Sheet1, 22, "Gray Level", "W_x", "W_y", "W_Y (nit)",
		      "W_CCT", "ΔUV", "W_R", "W_G", "W_B", "W_Gamma", "R_x", "R_y",
		      "R_Y (nit)", "G_x", "G_y", "G_Y (nit)", "B_x", "B_y", "B_Y (nit)", "DG_R",
		      "DG_G", "DG_B");
	    initSheet(Sheet2, 22, "Gray Level", "W_X", "W_Y (nit)", "W_Z", "W_CCT", "ΔUV", "W_R",
		      "W_G", "W_B", "W_Gamma", "R_X", "R_Y (nit)", "R_Z", "G_X", "G_Y (nit)", "G_Z",
		      "B_X", "B_Y (nit)", "B_Z", "DG_R", "DG_G", "DG_B");
	    initPropertySheet();
	};

	int RampMeasureFile::
	    getMaximumSize(Component_vector_ptr wMeasureData, Patch_vector_ptr rMeasureData,
			   Patch_vector_ptr gMeasureData, Patch_vector_ptr bMeasureData) {
	    using namespace math;
	    /*int wsize = wMeasureData != null ? wMeasureData->size() : 0;
	    int rsize = rMeasureData != null ? rMeasureData->size() : 0;
	    int gsize = gMeasureData != null ? gMeasureData->size() : 0;
	    int bsize = bMeasureData != null ? bMeasureData->size() : 0;*/
	    int_array sizes(new int[4]);
	     sizes[0] = wMeasureData != null ? wMeasureData->size() : 0;
	     sizes[1] = rMeasureData != null ? rMeasureData->size() : 0;
	     sizes[2] = gMeasureData != null ? gMeasureData->size() : 0;
	     sizes[3] = bMeasureData != null ? bMeasureData->size() : 0;
	     return IntArray::max(sizes, 4);
	};
	int RampMeasureFile::
	    getMaximumSize(Patch_vector_ptr wMeasureData, Patch_vector_ptr rMeasureData,
			   Patch_vector_ptr gMeasureData, Patch_vector_ptr bMeasureData) {
	    using namespace math;
	    /*int wsize = wMeasureData != null ? wMeasureData->size() : 0;
	    int rsize = rMeasureData != null ? rMeasureData->size() : 0;
	    int gsize = gMeasureData != null ? gMeasureData->size() : 0;
	    int bsize = bMeasureData != null ? bMeasureData->size() : 0;*/
	    int_array sizes(new int[4]);
	     sizes[0] = wMeasureData != null ? wMeasureData->size() : 0;
	     sizes[1] = rMeasureData != null ? rMeasureData->size() : 0;
	     sizes[2] = gMeasureData != null ? gMeasureData->size() : 0;
	     sizes[3] = bMeasureData != null ? bMeasureData->size() : 0;
	     return IntArray::max(sizes, 4);
	};
	/*
	   wMeasureData for Component_vector_ptr
	   wMeasureData2 for Patch_vector_ptr
	 */
	void RampMeasureFile::
	    setMeasureData(Component_vector_ptr wMeasureData, Patch_vector_ptr wMeasureData2,
			   Patch_vector_ptr rMeasureData, Patch_vector_ptr gMeasureData,
			   Patch_vector_ptr bMeasureData, bool XYZMode) {
	    //==================================================================
	    // 檢查來源資料
	    //==================================================================
	    /*if ((null == wMeasureData && null == wMeasureData2)
	       || (null != wMeasureData && null != wMeasureData2)) {
	       throw IllegalArgumentException();
	       } */
	    int size = -1;
	    int wsize = -1;
	    if (null != wMeasureData) {
		size = getMaximumSize(wMeasureData, rMeasureData, gMeasureData, bMeasureData);
	    } else {
		size = getMaximumSize(wMeasureData2, rMeasureData, gMeasureData, bMeasureData);
		wsize =(null!=wMeasureData2)? wMeasureData2->size():-1 ;
	    }
	    bool skipFirstLevel = (257 == wsize);

	    //==================================================================
	    //==================================================================
	    // 初始資料設定
	    //==================================================================
	    string_vector_ptr values(new string_vector(22));
	    //==================================================================
	    //==================================================================
	    // 迴圈處理
	    //==================================================================
	    double maxLuminance = -1;
	    for (int x = 0; x < size; x++) {
		if (wMeasureData != null) {
		    Component_ptr c = (*wMeasureData)[x];
		    int w = static_cast < int >(c->rgb->getValue(Channel::W));
		    (*values)[0] = _toString(w);
		    double_array XYZValues = getValues(c->XYZ, XYZMode);
		    (*values)[1] = _toString(XYZValues[0]);
		    (*values)[2] = _toString(XYZValues[1]);
		    (*values)[3] = _toString(XYZValues[2]);
		    xyY_ptr xyY(new CIExyY(c->XYZ));
		    double cct = CorrelatedColorTemperature::xy2CCTByMcCamyFloat(xyY);
		    cct = (cct > 30000 || cct < 0) ? -1 : cct;
		    (*values)[4] = _toString(static_cast < int >(cct));

		    double duv = CorrelatedColorTemperature::getduvWithDIlluminant(c->XYZ);
		    (*values)[5] = _toString(duv);

		    RGB_ptr intensity = c->intensity;
		    if (null != intensity) {
			(*values)[6] = _toString(intensity->R);
			(*values)[7] = _toString(intensity->G);
			(*values)[8] = _toString(intensity->B);
		    } else {
			StringVector::setContent(values, "-1", 3, 6, 7, 8);
		    }
		    (*values)[9] = -1;	//gamma

		    RGB_ptr rgb = c->rgb;
		    (*values)[19] = _toString(rgb->R);
		    (*values)[20] = _toString(rgb->G);
		    (*values)[21] = _toString(rgb->B);
		} else if (wMeasureData2 != null) {
		    Patch_ptr p = (*wMeasureData2)[x];
		    int w = static_cast < int >(p->getRGB()->getValue(Channel::W));
		    (*values)[0] = _toString(w);
		    XYZ_ptr XYZ = p->getXYZ();
		    double_array XYZValues = getValues(XYZ, XYZMode);
		    (*values)[1] = _toString(XYZValues[0]);
		    (*values)[2] = _toString(XYZValues[1]);
		    (*values)[3] = _toString(XYZValues[2]);
		    xyY_ptr xyY(new CIExyY(XYZ));
		    double cct = CorrelatedColorTemperature::xy2CCTByMcCamyFloat(xyY);
		    cct = (cct > 30000 || cct < 0) ? -1 : cct;
		    (*values)[4] = _toString(static_cast < int >(cct));

		    double duv = CorrelatedColorTemperature::getduvWithDIlluminant(XYZ);
		    (*values)[5] = _toString(duv);
		    StringVector::setContent(values, "-1", 3, 6, 7, 8);


		    if (-1 == maxLuminance && (skipFirstLevel ? 1 == x : true)) {
			maxLuminance = XYZValues[1];
		    }
		    //int level = wsize - x - 1;
		    /*if (wsize >= 256 && level < (skipFirstLevel ? 255 : 256)) {
			(*values)[9] =
			    _toString(math::GammaFinder::
				      findingGamma(level / (wsize - 1),
						   XYZValues[1] / maxLuminance));
		    } else {
			(*values)[9] = _toString(-1);
		    }*/
                    (*values)[9] = _toString(-1);

		    RGB_ptr rgb = p->getRGB();
		    (*values)[19] = _toString(rgb->R);
		    (*values)[20] = _toString(rgb->G);
		    (*values)[21] = _toString(rgb->B);
		} else {
		    StringVector::setContent(values, "0", 13, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 19, 20,
					     21);
		}

		if (rMeasureData != null) {
		    Patch_ptr p = (*rMeasureData)[x];
		    double_array XYZValues = getValues(p->getXYZ(), XYZMode);
		    (*values)[10] = _toString(XYZValues[0]);
		    (*values)[11] = _toString(XYZValues[1]);
		    (*values)[12] = _toString(XYZValues[2]);
		} else {
		    StringVector::setContent(values, "0", 3, 10, 11, 12);
		}
		if (gMeasureData != null) {
		    Patch_ptr p = (*gMeasureData)[x];
		    double_array XYZValues = getValues(p->getXYZ(), XYZMode);
		    (*values)[13] = _toString(XYZValues[0]);
		    (*values)[14] = _toString(XYZValues[1]);
		    (*values)[15] = _toString(XYZValues[2]);
		} else {
		    StringVector::setContent(values, "0", 3, 13, 14, 15);
		}
		if (bMeasureData != null) {
		    Patch_ptr p = (*bMeasureData)[x];
		    double_array XYZValues = getValues(p->getXYZ(), XYZMode);
		    (*values)[16] = _toString(XYZValues[0]);
		    (*values)[17] = _toString(XYZValues[1]);
		    (*values)[18] = _toString(XYZValues[2]);
		} else {
		    StringVector::setContent(values, "0", 3, 16, 17, 18);
		}

		this->insertData(XYZMode ? Sheet2 : Sheet1, values, false);
	    }
            //加入時間戳記   20140605 byBS+
            //(*values)[0] = DateTimeToStr(Now()).c_str();
            //(*values)[0] = FormatDateTime("yyyy-mm-dd hh:mm",Now()).c_str();
            (*values)[0] = FormatDateTime("yyyymmdd",Now()).c_str();
            (*values)[1] = FormatDateTime("hhmm",Now()).c_str();
            //String test= FormatDateTime("yyyy-mm-dd hh:mm",Now()).c_str();
            for(int i=2; i<22; i++)
                (*values)[i] = "-1";
            this->insertData(XYZMode ? Sheet2 : Sheet1, values, false);
	}
	void RampMeasureFile::
	    setMeasureData(Component_vector_ptr wMeasureData,
			   Patch_vector_ptr rMeasureData,
			   Patch_vector_ptr gMeasureData, Patch_vector_ptr bMeasureData) {
	    setMeasureData(wMeasureData, rMeasureData, gMeasureData, bMeasureData, false);
	}

	void RampMeasureFile::
	    setMeasureData(Component_vector_ptr wMeasureData,
			   Patch_vector_ptr rMeasureData,
			   Patch_vector_ptr gMeasureData, Patch_vector_ptr bMeasureData,
			   bool XYZMode) {
	    return setMeasureData(wMeasureData, nil_Patch_vector_ptr, rMeasureData, gMeasureData,
				  bMeasureData, XYZMode);
	}

	void RampMeasureFile::
	    setMeasureData(Patch_vector_ptr wMeasureData,
			   Patch_vector_ptr rMeasureData,
			   Patch_vector_ptr gMeasureData, Patch_vector_ptr bMeasureData,
			   bool XYZMode) {
	    return setMeasureData(nil_Component_vector_ptr, wMeasureData, rMeasureData,
				  gMeasureData, bMeasureData, XYZMode);
	}

	double_array RampMeasureFile::getValues(XYZ_ptr XYZ, bool XYZMode) {
	    double_array values(new double[3]);
	    if (XYZMode) {
		XYZ->getValues(values);
	    } else {
		CIExyY xyY(XYZ);
		xyY.getValues(values);
	    }
	    return values;
	}

	void RampMeasureFile::addProperty(bptr < cms::colorformat::DGLutProperty > property) {
	    using namespace std;
	    map < const std::string, string_ptr) properties = property->propertyMap;
	    map < const std::string, string_ptr)::const_iterator it = properties.begin();
	    while (it != properties.end()) {
		string key = it->first;
		string_ptr val = it->second;
		ExcelAccessBase::addProperty(key, *val);
		it++;
	    }
	};


	//==================================================================
	const std::string & IntensityMatrixFile::RSheet = "R";
	const std::string & IntensityMatrixFile::GSheet = "G";
	const std::string & IntensityMatrixFile::BSheet = "B";
	void IntensityMatrixFile::initSheet() {
	    string_vector_ptr header(new string_vector());
	    //ADO無法超過255個欄位
	    for (int x = 255; x > 0; x--) {
		string s = "GL" + _toString(x);
		header->push_back(s);
	    }
	    ExcelAccessBase::initSheet(RSheet, header);
	    ExcelAccessBase::initSheet(GSheet, header);
	    ExcelAccessBase::initSheet(BSheet, header);
	};
	IntensityMatrixFile::
	    IntensityMatrixFile(const std::string & filename):ExcelAccessBase(filename, Create) {
	    initSheet();
	};
	void IntensityMatrixFile::addIntensityVector(Component_vector_ptr intensityVector) {

	    string_vector_ptr rIntensitys(new string_vector());
	    string_vector_ptr gIntensitys(new string_vector());
	    string_vector_ptr bIntensitys(new string_vector());
	    int size = intensityVector->size();
	    //ADO無法超過255個欄位
	    for (int x = 0; x < 255 && x < size; x++) {
		Component_ptr c = (*intensityVector)[x];
		RGB_ptr intensity = c->intensity;
		rIntensitys->push_back(_toString(intensity->R));
		gIntensitys->push_back(_toString(intensity->G));
		bIntensitys->push_back(_toString(intensity->B));
	    }
	    insertData(RSheet, rIntensitys, false);
	    insertData(GSheet, gIntensitys, false);
	    insertData(BSheet, bIntensitys, false);
	};
    };
};

