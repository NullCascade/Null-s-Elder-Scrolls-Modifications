// Script Dragon includes.
#include "common\skyscript.h"
#include "common\obscript.h"
#include "common\types.h"
#include "common\enums.h"
#include "common\plugin.h"


// Definitions.
#define CONFIG_FILE "toggleui.ini"
#define ADDR_DRAW_MENUS 0x0156D500


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

// GetMenuIsEnabled - Checks to see if menu drawing is enabled.
bool
GetMenuIsEnabled(
	)
{
	return ( *(unsigned char*)( ADDR_DRAW_MENUS ) != 0x00 );
}

// SetMenusEnabled - Sets menu drawing.
void
SetMenusEnabled(
	unsigned char i_Value
	)
{
	*(unsigned char*)( ADDR_DRAW_MENUS ) = i_Value;
}


// Plugin entry point.
void
main(
	)
{
	//  Read initialization file.
	BYTE keyToggleUI = IniReadInt( CONFIG_FILE, "general", "toggleKey", 0x00 );

	// Keep track of the menu state.
	bool menusEnabled = true;
	SetMenusEnabled( menusEnabled );
	
	// Main plugin loop.
	while ( true ) {
		// Trigger on bound toggle key.
		if ( SafeGetKeyPressed( keyToggleUI ) ) {
			// Toggle menus/UI, then wait half a second.
			menusEnabled = !menusEnabled;
			SetMenusEnabled( menusEnabled );
			Wait( 250 );
		}
		
		// Must be called at the end of execution cycle.
		Wait(0);
	}
}

