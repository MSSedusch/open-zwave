//-----------------------------------------------------------------------------
//
//      ZWManager.cpp
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

#include "ZWManager.h"

using namespace OpenZWaveWinRT;
using namespace OpenZWave;
//using namespace Runtime::InteropServices;

//-----------------------------------------------------------------------------
//	<ZWManager::Create>
//	Create the unmanaged Manager singleton object, and add a watcher
//-----------------------------------------------------------------------------
void ZWManager::Create
(
)
{
	// Create the Manager singleton
	Manager::Create();

	// Add a notification handler
	//m_onNotification = ref new OnNotificationFromUnmanagedDelegate( this, &ZWManager::OnNotificationFromUnmanaged );
	//m_gchNotification = GCHandle::Alloc( m_onNotification ); 
	//IntPtr ip = Marshal::GetFunctionPointerForDelegate( m_onNotification );
	Manager::Get()->AddWatcher(OnNotificationFromUnmanaged, reinterpret_cast<void*>(this));

	// Add a controller state changed handler
	/*m_onStateChanged = gcnew OnControllerStateChangedFromUnmanagedDelegate( this, &ZWManager::OnControllerStateChangedFromUnmanaged );
	m_gchControllerState = GCHandle::Alloc( m_onStateChanged ); */
}

//-----------------------------------------------------------------------------
//	<ZWManager::OnNotificationFromUnmanaged>
//	Trigger an event from the unmanaged notification callback
//-----------------------------------------------------------------------------
void ZWManager::OnNotificationFromUnmanaged(Notification const* _notification, void* _context)
{
	ZWManager^ manager = reinterpret_cast<ZWManager^>(_context);
	ZWNotification^ notification = ref new ZWNotification( _notification );
	manager->OnNotification(notification);
}

//-----------------------------------------------------------------------------
//	<ZWManager::OnControllerStateChangedFromUnmanaged>
//	Trigger an event from the unmanaged controller state callback
//-----------------------------------------------------------------------------
void ZWManager::OnControllerStateChangedFromUnmanaged
(
	Driver::ControllerState _state,
	void* _context
)
{
	OnControllerStateChanged( (ZWControllerState)_state );
}

