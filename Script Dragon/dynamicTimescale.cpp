// Script Dragon includes.
#include "common\skyscript.h"
#include "common\obscript.h"
#include "common\types.h"
#include "common\enums.h"
#include "common\plugin.h"


// Definitions.
#define CONFIG_FILE "dynamicTimescale.ini"


// Global variables.
int timescaleMin = 5;
int timescaleMax = 60;


// SetTimeScale - Sets the time scale.
void
SetTimeScale(
	int i_Timescale
	)
{
	// Enforce minimums/maximums.
	if ( i_Timescale < timescaleMin ) i_Timescale = timescaleMin;
	if ( i_Timescale > timescaleMax ) i_Timescale = timescaleMax;

	// Build command.
	char command[64];
	sprintf( command, "set timescale to %d", i_Timescale );
	
	// Change timescale.
	ExecuteConsoleCommand( command, Game::GetPlayer() );
}


// PlayerInInteriorCell - Checks to see if a player is inside an interior cell.
bool
PlayerInInteriorCell(
	)
{
	return Cell::IsInterior( ObjectReference::GetParentCell( (TESObjectREFR*)Game::GetPlayer() ) );
}


// Plugin entry point.
void
main(
	)
{
	// Get settings.
	int heartbeat = IniReadInt( CONFIG_FILE, "settings", "heartbeat", 2000 );
	timescaleMin = IniReadInt( CONFIG_FILE, "settings", "min_timescale", 5 );
	timescaleMax = IniReadInt( CONFIG_FILE, "settings", "max_timescale", 60 );

	// Get timescales.
	int tsDefault = IniReadInt( CONFIG_FILE, "timescale", "default", 20 );
	int tsCombat = IniReadInt( CONFIG_FILE, "timescale", "combat", tsDefault );
	int tsInterior = IniReadInt( CONFIG_FILE, "timescale", "interior", tsDefault );

	// Trackers.
	int curTimescale = tsDefault;
	int newTimescale = curTimescale;

	// Initial set.
	SetTimeScale( curTimescale ); 

	// Main execution loop.
	while ( true ) {
		// In combat
		if ( Actor::IsInCombat( Game::GetPlayer() ) ) {
			newTimescale = tsCombat;
		}

		// Interior
		else if ( PlayerInInteriorCell() ) {
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

