/* 
	USE THIS ONE AS A TEMPLATE FOR YOUR SCRIPT PLUGINS
*/

#include "common\skyscript.h"
#include "common\obscript.h"
#include "common\types.h"
#include "common\enums.h"
#include "common\plugin.h"

void
main(
	)
{
	Game::EnableFastTravel( false );
	while ( true ) {
		if ( Game::IsFastTravelEnabled() ) Game::EnableFastTravel( false );
		Wait(8);
		Wait(0);
	}
}

