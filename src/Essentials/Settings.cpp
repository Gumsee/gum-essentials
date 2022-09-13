#include "Settings.h"
#include <System/IO/Output.h>

namespace Settings
{
	std::map<int, int> Setting;

	int getSetting(int SettingName) 			{ return Setting[SettingName]; }
	void setSetting(int SettingName, int Value) { Setting[SettingName] = Value; }


	void init()
	{
		Gum::Output::log("Initializing Settings...");
		if ( Setting.find(Names::RENDERDISTANCE) == Setting.end() ) 		{ setSetting(Names::RENDERDISTANCE, 5000); }
		if ( Setting.find(Names::MAXIMAL_INSTANCES) == Setting.end() ) 		{ setSetting(Names::MAXIMAL_INSTANCES, 10000); }
		if ( Setting.find(Names::SHADOW_SIZE) == Setting.end() ) 			{ setSetting(Names::SHADOW_SIZE, 8096); }
		if ( Setting.find(Names::MAXIMUMFALLDISTANCE) == Setting.end() ) 	{ setSetting(Names::MAXIMUMFALLDISTANCE, -1000); }
		if ( Setting.find(Names::WIREFRAMED) == Setting.end() ) 			{ setSetting(Names::WIREFRAMED, 0); }
		if ( Setting.find(Names::WORLD_SIZE) == Setting.end() ) 			{ setSetting(Names::WORLD_SIZE, 50000); }
		if ( Setting.find(Names::EDITMODE) == Setting.end() ) 				{ setSetting(Names::EDITMODE, 0); }
		if ( Setting.find(Names::NUM_ACTIVE_LIGHTS) == Setting.end() ) 		{ setSetting(Names::NUM_ACTIVE_LIGHTS, 4); }
		if ( Setting.find(Names::REFLECTION_SIZE) == Setting.end() ) 		{ setSetting(Names::REFLECTION_SIZE, 512); }
	}
}