#ifndef LCDMODELH
#define LCDMODELH

//C�t�Τ��

//C++�t�Τ��

//vcl�w�Y���

//��L�w�Y���

//�����ؤ��Y���

//�����ؤ�gui�Y���

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

