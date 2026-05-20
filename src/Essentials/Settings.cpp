#include "Settings.h"

namespace Settings
{
	std::map<int, float> Setting = {
        {Names::RENDERDISTANCE, 500},
        {Names::MAXIMAL_INSTANCES, 10000},
        {Names::SHADOW_SIZE, 4096},
        {Names::SHADOW_DISTANCE_FACTOR, 1},
        {Names::MAXIMUMFALLDISTANCE, -1000},
        {Names::WIREFRAMED, 0},
        {Names::WORLD_SIZE, 50000},
        {Names::EDITMODE, 0},
        {Names::NUM_ACTIVE_LIGHTS, 4},
        {Names::REFLECTION_SIZE, 512},
    };

	float getSetting(int SettingName) 			{ return Setting[SettingName]; }
	void setSetting(int SettingName, float Value) { Setting[SettingName] = Value; }
}