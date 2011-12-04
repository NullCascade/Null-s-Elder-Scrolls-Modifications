// Script Dragon includes.
#include "common\skyscript.h"
#include "common\obscript.h"
#include "common\types.h"
#include "common\enums.h"
#include "common\plugin.h"
#include "common\nullCommon.h"


// Definitions.
#define CONFIG_FILE			"scaleQuestRewards.ini"


// GetPlayerRef - Returns the player as a TESObjectREFR*.
TESObjectREFR*
GetPlayerRef(
	)
{
	return (TESObjectREFR*)Game::GetPlayer();
}

// PlayerHasItem - Returns true if the user has an item.
bool
PlayerHasItem(
	uint i_Item
	)
{
	return ( ObjectReference::GetItemCount( GetPlayerRef(), Game::GetFormById( i_Item ) ) > 0 );
}


// UpgradeItem - Upgrades an item if the player meets the level requirement.
void
UpgradeItem(
	uint i_From,
	uint i_To,
	uint i_LevelReq
	)
{
	unsigned int playerLevel = Actor::GetLevel( Game::GetPlayer() );
	while ( PlayerHasItem( i_From ) && playerLevel >= i_LevelReq ) {
		ObjectReference::RemoveItem( GetPlayerRef(), Game::GetFormById( i_From ), 1, false, 0 );
		ObjectReference::AddItem( GetPlayerRef(), Game::GetFormById( i_To ), 1, false );
	}
}


