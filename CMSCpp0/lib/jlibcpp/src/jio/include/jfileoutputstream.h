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
#ifndef J_FILEOUTPUTSTREAM_H
#define J_FILEOUTPUTSTREAM_H

#include "joutputstream.h"
#include "jfile.h"

namespace jio {

/**
 * \brief
 * 
 * \author Jeff Ferr
 */
class FileOutputStream : public jio::OutputStream{

	private:
		/** \brief Seek */
		int64_t _current;
		/** \brief */
		File *_file;
		/** \brief */
        char *_buffer;
        /** \brief */
        int _buffer_length;
        /** \brief */
		int _current_index; 
        /** \brief */
        int64_t _sent_bytes;

	public:
		/**
		 * \brief
		 * 
		 */
		FileOutputStream(std::string filename_);
		
		/**
		 * \brief
		 * 
		 */
		FileOutputStream(File *file_);
		
		/**
		 * \brief
		 *
		 */
		virtual ~FileOutputStream();

		/**
		 * \brief
		 *
		 */
		virtual bool IsEmpty();

		/**
		 * \brief
		 *
		 */
		virtual int64_t Available();

		/**
		 * \brief
		 *
		 */
		virtual int64_t GetSize();
		
		/**
		 * \brief
		 * 
		 */
		virtual int Write(int b);

		/**
		 * \brief
		 * 
		 */
		virtual int64_t Write(const char *, int64_t size);
    
		/**
		 * \brief
		 * 
		 */
		virtual int64_t Flush();

		/**
		 * \brief
		 *
		 */
		virtual void Seek(int64_t index);
		
		/**
		 * \brief
		 *
		 */
		virtual void Close();
		
		/**
		 * \brief
		 *
		 */
		int64_t GetSentBytes();

};

}

#endif
