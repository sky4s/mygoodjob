#include <includeall.h>
#pragma hdrstop
#include "lcdmodel.h"

//C系統文件

//C++系統文件

//vcl庫頭文件

//其他庫頭文件

//本項目內頭文件

//本項目內gui頭文件

namespace cms {
    namespace devicemodel {
	using namespace java::lang;
	using namespace Dep;
	using namespace Indep;
	using namespace std;
	using namespace cms::colorformat;
	using namespace cms::util;

	 DeltaEReport::DeltaEReport() {
	};
	 bptr < DeltaEReport >
	    DeltaEReport::getDeltaEReport(Patch_vector_ptr patchList1,
					  Patch_vector_ptr patchList2) {
	    if (patchList1->size() != patchList2->size()) {
		throw
		    IllegalArgumentException
		    ("patchList1->size() != patchList2->size()");
	    }
	    int size = patchList1->size();
	    DeltaE_vector_ptr deltaEVector(new DeltaE_vector(size));

	    for (int x = 0; x < size; x++) {
		Lab_ptr Lab1 = (*patchList1)[x]->getLab();
		Lab_ptr Lab2 = (*patchList2)[x]->getLab();
		DeltaE_ptr deltaE(new DeltaE(Lab1, Lab2, false));
		deltaE->getCIEDeltaE();
		deltaE->getCIE94DeltaE();
		deltaE->getCIE2000DeltaE();
		(*deltaEVector)[x] = deltaE;
	    };
	    bptr < DeltaEReport > report(new DeltaEReport());
	    report->deltaEVector = deltaEVector;
	    report->patchList1 = patchList1;
	    report->patchList2 = patchList2;
	    return report;
	};
	void DeltaEReport::storeToExcel(const std::string & filename) {
	    //SimpleExcelAccess excel(filename,);

	    Util::deleteExist(filename);
	    SimpleExcelAccess excel(filename, Create,
				    StringVector::fromCString(12, "R", "G",
							      "B", "L",
							      "a", "_b",
							      "L'", "a'",
							      "_b'", "dE",
							      "dE94",
							      "dE00"));
	    int size = patchList1->size();
	    for (int x = 0; x != size; x++) {
		Patch_ptr p1 = (*patchList1)[x];
		Patch_ptr p2 = (*patchList2)[x];
		RGB_ptr rgb = p1->getRGB();
		Lab_ptr Lab1 = p1->getLab();
		Lab_ptr Lab2 = p2->getLab();
		DeltaE_ptr de = (*deltaEVector)[x];

		string_vector_ptr values =
		    StringVector::fromDouble(12, rgb->R, rgb->G,
					     rgb->B, Lab1->L, Lab1->a,
					     Lab1->b, Lab2->L, Lab2->a,
					     Lab2->b, de->getCIEDeltaE(),
					     de->getCIE94DeltaE(),
					     de->getCIE2000DeltaE());
		excel.insert(values);
	    };
	};
	//=========================================================================================
	bptr < DeltaEReport >
	    DeviceCharacterizationModel::
	    testForwardModel(Patch_vector_ptr targetLabPatchList) {
	    Patch_vector_ptr labPatchList =
		produceForwardModelPatchList(targetLabPatchList);
	    bptr < DeltaEReport > report =
		DeltaEReport::getDeltaEReport(targetLabPatchList,
					      labPatchList);
	    return report;
	};
	Patch_vector_ptr DeviceCharacterizationModel::
	    produceForwardModelPatchList(Patch_vector_ptr rgbPatchList) {
	    int size = rgbPatchList->size();
	    Patch_vector_ptr modelPatchList(new Patch_vector(size));


	    for (int x = 0; x < size; x++) {
		Patch_ptr p = (*rgbPatchList)[x];
		RGB_ptr rgb = p->getRGB();
		XYZ_ptr XYZ = getXYZ(rgb, false);
		Lab_ptr Lab(new CIELab(XYZ, targetWhitePoint));

		//Patch_ptr newp(new Patch(p->getName(), XYZ, nil_XYZ_ptr, rgb));
		Patch_ptr newp(new Patch(p->getName(), XYZ, Lab, rgb));
		(*modelPatchList)[x] = newp;
	    }
	    return modelPatchList;
	};
	void DeviceCharacterizationModel::
	    setTargetWhitePoint(XYZ_ptr targetWhitePoint) {
	    this->targetWhitePoint = targetWhitePoint;
	};
	//=========================================================================================
      LCDModel::LCDModel(LCDTarget_ptr lcdTarget):lcdTarget(lcdTarget)
	{
	};
	//=========================================================================================
	XYZ_ptr MultiMatrixModel::recoverAbsoluteOrRelative(XYZ_ptr rXYZ,
							    XYZ_ptr gXYZ,
							    XYZ_ptr bXYZ,
							    boolean
							    relativeXYZ) {
	    Patch_ptr blackPatch = lcdTarget->getBlackPatch();
	    XYZ_ptr flare = blackPatch->getXYZ();
	    XYZ_ptr recoverXYZ = recover(rXYZ, gXYZ, bXYZ, flare);
	    if (relativeXYZ) {
		recoverXYZ = CIEXYZ::minus(recoverXYZ, flare);
	    }
	    return recoverXYZ;
	};
	XYZ_ptr MultiMatrixModel::recover(XYZ_ptr rXYZ, XYZ_ptr gXYZ,
					  XYZ_ptr bXYZ, XYZ_ptr black) {
	    XYZ_ptr XYZ = CIEXYZ::plus(rXYZ, gXYZ);
	    XYZ = CIEXYZ::plus(XYZ, bXYZ);
	    XYZ_ptr doubleBlack = CIEXYZ::plus(black, black);
	    XYZ = CIEXYZ::minus(XYZ, doubleBlack);
	    return XYZ;
	};
      MultiMatrixModel::MultiMatrixModel(LCDTarget_ptr lcdTarget):LCDModel(lcdTarget),
	    interpolator(lcdTarget)
	{
	};
	XYZ_ptr MultiMatrixModel::getXYZ(RGB_ptr rgb, boolean relativeXYZ) {
	    XYZ_ptr XYZ = getXYZ(rgb->R, rgb->G, rgb->B, relativeXYZ);
	    return XYZ;
	};
	RGB_ptr MultiMatrixModel::getRGB(XYZ_ptr XYZ, boolean relativeXYZ) {
	    throw new UnsupportedOperationException();
	};
	XYZ_ptr MultiMatrixModel::getXYZ(double r, double g, double b) {
	    return getXYZ(r, g, b, true);
	};
	XYZ_ptr MultiMatrixModel::getXYZ(double r, double g, double b,
					 boolean relativeXYZ) {
	    Patch_ptr rPatch = interpolator.getPatch(Channel::R, r);
	    Patch_ptr gPatch = interpolator.getPatch(Channel::G, g);
	    Patch_ptr bPatch = interpolator.getPatch(Channel::B, b);
	    XYZ_ptr rXYZ = rPatch->getXYZ();
	    XYZ_ptr gXYZ = gPatch->getXYZ();
	    XYZ_ptr bXYZ = bPatch->getXYZ();
	    return recoverAbsoluteOrRelative(rXYZ, gXYZ, bXYZ,
					     relativeXYZ);
	};

