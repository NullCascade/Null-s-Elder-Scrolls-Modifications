// Script Dragon includes.
#include "common\skyscript.h"
#include "common\obscript.h"
#include "common\types.h"
#include "common\enums.h"
#include "common\plugin.h"
#include "common\nullCommon.h"


// Definitions.
#define CONFIG_FILE "decoratorAssist.ini"


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

// SetPos - Sets the object's position on an axis - without blinking!
void
SetPosition(
	char* axis,
	float value
	)
{
	// Is an object grabbed?
	if ( !grabbedObj || !assistMode ) return;

	// Build command.
	char command[128];
	sprintf( command, "SetPos %s %f", axis, value );

	// Set position.
	ExecuteConsoleCommand( command, grabbedObj );
}

// SetAngle - Sets the object's rotation on an axis - without blinking!
void
SetAngle(
	char* axis,
	float value
	)
{
	// Is an object grabbed?
	if ( !grabbedObj || !assistMode ) return;

	// Build command.
	char command[128];
	sprintf( command, "SetAngle %s %f", axis, value );

	// Set position.
	ExecuteConsoleCommand( command, grabbedObj );
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
//	ObjectReference::BlockActivation( grabbedObj, true );
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
//	ObjectReference::BlockActivation( grabbedObj, false );
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
		if ( IO::SafeGetKeyPressed( keyDecorate ) ) {
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
			if ( IO::SafeGetKeyPressed( keyRotate ) ) {
				if ( IO::SafeGetKeyPressed( keyMoveXPos ) ) {
					rotX += ( IO::SafeGetKeyPressed( keyMulti ) ) ? rotChangeValue * valMulti : rotChangeValue;
					rotated = true;
				}
				if ( IO::SafeGetKeyPressed( keyMoveXNeg ) ) {
					rotX -= ( IO::SafeGetKeyPressed( keyMulti ) ) ? rotChangeValue * valMulti : rotChangeValue;
					rotated = true;
				}
				if ( IO::SafeGetKeyPressed( keyMoveYPos ) ) {
					rotY += ( IO::SafeGetKeyPressed( keyMulti ) ) ? rotChangeValue * valMulti : rotChangeValue;
					rotated = true;
				}
				if ( IO::SafeGetKeyPressed( keyMoveYNeg ) ) {
					rotY -= ( IO::SafeGetKeyPressed( keyMulti ) ) ? rotChangeValue * valMulti : rotChangeValue;
					rotated = true;
				}
				if ( IO::SafeGetKeyPressed( keyMoveZPos ) ) {
					rotZ += ( IO::SafeGetKeyPressed( keyMulti ) ) ? rotChangeValue * valMulti : rotChangeValue;
					rotated = true;
				}
				if ( IO::SafeGetKeyPressed( keyMoveZNeg ) ) {
					rotZ -= ( IO::SafeGetKeyPressed( keyMulti ) ) ? rotChangeValue * valMulti : rotChangeValue;
					rotated = true;
				}
			}

			// No? Then we're moving.
			else {
				if ( IO::SafeGetKeyPressed( keyMoveXPos ) ) {
					posX += ( IO::SafeGetKeyPressed( keyMulti ) ) ? moveChangeValue * valMulti : moveChangeValue;
					moved = true;
				}
				if ( IO::SafeGetKeyPressed( keyMoveXNeg ) ) {
					posX -= ( IO::SafeGetKeyPressed( keyMulti ) ) ? moveChangeValue * valMulti : moveChangeValue;
					moved = true;
				}
				if ( IO::SafeGetKeyPressed( keyMoveYPos ) ) {
					posY += ( IO::SafeGetKeyPressed( keyMulti ) ) ? moveChangeValue * valMulti : moveChangeValue;
					moved = true;
				}
				if ( IO::SafeGetKeyPressed( keyMoveYNeg ) ) {
					posY -= ( IO::SafeGetKeyPressed( keyMulti ) ) ? moveChangeValue * valMulti : moveChangeValue;
					moved = true;
				}
				if ( IO::SafeGetKeyPressed( keyMoveZPos ) ) {
					posZ += ( IO::SafeGetKeyPressed( keyMulti ) ) ? moveChangeValue * valMulti : moveChangeValue;
					moved = true;
				}
				if ( IO::SafeGetKeyPressed( keyMoveZNeg ) ) {
					posZ -= ( IO::SafeGetKeyPressed( keyMulti ) ) ? moveChangeValue * valMulti : moveChangeValue;
					moved = true;
				}
			}

			// Update the location and rotation.
			if ( moved ) {
				SetPosition( "X", posX );
				SetPosition( "Y", posY );
				SetPosition( "Z", posZ );
			}
			if ( rotated ) {
				SetAngle( "X", rotX );
				SetAngle( "Y", rotY );
				SetAngle( "Z", rotZ );
			}
			Wait( delay );
		}

		// Must be called at the end of execution cycle.
		Wait(0);
	}
}

