// Script Dragon includes.
#include "common\skyscript.h"
#include "common\obscript.h"
#include "common\types.h"
#include "common\enums.h"
#include "common\plugin.h"


// Definitions.
#define CONFIG_FILE "soulstoperks.ini"
#define WAIT_TIME 200


// Costs.
int PPC_Constant = 10;
int PPC_Level = 0;
int debugMode = 1;


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


// GetPlayerCharacter - Borrowed from the 'Perk Reset' plugin from hitachihex.
DWORD
GetPlayerCharacter(
	)
{
	return ( ( ( DWORD(__thiscall*)(DWORD) )0xA03CD0 )( 0x0155C064 ) );
}


// GetPerkCount - Borrowed from the 'Perk Reset' plugin from hitachihex.
unsigned char
GetPerkCount(
	) 
{
	return ( ((unsigned char(__thiscall*)(DWORD))0x9E8E70)( GetPlayerCharacter() ) );
}


// SetPerkCount - Borrowed from the 'Perk Reset' plugin from hitachihex.
void
SetPerkCount(
	unsigned char i_Count
	)
{
	((void(__thiscall*)(DWORD, unsigned char))0x9E8E90)( GetPlayerCharacter(), i_Count );
	return;
}


// GetDragonSoulCount - Wrapper for getting the player's dragon soul count.
int
GetDragonSoulCount(
	) 
{
	return Actor::GetActorValue( Game::GetPlayer(), "dragonsouls" );
}


// SetDragonSoulCount - Wrapper for setting the player's dragon soul count.
void
SetDragonSoulCount(
	int i_Count
	)
{
	Actor::ModActorValue( Game::GetPlayer(), "dragonsouls", -GetPerkPointCost() );
}


// Plugin 'entry' point.
void
main(
	)
{
	// Initialization.
	BYTE keyBuyPerkPoint = IniReadInt( CONFIG_FILE, "general", "buyKey", 0xDE );
	debugMode = IniReadInt( CONFIG_FILE, "general", "debug", 0 );
	PPC_Constant = IniReadInt( CONFIG_FILE, "cost", "constant", PPC_Constant );
	PPC_Level = IniReadInt( CONFIG_FILE, "cost", "levelMult", PPC_Level );

	// Main plugin loop.
	while ( true ) {
		// Calculate them perk points.
		if ( GetKeyPressed( keyBuyPerkPoint ) ) {
			int perkPointCost = GetPerkPointCost();
			int perkCount = GetPerkCount();
			int dragonSouls = GetDragonSoulCount();

			// Can we get more perks?
			if ( perkCount > 200 ) {
				PrintNote( "Too many perks. Get rid of some and try again." );
				Wait( WAIT_TIME );
			}

			// Do we have enough souls?
			else if ( dragonSouls < perkPointCost ) {
				PrintNote( "%d dragon souls are required for more power.", perkPointCost );
				Wait( WAIT_TIME );
			}

			// All's good? Give me my perk!
			else {
				SetDragonSoulCount( dragonSouls - perkPointCost );
				SetPerkCount( perkCount + 1 );
				PrintNote( "The souls of %d dragons have granted you new power.", perkPointCost );
				Wait( WAIT_TIME );
			}
		}

		// Must be called at the end of execution cycle.
		Wait( 0 );
	}
}