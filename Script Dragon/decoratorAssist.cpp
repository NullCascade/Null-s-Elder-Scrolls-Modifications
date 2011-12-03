// Script Dragon includes.
#include "common\skyscript.h"
#include "common\obscript.h"
#include "common\types.h"
#include "common\enums.h"
#include "common\plugin.h"


// Definitions.
#define CONFIG_FILE "decoratorAssist.ini"
#define ADDR_IS_RENAMING	0x01592028


// Globals.
int valMulti = 0;
int moveChangeValue = 0;
int rotChangeValue = 0;
int delay = 0;
BYTE keyDecorate = 0x00;
BYTE keyRotate = 0x00;
BYTE keyMulti = 0x00;
BYTE keyMoveXPos = 0x00;
BYTE keyMoveXNeg = 0x00;
BYTE keyMoveYPos = 0x00;
BYTE keyMoveYNeg = 0x00;
BYTE keyMoveZPos = 0x00;
BYTE keyMoveZNeg = 0x00;
bool assistMode = false;
float posX = 0.0f;
float posY = 0.0f;
float posZ = 0.0f;
float rotX = 0.0f;
float rotY = 0.0f;
float rotZ = 0.0f;
TESObjectREFR* grabbedObj = NULL;
TESObjectCELL* currentCell = NULL;


// SafeGetKeyPressed - Checks if the key is pressed, but won't work if in menu mode.
bool
SafeGetKeyPressed(
	BYTE i_Key,
	bool i_Control = false,
	bool i_Shift = false,
	bool i_Alt = false
	)
{
	// Don't enable in menu mode.
	if ( Utility::IsInMenuMode() ) return false;

	// Are we naming something?
	if ( *(unsigned int*)( (DWORD)( ADDR_IS_RENAMING ) ) == 1 ) return false;

	// Don't enable if the key is set to 0x00.
	if ( i_Key == 0x00 ) return false;

	// Are the control keys pressed?
	if ( i_Control && !GetKeyPressed( 0xA2 ) ) return false;
	if ( i_Shift && !GetKeyPressed( 0xA0 ) ) return false;
	if ( i_Alt && !GetKeyPressed( 0xA4 ) ) return false;

	// Otherwise, check as normal.
	return GetKeyPressed( i_Key );
}

// EnableDecorationMode
bool
EnableDecorationMode(
	)
{
	// Are we even in decoration mode?
	if ( assistMode ) return true;

	// Get held object.
	TESObjectREFR* grabbedObjTmp = Game::GetPlayerGrabbedRef();
	if ( grabbedObjTmp == NULL ) return false;

	// Wait for the player to release the object.
	PrintNote( "Release the object to decorate." );
	while ( Game::GetPlayerGrabbedRef() != NULL ) {
		Wait( 10 );
	}

	// Enter assist mode.
	assistMode = true;
	PrintNote( "Decorator mode enabled." );
	Debug::ToggleCollisions();
	ObjectReference::BlockActivation( grabbedObj, true );
	grabbedObj = grabbedObjTmp;
	currentCell = ObjectReference::GetParentCell( (TESObjectREFR*)Game::GetPlayer() );

	// Get position.
	posX = ObjectReference::GetPositionX( grabbedObj );
	posY = ObjectReference::GetPositionY( grabbedObj );
	posZ = ObjectReference::GetPositionZ( grabbedObj );

	// Get rotation.
	rotX = ObjectReference::GetAngleX( grabbedObj );
	rotY = ObjectReference::GetAngleY( grabbedObj );
	rotZ = ObjectReference::GetAngleZ( grabbedObj );

	return assistMode;
}


// DisableDecorationMode
bool
DisableDecorationMode(
	)
{
	// Are we even in decoration mode?
	if ( !assistMode ) return false;

	// Disable.
	assistMode = false;
	PrintNote( "Decorator mode disabled." );
	Debug::ToggleCollisions();
	ObjectReference::BlockActivation( grabbedObj, false );
	grabbedObj = NULL;

	// Reset position data.
	posX = 0.0f;	rotX = 0.0f;
	posY = 0.0f;	rotY = 0.0f;
	posZ = 0.0f;	rotZ = 0.0f;

	// Wait between key presses so it won't quickly re-enable.
	Wait( 250 );

	return assistMode;
}


// ShouldExitDecorationMode - Returns true if 
bool
ShouldExitDecorationMode(
	)
{
	// Are we even in decoration mode?
	if ( !assistMode ) return false;

	// Get the actor.
	CActor* player = Game::GetPlayer();
	if ( player == NULL ) return true;

	// In combat?
	if ( Actor::IsInCombat( player ) ) return true;

	// In menu mode?
	if ( Utility::IsInMenuMode() ) return true;

	// Changed area?
	if ( currentCell != ObjectReference::GetParentCell( (TESObjectREFR*)Game::GetPlayer() ) ) return true;

	// All's good?
	return false;
}


