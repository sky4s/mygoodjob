#ifndef RGBARRAYH
#define RGBARRAYH
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>

namespace cms {
    namespace util {
	class RGBArray {

	};
	class RGBVector {
	  protected:
	    RGB_vector_ptr rgbVector;
	  public:
	    RGBVector(RGB_vector_ptr rgbVector);
	};
	class RGBVectorOp:public RGBVector {
	  public:
	    virtual RGBVectorOp createInstance();
	    void addSource(RGBVectorOp source);
	};
    };
}
#endif

