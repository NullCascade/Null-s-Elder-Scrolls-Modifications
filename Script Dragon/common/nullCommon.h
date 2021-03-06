#pragma once

#include "types.h"
#include "skyscript.h"

// Handy settings.
namespace Skyrim {
	enum Version {
		v1_1_21_0 = 0x83EC8B55,
		v1_1_21_0_rus = 0xE04D8BE0,
		v1_2_12_0 = 0x8B500C45,
		v1_3_7_0 = 0XF8458900,
		v1_3_10_0 = 0xE04589FF,
		v1_4_21_0 = 0x89078b08
	};


	// Addresses.
	namespace Addresses {
		enum DrawMenus {
			DrawMenus_v1_1_21_0 = 0x0156D500,
			DrawMenus_v1_2_12_0 = 0x015997D0,
			DrawMenus_v1_3_7_0 = 0x015807E0,
			DrawMenus_v1_3_10_0 = 0x015817E0,
			DrawMenus_v1_4_21_0 = 0x0138D580
		};
		enum IsRenaming {
			IsRenaming_v1_1_21_0 = 0x01565D68,
			IsRenaming_v1_2_12_0 = 0x01592028,
			IsRenaming_v1_3_7_0 = 0x01579038,
			IsRenaming_v1_3_10_0 = 0x0157A038,
			IsRenaming_v1_4_21_0 = 0x01387358
		};
		enum SettingHUDOpacity {
			SettingHUDOpacity_v1_1_21_0 = 0x0156F514,
			SettingHUDOpacity_v1_2_12_0 = 0x0159BCAC,
			SettingHUDOpacity_v1_3_7_0 = 0x01582CBC,
			SettingHUDOpacity_v1_3_10_0 = 0x01583CBC,
			SettingHUDOpacity_v1_4_21_0 = 0x01285EFC
		};
		enum HUDOpacityBase {
			HUDOpacityBase_v1_1_21_0 = 0x01565CDC,
			HUDOpacityBase_v1_2_12_0 = 0x01591F9C,
			HUDOpacityBase_v1_3_7_0 = 0x01578FAC,
			HUDOpacityBase_v1_3_10_0 = 0x01579FAC,
			HUDOpacityBase_v1_4_21_0 = 0x015872CC
		};
	}

	// Offsets.
	namespace Offsets {
		enum PerkPoints {
			PerkPoints_v1_1_21_0 = 0x6D1,
			PerkPoints_v1_2_12_0 = 0x6C9,
			PerkPoints_v1_3_7_0 = 0x6C9,
			PerkPoints_v1_3_10_0 = 0x6C9,
			PerkPoints_v1_4_21_0 = 0x6C9
		};
	}


	// Get version.
	uint
	GetVersion(
		);


	// Running Version
	bool
	UsingVersion(
		Skyrim::Version i_Version
		);


	// Certain addresses.
	BYTE*
	GetAddrDrawMenus(
		);

	BYTE*
	GetAddrIsRenaming(
		);

	BYTE*
	GetAddrPerkPoints(
		);
	
	float*
	GetAddrSettingHUDOpacity(
		);

	float*
	GetAddrHudOpacity(
		);
}

namespace IO {
	// SafeGetKeyPressed - Checks if the key is pressed, with checks for menu mode and modifiers.
	bool
	SafeGetKeyPressed(
		BYTE i_Key,
		bool i_AllowMenuMode = false,
		bool i_Control = false,
		bool i_Shift = false,
		bool i_Alt = false
		);
}