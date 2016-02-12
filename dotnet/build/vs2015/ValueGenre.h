#include "Notification.h"

using namespace OpenZWave;

namespace OpenZWaveDotNet
{
	public enum class ValueGenre
	{
		Basic = ValueID::ValueGenre_Basic,
		User = ValueID::ValueGenre_User,
		Config = ValueID::ValueGenre_Config,
		System = ValueID::ValueGenre_System
	};
}
