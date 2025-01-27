/***************************************************************************
 *   Copyright (C) 2005 by Jeff Ferr                                       *
 *   root@sat                                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "jconsolehandler.h"

#include <iostream>
#include <string>
#include <sstream>

#include <time.h>

namespace       jlogger {

    ConsoleHandler::ConsoleHandler():jlogger::StreamHandler() {
	jcommon::Object::SetClassName("jlogger::ConsoleHandler");
    }
    ConsoleHandler::~ConsoleHandler() {
    }

    void            ConsoleHandler::WriteRecord(LogRecord * log) {
#ifndef _BCB
	_mutex.Lock();
#endif

	if (log->GetType() == INFO_LOGGER) {
	    std::cout << log->GetRecord() << std::flush;
	} else {
	    std::cerr << log->GetRecord() << std::flush;
	}
#ifndef _BCB
	_mutex.Unlock();
#endif
    }

}

