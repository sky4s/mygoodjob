#ifndef BINDERH
#define BINDERH

//C系統文件

//C++系統文件
#ifdef __BORLANDC__
# pragma pack(push, 8)
#endif

#include <map>

#ifdef __BORLANDC__
# pragma pack(pop)
#endif
//其他庫頭文件
#include <vcl.h>
#include <Controls.hpp>
//本項目內頭文件
#include <java/lang.h>

typedef std::multimap < TControl *, uiset_ptr >::const_iterator SetterIterator;
typedef std::pair < SetterIterator, SetterIterator > Range;

namespace gui {
    namespace util {

	class TextFilterIF {
	  public:
	    virtual String filter(const int value) = 0;
	};

	class UIValueSetter {
	    friend class MultiUIBinder;
	  private:
	    TextFilterIF_ptr filter;
	    FilterFunction filterFunction;
	  protected:
	    OnChangeFunction originalOnChangeFunction;
	    OnKeyPressFunction originalOnKeyPressFunction;
	    UIValueSetter();
	  public:
	    virtual void set(TObject * sender) = 0;
	    void setFilter(TextFilterIF_ptr filter);
	    void setFilterFunction(FilterFunction func);
	    String getString(int value);

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

	class StaticText2ScrollBarSetter:public UIValueSetter {
	  protected:
	    TStaticText * text;
	    TScrollBar *scrollBar;
	  public:
	    StaticText2ScrollBarSetter(TStaticText * text, TScrollBar * scrollBar);
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
	    void processOnChange(TScrollBar * scrollBar, uiset_ptr setter);
	    void __fastcall activeWithOnKeyPress(TObject * sender, const char &key);
	    void __fastcall active0(TObject * sender, bool onKeyPress, const char &key);
	  public:
	    MultiUIBinder();
	    void __fastcall active(TObject * sender);
	    void bind(TEdit * edit, TScrollBar * scrollBar);
	    void bind(TEdit * edit1, TEdit * edit2);
	    void bind(TScrollBar * scrollBar1, TScrollBar * scrollBar2);

	    void bind(TLabel * label, TScrollBar * scrollBar);
	    void bind(TextFilterIF_ptr filter, TLabel * label, TScrollBar * scrollBar);
	    void bind(FilterFunction filterFunction, TLabel * label, TScrollBar * scrollBar);

	    void bind(TStaticText * text, TScrollBar * scrollBar);
	    void bind(TextFilterIF_ptr filter, TStaticText * text, TScrollBar * scrollBar);
	    void bind(FilterFunction filterFunction, TStaticText * text, TScrollBar * scrollBar);

	    /*
	       提供custom的Setter定義
	     */
	    void bind(TControl * ctrl1, TControl * ctrl2, uiset_ptr setter);
	    int loose(TControl * ctrl);


	};
    };
};

#endif

