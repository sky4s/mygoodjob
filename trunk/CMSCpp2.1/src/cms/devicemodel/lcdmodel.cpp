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
	 LCDModel::LCDModel(LCDTarget_ptr lcdTarget):lcdTarget(lcdTarget) {
	};

	 MultiMatrixModel::MultiMatrixModel(LCDTarget_ptr lcdTarget):LCDModel(lcdTarget) {
	};
	XYZ_ptr MultiMatrixModel::getXYZ(RGB_ptr rgb, boolean relativeXYZ) {
	};
	RGB_ptr MultiMatrixModel::getRGB(XYZ_ptr XYZ, boolean relativeXYZ) {
	    throw new UnsupportedOperationException();
	};
    };
};

