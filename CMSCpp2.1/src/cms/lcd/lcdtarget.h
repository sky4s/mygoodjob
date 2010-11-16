#ifndef LCDTARGETH
#define LCDTARGETH

//C�t�Τ��

//C++�t�Τ��

//vcl�w�Y���

//��L�w�Y���

//�����ؤ��Y���

//�����ؤ�gui�Y���

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

