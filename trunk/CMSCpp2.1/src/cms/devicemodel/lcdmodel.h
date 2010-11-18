#ifndef LCDMODELH
#define LCDMODELH

//C系統文件

//C++系統文件

//vcl庫頭文件

//其他庫頭文件

//本項目內頭文件

//本項目內gui頭文件

namespace cms {
    namespace devicemodel {
	class DeviceCharacterizationModel {
	  public:
	    virtual XYZ_ptr getXYZ(RGB_ptr rgb, boolean relativeXYZ) = 0;
	    virtual RGB_ptr getRGB(XYZ_ptr XYZ, boolean relativeXYZ) = 0;
	};
	class LCDModel:public DeviceCharacterizationModel {
	  protected:
	    LCDTarget_ptr lcdTarget;
	    LCDModel(LCDTarget_ptr lcdTarget);
	};

	class MultiMatrixModel:public LCDModel {
	  public:
	    MultiMatrixModel(LCDTarget_ptr lcdTarget);
	    virtual XYZ_ptr getXYZ(RGB_ptr rgb, boolean relativeXYZ);
	    virtual RGB_ptr getRGB(XYZ_ptr XYZ, boolean relativeXYZ);
	};
    };
};

#endif

