// Script Dragon includes.
#include "common\skyscript.h"
#include "common\obscript.h"
#include "common\types.h"
#include "common\enums.h"
#include "common\plugin.h"


// Definitions.
#define CONFIG_FILE "toggleui.ini"


// Plugin entry point.
void
main(
	)
{
	//  Read initialization file.
	BYTE keyToggleUI = IniReadInt( CONFIG_FILE, "general", "toggleKey", 0xDD );;
	
	// Main plugin loop.
	while ( true ) {
		// Trigger on bound toggle key.
		if ( GetKeyPressed( keyToggleUI ) ) {
			// Toggle menus/UI, then wait half a second.
			Debug::ToggleMenus();
			Wait( 500 );
		}
		
		// Must be called at the end of execution cycle.
		Wait(0);
	}
}

