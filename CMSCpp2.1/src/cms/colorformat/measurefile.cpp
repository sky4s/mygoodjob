#include <includeall.h>
#pragma hdrstop
#include "measurefile.h"
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace cms {
    namespace colorformat {
	using namespace Dep;
	using namespace Indep;
	using namespace java::lang;
	using namespace cms::util;
	const std::string & RampMeasureFile::Sheet1 = "Sheet1";
	 RampMeasureFile::RampMeasureFile(const std::string & fileName,
					  const Mode
					  mode):ExcelAccessBase(fileName,
								mode) {
	    initSheet(Sheet1, 18, "Gray Level", "W_x", "W_y", "W_Y (nit)",
		      "W_C.T.", "ΔUV", "W_R", "W_G", "W_B", "R_x", "R_y",
		      "R_Y (nit)", "G_x", "G_y", "G_Y (nit)", "B_x", "B_y",
		      "B_Y (nit)");
	};
	void RampMeasureFile::
	    setMeasureData(Component_vector_ptr wMeasureData,
			   Patch_vector_ptr rMeasureData,
			   Patch_vector_ptr gMeasureData,
			   Patch_vector_ptr bMeasureData) {
	    //==================================================================
	    // 檢查來源資料
	    //==================================================================
	    int size = wMeasureData->size();
	    int rsize = rMeasureData != null ? rMeasureData->size() : size;
	    int gsize = gMeasureData != null ? gMeasureData->size() : size;
	    int bsize = bMeasureData != null ? bMeasureData->size() : size;
	    if (size != rsize || size != gsize || size != bsize) {
		throw IllegalArgumentException("size is not match");
	    }
	    //==================================================================//==================================================================// 初始資料設定//==================================================================
		db->setTableName(Sheet1);
	    string_vector_ptr headerNames = getHeaderNames(Sheet1);
	    string_vector_ptr values(new string_vector(18));
	    //==================================================================
	    //==================================================================
	    // 迴圈處理
	    //==================================================================
	    for (int x = 0; x < size; x++) {
		if (wMeasureData != null) {
		    Component_ptr c = (*wMeasureData)[x];
		    int w =
			static_cast < int >(c->rgb->getValue(Channel::W));
		    (*values)[0] = _toString(w);
		    xyY_ptr xyY(new CIExyY(c->XYZ));
		    (*values)[1] = _toString(xyY->x);
		    (*values)[2] = _toString(xyY->y);
		    (*values)[3] = _toString(xyY->Y);

		    double cct =
			CorrelatedColorTemperature::
			xy2CCTByMcCamyFloat(xyY);
		    (*values)[4] = _toString(static_cast < int >(cct));
		    (*values)[5] = "0";


		    RGB_ptr intensity = c->intensity;
		    (*values)[6] = _toString(intensity->R);
		    (*values)[7] = _toString(intensity->G);
		    (*values)[8] = _toString(intensity->B);
		} else {

		}

		if (rMeasureData != null) {
		    Patch_ptr p = (*rMeasureData)[x];
		    xyY_ptr rxyY(new CIExyY(p->getXYZ()));
		    (*values)[9] = _toString(rxyY->x);
		    (*values)[10] = _toString(rxyY->y);
		    (*values)[11] = _toString(rxyY->Y);
		} else {
		    /*(*values)[9] = "0";
		       (*values)[10] = "0";
		       (*values)[11] = "0"; */
		    StringVector::setContent(values, "0", 3, 9, 10, 11);
		}
		if (gMeasureData != null) {
		    Patch_ptr p = (*gMeasureData)[x];
		    xyY_ptr gxyY(new CIExyY(p->getXYZ()));
		    (*values)[12] = _toString(gxyY->x);
		    (*values)[13] = _toString(gxyY->y);
		    (*values)[14] = _toString(gxyY->Y);
		} else {
		    /*(*values)[12] = "0";
		       (*values)[13] = "0";
		       (*values)[14] = "0"; */
		    StringVector::setContent(values, "0", 3, 12, 13, 14);
		}
		if (bMeasureData != null) {
		    Patch_ptr p = (*gMeasureData)[x];
		    xyY_ptr bxyY(new CIExyY(p->getXYZ()));
		    (*values)[15] = _toString(bxyY->x);
		    (*values)[16] = _toString(bxyY->y);
		    (*values)[17] = _toString(bxyY->Y);
		} else {
		    /*(*values)[15] = "0";
		       (*values)[16] = "0";
		       (*values)[17] = "0"; */
		    StringVector::setContent(values, "0", 3, 15, 16, 17);
		}

		db->insert(headerNames, values, false);
	    }
	    //==================================================================
	};

	/*void RampMeasureFile::setMeasureData(const Channel & channel,
	   Patch_vector_ptr measureData)
	   {
	   //==================================================================
	   // 初始資料設定
	   //==================================================================
	   int size = measureData->size();
	   db->setTableName(Sheet1);
	   string_vector_ptr headerNames = getHeaderNames(Sheet1);
	   string_vector_ptr values(new string_vector(18));
	   //==================================================================
	   //==================================================================
	   // 迴圈處理
	   //==================================================================
	   for (int x = 0; x < size; x++) {
	   Patch_ptr patch = (*measureData)[x];
	   xyY_ptr xyY(new CIExyY(patch->getXYZ()));
	   }
	   //==================================================================
	   }; */
    };
};

