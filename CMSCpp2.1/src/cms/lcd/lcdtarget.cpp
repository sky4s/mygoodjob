#include <includeall.h>
#pragma hdrstop
#include "lcdtarget.h"

//C系統文件

//C++系統文件
#include <algorithm>

//vcl庫頭文件

//其他庫頭文件

//本項目內頭文件

//本項目內gui頭文件
namespace cms {
    namespace lcd {
	using namespace cms::colorformat;
	using namespace Dep;
	using namespace Indep;
	using namespace math;

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
	    brightestPatchIndex(-1),
	    filter(LCDTarget_ptr(this)) {

	};


	LCDTarget_ptr LCDTarget::Instance::getFromAUORampXLS(string_ptr filename) {

	    SimpleExcelAccess xls(*filename);
	    bptr < DBQuery > query = xls.retrieve();
	    Patch_vector_ptr patchList(new Patch_vector());

	    Patch_vector_ptr rPatchList(new Patch_vector());
	    Patch_vector_ptr gPatchList(new Patch_vector());
	    Patch_vector_ptr bPatchList(new Patch_vector());

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
		rPatchList->push_back(rPatch);
		gPatchList->push_back(gPatch);
		bPatchList->push_back(bPatch);
	    }
	    reverse(patchList->begin(), patchList->end());

	    patchList->reserve(patchList->size() * 4);
	    patchList->insert(patchList->end(), rPatchList->rbegin(), rPatchList->rend());
	    patchList->insert(patchList->end(), gPatchList->rbegin(), gPatchList->rend());
	    patchList->insert(patchList->end(), bPatchList->rbegin(), bPatchList->rend());
	    LCDTarget_ptr target(new LCDTarget(patchList));
	    return target;
	};
      LCDTarget::Filter::Filter(LCDTarget_ptr lcdTarget):lcdTarget(lcdTarget) {
	};
	Patch_vector_ptr LCDTarget::Filter::grayPatch() {
	    return grayPatch(false);
	};
	Patch_vector_ptr LCDTarget::Filter::grayPatch(bool withBlack) {
	    Patch_vector_ptr tmp(new Patch_vector());
	    if (withBlack) {
		tmp->push_back(lcdTarget->getBlackPatch());
	    }

	    Patch::Filter::grayPatch(lcdTarget->getPatchList(), tmp);
	    return tmp;
	};
	Patch_vector_ptr LCDTarget::Filter::oneValueChannel(const Dep::Channel & channel) {
	    if (channel == Channel::W) {
		return grayPatch();
	    }
	    Patch_vector_ptr tmp(new Patch_vector());
	    Patch::Filter::oneValueChannel(lcdTarget->getPatchList(), tmp, channel);
	    return tmp;
	};
	Patch_vector_ptr LCDTarget::Filter::grayScalePatch(const Dep::Channel & ch, bool withBlack) {
	    Patch_vector_ptr singleChannelPatch(new Patch_vector());
	    if (withBlack) {
		Patch_ptr blackPatch = lcdTarget->getBlackPatch();
		singleChannelPatch->push_back(blackPatch);
	    }
	    Patch_vector_ptr oneValueChannelPatch = oneValueChannel(ch);
	    singleChannelPatch->insert(singleChannelPatch->begin(), oneValueChannelPatch->begin(),
				       oneValueChannelPatch->end());
	    return singleChannelPatch;

	};

	//==========================================================================================
	Interpolator::Interpolator(double_vector_ptr input, double_vector_ptr outputu,
				   double_vector_ptr outputv, double_vector_ptr outputY) {
	    u = bptr < Interpolation > (new Interpolation(input, outputu));
	    v = bptr < Interpolation > (new Interpolation(input, outputv));
	    Y = bptr < Interpolation > (new Interpolation(input, outputY));
	};
	double_array Interpolator::interpolate(double x) {
	    double_array result(new double[3]);
	    result[0] = u->interpolate(x, Linear);
	    result[1] = v->interpolate(x, Linear);
	    result[2] = Y->interpolate(x, Linear);
	    return result;
	};


	//==========================================================================================
      LCDTargetInterpolator::LCDTargetInterpolator(LCDTarget_ptr lcdTarget):lcdTarget(lcdTarget)
	{
	    init(lcdTarget);
	};
	void LCDTargetInterpolator::init(LCDTarget_ptr lcdTarget) {

	    //int size = lcdTarget->size() / 4;
	    //LCDTarget::Filter::double_vector_ptr input(new double_vector(size));
	    Patch_vector_ptr grayPatchs = lcdTarget->filter.grayPatch(true);
	    Patch_ptr blackPatch = lcdTarget->getBlackPatch();
	    Patch_vector_ptr rPatchs = lcdTarget->filter.oneValueChannel(Channel::R);
	    Patch_vector_ptr gPatchs = lcdTarget->filter.oneValueChannel(Channel::G);
	    Patch_vector_ptr bPatchs = lcdTarget->filter.oneValueChannel(Channel::B);
	    rPatchs->insert(rPatchs->begin(), blackPatch);
	    //RGB_ptr keyRGB = lcdTarget->getKeyRGB();

	    //double_vector_ptr codeVector(new double_vector(size));
	};
	bptr < Interpolator > LCDTargetInterpolator::initInterpolator(Patch_vector_ptr patchVector) {
	};
	double_array LCDTargetInterpolator::getValues(const Dep::Channel & ch, double code) {
	    int index = getArrayIndex(ch);
	    switch (index) {
	    case 0:
		return r->interpolate(code);
	    case 1:
		return g->interpolate(code);
	    case 2:
		return b->interpolate(code);
	    case 3:
		return w->interpolate(code);
	    default:
		return nil_double_array;
	    }
	};
	int LCDTargetInterpolator::getArrayIndex(const Dep::Channel & ch) {
	    return ch == Channel::W ? 3 : ch.getArrayIndex();
	};
	Patch_ptr LCDTargetInterpolator::getPatch(const Dep::Channel & ch, double value) {
	};
    };
};

