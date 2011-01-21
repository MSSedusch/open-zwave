//-----------------------------------------------------------------------------
//
//	Clock.h
//
//	Implementation of the Z-Wave COMMAND_CLASS_CLOCK
//
//	Copyright (c) 2010 Mal Lansell <openzwave@lansell.org>
//
//	SOFTWARE NOTICE AND LICENSE
//
//	This file is part of OpenZWave.
//
//	OpenZWave is free software: you can redistribute it and/or modify
//	it under the terms of the GNU Lesser General Public License as published
//	by the Free Software Foundation, either version 3 of the License,
//	or (at your option) any later version.
//
//	OpenZWave is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU Lesser General Public License for more details.
//
//	You should have received a copy of the GNU Lesser General Public License
//	along with OpenZWave.  If not, see <http://www.gnu.org/licenses/>.
//
//-----------------------------------------------------------------------------

#ifndef _Clock_H
#define _Clock_H

#include "CommandClass.h"

namespace OpenZWave
{
	class ValueByte;
	class ValueList;

	/** \brief Implements COMMAND_CLASS_CLOCK (0x81), a Z-Wave device command class.
	 */
	class Clock: public CommandClass
	{
	public:
		static CommandClass* Create( uint32 const _homeId, uint8 const _nodeId ){ return new Clock( _homeId, _nodeId ); }
		virtual ~Clock(){}

		static uint8 const StaticGetCommandClassId(){ return 0x81; }
		static string const StaticGetCommandClassName(){ return "COMMAND_CLASS_CLOCK"; }

		// From CommandClass
		virtual bool RequestState( uint32 const _requestFlags );
		virtual void RequestValue( uint8 const _index = 0 );
		virtual uint8 const GetCommandClassId()const{ return StaticGetCommandClassId(); }
		virtual string const GetCommandClassName()const{ return StaticGetCommandClassName(); }
		virtual bool HandleMsg( uint8 const* _data, uint32 const _length, uint32 const _instance = 1 );
		virtual bool SetValue( Value const& _value );

	protected:
		virtual void CreateVars( uint8 const _instance );

	private:
		Clock( uint32 const _homeId, uint8 const _nodeId ): CommandClass( _homeId, _nodeId ){}

		ValueInstances<ValueList>	m_day;
		ValueInstances<ValueByte>	m_hour;
		ValueInstances<ValueByte>	m_minute;
	};

} // namespace OpenZWave

#endif
