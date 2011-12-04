// Script Dragon includes.
#include "common\skyscript.h"
#include "common\obscript.h"
#include "common\types.h"
#include "common\enums.h"
#include "common\plugin.h"
#include "common\nullCommon.h"


// Definitions.
#define CONFIG_FILE			"toggleui.ini"


// GetHUDOpacity - Reads the HUD opacity value from memory.
float
GetHUDOpacity(
	)
{
	return *(float*)( Skyrim::GetAddrSettingHUDOpacity() );
}


// SetHUDOpacity - Sets the hud opacity. Provided by HitachiHex.
void
SetHUDOpacity(
	float i_Value
	)
{
	*(float*)( Skyrim::GetAddrHudOpacity() ) = i_Value;
}


// SetShowUI - Enables/disables entire UI drawing.
void
SetShowUI(
	unsigned int i_Value
	)
{
	*(unsigned char*)( Skyrim::GetAddrDrawMenus() ) = i_Value;
}


// SetShowCompass - Enable/disables the rendering of the compass.
void
SetShowCompass(
	bool i_Value
	)
{
	Utility::SetINIBool( "bShowCompass:interface", i_Value );
}


// SetShowQuestMarkers - Enable/disables the rendering of compass(/map?) quest markers.
void
SetShowQuestMarkers(
	bool i_Value
	)
{
	Utility::SetINIBool( "bShowQuestMarkers:gameplay", i_Value );
}


// SetShowFloatingQuestMarkers - Enable/disables the rendering of floating quest markers.
void
SetShowFloatingQuestMarkers(
	bool i_Value
	)
{
	Utility::SetINIBool( "bShowFloatingQuestMarkers:gameplay", i_Value );
}


// Plugin entry point.
void
main(
	)
{
	//  Read initialization file.
	bool showUI = ( IniReadInt( CONFIG_FILE, "defaults", "ui", 1 ) != 0 );
	bool showCompass = ( IniReadInt( CONFIG_FILE, "defaults", "compass", 1 ) != 0 );
	bool showQuestMarkers = ( IniReadInt( CONFIG_FILE, "defaults", "quest_markers", 1 ) != 0 );
	bool showFloatingQuestMarkers = ( IniReadInt( CONFIG_FILE, "defaults", "float_quest_markers", 1 ) != 0 );
	BYTE keyToggleUI = IniReadInt( CONFIG_FILE, "keys", "ui", 0x00 );
	BYTE keyToggleCompass = IniReadInt( CONFIG_FILE, "keys", "compass", 0x00 );
	BYTE keyToggleQuestMarkers = IniReadInt( CONFIG_FILE, "keys", "quest_markers", 0x00 );
	BYTE keyToggleFloatingQuestMarkers = IniReadInt( CONFIG_FILE, "keys", "float_quest_markers", 0x00 );

	// Keep track of the menu state.
	SetShowCompass( showCompass );
	SetShowQuestMarkers( showQuestMarkers );
	SetShowFloatingQuestMarkers( showFloatingQuestMarkers );
	SetHUDOpacity( showUI ? GetHUDOpacity() : 0.0 );

	// Handle multiple keys at once.
	bool keyPressWait = false;
	
	// Main plugin loop.
	while ( true ) {
		// Wait if we just got a key event.
		if ( keyPressWait ) {
			Wait( 250 );
			keyPressWait = false;
		}

		// Enable/disable UI.
		if ( IO::SafeGetKeyPressed( keyToggleUI ) ) {
			// Toggle menus/UI, then wait half a second.
			showUI = !showUI;
			SetHUDOpacity( showUI ? GetHUDOpacity() : 0.0 );
			keyPressWait = true;
		}

		// Enable/disable compass.
		if ( IO::SafeGetKeyPressed( keyToggleCompass ) ) {
			showCompass = !showCompass;
			SetShowCompass( showCompass );
			keyPressWait = true;
		}

		// Enable/disable quest markers.
		if ( IO::SafeGetKeyPressed( keyToggleQuestMarkers ) ) {
			showQuestMarkers = !showQuestMarkers;
			SetShowQuestMarkers( showQuestMarkers );
			keyPressWait = true;
		}

		// Enable/disable floating quest markers.
		if ( IO::SafeGetKeyPressed( keyToggleFloatingQuestMarkers ) ) {
			showFloatingQuestMarkers = !showFloatingQuestMarkers;
			SetShowFloatingQuestMarkers( showFloatingQuestMarkers );
			keyPressWait = true;
		}
		
		// Must be called at the end of execution cycle.
		Wait(0);
	}
}

