#pragma once
#include <map>

namespace Settings
{
	enum Names
	{
		RENDERDISTANCE,
		MAXIMAL_INSTANCES,
		WIREFRAMED,
		SHADOW_SIZE,
		SHADOW_DISTANCE_FACTOR,
		MAXIMUMFALLDISTANCE,
		WORLD_SIZE,
		SHOWDEBUGINFO,
		EDITMODE,
		NUM_ACTIVE_LIGHTS,
		REFLECTION_SIZE,
	};
	extern std::map<int, float> Setting;

	extern void setSetting(int SettingName, float Value);
	extern float getSetting(int SettingName);
}