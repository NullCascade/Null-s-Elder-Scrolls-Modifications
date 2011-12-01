// Script Dragon includes.
#include "common\skyscript.h"
#include "common\obscript.h"
#include "common\types.h"
#include "common\enums.h"
#include "common\plugin.h"


// Definitions.
#define CONFIG_FILE "toggleui.ini"


// SafeGetKeyPressed - Checks if the key is pressed, but won't work if in menu mode.
bool
SafeGetKeyPressed(
	BYTE i_Key
	)
{
	// Don't enable in menu mode.
	if ( Utility::IsInMenuMode() ) return false;

	// Don't enable if the key is set to 0x00.
	if ( i_Key == 0x00 ) return false;

	// Otherwise, check as normal.
	return GetKeyPressed( i_Key );
}


// Plugin entry point.
void
main(
	)
{
	//  Read initialization file.
	BYTE keyToggleUI = IniReadInt( CONFIG_FILE, "general", "toggleKey", 0xDD );
	BYTE keyScreenshot = IniReadInt( CONFIG_FILE, "screenshot", "screenshot_key", 0x00 );
	bool turnOffForScreenshots = ( IniReadInt( CONFIG_FILE, "screenshot", "auto_disable", 0 ) ==  1 );

	// Keep track of the menu state.
	bool menusDisabled = false;
	
	// Main plugin loop.
	while ( true ) {
		// Trigger on bound toggle key.
		if ( SafeGetKeyPressed( keyToggleUI ) ) {
			// Toggle menus/UI, then wait half a second.
			Debug::ToggleMenus();
			menusDisabled = !menusDisabled;
			Wait( 500 );
		}

		// Taking screenshot?
		if ( turnOffForScreenshots && !menusDisabled && SafeGetKeyPressed( keyScreenshot ) ) {
			Debug::ToggleMenus();
			Wait( 1000 );
			Debug::ToggleMenus();
		}
		
		// Must be called at the end of execution cycle.
		Wait(0);
	}
}

