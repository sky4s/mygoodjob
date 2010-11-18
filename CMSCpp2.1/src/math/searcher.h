#ifndef SEARCHERH
#define SEARCHERH

//C系統文件

//C++系統文件


//其他庫頭文件

//本項目內頭文件
//#include <java/lang.h>

namespace math {
    class Searcher {
      private:

      public:
	static int sequentialSearch(double_vector_ptr a, double key);
	static int sequentialSearch(int_vector_ptr a, int key);
	static int_vector_ptr leftNearSequentialSearchAll(double_vector_ptr a, double key);
	static int leftNearSequentialSearch0(int arrayLength, int binarySearchResult);
	static int leftNearSequentialSearch(double_vector_ptr a, double key);
    };
};

#endif