// CheckForUpdates - Main function. Handles updating of quest items.
void
CheckForUpdates(
	)
{
	// Chillrend.
	UpgradeItem( ID_TESObjectWEAP::TG07Chillrend001, ID_TESObjectWEAP::TG07Chillrend002, 11 );
	UpgradeItem( ID_TESObjectWEAP::TG07Chillrend002, ID_TESObjectWEAP::TG07Chillrend003, 19 );
	UpgradeItem( ID_TESObjectWEAP::TG07Chillrend003, ID_TESObjectWEAP::TG07Chillrend004, 27 );
	UpgradeItem( ID_TESObjectWEAP::TG07Chillrend004, ID_TESObjectWEAP::TG07Chillrend005, 36 );
	UpgradeItem( ID_TESObjectWEAP::TG07Chillrend005, ID_TESObjectWEAP::TG07Chillrend006, 46 );

	// Dragonbane.
	UpgradeItem( ID_TESObjectWEAP::MQ203AkaviriKatana1, ID_TESObjectWEAP::MQ203AkaviriKatana2, 19 );
	UpgradeItem( ID_TESObjectWEAP::MQ203AkaviriKatana2, ID_TESObjectWEAP::MQ203AkaviriKatana3, 27 );
	UpgradeItem( ID_TESObjectWEAP::MQ203AkaviriKatana3, ID_TESObjectWEAP::MQ203AkaviriKatana4, 36 );
	UpgradeItem( ID_TESObjectWEAP::MQ203AkaviriKatana4, ID_TESObjectWEAP::MQ203AkaviriKatana5, 46 );

	// Gauldur Blackblade.
	UpgradeItem( ID_TESObjectWEAP::dunFolgunthurMikrulSword02, ID_TESObjectWEAP::dunFolgunthurMikrulSword03, 12 );
	UpgradeItem( ID_TESObjectWEAP::dunFolgunthurMikrulSword03, ID_TESObjectWEAP::dunFolgunthurMikrulSword04, 19 );
	UpgradeItem( ID_TESObjectWEAP::dunFolgunthurMikrulSword04, ID_TESObjectWEAP::dunFolgunthurMikrulSword05, 27 );
	UpgradeItem( ID_TESObjectWEAP::dunFolgunthurMikrulSword05, ID_TESObjectWEAP::dunFolgunthurMikrulSword06, 36 );

	// Gauldur Blackbow.
	UpgradeItem( ID_TESObjectWEAP::dunGeirmundSigdisBow02, ID_TESObjectWEAP::dunGeirmundSigdisBow03, 12 );
	UpgradeItem( ID_TESObjectWEAP::dunGeirmundSigdisBow03, ID_TESObjectWEAP::dunGeirmundSigdisBow04, 19 );
	UpgradeItem( ID_TESObjectWEAP::dunGeirmundSigdisBow04, ID_TESObjectWEAP::dunGeirmundSigdisBow05, 27 );
	UpgradeItem( ID_TESObjectWEAP::dunGeirmundSigdisBow05, ID_TESObjectWEAP::dunGeirmundSigdisBow06, 36 );

	// Mage's Circlet
	UpgradeItem( ID_TESObjectARMO::MG04Reward01, ID_TESObjectARMO::MG04Reward02, 5 );
	UpgradeItem( ID_TESObjectARMO::MG04Reward02, ID_TESObjectARMO::MG04Reward03, 10 );
	UpgradeItem( ID_TESObjectARMO::MG04Reward03, ID_TESObjectARMO::MG04Reward04, 15 );
	UpgradeItem( ID_TESObjectARMO::MG04Reward04, ID_TESObjectARMO::MG04Reward05, 20 );
	UpgradeItem( ID_TESObjectARMO::MG04Reward05, ID_TESObjectARMO::MG04Reward06, 25 );

	// Nightingale Blade.
	UpgradeItem( ID_TESObjectWEAP::NightingaleBlade01, ID_TESObjectWEAP::NightingaleBlade02, 19 );
	UpgradeItem( ID_TESObjectWEAP::NightingaleBlade02, ID_TESObjectWEAP::NightingaleBlade03, 27 );
	UpgradeItem( ID_TESObjectWEAP::NightingaleBlade03, ID_TESObjectWEAP::NightingaleBlade04, 36 );
	UpgradeItem( ID_TESObjectWEAP::NightingaleBlade04, ID_TESObjectWEAP::NightingaleBlade05, 46 );

	// Nightingale Bow.
	UpgradeItem( ID_TESObjectWEAP::NightingaleBow01, ID_TESObjectWEAP::NightingaleBow02, 19 );
	UpgradeItem( ID_TESObjectWEAP::NightingaleBow02, ID_TESObjectWEAP::NightingaleBow03, 27 );
	UpgradeItem( ID_TESObjectWEAP::NightingaleBow03, ID_TESObjectWEAP::NightingaleBow04, 36 );
	UpgradeItem( ID_TESObjectWEAP::NightingaleBow04, ID_TESObjectWEAP::NightingaleBow05, 46 );

	// Nightingale Armor.
	UpgradeItem( ID_TESObjectARMO::ArmorNightingaleCuirassPlayer01, ID_TESObjectARMO::ArmorNightingaleCuirassPlayer02, 19 );
	UpgradeItem( ID_TESObjectARMO::ArmorNightingaleCuirassPlayer02, ID_TESObjectARMO::ArmorNightingaleCuirassPlayer03, 32 );

	// Nightingale Boots.
	UpgradeItem( ID_TESObjectARMO::ArmorNightingaleBootsPlayer01, ID_TESObjectARMO::ArmorNightingaleBootsPlayer02, 19 );
	UpgradeItem( ID_TESObjectARMO::ArmorNightingaleBootsPlayer02, ID_TESObjectARMO::ArmorNightingaleBootsPlayer03, 32 );

	// Nightingale Gloves.
	UpgradeItem( ID_TESObjectARMO::ArmorNightingaleGauntletsPlayer01, ID_TESObjectARMO::ArmorNightingaleGauntletsPlayer02, 19 );
	UpgradeItem( ID_TESObjectARMO::ArmorNightingaleGauntletsPlayer02, ID_TESObjectARMO::ArmorNightingaleGauntletsPlayer03, 32 );

	// Nightingale Hood.
	UpgradeItem( ID_TESObjectARMO::ArmorNightingaleHelmetPlayer01, ID_TESObjectARMO::ArmorNightingaleHelmetPlayer02, 19 );
	UpgradeItem( ID_TESObjectARMO::ArmorNightingaleHelmetPlayer02, ID_TESObjectARMO::ArmorNightingaleHelmetPlayer03, 32 );

	// The Pale Blade.
	UpgradeItem( ID_TESObjectWEAP::dunFrostmereCryptPaleBlade01, ID_TESObjectWEAP::dunFrostmereCryptPaleBlade02, 6 );
	UpgradeItem( ID_TESObjectWEAP::dunFrostmereCryptPaleBlade02, ID_TESObjectWEAP::dunFrostmereCryptPaleBlade03, 12 );
	UpgradeItem( ID_TESObjectWEAP::dunFrostmereCryptPaleBlade03, ID_TESObjectWEAP::dunFrostmereCryptPaleBlade04, 19 );
	UpgradeItem( ID_TESObjectWEAP::dunFrostmereCryptPaleBlade04, ID_TESObjectWEAP::dunFrostmereCryptPaleBlade05, 27 );

	// Shield of Solitude.
	UpgradeItem( ID_TESObjectARMO::MS06ShieldL12, ID_TESObjectARMO::MS06ShieldL18, 18 );
	UpgradeItem( ID_TESObjectARMO::MS06ShieldL18, ID_TESObjectARMO::MS06ShieldL25, 25 );
	UpgradeItem( ID_TESObjectARMO::MS06ShieldL25, ID_TESObjectARMO::MS06ShieldL32, 32 );
	UpgradeItem( ID_TESObjectARMO::MS06ShieldL32, ID_TESObjectARMO::MS06ShieldL40, 40 );

	// Tsun's Battle Axe.
	UpgradeItem( ID_TESObjectWEAP::MQ304DraugrBattleAxeTsun01, ID_TESObjectWEAP::MQ304DraugrBattleAxeTsun02, 14 );
	UpgradeItem( ID_TESObjectWEAP::MQ304DraugrBattleAxeTsun02, ID_TESObjectWEAP::MQ304DraugrBattleAxeTsun03, 18 );
	UpgradeItem( ID_TESObjectWEAP::MQ304DraugrBattleAxeTsun03, ID_TESObjectWEAP::MQ304DraugrBattleAxeTsun04, 23 );
}


// Plugin 'entry' point.
void
main(
	)
{
	// Initialization.
	BYTE forceCheckKey = IniReadInt( CONFIG_FILE, "settings", "forceCheckKey", 0x00 );
	int checkOnLoad = IniReadInt( CONFIG_FILE, "settings", "checkOnLoad", true );

	// Check for updates.
	if ( checkOnLoad ) CheckForUpdates();

	// Main plugin loop.
	while ( true ) {
		// Allow a force check.
		if ( IO::SafeGetKeyPressed( forceCheckKey ) ) {
			PrintNote( "Checking for updated items..." );
			CheckForUpdates();
			Wait( 2000 );
			PrintNote( "Update complete." );
		}

		// Must be called at the end of execution cycle.
		Wait( 0 );
	}
}