//-----------------------------------------------------------------------------
//
//      ZWOptions.cpp
//
//      Cli/C++ wrapper for the C++ OpenZWave Options class
//
//		Copyright (c) 2010 Mal Lansell <openzwave@lansell.org>
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
#include "ZWOptions.h"
#include "Misc.h"

using namespace OpenZWaveWinRT;
using namespace OpenZWave;
using namespace DsbCommon;
//using namespace Runtime::InteropServices;

//-----------------------------------------------------------------------------
//	<ZWOptions::Create>
//	Create the unmanaged Options singleton object
//-----------------------------------------------------------------------------
void ZWOptions::Create
(
	Platform::String^ _configPath,
	Platform::String^	_userPath,
	Platform::String^	_commandLine
	)
{
	// Create the Manager singleton
	Options::Create( ConvertTo<string>(_configPath), ConvertTo<string>(_userPath), ConvertTo<string>(_commandLine) );
}

//-----------------------------------------------------------------------------
// <ZWOptions::AddOptionBool>
// Add a boolean option to the program
//-----------------------------------------------------------------------------
bool ZWOptions::AddOptionBool
( 
	Platform::String^ _name,
	bool _default
)
{ 
	return Options::Get()->AddOptionBool(ConvertTo<string>(_name), _default);
}

//-----------------------------------------------------------------------------
// <ZWOptions::AddOptionInt>
// Add an integer option to the program
//-----------------------------------------------------------------------------
bool ZWOptions::AddOptionInt
(
	Platform::String^ _name,
	int32 _default
	)
{	
	return Options::Get()->AddOptionInt(ConvertTo<string>(_name), _default);
}

//-----------------------------------------------------------------------------
// <ZWOptions::AddOptionString>
// Add a string option to the program
//-----------------------------------------------------------------------------
bool ZWOptions::AddOptionString
(
	Platform::String^ _name,
	Platform::String^ _default,
	bool _append
	)
{	
	return Options::Get()->AddOptionString(ConvertTo<string>(_name), ConvertTo<string>(_default), _append);
}

//-----------------------------------------------------------------------------
// <ZWOptions::GetOptionAsBool>
// Gets the value of a boolean option
//-----------------------------------------------------------------------------
//bool ZWOptions::GetOptionAsBool
//(
//	String^ _name,
//	[Out] System::Boolean %o_value
//	)
//{
//	bool value;
//	if (Options::Get()->GetOptionAsBool((const char*)(Marshal::StringToHGlobalAnsi(_name)).ToPointer(), &value))
//	{
//		o_value = value;
//		return true;
//	}
//	return false;
//}
//
//-----------------------------------------------------------------------------
// <ZWOptions::GetOptionAsInt>
// Gets the value of an integer option
//-----------------------------------------------------------------------------
bool ZWOptions::GetOptionAsInt
(
	Platform::String^ _name,
	int32* o_value
	)
{
	int32 value;
	if (Options::Get()->GetOptionAsInt(ConvertTo<string>(_name), &value))
	{
		*o_value = value;
		return true;
	}
	return false;
}
//
////-----------------------------------------------------------------------------
//// <ZWOptions::GetOptionAsString>
//// Gets the value of a string option
////-----------------------------------------------------------------------------
//bool ZWOptions::GetOptionAsString
//(
//	String^ _name,
//	[Out] String^ %o_value
//	)
//{
//	string value;
//	if (Options::Get()->GetOptionAsString((const char*)(Marshal::StringToHGlobalAnsi(_name)).ToPointer(), &value))
//	{
//		o_value = gcnew String(value.c_str());
//		return true;
//	}
//	return false;
//}
//
////-----------------------------------------------------------------------------
//// <ZWOptions::GetOptionType>
//// Gets the type of the value stored by the option
////-----------------------------------------------------------------------------
//ZWOptionType ZWOptions::GetOptionType
//(
//	String^ _name
//	)
//{
//	const char* name = (const char*)(Marshal::StringToHGlobalAnsi(_name)).ToPointer();
//	return (ZWOptionType)Enum::ToObject(ZWOptionType::typeid, Options::Get()->GetOptionType(name));
//}