// Plugin entry point.
void
main(
	)
{
	//  Read initialization file.
	valMulti = IniReadInt( CONFIG_FILE, "settings", "multi_value", 10 );
	moveChangeValue = IniReadInt( CONFIG_FILE, "settings", "move_amount", 1 ) / 100;
	rotChangeValue = IniReadInt( CONFIG_FILE, "settings", "rotate_amount", 1 );
	delay = IniReadInt( CONFIG_FILE, "settings", "delay", 10 );
	keyDecorate = IniReadInt( CONFIG_FILE, "keys", "key_decorate", 0x00 );
	keyRotate = IniReadInt( CONFIG_FILE, "keys", "key_rotate", 0x00 );
	keyMulti = IniReadInt( CONFIG_FILE, "keys", "key_multi", 0x00 );
	keyMoveXPos = IniReadInt( CONFIG_FILE, "keys", "key_x_pos", 0x00 );
	keyMoveXNeg = IniReadInt( CONFIG_FILE, "keys", "key_x_neg", 0x00 );
	keyMoveYPos = IniReadInt( CONFIG_FILE, "keys", "key_y_pos", 0x00 );
	keyMoveYNeg = IniReadInt( CONFIG_FILE, "keys", "key_y_neg", 0x00 );
	keyMoveZPos = IniReadInt( CONFIG_FILE, "keys", "key_z_pos", 0x00 );
	keyMoveZNeg = IniReadInt( CONFIG_FILE, "keys", "key_z_neg", 0x00 );
	
	// Main plugin loop.
	while ( true ) {
		// Enter/exit decoration mode.
		if ( SafeGetKeyPressed( keyDecorate ) ) {
			// Get the grabbed object.
			TESObjectREFR* grabbedObjTmp = Game::GetPlayerGrabbedRef();

			// Disabling decoration mode?
			if ( assistMode ) {
				DisableDecorationMode();
			}

			// Are we enabling decoration mode?
			else if ( grabbedObjTmp != NULL ) {
				EnableDecorationMode();
			}
		}

		// Is it safe to still be in assist mode?
		if ( assistMode && ShouldExitDecorationMode() ) DisableDecorationMode();

		// Are we assisting?
		if ( assistMode ) {
			bool moved = false;
			bool rotated = false;

			// Are we rotating?
			if ( SafeGetKeyPressed( keyRotate ) ) {
				if ( SafeGetKeyPressed( keyMoveXPos ) ) {
					rotX += ( SafeGetKeyPressed( keyMulti ) ) ? rotChangeValue * valMulti : rotChangeValue;
					rotated = true;
				}
				if ( SafeGetKeyPressed( keyMoveXNeg ) ) {
					rotX -= ( SafeGetKeyPressed( keyMulti ) ) ? rotChangeValue * valMulti : rotChangeValue;
					rotated = true;
				}
				if ( SafeGetKeyPressed( keyMoveYPos ) ) {
					rotY += ( SafeGetKeyPressed( keyMulti ) ) ? rotChangeValue * valMulti : rotChangeValue;
					rotated = true;
				}
				if ( SafeGetKeyPressed( keyMoveYNeg ) ) {
					rotY -= ( SafeGetKeyPressed( keyMulti ) ) ? rotChangeValue * valMulti : rotChangeValue;
					rotated = true;
				}
				if ( SafeGetKeyPressed( keyMoveZPos ) ) {
					rotZ += ( SafeGetKeyPressed( keyMulti ) ) ? rotChangeValue * valMulti : rotChangeValue;
					rotated = true;
				}
				if ( SafeGetKeyPressed( keyMoveZNeg ) ) {
					rotZ -= ( SafeGetKeyPressed( keyMulti ) ) ? rotChangeValue * valMulti : rotChangeValue;
					rotated = true;
				}
			}

			// No? Then we're moving.
			else {
				if ( SafeGetKeyPressed( keyMoveXPos ) ) {
					posX += ( SafeGetKeyPressed( keyMulti ) ) ? moveChangeValue * valMulti : moveChangeValue;
					moved = true;
				}
				if ( SafeGetKeyPressed( keyMoveXNeg ) ) {
					posX -= ( SafeGetKeyPressed( keyMulti ) ) ? moveChangeValue * valMulti : moveChangeValue;
					moved = true;
				}
				if ( SafeGetKeyPressed( keyMoveYPos ) ) {
					posY += ( SafeGetKeyPressed( keyMulti ) ) ? moveChangeValue * valMulti : moveChangeValue;
					moved = true;
				}
				if ( SafeGetKeyPressed( keyMoveYNeg ) ) {
					posY -= ( SafeGetKeyPressed( keyMulti ) ) ? moveChangeValue * valMulti : moveChangeValue;
					moved = true;
				}
				if ( SafeGetKeyPressed( keyMoveZPos ) ) {
					posZ += ( SafeGetKeyPressed( keyMulti ) ) ? moveChangeValue * valMulti : moveChangeValue;
					moved = true;
				}
				if ( SafeGetKeyPressed( keyMoveZNeg ) ) {
					posZ -= ( SafeGetKeyPressed( keyMulti ) ) ? moveChangeValue * valMulti : moveChangeValue;
					moved = true;
				}
			}

			// Update the location and rotation.
			if ( moved ) ObjectReference::SetPosition( grabbedObj, posX, posY, posZ );
			if ( rotated ) ObjectReference::SetAngle( grabbedObj, rotX, rotY, rotZ );
			Wait( delay );
		}

		// Must be called at the end of execution cycle.
		Wait(0);
	}
}

