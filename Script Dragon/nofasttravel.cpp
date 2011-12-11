// Script Dragon includes.
#include "common\skyscript.h"
#include "common\obscript.h"
#include "common\types.h"
#include "common\enums.h"
#include "common\plugin.h"
#include "common\nullCommon.h"


// Definitions.
#define CONFIG_FILE "nofasttravel.ini"


// DisableFastTravel
void
DisableFastTravel(
	)
{
	ExecuteConsoleCommand( "EnableFastTravel 0", Game::GetPlayer() );
}


void
main(
	)
{
	// Get the customized delay.
	int heartbeat = IniReadInt( CONFIG_FILE, "settings", "heartbeat", 500 );

	// Initial disable.
	Game::EnableFastTravel( false );
	
	// Redisable every heartbeat miliseconds.
	while ( true ) {
		DisableFastTravel();
		Wait(heartbeat);
	}
}

