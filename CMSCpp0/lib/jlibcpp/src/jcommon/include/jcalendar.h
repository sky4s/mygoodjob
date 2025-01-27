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
 a***************************************************************************/
#ifndef J_CALENDAR_H
#define J_CALENDAR_H

#include "jobject.h"

#include <string>

#include <stdint.h>

#ifdef _BCB
#include <time.h>
#endif

namespace jcommon {

/**
 * \brief
 * 
 * \author Jeff Ferr
 */
class Calendar : public jcommon::Object{

	private:
		/** \brief Days */
		int _day;
		/** \brief Months */
		int _month;
		/** \brief Years */
		int _year;
		
		bool is_bissexto(int ano);
		
	public:
		/**
		* \brief
		*
		*/
		Calendar();
		
		/**
		* \brief
		*
		*/
		Calendar(int day, int month, int year);

		/**
		* \brief
		*
		*/
		virtual ~Calendar();

		/**
		* \brief
		*
		*/
		time_t GetTimeInSeconds();
		
		/**
		* \brief
		*
		*/
		void SetTimeInSeconds(time_t secs);
		
		/**
		* \brief
		*
		*/
		void SetTime(int day, int month, int year);
		
		/**
		* \brief
		*
		*/
		int GetDay() ;
		
		/**
		* \brief
		*
		*/
		int GetMonth();
		
		/**
		* \brief
		*
		*/
		int GetYear();
		
		/**
		* \brief
		*
		*/
		bool IsBissexto();
		
		/**
		* \brief
		*
		*/
		void AddDays(int n);
		
		/**
		* \brief
		*
		*/
		void SubDays(int n);
		
		/**
		* \brief
		*
		*/
		void IncrementDay();
		
		/**
		* \brief
		*
		*/
		void DecrementDay();
		
		/**
		* \brief
		*
		*/
		bool IsValidated();
		
		/**
		* \brief Conta os dias desta data ateh date2
		*
		*/
		int CountDays(Calendar *date2);
		
		/**
		* \brief
		*
		*/
		virtual bool Equals(Object *o);
		
		/**
		* \brief
		*
		*/
		virtual int Compare(Object *o);
		
};

}

#endif
