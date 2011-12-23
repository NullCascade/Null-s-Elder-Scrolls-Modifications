#include "nullCommon.h"


uint
Skyrim::GetVersion(
	)
{
	return *(DWORD*)0x00DDDC00;
}


bool
Skyrim::UsingVersion(
	Skyrim::Version i_Version
	)
{
	return ( GetVersion() == i_Version );
}


BYTE*
Skyrim::GetAddrDrawMenus(
	)
{
	switch ( GetVersion() ) {
		case Skyrim::v1_1_21_0: return (BYTE*)( Skyrim::Addresses::DrawMenus_v1_1_21_0 );
		case Skyrim::v1_2_12_0: return (BYTE*)( Skyrim::Addresses::DrawMenus_v1_2_12_0 );
		case Skyrim::v1_3_7_0: return (BYTE*)( Skyrim::Addresses::DrawMenus_v1_3_7_0 );
		case Skyrim::v1_3_10_0: return (BYTE*)( Skyrim::Addresses::DrawMenus_v1_3_10_0 );
	}
	return NULL;
}


BYTE*
Skyrim::GetAddrIsRenaming(
	)
{
	switch ( GetVersion() ) {
		case Skyrim::v1_1_21_0: return (BYTE*)( Skyrim::Addresses::IsRenaming_v1_1_21_0 );
		case Skyrim::v1_2_12_0: return (BYTE*)( Skyrim::Addresses::IsRenaming_v1_2_12_0 );
		case Skyrim::v1_3_7_0: return (BYTE*)( Skyrim::Addresses::IsRenaming_v1_3_7_0 );
		case Skyrim::v1_3_10_0: return (BYTE*)( Skyrim::Addresses::IsRenaming_v1_3_10_0 );
	}
	return NULL;
}


BYTE*
Skyrim::GetAddrPerkPoints(
	)
{
	switch ( GetVersion() ) {
		case Skyrim::v1_1_21_0: return (BYTE*)( (DWORD)( Game::GetPlayer() ) + Skyrim::Offsets::PerkPoints_v1_1_21_0 );
		case Skyrim::v1_2_12_0: return (BYTE*)( (DWORD)( Game::GetPlayer() ) + Skyrim::Offsets::PerkPoints_v1_2_12_0 );
		case Skyrim::v1_3_7_0: return (BYTE*)( (DWORD)( Game::GetPlayer() ) + Skyrim::Offsets::PerkPoints_v1_3_7_0 );
		case Skyrim::v1_3_10_0: return (BYTE*)( (DWORD)( Game::GetPlayer() ) + Skyrim::Offsets::PerkPoints_v1_3_10_0 );
	}
	return NULL;
}


float*
Skyrim::GetAddrSettingHUDOpacity(
	)
{
	switch ( GetVersion() ) {
		case Skyrim::v1_1_21_0: return (float*)( Skyrim::Addresses::SettingHUDOpacity_v1_1_21_0 );
		case Skyrim::v1_2_12_0: return (float*)( Skyrim::Addresses::SettingHUDOpacity_v1_2_12_0 );
		case Skyrim::v1_3_7_0: return (float*)( Skyrim::Addresses::SettingHUDOpacity_v1_3_7_0 );
		case Skyrim::v1_3_10_0: return (float*)( Skyrim::Addresses::SettingHUDOpacity_v1_3_10_0 );
	}
	return NULL;
}


float*
Skyrim::GetAddrHudOpacity(
	)
{
	// Get base offset.
	DWORD dwPtr = NULL;
	switch ( GetVersion() ) {
		case Skyrim::v1_1_21_0:
			dwPtr = *(PDWORD)( Skyrim::Addresses::HUDOpacityBase_v1_1_21_0 );
			break;
		case Skyrim::v1_2_12_0:
			dwPtr = *(PDWORD)( Skyrim::Addresses::HUDOpacityBase_v1_2_12_0 );
			break;
		case Skyrim::v1_3_7_0:
			dwPtr = *(PDWORD)( Skyrim::Addresses::HUDOpacityBase_v1_3_7_0 );
			break;
		case Skyrim::v1_3_10_0:
			dwPtr = *(PDWORD)( Skyrim::Addresses::HUDOpacityBase_v1_3_10_0 );
			break;
		default:
			return NULL;
	}

	// Follow memory to the pointer to the value.
	dwPtr = *(PDWORD)( dwPtr + 0x4 );
	dwPtr = *(PDWORD)( dwPtr + 0x2C );
	dwPtr = *(PDWORD)( dwPtr + 0x4 );
	dwPtr = *(PDWORD)( dwPtr + 0x15C );
	return (float*)( dwPtr + 0x3C );
}


// SafeGetKeyPressed - Checks if the key is pressed, with checks for menu mode and modifiers.
bool
IO::SafeGetKeyPressed(
	BYTE i_Key,
	bool i_AllowMenuMode,
	bool i_Control,
	bool i_Shift,
	bool i_Alt
	)
{
	// Don't enable if the key is set to 0x00.
	if ( i_Key == NULL ) return false;

	// Don't enable in menu mode.
	if ( !i_AllowMenuMode && Utility::IsInMenuMode() ) return false;
	if ( ( !i_AllowMenuMode ) && ( Skyrim::GetAddrIsRenaming() ) && ( *Skyrim::GetAddrIsRenaming() == 1 ) ) return false;

	// Are the control keys pressed?
	if ( i_Control && !GetKeyPressed( 0xA2 ) ) return false;
	if ( i_Shift && !GetKeyPressed( 0xA0 ) ) return false;
	if ( i_Alt && !GetKeyPressed( 0xA4 ) ) return false;

	// Otherwise, check as normal.
	return GetKeyPressed( i_Key );
}