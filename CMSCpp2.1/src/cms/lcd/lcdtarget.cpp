#include <includeall.h>
#pragma hdrstop
#include "lcdtarget.h"

//C系統文件

//C++系統文件

//vcl庫頭文件

//其他庫頭文件

//本項目內頭文件

//本項目內gui頭文件
namespace cms {
    namespace lcd {
	using namespace cms::colorformat;
	using namespace Dep;
	using namespace Indep;

	Patch_ptr LCDTarget::getBlackPatch() {
	    if (blackPatchIndex == -1) {
		for (int x = 0; x < patchList->size(); x++) {
		    Patch_ptr p = (*patchList)[x];
		    RGB_ptr rgb = p->getRGB();
		    if (rgb->isBlack()) {
			blackPatchIndex = x;
			break;
		    }
		};

	    }
	    return (*patchList)[blackPatchIndex];
	};
	Patch_ptr LCDTarget::getBrightestPatch() {
	    if (brightestPatchIndex == -1) {
		double brightestY = 0;
		for (int x = 0; x < patchList->size(); x++) {
		    Patch_ptr p = (*patchList)[x];
		    double Y = p->getXYZ()->Y;
		    if (Y > brightestY) {
			brightestY = Y;
			brightestPatchIndex = x;
		    }

		};
	    }
	    return (*patchList)[brightestPatchIndex];
	};
	Patch_ptr LCDTarget::getDarkestPatch() {
	    if (darkestPatchIndex == -1) {
		double darkestY = std::numeric_limits < double >::max();
		for (int x = 0; x < patchList->size(); x++) {
		    Patch_ptr p = (*patchList)[x];
		    double Y = p->getXYZ()->Y;
		    if (Y < darkestY) {
			darkestY = Y;
			darkestPatchIndex = x;
		    }

		};
	    }
	    return (*patchList)[darkestPatchIndex];
	};
	Patch_vector_ptr LCDTarget::getLabPatchList() {
	    Patch_ptr whitePatch = getWhitePatch();
	    XYZ_ptr whiteXYZ = whitePatch->getXYZ();
	    return getLabPatchList(whiteXYZ);
	};
	Patch_vector_ptr LCDTarget::getLabPatchList(XYZ_ptr whitePoint) {
	    Patch_vector_ptr labPatchList = Patch::Produce::LabPatches(patchList, whitePoint);
	    return labPatchList;
	};
	Patch_ptr LCDTarget::getWhitePatch() {
	    if (whitePatchIndex == -1) {
		for (int x = 0; x < patchList->size(); x++) {
		    Patch_ptr p = (*patchList)[x];
		    RGB_ptr rgb = p->getRGB();
		    if (rgb->isWhite()) {
			whitePatchIndex = x;
			break;
		    }
		};

	    }
	    return (*patchList)[whitePatchIndex];
	};

      LCDTarget::LCDTarget(Patch_vector_ptr patchList):Target(patchList), blackPatchIndex(-1), whitePatchIndex(-1), darkestPatchIndex(-1),
	    brightestPatchIndex(-1) {

	};


	LCDTarget LCDTarget::Instance::getFromAUORampXLS(string_ptr filename) {

	    SimpleExcelAccess xls(*filename);
	    bptr < DBQuery > query = xls.retrieve();
	    Patch_vector_ptr patchList(new Patch_vector());

	    while (query->hasNext()) {
		string_vector_ptr result = query->nextResult();
		double_vector_ptr values = DBQuery::toDoubleVector(result);
		int grayLevel = (int) (*values)[0];
		double x = (*values)[1];
		double y = (*values)[2];
		double Y = (*values)[3];
		double wr = (*values)[6];
		double wg = (*values)[7];
		double wb = (*values)[8];


		double rx = (*values)[9];
		double ry = (*values)[10];
		double rY = (*values)[11];
		double gx = (*values)[12];
		double gy = (*values)[13];
		double gY = (*values)[14];
		double bx = (*values)[15];
		double by = (*values)[16];
		double bY = (*values)[17];


		RGB_ptr w(new RGBColor(grayLevel, grayLevel, grayLevel));
		RGB_ptr intensity(new RGBColor(wr, wg, wb));

		RGB_ptr r(new RGBColor(grayLevel, 0, 0));
		RGB_ptr g(new RGBColor(0, grayLevel, 0));
		RGB_ptr b(new RGBColor(0, 0, grayLevel));

		xyY_ptr wxyY(new CIExyY(x, y, Y));
		XYZ_ptr wXYZ = wxyY->toXYZ();
		xyY_ptr rxyY(new CIExyY(rx, ry, rY));
		XYZ_ptr rXYZ = rxyY->toXYZ();
		xyY_ptr gxyY(new CIExyY(gx, gy, gY));
		XYZ_ptr gXYZ = gxyY->toXYZ();
		xyY_ptr bxyY(new CIExyY(bx, by, bY));
		XYZ_ptr bXYZ = bxyY->toXYZ();

		Patch_ptr wPatch(new Patch(w->toString(), wXYZ, nil_XYZ_ptr, w, intensity));
		Patch_ptr rPatch(new Patch(r->toString(), rXYZ, nil_XYZ_ptr, r));
		Patch_ptr gPatch(new Patch(g->toString(), gXYZ, nil_XYZ_ptr, g));
		Patch_ptr bPatch(new Patch(b->toString(), bXYZ, nil_XYZ_ptr, b));

		patchList->push_back(wPatch);
		patchList->push_back(rPatch);
		patchList->push_back(gPatch);
		patchList->push_back(bPatch);
	    }
	    LCDTarget target(patchList);
	    return target;
	};
    };
};

