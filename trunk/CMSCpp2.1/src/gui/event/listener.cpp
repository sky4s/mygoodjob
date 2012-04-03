#include <includeall.h>
#pragma hdrstop
#include "listener.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
namespace gui {
    namespace event {

	void WindowAdapter::windowClosing(TObject * Sender, TCloseAction & Action) {
	};
	void WindowAdapter::windowActivated(TObject * Sender, TCloseAction & Action) {
	};
	void WindowAdapter::windowDeactivated(TObject * Sender, TCloseAction & Action) {
	};
	//const TCloseAction WindowAdapter::None = caNone;
    };
};