//-----------------------------------------------------------------------------
// <ZWManager::GetValueAsBool>
// Gets a value as a Bool
//-----------------------------------------------------------------------------
bool ZWManager::GetValueAsBool
( 
	ZWValueID^ id, bool* o_value
)
{ 
	bool value;
	if( Manager::Get()->GetValueAsBool(id->CreateUnmanagedValueID(), &value ) )
	{
		*o_value = value;
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
// <ZWManager::GetValueAsByte>
// Gets a value as a Byte
//-----------------------------------------------------------------------------
bool ZWManager::GetValueAsByte
( 
	ZWValueID^ id,
	BYTE* o_value
)
{ 
	uint8 value;
	if( Manager::Get()->GetValueAsByte(id->CreateUnmanagedValueID(), &value ) )
	{
		*o_value = value;
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
// <ZWManager::GetValueAsDecimal>
// Gets a value as a Decimal
//-----------------------------------------------------------------------------
//bool ZWManager::GetValueAsDecimal
//( 
//	ZWValueID^ id,
//	DECIMAL o_value
//)
//{ 
//	string value;
//	if( Manager::Get()->GetValueAsString(id->CreateUnmanagedValueID(), &value ) )
//	{
//		String^ decimal = gcnew String(value.c_str());
//		o_value = parse ::Decimal::Parse( decimal );
//		return true;
//	}
//	return false;
//}
//
//-----------------------------------------------------------------------------
// <ZWManager::GetValueAsInt>
// Gets a value as an Int32
//-----------------------------------------------------------------------------
bool ZWManager::GetValueAsInt
( 
	ZWValueID^ id,
	int32* o_value
)
{ 
	int32 value;
	if( Manager::Get()->GetValueAsInt(id->CreateUnmanagedValueID(), &value ) )
	{
		o_value = &value;
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
// <ZWManager::GetValueAsShort>
// Gets a value as an Int16
//-----------------------------------------------------------------------------
bool ZWManager::GetValueAsShort
( 
	ZWValueID^ id,
	int16* o_value
)
{ 
	int16 value;
	if( Manager::Get()->GetValueAsShort(id->CreateUnmanagedValueID(), &value ) )
	{
		o_value = &value;
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
// <ZWManager::GetValueAsString>
// Gets a value as a String
//-----------------------------------------------------------------------------
bool ZWManager::GetValueAsString
( 
	ZWValueID^ id, 
	Platform::String^* o_value
)
{ 
	string value;
	if( Manager::Get()->GetValueAsString(id->CreateUnmanagedValueID(), &value ) )
	{
		std::wstring wid_str = std::wstring(value.begin(), value.end());
		const wchar_t* w_char = wid_str.c_str();
		*o_value = ref new Platform::String(w_char);
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
// <ZWManager::GetValueListSelection>
// Gets the selected item from a list value (returning a string)
//-----------------------------------------------------------------------------
bool ZWManager::GetValueListSelection
( 
	ZWValueID^ id, 
	Platform::String^ o_value
)
{ 
	string value;
	if( Manager::Get()->GetValueListSelection(id->CreateUnmanagedValueID(), &value ) )
	{
		std::wstring wid_str = std::wstring(value.begin(), value.end());
		const wchar_t* w_char = wid_str.c_str();
		o_value = ref new Platform::String(w_char);
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
// <ZWManager::GetValueListSelection>
// Gets the selected item from a list value (returning the value)
//-----------------------------------------------------------------------------
bool ZWManager::GetValueListSelection
( 
	ZWValueID^ id, 
	int32* o_value
)
{ 
	int32 value;
	if( Manager::Get()->GetValueListSelection(id->CreateUnmanagedValueID(), &value ) )
	{
		o_value = &value;
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
// <ZWManager::GetValueListItems>
// Gets the list of items from a list value
//-----------------------------------------------------------------------------
bool ZWManager::GetValueListItems
( 
	ZWValueID^ id, 
	Platform::Array<Platform::String^>^* o_value
)
{
	vector<string> items;
	if( Manager::Get()->GetValueListItems(id->CreateUnmanagedValueID(), &items ) )
	{
		auto temp = ref new Platform::Array<Platform::String^>(items.size());
		for( uint32 i=0; i<items.size(); ++i )
		{
			std::wstring wid_str = std::wstring(items[i].begin(), items[i].end());
			const wchar_t* w_char = wid_str.c_str();
			temp[i] = ref new Platform::String(w_char);
		}
		*o_value = temp;
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
// <ZWManager::GetValueListValues>
// Gets the list of values from a list value
//-----------------------------------------------------------------------------
bool ZWManager::GetValueListValues
( 
	ZWValueID^ id, 
	Platform::Array<int>^* o_value
)
{
	vector<int32> items;
	if( Manager::Get()->GetValueListValues(id->CreateUnmanagedValueID(), &items ) )
	{		
		auto temp = ref new Platform::Array<int>(items.size());
		for( uint32 i=0; i<items.size(); ++i )
		{
			temp[i] = items[i];
		}
		*o_value = temp;
		return true;
	}
	return false;
}
//
//-----------------------------------------------------------------------------
// <ZWManager::GetNeighbors>
// Gets the neighbors for a node
//-----------------------------------------------------------------------------
uint32 ZWManager::GetNodeNeighbors
( 
	uint32 homeId,
	uint8 nodeId,
	Platform::Array<BYTE>^* o_neighbors
)
{
	uint8* neighbors;
	uint32 numNeighbors = Manager::Get()->GetNodeNeighbors( homeId, nodeId, &neighbors );
	if( numNeighbors )
	{
		auto temp = ref new Platform::Array<BYTE>(numNeighbors);
		for( uint32 i=0; i<numNeighbors; ++i )
		{
			temp[i] = neighbors[i];
		}
		delete [] neighbors;
		*o_neighbors = temp;
	}
	return numNeighbors;
}

////-----------------------------------------------------------------------------
//// <ZWManager::GetSwitchPoint>
//// Get switchpoint data from the schedule
////-----------------------------------------------------------------------------
//bool ZWManager::GetSwitchPoint
//( 
//	ZWValueID^ id,
//	uint8 idx, 
//	[Out] System::Byte %o_hours,
//	[Out] System::Byte %o_minutes,
//	[Out] System::SByte %o_setback
//)
//{
//	uint8 hours;
//	uint8 minutes;
//	int8 setback;
//	if( Manager::Get()->GetSwitchPoint( id->CreateUnmanagedValueID(), idx, &hours, &minutes, &setback ) )
//	{
//		o_hours = hours;
//		o_minutes = minutes;
//		o_setback = setback;
//		return true;
//	}
//
//	return false;
//}
//
////-----------------------------------------------------------------------------
//// <ZWManager::GetAssociations>
//// Gets the associations for a group
////-----------------------------------------------------------------------------
//uint32 ZWManager::GetAssociations
//( 
//	uint32 homeId,
//	uint8 nodeId,
//	uint8 groupIdx,
//	[Out] cli::array<Byte>^ %o_associations
//)
//{
//	uint8* associations;
//	uint32 numAssociations = Manager::Get()->GetAssociations( homeId, nodeId, groupIdx, &associations );
//	if( numAssociations )
//	{
//		o_associations = gcnew cli::array<Byte>(numAssociations);
//		for( uint32 i=0; i<numAssociations; ++i )
//		{
//			o_associations[i] = associations[i];		
//		}
//		delete [] associations;
//	}
//
//	return numAssociations;
//}
//
////-----------------------------------------------------------------------------
//// <ZWManager::BeginControllerCommand>
//// Start a controller command process
////-----------------------------------------------------------------------------
//[Obsolete("BeginControllerCommand is deprecated, please use the specialized methods instead.", true)]
//bool ZWManager::BeginControllerCommand
//(
//	uint32 homeId,
//	ZWControllerCommand command,
//	bool highPower,
//	uint8 nodeId
//)
//{
//	IntPtr ip = Marshal::GetFunctionPointerForDelegate( m_onStateChanged );
//	return( Manager::Get()->BeginControllerCommand( homeId, (Driver::ControllerCommand)command, (Driver::pfnControllerCallback_t)ip.ToPointer(), NULL, highPower, nodeId ) );
//}
//
bool ZWManager::GetNodeClassInformation
(
	uint32 homeId, 
	uint8 nodeId, 
	uint8 commandClassId, 
	Platform::String^ o_name, 
	BYTE o_version
)
{
	string value;
	uint8 version;
	if (Manager::Get()->GetNodeClassInformation(homeId, nodeId, commandClassId, &value, &version))
	{
		std::wstring wid_str = std::wstring(value.begin(), value.end());
		const wchar_t* w_char = wid_str.c_str();
		o_name = ref new Platform::String(w_char);
		o_version = version;
		return true;
	}
	return false;
}
//
////-----------------------------------------------------------------------------
//// <ZWManager::GetAllScenes>
//// Gets a list of all the SceneIds
////-----------------------------------------------------------------------------
//uint8 ZWManager::GetAllScenes
//(
//	[Out] cli::array<Byte>^ %o_sceneIds
//)
//{
//	uint8* sceneIds;
//	uint32 numScenes = Manager::Get()->GetAllScenes( &sceneIds );
//	if( numScenes )
//	{
//		o_sceneIds = gcnew cli::array<Byte>(numScenes);
//		for( uint32 i=0; i<numScenes; ++i )
//		{
//			o_sceneIds[i] = sceneIds[i];		
//		}
//		delete [] sceneIds;
//	}
//
//	return numScenes;
//}
//
////-----------------------------------------------------------------------------
//// <ZWManager::SceneGetValues>
//// Retrieves the scene's list of values
////-----------------------------------------------------------------------------
//int ZWManager::SceneGetValues
//(
//	uint8 sceneId,
//	[Out] cli::array<ZWValueID ^>^ %o_values
//)
//{
//	vector<ValueID> values;
//	uint32 numValues = Manager::Get()->SceneGetValues( sceneId, &values );
//	if( numValues )
//	{
//		o_values = gcnew cli::array<ZWValueID ^>(numValues);
//		for( uint32 i=0; i<numValues; ++i )
//		{
//			o_values[i] = gcnew ZWValueID(values[i]);		
//		}
//	}
//
//	return numValues;
//}
//
////-----------------------------------------------------------------------------
//// <ZWManager::SceneGetValueAsBool>
//// Retrieves a scene's value as a bool
////-----------------------------------------------------------------------------
//bool ZWManager::SceneGetValueAsBool
//(
//	uint8 sceneId,
//	ZWValueID^ valueId,
//	[Out] System::Boolean %o_value
//)
//{
//	bool value;
//	if( Manager::Get()->SceneGetValueAsBool( sceneId, valueId->CreateUnmanagedValueID(), &value ) )
//	{
//		o_value = value;
//		return true;
//	}
//	return false;
//}
//
//-----------------------------------------------------------------------------
// <ZWManager::SceneGetValueAsByte>
// Retrieves a scene's value as an 8-bit unsigned integer
//-----------------------------------------------------------------------------
bool ZWManager::SceneGetValueAsByte
(
	uint8 sceneId,
	ZWValueID^ valueId,
	BYTE* o_value
)
{
	uint8 value;
	if( Manager::Get()->SceneGetValueAsByte( sceneId, valueId->CreateUnmanagedValueID(), &value ) )
	{
		*o_value = value;
		return true;
	}
	return false;
}

////-----------------------------------------------------------------------------
//// <ZWManager::SceneGetValueAsDecimal>
//// Retrieves a scene's value as a decimal
////-----------------------------------------------------------------------------
//bool ZWManager::SceneGetValueAsDecimal
//(
//	uint8 sceneId,
//	ZWValueID^ valueId,
//	[Out] System::Decimal %o_value
//)
//{
//	string value;
//	if( Manager::Get()->SceneGetValueAsString( sceneId, valueId->CreateUnmanagedValueID(), &value ) )
//	{
//		String^ decimal = gcnew String(value.c_str());
//		o_value = Decimal::Parse( decimal );
//		return true;
//	}
//	return false;
//}
//
////-----------------------------------------------------------------------------
//// <ZWManager::SceneGetValueAsInt>
//// Retrieves a scene's value as a 32-bit signed integer
////-----------------------------------------------------------------------------
//bool ZWManager::SceneGetValueAsInt
//(
//	uint8 sceneId,
//	ZWValueID^ valueId,
//	[Out] System::Int32 %o_value
//)
//{
//	int32 value;
//	if( Manager::Get()->SceneGetValueAsInt( sceneId, valueId->CreateUnmanagedValueID(), &value ) )
//	{
//		o_value = value;
//		return true;
//	}
//	return false;
//}
//
////-----------------------------------------------------------------------------
//// <ZWManager::SceneGetValueAsShort>
//// Retrieves a scene's value as a 16-bit signed integer
////-----------------------------------------------------------------------------
//bool ZWManager::SceneGetValueAsShort
//(
//	uint8 sceneId,
//	ZWValueID^ valueId,
//	[Out] System::Int16 %o_value
//)
//{
//	int16 value;
//	if( Manager::Get()->SceneGetValueAsShort( sceneId, valueId->CreateUnmanagedValueID(), &value ) )
//	{
//		o_value = value;
//		return true;
//	}
//	return false;
//}
//
////-----------------------------------------------------------------------------
//// <ZWManager::SceneGetValueAsString>
//// Retrieves a scene's value as a string
////-----------------------------------------------------------------------------
//bool ZWManager::SceneGetValueAsString
//(
//	uint8 sceneId,
//	ZWValueID^ valueId,
//	[Out] String^ %o_value
//)
//{
//	string value;
//	if( Manager::Get()->SceneGetValueAsString( sceneId, valueId->CreateUnmanagedValueID(), &value ) )
//	{
//		o_value = gcnew String(value.c_str());
//		return true;
//	}
//	return false;
//}
//
////-----------------------------------------------------------------------------
//// <ZWManager::SceneGetValueListSelection>
//// Retrieves a scene's value in a list (as a string)
////-----------------------------------------------------------------------------
//bool ZWManager::SceneGetValueListSelection
//(
//	uint8 sceneId,
//	ZWValueID^ valueId,
//	[Out] String^ %o_value
//)
//{
//	string value;
//	if( Manager::Get()->SceneGetValueListSelection( sceneId, valueId->CreateUnmanagedValueID(), &value ) )
//	{
//		o_value = gcnew String(value.c_str());
//		return true;
//	}
//	return false;
//}
//
////-----------------------------------------------------------------------------
//// <ZWManager::SceneGetValueListSelection>
//// Retrieves a scene's value in a list (as a integer)
////-----------------------------------------------------------------------------
//bool ZWManager::SceneGetValueListSelection
//(
//	uint8 sceneId,
//	ZWValueID^ valueId,
//	System::Int32 %o_value
//)
//{
//	int32 value;
//	if( Manager::Get()->SceneGetValueListSelection( sceneId, valueId->CreateUnmanagedValueID(), &value ) )
//	{
//		o_value = value;
//		return true;
//	}
//	return false;
//}


