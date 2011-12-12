// Script Dragon includes.
#include "common\skyscript.h"
#include "common\obscript.h"
#include "common\types.h"
#include "common\enums.h"
#include "common\plugin.h"
#include "common\nullCommon.h"

// Definitions.
#define CONFIG_FILE			"soulstoperks.ini"


// Costs.
int PPC_Constant = 10;
int PPC_Level = 0;


// GetPerkPointCost - Calculates the cost of buying a perk point.
int
GetPerkPointCost(
	)
{
	// The formula: ( PlayerLevel * PPC_Level ) + PPC_Constant = DragonSoulsRequired
	unsigned int playerLevel = Actor::GetLevel( Game::GetPlayer() );
	int cost = ( playerLevel * PPC_Level ) + PPC_Constant;

	// Ensure no negative cost, and finish up.
	if ( cost < 0 ) cost = 10;
	return cost;
}


// GetPerkCount - Borrowed from the 'Perk Reset' plugin from hitachihex.
BYTE
GetPerkCount(
	) 
{
	return *Skyrim::GetAddrPerkPoints();
}


// SetPerkCount - Borrowed from the 'Perk Reset' plugin from hitachihex.
void
SetPerkCount(
	BYTE i_Count
	)
{
	*Skyrim::GetAddrPerkPoints() = i_Count;
}


// GetDragonSoulCount - Wrapper for getting the player's dragon soul count.
int
GetDragonSoulCount(
	) 
{
	return Actor::GetActorValue( Game::GetPlayer(), "dragonsouls" );
}


// ModDragonSoulCount - Wrapper for modifying the player's dragon soul count.
void
ModDragonSoulCount(
	int i_Change
	)
{
	Actor::ModActorValue( Game::GetPlayer(), "dragonsouls", i_Change );
}


// Plugin 'entry' point.
void
main(
	)
{
	// Initialization.
	BYTE keyBuyPerkPoint = IniReadInt( CONFIG_FILE, "general", "buyKey", 0xDE );
	PPC_Constant = IniReadInt( CONFIG_FILE, "cost", "constant", PPC_Constant );
	PPC_Level = IniReadInt( CONFIG_FILE, "cost", "levelMult", PPC_Level );

	// Version supported?
	bool failState = false;
	if ( !Skyrim::GetAddrPerkPoints() ) {
		PrintNote( "[SoulsToPerks] Skyrim version not supported: 0x%x", Skyrim::GetVersion() );
		failState = true;
	}

	// Main plugin loop.
	while ( true ) {
		// Fail mode?
		if ( failState ) {
			Wait( 1000 );
			continue;
		}

		// Calculate them perk points.
		if ( IO::SafeGetKeyPressed( keyBuyPerkPoint ) ) {
			int perkPointCost = GetPerkPointCost();
			int perkCount = GetPerkCount();
			int dragonSouls = GetDragonSoulCount();

			// Is this version supported?
			if ( Skyrim::GetAddrPerkPoints() == NULL ) {
				PrintNote( "Error: Version not supported. Please update this mod." );
				Wait( 2000 );
			}

			// Can we get more perks?
			else if ( perkCount == 255 ) {
				PrintNote( "Error: Too many perks. Get rid of some and try again." );
				Wait( 2000 );
			}

			// Do we have enough souls?
			else if ( dragonSouls < perkPointCost ) {
				PrintNote( "%d dragon souls are required for more power.", perkPointCost );
				Wait( 2000 );
			}

			// All's good? Give me my perk!
			else {
				ModDragonSoulCount( -perkPointCost );
				SetPerkCount( perkCount + 1 );
				PrintNote( "The souls of %d dragons have granted you a new power.", perkPointCost );
				Wait( 2000 );
			}
		}

		// Must be called at the end of execution cycle.
		Wait( 0 );
	}
}