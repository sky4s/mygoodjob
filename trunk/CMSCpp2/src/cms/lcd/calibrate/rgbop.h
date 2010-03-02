#ifndef RGBOPH
#define RGBOPH
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
#define RGBOp_Type RGBOp < Type >

namespace cms {
    namespace lcd {
	namespace calibrate {
	    template < class Type > class RGBOp {
	      private:
		bptr < Type > source;
		std::vector < bptr < RGBOp_Type > >opvector;
	      protected:
		bptr < Type > createInstance(bptr < Type > source) {
		    bptr < Type >  rendering = getRendering(source);
		     foreach(bptr < RGBOp_Type > op, opvector) {
			rendering = op->createInstance(rendering);
		    };
		     return rendering;
		};
		virtual bptr < Type > getRendering(bptr < Type > source)
		= 0;

	      public:
		 RGBOp() {
		};
	      RGBOp(bptr < Type > source):source(source) {
		};
		bptr < Type > createInstance() {
		    return createInstance(source);
		};
		void setSource(bptr < Type > source) {
		    this->source = source;
		};
		void addOp(bptr < RGBOp_Type > op) {
		    opvector.push_back(op);
		};
	    };

	    /*template <> class RGBGammaOp_ < RGBGamma > {

	       }; */

	    /*template <> class TestOp:public RGBOp < RGBGamma_ptr > {
	       }; */


	};
    };
};
#endif

