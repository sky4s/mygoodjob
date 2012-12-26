#ifndef RGBOPH
#define RGBOPH
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>
#define RGBOp_Type RGBOp < Type >

namespace cms {
    namespace lcd {
	namespace calibrate {
	    template < class Type > class RGBOp {
	      private:
		std::vector < bptr < RGBOp_Type > >opvector;
	      protected:
		bptr < Type > source;
		bptr < Type > createInstance(bptr < Type > source) {
		    bptr < Type > rendering = getRendering(source);
		    foreach(bptr < RGBOp_Type > op, opvector) {
			rendering = op->createInstance(rendering);
			if (0 != errorMessage.size()) {
			    errorMessage = errorMessage  + "\n" + op->errorMessage;
			} else {
			    errorMessage = op->errorMessage;
			};
		    };
		    return rendering;
		};
		virtual bptr < Type > getRendering(bptr < Type > source) {
		    return source;
		};
		std::string errorMessage;
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
		std::string getErrorMessage() {
		    return errorMessage;
		}
	    };

	};
    };
};
#endif

