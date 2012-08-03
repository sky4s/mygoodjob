#ifndef QUANTIZERH
#define QUANTIZERH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace cms {
    namespace lcd {
	namespace calibrate {
	    /*enum QuantiType {
	       NearOriginal, Quadrant1, Quadrant3
	       }; */
	    class ColorimetricQuantizer {
	      public:
		static RGB_vector_ptr colorimetricQuantization(RGB_vector_ptr dglut, int quadrant);
	      private:
		static int_array getBestRGB(int r, int g, int b, int quadrant);
		static double_array getxy(int r, int g, int b);
		static double_array getxyPrecise(int r, int g, int b);
		static int getQuadrant(double x, double y);
	    };
	};
    };
};

#endif

