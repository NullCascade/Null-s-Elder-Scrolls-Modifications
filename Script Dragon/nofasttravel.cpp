// Script Dragon includes.
#include "common\skyscript.h"
#include "common\obscript.h"
#include "common\types.h"
#include "common\enums.h"
#include "common\plugin.h"


// Definitions.
#define CONFIG_FILE "nofasttravel.ini"

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
		Wait(heartbeat);
		if ( Game::IsFastTravelEnabled() ) Game::EnableFastTravel( false );
		Wait(0);
	}
}

