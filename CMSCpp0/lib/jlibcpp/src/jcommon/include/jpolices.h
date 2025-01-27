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
#ifndef J_POLICES_H
#define J_POLICES_H

#include "jobject.h"

#include <string>
#include <map>

namespace jcommon {

/**
 * \brief
 * 
 * \author Jeff Ferr
 */
struct jpolice_t {
	std::string key,
		value;
	int id; // 0 - comment, 1 - id
};

class Polices : public virtual jcommon::Object{

	private:
		std::vector<struct jpolice_t> _polices;
		std::string _filename;

	public:
		Polices();
		virtual ~Polices();

		void Load(std::string filename);
		void Save();
		int GetSize();
		std::vector<struct jpolice_t> & GetPolices();
		std::string GetContent(std::string id);

};

}

#endif
