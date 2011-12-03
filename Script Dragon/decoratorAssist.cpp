// Script Dragon includes.
#include "common\skyscript.h"
#include "common\obscript.h"
#include "common\types.h"
#include "common\enums.h"
#include "common\plugin.h"


// Definitions.
#define CONFIG_FILE "decoratorAssist.ini"

// SafeGetKeyPressed - Checks if the key is pressed, but won't work if in menu mode.
bool
SafeGetKeyPressed(
	BYTE i_Key
	)
{
	// Don't enable in menu mode.
	if ( Utility::IsInMenuMode() ) return false;

	// Are we naming something?
	if ( *(unsigned int*)( (DWORD)( 0x01565D68 ) ) == 1 ) return false;

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
	BYTE keyDecorate = IniReadInt( CONFIG_FILE, "settings", "decorate_key", 0x00 );

	// Assistance mode?
	bool assistMode = false;
	TESObjectREFR* grabbedObj = NULL;
	
	// Main plugin loop.
	while ( true ) {
		// Enter/exit decoration mode.
		if ( SafeGetKeyPressed( keyDecorate ) ) {
			grabbedObj = Game::GetPlayerGrabbedRef();
			if ( grabbedObj != NULL ) {
				assistMode = !assistMode;
				if ( assistMode ) {
					PrintNote( "Decorator mode enabled." );
					Game::DisablePlayerControls( true, true, true, false, true, true, true, true, true );
					Game::SetCameraTarget( (CActor*)grabbedObj );
				} else {
					PrintNote( "Decorator mode disabled." );
					Game::DisablePlayerControls( false, false, false, false, false, false, false, false, false );
					Game::SetCameraTarget( Game::GetPlayer() );
				}
			} else {
				PrintNote( "Must be holding an object." );
			}
			Wait( 250 );
		}

		// Are we assisting?
		if ( assistMode ) {
			
		}

		// Must be called at the end of execution cycle.
		Wait(0);
	}
}

