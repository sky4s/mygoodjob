#ifndef BINDERH
#define BINDERH

//C系統文件

//C++系統文件
#include <map>
//其他庫頭文件
#include <vcl.h>
#include <Controls.hpp>
//本項目內頭文件
#include <java/lang.h>

typedef std::multimap < TControl *, uiset_ptr >::const_iterator SetterItrator;
typedef std::pair < SetterItrator, SetterItrator > Range;

namespace gui {
    namespace util {
	class UIValueSetter {
	  public:
	    virtual void set(TObject * sender) = 0;
	};

	class Edit2ScrollBarSetter:public UIValueSetter {
	  protected:
	    TEdit * edit;
	    TScrollBar *scrollBar;
	  public:
	    Edit2ScrollBarSetter(TEdit * edit, TScrollBar * scrollBar);
	    virtual void set(TObject * sender);
	};

	class Label2ScrollBarSetter:public UIValueSetter {
	  protected:
	    TLabel * label;
	    TScrollBar *scrollBar;
	  public:
	    Label2ScrollBarSetter(TLabel * label, TScrollBar * scrollBar);
	    virtual void set(TObject * sender);
	};

	class ScrollBar2ScrollBarSetter:public UIValueSetter {
	  protected:
	    TScrollBar * scrollBar1, *scrollBar2;
	  public:
	    ScrollBar2ScrollBarSetter(TScrollBar * scrollBar1, TScrollBar * scrollBar2);
	    virtual void set(TObject * sender);
	};

	class Edit2EditSetter:public UIValueSetter {
	  protected:
	    TEdit * edit1, *edit2;
	  public:
	    Edit2EditSetter(TEdit * edit1, TEdit * edit2);
	    virtual void set(TObject * sender);
	};


	class MultiUIBinder {
	  private:
	    std::multimap < TControl *, uiset_ptr > setterMap;
	  public:
	    MultiUIBinder();
	    void active(TObject * sender);
	    void bind(TEdit * edit, TScrollBar * scrollBar);
	    void bind(TEdit * edit1, TEdit * edit2);
	    void bind(TScrollBar * scrollBar1, TScrollBar * scrollBar2);
	    void bind(TLabel * label, TScrollBar * scrollBar);
	    void bind(TEdit * edit, TScrollBar * scrollBaruiset_ptr, uiset_ptr setter);
	    void bind(TEdit * edit1, TEdit * edit2, uiset_ptr setter);
	    void bind(TScrollBar * scrollBar1, TScrollBar * scrollBar2, uiset_ptr setter);
	    void bind(TLabel * label, TScrollBar * scrollBar, uiset_ptr setter);
	};
    };
};

#endif

