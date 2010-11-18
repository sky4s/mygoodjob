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
	 LCDModel::LCDModel(LCDTarget_ptr lcdTarget):lcdTarget(lcdTarget) {
	};

	XYZ_ptr MultiMatrixModel::recoverAbsoluteOrRelative(XYZ_ptr rXYZ, XYZ_ptr gXYZ,
							    XYZ_ptr bXYZ, boolean relativeXYZ) {
	    Patch_ptr blackPatch = lcdTarget->getBlackPatch();
	    XYZ_ptr flare = blackPatch->getXYZ();
	    XYZ_ptr recoverXYZ = recover(rXYZ, gXYZ, bXYZ, flare);
	    if (relativeXYZ) {
		recoverXYZ = CIEXYZ::minus(recoverXYZ, flare);
	    }
	    return recoverXYZ;
	};
	XYZ_ptr MultiMatrixModel::recover(XYZ_ptr rXYZ, XYZ_ptr gXYZ, XYZ_ptr bXYZ, XYZ_ptr black) {
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
	    XYZ_ptr XYZ = getXYZ(rgb->R, rgb->G, rgb->B);
	    return XYZ;
	};
	RGB_ptr MultiMatrixModel::getRGB(XYZ_ptr XYZ, boolean relativeXYZ) {
	    throw new UnsupportedOperationException();
	};
	XYZ_ptr MultiMatrixModel::getXYZ(double r, double g, double b) {
	    return getXYZ(r, g, b, true);
	};
	XYZ_ptr MultiMatrixModel::getXYZ(double r, double g, double b, boolean relativeXYZ) {
	    Patch_ptr rPatch = interpolator.getPatch(Channel::R, r);
	    Patch_ptr gPatch = interpolator.getPatch(Channel::G, g);
	    Patch_ptr bPatch = interpolator.getPatch(Channel::B, b);
	    XYZ_ptr rXYZ = rPatch->getXYZ();
	    XYZ_ptr gXYZ = gPatch->getXYZ();
	    XYZ_ptr bXYZ = bPatch->getXYZ();
	    return recoverAbsoluteOrRelative(rXYZ, gXYZ, bXYZ, relativeXYZ);
	};
    };
};

