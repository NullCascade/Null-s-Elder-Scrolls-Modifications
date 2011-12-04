#pragma once

#include "types.h"
#include "skyscript.h"

// Handy settings.
namespace Skyrim {
	enum Version {
		v1_1_21_0 = 0x83EC8B55,
		v1_1_21_0_rus = 0xE04D8BE0,
		v1_2_12_0 = 0x8B500C45
	};


	// Addresses.
	namespace Addresses {
		enum IsRenaming {
			IsRenaming_v1_1_21_0 = 0x01565D68,
			IsRenaming_v1_2_12_0 = 0x01592028
		};
	}

	// Offsets.
	namespace Offsets {
		enum PerkPoints {
			PerkPoints_v1_1_21_0 = 0x6D1,
			PerkPoints_v1_2_12_0 = 0x6c9
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
	uint
	GetAddrIsRenaming(
		);

	uint
	GetAddrPerkPoints(
		);
}

namespace IO {
	// SafeGetKeyPressed - Checks if the key is pressed, with checks for menu mode and modifiers.
	bool
	SafeGetKeyPressed(
		BYTE i_Key,
		bool i_AllowMenuMode = true,
		bool i_Control = false,
		bool i_Shift = false,
		bool i_Alt = false
		);
}