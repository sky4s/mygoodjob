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
#include "jbitoutputstream.h"
#include "jfileoutputstream.h"
#include "joutofboundsexception.h"
#include "jioexception.h"

#include <iostream>
#include <string>
#include <sstream>

#include <time.h>

namespace jio {

BitOutputStream::BitOutputStream(std::string filename):
	OutputStream()
{
    jcommon::Object::SetClassName("jio::BitOutputStream");
    jcommon::Object::SetClassName("jio::OutputStream");
	
    stream = NULL;
	haveByte = false;
	show = false;
    bitCount = 0;
	currentByte = 0;
	
	try {
		stream = new FileOutputStream(filename);
	} catch (...) {
		stream = NULL;

		throw IOException("Cannot open file in BitInputStream");
	}
}

BitOutputStream::BitOutputStream(OutputStream *os):
	OutputStream()
{
    jcommon::Object::SetClassName("jio::BitOutputStream");
    jcommon::Object::SetClassName("jio::OutputStream");
	
	if ((void *)os == NULL) {
		throw IOException("Null pointer exception");
	}

	stream = os;
	haveByte = false;
	show = false;
    bitCount = 0;
	currentByte = 0;
}

BitOutputStream::~BitOutputStream()
{
	if (stream != NULL) {
		delete stream;
	}
}

bool BitOutputStream::IsEmpty()
{
	return Available() == 0;
}

int64_t BitOutputStream::Available()
{
	return 0LL;
}

int BitOutputStream::Write(int b)
{
	return stream->Write(b);
}

int64_t BitOutputStream::Write(char *b, int64_t size)
{
	return stream->Write(b, size);
}

int64_t BitOutputStream::Flush()
{
	while (bitCount > 0) {
		WriteBit(1);
	}
	
	stream->Flush();

	return 1LL;
}

void BitOutputStream::Close()
{
	stream->Close();
}

void BitOutputStream::WriteBit(int bit)
{
	bit = (bit==0)?0:1;
	
	currentByte = currentByte << 1 | bit;
	bitCount++;
	
	if (bitCount == 8) {
		Write(currentByte);
		currentByte = 0;
		bitCount = 0;
	}
}

void BitOutputStream::WriteBits(int bits, int num)
{
	if ((num < 0) || (num > 32)) {
		throw jcommon::OutOfBoundsException("Number of bits is out of range");
	}
	
	int mask;
	
	for (int i=num-1; i>=0; i--) {
		mask = 1 << i;
		
		WriteBit((bits & mask) / mask);
	}
}

int64_t BitOutputStream::GetSentBytes()
{
	return 0LL;
}

}

