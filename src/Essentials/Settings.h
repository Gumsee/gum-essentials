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
		MAXIMUMFALLDISTANCE,
		WORLD_SIZE,
		SHOWDEBUGINFO,
		EDITMODE,
		NUM_ACTIVE_LIGHTS,
		REFLECTION_SIZE,
	};
	extern std::map<int, int> Setting;


	extern void init();
	extern void setSetting(int SettingName, int Value);
	extern int getSetting(int SettingName);
}