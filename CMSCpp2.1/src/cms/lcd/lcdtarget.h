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
	    Patch_vector_ptr getLabPatchList();
	    Patch_vector_ptr getLabPatchList(XYZ_ptr whitePoint);
	    Patch_ptr getWhitePatch();
	    class Instance {
	      public:
		static LCDTarget getFromAUORampXLS(string_ptr filename);
	    };
	    friend class Instance;
	  protected:
	     LCDTarget(Patch_vector_ptr patchList);
	};
    };
};
#endif

