#include "Settings.h"

namespace Settings
{
	std::map<int, int> Setting = {
        {Names::RENDERDISTANCE, 500},
        {Names::MAXIMAL_INSTANCES, 10000},
        {Names::SHADOW_SIZE, 4096},
        {Names::MAXIMUMFALLDISTANCE, -1000},
        {Names::WIREFRAMED, 0},
        {Names::WORLD_SIZE, 50000},
        {Names::EDITMODE, 0},
        {Names::NUM_ACTIVE_LIGHTS, 4},
        {Names::REFLECTION_SIZE, 512},
    };

	int getSetting(int SettingName) 			{ return Setting[SettingName]; }
	void setSetting(int SettingName, int Value) { Setting[SettingName] = Value; }
}