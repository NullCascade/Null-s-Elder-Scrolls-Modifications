// Script Dragon includes.
#include "common\skyscript.h"
#include "common\obscript.h"
#include "common\types.h"
#include "common\enums.h"
#include "common\plugin.h"


// Definitions.
#define TIMESCALE_MIN 5
#define TIMESCALE_MAX 60


// SetTimeScale - Sets the time scale.
void
SetTimeScale(
	int i_Timescale
	)
{
	// Enforce minimums/maximums.
	if ( i_Timescale < TIMESCALE_MIN ) i_Timescale = TIMESCALE_MIN;
	if ( i_Timescale > TIMESCALE_MAX ) i_Timescale = TIMESCALE_MAX;

	// Build command.
	char command[64];
	sprintf( command, "set timescale to %d", i_Timescale );
	
	// Change timescale.
	ExecuteConsoleCommand( command, Game::GetPlayer() );
}


// Plugin entry point.
void
main(
	)
{
	// Get the player and cell.
	CActor* player = Game::GetPlayer();
	TESObjectCELL* playerCell;

	// Get settings.
	int tsCombat;
	int tsInterior;
	int tsDefault;
	int heartbeat;

	// Trackers.
	int curTimescale = tsDefault;
	int newTimescale = curTimescale;
	bool wasInCombat = false;

	// Initial set.
	SetTimeScale( curTimescale ); 

	while ( true ) {
		// In combat
		if ( Actor::IsInCombat( player ) ) {
			newTimescale = tsCombat;
		}

		// Interior
		else if ( false ) {
			newTimescale = tsInterior;
		}

		// Default
		else {
			newTimescale = tsDefault;
		}

		// Did the timescale change?
		if ( newTimescale != curTimescale ) {
			SetTimeScale( newTimescale );
			curTimescale = newTimescale;
		}
		
		// Must be called at the end of execution cycle.
		Wait(heartbeat);
	}
}

