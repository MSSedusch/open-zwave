#include "Notification.h"

using namespace OpenZWave;

namespace OpenZWaveDotNet
{
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
}
