#include <includeall.h>
#pragma hdrstop
#include "RegisterFramework.h"
#include <fpga/gui_class.h>

namespace gui {
    namespace framework {
	RegisterMap::RegisterMap(std::string filename) {
	    map = AbstractBase::getStringMap(filename);
	};

	void RegisterMap::reset() {
	    map = nil_StringMap_ptr;
	};

	bptr < RegisterType > RegisterMap::getRegister(std::string regname) {
	};

	//=====================================================================

	void RegisterFramework::scanUI(TForm * form) {
	    childScan(form);
	};

	void RegisterFramework::childScan(TWinControl * ctrl) {
	    int count = ctrl->ControlCount;
	    for (int x = 0; x < count; x++) {
		TControl *child = ctrl->Controls[x];
		String name = child->Name;

		TWinControl *wctrl = dynamic_cast < TWinControl * >(child);
		if (null != wctrl) {
		    childScan(wctrl);
		    continue;
		}
	    }
	}

    };

};

