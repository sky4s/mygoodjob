#include <includeall.h>
#pragma hdrstop
#include "lcdmodel.h"

//C�t�Τ��

//C++�t�Τ��

//vcl�w�Y���

//��L�w�Y���

//�����ؤ��Y���

//�����ؤ�gui�Y���

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

