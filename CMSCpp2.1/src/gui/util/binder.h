#ifndef BINDERH
#define BINDERH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件


namespace gui {
    namespace util {
	class UIBinder {
	  private:
	    TEdit * edit;
	    TScrollBar *scrollBar;
	  protected:
	     virtual double editToScrollBar(double value);
	    virtual double scrollBarToEdit(double value);
	  public:
	     UIBinder(TEdit * edit, TScrollBar * scrollBar);

	};
    };
};

#endif

