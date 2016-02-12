#include "Notification.h"

using namespace OpenZWave;

namespace OpenZWaveDotNet
{
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
}