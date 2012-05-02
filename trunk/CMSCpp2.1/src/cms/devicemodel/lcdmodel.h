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
	typedef bptr < DeltaE > DeltaE_ptr;
	typedef std::vector < DeltaE_ptr > DeltaE_vector;
	typedef bptr < DeltaE_vector > DeltaE_vector_ptr;

	class DeltaEReport {
	  private:
	    DeltaE_vector_ptr deltaEVector;
	    Patch_vector_ptr patchList1, patchList2;
	     DeltaEReport();
	  public:
	    static bptr < DeltaEReport > getDeltaEReport(Patch_vector_ptr patchList1,
							 Patch_vector_ptr patchList2);
	    void storeToExcel(const std::string & filename);
	};
	class DeviceCharacterizationModel {
	  protected:
	    XYZ_ptr targetWhitePoint;
	  public:
	    virtual XYZ_ptr getXYZ(RGB_ptr rgb, boolean relativeXYZ) = 0;
	    virtual RGB_ptr getRGB(XYZ_ptr XYZ, boolean relativeXYZ) = 0;
	     bptr < DeltaEReport > testForwardModel(Patch_vector_ptr targetLabPatchList);
	    Patch_vector_ptr produceForwardModelPatchList(Patch_vector_ptr rgbPatchList);
	    void setTargetWhitePoint(XYZ_ptr targetWhitePoint);
	};
	class LCDModel:public DeviceCharacterizationModel {
	  protected:
	    LCDTarget_ptr lcdTarget;
	    LCDModel(LCDTarget_ptr lcdTarget);
	  public:
	};

	class MultiMatrixModel:public LCDModel {
	  private:
	    cms::lcd::LCDTargetInterpolator interpolator;
	    XYZ_ptr recoverAbsoluteOrRelative(XYZ_ptr rXYZ, XYZ_ptr gXYZ,
					      XYZ_ptr bXYZ, boolean relativeXYZ);
	  public:
	     MultiMatrixModel(LCDTarget_ptr lcdTarget);
	    virtual XYZ_ptr getXYZ(RGB_ptr rgb, boolean relativeXYZ);
	    virtual RGB_ptr getRGB(XYZ_ptr XYZ, boolean relativeXYZ);
	    static XYZ_ptr recover(XYZ_ptr rXYZ, XYZ_ptr gXYZ, XYZ_ptr bXYZ, XYZ_ptr black);
	  protected:
	     XYZ_ptr getXYZ(double r, double g, double b);
	    XYZ_ptr getXYZ(double r, double g, double b, boolean relativeXYZ);

	};

	class DeHook2LCDModel:public LCDModel {
	  private:
	    XYZ_ptr interpolate(Patch_ptr patch1, Patch_ptr patch2, double x1, double x2, double x);
	  public:
	     DeHook2LCDModel(LCDTarget_ptr lcdTarget);
	    virtual XYZ_ptr getXYZ(RGB_ptr rgb, boolean relativeXYZ);
	    virtual RGB_ptr getRGB(XYZ_ptr XYZ, boolean relativeXYZ);
	  protected:
	     XYZ_ptr getXYZ(double r, double g, double b, boolean relativeXYZ);
	};


    };
};

#endif

