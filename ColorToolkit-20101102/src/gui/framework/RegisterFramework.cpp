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

	RegisterFramework::RegisterFramework() {
	    childmap = TControlVecMap_ptr(new TControlVecMap());
	};

	void RegisterFramework::scanUI(TForm * form) {
	    childScan(form);

	};

	void RegisterFramework::childScan(TWinControl * ctrl) {
	    int count = ctrl->ControlCount;
	    for (int x = 0; x < count; x++) {
		TControl *child = ctrl->Controls[x];
		String name = child->Name;
		TWinControl *parent = child->Parent;

		TControl_vector_ptr ctrlvec = (*childmap)[parent];
		if (nil_TControlVecMap_ptr == ctrlvec) {
		    ctrlvec = TControl_vector_ptr(new TControl_vector());
		}
		ctrlvec->push_back(child);
		(*childmap)[parent] = ctrlvec;

		TWinControl *wctrl = dynamic_cast < TWinControl * >(child);
		if (null != wctrl) {
		    childScan(wctrl);
		    continue;
		}
	    }
	}

    };

};