	//=========================================================================================

      DeHook2LCDModel::DeHook2LCDModel(LCDTarget_ptr lcdTarget):LCDModel(lcdTarget)
	{
	};
	XYZ_ptr DeHook2LCDModel::getXYZ(RGB_ptr rgb, boolean relativeXYZ) {
	    XYZ_ptr XYZ = getXYZ(rgb->R, rgb->G, rgb->B, relativeXYZ);
	    return XYZ;
	};
	RGB_ptr DeHook2LCDModel::getRGB(XYZ_ptr XYZ, boolean relativeXYZ) {
	    throw new UnsupportedOperationException();
	};
	XYZ_ptr DeHook2LCDModel::getXYZ(double r, double g, double b,
					boolean relativeXYZ) {
	    int r0 = static_cast < int >(r);
	    int r1 = r0 + 1;
	    int g0 = static_cast < int >(g);
	    int g1 = g0 + 1;
	    Patch_ptr r0p = lcdTarget->getPatch(r0, 0, 0);
	    Patch_ptr r1p = lcdTarget->getPatch(r1, 0, 0);
	    Patch_ptr g0p = lcdTarget->getPatch(0, g0, 0);
	    Patch_ptr g1p = lcdTarget->getPatch(0, g1, 0);
	    Patch_ptr bp = lcdTarget->getPatch(0, 0, b);
	    Patch_ptr kp = lcdTarget->getPatch(0, 0, 0);

	    XYZ_ptr rXYZ =
		r1p != null ? interpolate(r0p, r1p, r0, r1,
					  r) : r0p->getXYZ();
	    XYZ_ptr gXYZ =
		g1p != null ? interpolate(g0p, g1p, g0, g1,
					  g) : g0p->getXYZ();
	    XYZ_ptr bXYZ = bp->getXYZ();
	    XYZ_ptr flare = kp->getXYZ();
	    XYZ_ptr result =
		MultiMatrixModel::recover(rXYZ, gXYZ, bXYZ, flare);
	    if (relativeXYZ) {
		result = CIEXYZ::minus(result, flare);
	    }
	    return result;


	    /*Patch_ptr rPatch = interpolator.getPatch(Channel::R, r);
	       Patch_ptr gPatch = interpolator.getPatch(Channel::G, g);
	       Patch_ptr bPatch = interpolator.getPatch(Channel::B, b);
	       XYZ_ptr rXYZ = rPatch->getXYZ();
	       XYZ_ptr gXYZ = gPatch->getXYZ();
	       XYZ_ptr bXYZ = bPatch->getXYZ();
	       return recoverAbsoluteOrRelative(rXYZ, gXYZ, bXYZ, relativeXYZ); */
	};

	XYZ_ptr DeHook2LCDModel::interpolate(Patch_ptr patch1,
					     Patch_ptr patch2, double x1,
					     double x2, double x) {
	    using namespace math;
	    XYZ_ptr XYZ1 = patch1->getXYZ();
	    XYZ_ptr XYZ2 = patch2->getXYZ();
	    xyY_ptr xyY1(new CIExyY(XYZ1));
	    xyY_ptr xyY2(new CIExyY(XYZ2));
	    double_array uvpValues1 = xyY1->getuvPrimeYValues();
	    double_array uvpValues2 = xyY2->getuvPrimeYValues();
	    double_array uvpValues(new double[3]);

	    uvpValues[0] =
		Interpolation::linear(x1, x2, uvpValues1[0], uvpValues2[0],
				      x);
	    uvpValues[1] =
		Interpolation::linear(x1, x2, uvpValues1[1], uvpValues2[1],
				      x);
	    uvpValues[2] =
		Interpolation::linear(x1, x2, uvpValues1[2], uvpValues2[2],
				      x);

	    CIExyY xyY;
	    xyY.setuvPrimeYValues(uvpValues);
	    return xyY.toXYZ();
	};
	//=========================================================================================
    };
};

