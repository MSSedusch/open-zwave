//-----------------------------------------------------------------------------
//
//      ZWValueID.h
//
//      Cli/C++ wrapper for the C++ OpenZWave Manager class
//
//      Copyright (c) 2010 Amer Harb <harb_amer@hotmail.com>
//
//      SOFTWARE NOTICE AND LICENSE
//
//      This file is part of OpenZWave.
//
//      OpenZWave is free software: you can redistribute it and/or modify
//      it under the terms of the GNU Lesser General Public License as published
//      by the Free Software Foundation, either version 3 of the License,
//      or (at your option) any later version.
//
//      OpenZWave is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU Lesser General Public License for more details.
//
//      You should have received a copy of the GNU Lesser General Public License
//      along with OpenZWave.  If not, see <http://www.gnu.org/licenses/>.
//
//-----------------------------------------------------------------------------


#pragma once
#include "Windows.h"
#include "ValueID.h"
#include "stdio.h"
#include "Notification.h"

//#include <msclr/auto_gcroot.h>
//#include <msclr/lock.h>

//using namespace System;
//using namespace System::Threading;
//using namespace System::Collections::Generic;
using namespace OpenZWave;
//using namespace Runtime::InteropServices;

namespace OpenZWaveWinRT 
{
	public enum class ValueType
	{
		Bool = ValueID::ValueType_Bool,
		Byte = ValueID::ValueType_Byte,
		Decimal = ValueID::ValueType_Decimal,
		Int = ValueID::ValueType_Int,
		List = ValueID::ValueType_List,
		Schedule = ValueID::ValueType_Schedule,
		Short = ValueID::ValueType_Short,
		String = ValueID::ValueType_String,
		Button = ValueID::ValueType_Button,
		Raw = ValueID::ValueType_Raw
	};

	public enum class ValueGenre
	{
		Basic = ValueID::ValueGenre_Basic,
		User = ValueID::ValueGenre_User,
		Config = ValueID::ValueGenre_Config,
		System = ValueID::ValueGenre_System
	};

	public enum class Type
	{
		ValueAdded = Notification::Type_ValueAdded,
		ValueRemoved = Notification::Type_ValueRemoved,
		ValueChanged = Notification::Type_ValueChanged,
		ValueRefreshed = Notification::Type_ValueRefreshed,
		Group = Notification::Type_Group,
		NodeNew = Notification::Type_NodeNew,
		NodeAdded = Notification::Type_NodeAdded,
		NodeRemoved = Notification::Type_NodeRemoved,
		NodeReset = Notification::Type_NodeReset,
		NodeProtocolInfo = Notification::Type_NodeProtocolInfo,
		NodeNaming = Notification::Type_NodeNaming,
		NodeEvent = Notification::Type_NodeEvent,
		PollingDisabled = Notification::Type_PollingDisabled,
		PollingEnabled = Notification::Type_PollingEnabled,
		SceneEvent = Notification::Type_SceneEvent,
		CreateButton = Notification::Type_CreateButton,
		DeleteButton = Notification::Type_DeleteButton,
		ButtonOn = Notification::Type_ButtonOn,
		ButtonOff = Notification::Type_ButtonOff,
		DriverReady = Notification::Type_DriverReady,
		DriverFailed = Notification::Type_DriverFailed,
		DriverReset = Notification::Type_DriverReset,
		EssentialNodeQueriesComplete = Notification::Type_EssentialNodeQueriesComplete,
		NodeQueriesComplete = Notification::Type_NodeQueriesComplete,
		AwakeNodesQueried = Notification::Type_AwakeNodesQueried,
		AllNodesQueriedSomeDead = Notification::Type_AllNodesQueriedSomeDead,
		AllNodesQueried = Notification::Type_AllNodesQueried,
		Notification = Notification::Type_Notification,
		DriverRemoved = Notification::Type_DriverRemoved,
		ControllerCommand = Notification::Type_ControllerCommand
	};

	public enum class Code
	{
		MsgComplete = Notification::Code_MsgComplete,
		Timeout = Notification::Code_Timeout,
		NoOperation = Notification::Code_NoOperation,
		Awake = Notification::Code_Awake,
		Sleep = Notification::Code_Sleep,
		Dead = Notification::Code_Dead,
		Alive = Notification::Code_Alive
	};

	public ref class ZWValueID sealed
	{	

	public:
		

		

		/**
		 * Create a ZWValue ID from its component parts.
		 * This method is provided only to allow ValueIDs to be saved and recreated by the application.  Only
		 * ValueIDs that have been reported by OpenZWave notifications should ever be used.
		 * \param homeId Home ID of the PC Z-Wave Controller that manages the device.
		 * \param nodeId Node ID of the device reporting the value.
		 * \param genre classification of the value to enable low level system or configuration parameters to be filtered out.
		 * \param commandClassId ID of command class that creates and manages this value.
		 * \param instance Instance index of the command class.
		 * \param valueIndex Index of the value within all the values created by the command class instance.
		 * \param type Type of value (bool, byte, string etc).
		 * \return The ValueID.
		 * \see ValueID
		 */
		ZWValueID
		( 
			uint32 homeId,
			uint8 nodeId,
			ValueGenre genre,
			uint8 commandClassId,
			uint8 instance,
			uint8 valueIndex,
			ValueType type,
			uint8 pollIntensity
		)
		{
			m_valueId = new ValueID( homeId, nodeId, (ValueID::ValueGenre)genre, commandClassId, instance, valueIndex, (ValueID::ValueType)type );
		}


		virtual ~ZWValueID()
		{ 
			delete m_valueId;
		}


		//

		uint32		GetHomeId()			{ return m_valueId->GetHomeId(); }
		uint8		GetNodeId()			{ return m_valueId->GetNodeId(); }
		//ValueGenre	GetGenre()			{ return (ValueGenre)Enum::ToObject( ValueGenre::typeid, m_valueId->GetGenre() ); }
		uint8		GetCommandClassId()	{ return m_valueId->GetCommandClassId(); }
		uint8		GetInstance()		{ return m_valueId->GetInstance(); }
		uint8		GetIndex()			{ return m_valueId->GetIndex(); }
		uint32	GetValueType()		{ return (uint32)m_valueId->GetType(); }
		uint64		GetId()				{ return m_valueId->GetId(); }

		// Comparison Operators
		//bool operator ==	( ZWValueID^ _other ){ return( (*m_valueId) == (*_other->m_valueId) ); }
		//bool operator !=	( ZWValueID^ _other ){ return( (*m_valueId) != (*_other->m_valueId) ); }
		//bool operator <		( ZWValueID^ _other ){ return( (*m_valueId) < (*_other->m_valueId) ); }
		//bool operator >		( ZWValueID^ _other ){ return( (*m_valueId) > (*_other->m_valueId) ); }

	internal:
		ZWValueID(ValueID const& valueId)
		{
			m_valueId = new ValueID(valueId);
		}

		ValueID CreateUnmanagedValueID() { return ValueID(*m_valueId); }
		ValueID* m_valueId;
	};
}
