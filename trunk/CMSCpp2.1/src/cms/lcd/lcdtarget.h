#ifndef LCDTARGETH
#define LCDTARGETH

//C系統文件

//C++系統文件

//vcl庫頭文件

//其他庫頭文件

//本項目內頭文件

//本項目內gui頭文件

namespace cms {
    namespace lcd {
	class LCDTarget:public Target {

	  private:
	    int blackPatchIndex, whitePatchIndex, darkestPatchIndex, brightestPatchIndex;
	  public:
	     Patch_ptr getBlackPatch();
	    Patch_ptr getBrightestPatch();
	    Patch_ptr getDarkestPatch();
	    virtual Patch_vector_ptr getLabPatchList();
	    Patch_vector_ptr getLabPatchList(XYZ_ptr whitePoint);
	    Patch_ptr getWhitePatch();
	    class Instance {
	      public:
		static LCDTarget_ptr getFromAUORampXLS(string_ptr filename);
	    };
	    friend class Instance;
	  protected:
	     LCDTarget(Patch_vector_ptr patchList);
	};

	class LCDTargetInterpolator;
	class Interpolator {
	    friend class LCDTargetInterpolator;
	  private:
	     bptr < Interpolation > u, v, Y;
	     Interpolator(double_vector_ptr input, double_vector_ptr outputu,
			  double_vector_ptr outputv, double_vector_ptr outputY);
	    double_array interpolate(double x);
	};

	class LCDTargetInterpolator {
	  private:
	    LCDTarget_ptr lcdTarget;
	    LCDTargetInterpolator(LCDTarget_ptr lcdTarget);
	  public:
	    Patch_ptr getPatch(const Dep::Channel & ch, double value);
	};
    };
};
#endif

