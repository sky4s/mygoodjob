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
	    void calculatePatchLab(XYZ_ptr whitePoint);

	    class Instance {
	      public:
		static LCDTarget_ptr getFromAUORampXLS(string_ptr filename);
		static LCDTarget_ptr getFromAlteredLogoXLS(string_ptr filename);
	    };

	    class Filter {
	      private:
		//LCDTarget_ptr lcdTarget;
		LCDTarget * lcdTarget;
	      public:
		//Filter(LCDTarget_ptr lcdTarget);
		Filter(LCDTarget * lcdTarget);
		Patch_vector_ptr grayPatch();
		Patch_vector_ptr grayPatch(bool withBlack);
		Patch_vector_ptr oneValueChannel(const Dep::Channel & ch);
		Patch_vector_ptr grayScalePatch(const Dep::Channel & ch, bool withBlack);
	    };
	    friend class Instance;
	    Filter filter;
	  protected:
	     LCDTarget(Patch_vector_ptr patchList);
	};

	class LCDTargetInterpolator;
	class Interpolator {
	    friend class LCDTargetInterpolator;
	  private:
	     bptr < math::Interpolation > u, v, Y;
	     Interpolator(double_vector_ptr input, double_vector_ptr outputu,
			  double_vector_ptr outputv, double_vector_ptr outputY);
	    double_array interpolate(double x);
	};

	class LCDTargetInterpolator {
	  private:
	    bptr < Interpolator > r, g, b, w;
	    LCDTarget_ptr lcdTarget;

	    void init(LCDTarget_ptr lcdTarget);
	    static bptr < Interpolator > initInterpolator(Patch_vector_ptr patchVector);
	  protected:
	     double_array getValues(const Dep::Channel & ch, double code);
	    static int getArrayIndex(const Dep::Channel & ch);
	    XYZ_ptr getXYZFromDomainValues(double_array values);
	  public:
	     Patch_ptr getPatch(const Dep::Channel & ch, double value);
	     LCDTargetInterpolator(LCDTarget_ptr lcdTarget);
	};
    };
};
#endif

