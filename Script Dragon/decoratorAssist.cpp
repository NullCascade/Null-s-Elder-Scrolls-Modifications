// Script Dragon includes.
#include "common\skyscript.h"
#include "common\obscript.h"
#include "common\types.h"
#include "common\enums.h"
#include "common\plugin.h"


// Definitions.
#define CONFIG_FILE "decoratorAssist.ini"
#define ADDR_IS_RENAMING	0x01592028
#define KEY_LEFT_SHIFT		0xA0
#define KEY_LEFT_CONTROL	0xA2

// SafeGetKeyPressed - Checks if the key is pressed, but won't work if in menu mode.
bool
SafeGetKeyPressed(
	BYTE i_Key
	)
{
	// Don't enable in menu mode.
	if ( Utility::IsInMenuMode() ) return false;

	// Are we naming something?
	if ( *(unsigned int*)( (DWORD)( ADDR_IS_RENAMING ) ) == 1 ) return false;

	// Don't enable if the key is set to 0x00.
	if ( i_Key == 0x00 ) return false;

	// Otherwise, check as normal.
	return GetKeyPressed( i_Key );
}


// Plugin entry point.
void
main(
	)
{
	//  Read initialization file.
	BYTE keyDecorate = IniReadInt( CONFIG_FILE, "settings", "key_decorate", 0x00 );
	BYTE keyMoveXPos = IniReadInt( CONFIG_FILE, "settings", "key_x_pos", 0x00 );
	BYTE keyMoveXNeg = IniReadInt( CONFIG_FILE, "settings", "key_x_neg", 0x00 );
	BYTE keyMoveYPos = IniReadInt( CONFIG_FILE, "settings", "key_y_pos", 0x00 );
	BYTE keyMoveYNeg = IniReadInt( CONFIG_FILE, "settings", "key_y_neg", 0x00 );
	BYTE keyMoveZPos = IniReadInt( CONFIG_FILE, "settings", "key_z_pos", 0x00 );
	BYTE keyMoveZNeg = IniReadInt( CONFIG_FILE, "settings", "key_z_neg", 0x00 );
	float moveChangeValue = IniReadInt( CONFIG_FILE, "movement", "move_amount", 1 ) / 100;

	// Assistance mode?
	bool assistMode = false;
	TESObjectREFR* grabbedObj = NULL;
	float posX = 0.0f;
	float posY = 0.0f;
	float posZ = 0.0f;
	float rotX = 0.0f;
	float rotY = 0.0f;
	float rotZ = 0.0f;
	
	// Main plugin loop.
	while ( true ) {
		// Enter/exit decoration mode.
		if ( SafeGetKeyPressed( keyDecorate ) ) {
			// Get the grabbed object.
			TESObjectREFR* grabbedObjTmp = Game::GetPlayerGrabbedRef();

			// Disabling decoration mode?
			if ( assistMode ) {
				// Exit assist mode.
				assistMode = false;
				PrintNote( "Decorator mode disabled." );
				Debug::ToggleCollisions();
				grabbedObj = NULL;

				// Reset position data.
				posX = 0.0f;	rotX = 0.0f;
				posY = 0.0f;	rotY = 0.0f;
				posZ = 0.0f;	rotZ = 0.0f;

				// Wait between key presses so it won't quickly re-enable.
				Wait( 250 );
			}

			// Are we enabling decoration mode?
			else if ( grabbedObjTmp != NULL ) {
				// Wait for the player to release the object.
				PrintNote( "Release the object to decorate." );
				while ( Game::GetPlayerGrabbedRef() != NULL ) {
					Wait( 10 );
				}

				// Enter assist mode.
				assistMode = true;
				PrintNote( "Decorator mode enabled." );
				Debug::ToggleCollisions();
				grabbedObj = grabbedObjTmp;

				// Get position.
				posX = ObjectReference::GetPositionX( grabbedObj );
				posY = ObjectReference::GetPositionY( grabbedObj );
				posZ = ObjectReference::GetPositionZ( grabbedObj );

				// Get rotation.
				rotX = ObjectReference::GetAngleX( grabbedObj );
				rotY = ObjectReference::GetAngleY( grabbedObj );
				rotZ = ObjectReference::GetAngleZ( grabbedObj );
			}
		}

		// Are we assisting?
		if ( assistMode ) {
			bool moved = false;
			bool rotated = false;

			// Are we rotating?
			if ( SafeGetKeyPressed( KEY_LEFT_CONTROL ) ) {
				if ( SafeGetKeyPressed( keyMoveXPos ) ) {
					rotX += ( SafeGetKeyPressed( KEY_LEFT_SHIFT ) ) ? moveChangeValue : moveChangeValue * 10;
					rotated = true;
				}
				if ( SafeGetKeyPressed( keyMoveXNeg ) ) {
					rotX -= ( SafeGetKeyPressed( KEY_LEFT_SHIFT ) ) ? moveChangeValue : moveChangeValue * 10;
					rotated = true;
				}
				if ( SafeGetKeyPressed( keyMoveYPos ) ) {
					rotY += ( SafeGetKeyPressed( KEY_LEFT_SHIFT ) ) ? moveChangeValue : moveChangeValue * 10;
					rotated = true;
				}
				if ( SafeGetKeyPressed( keyMoveYNeg ) ) {
					rotY -= ( SafeGetKeyPressed( KEY_LEFT_SHIFT ) ) ? moveChangeValue : moveChangeValue * 10;
					rotated = true;
				}
				if ( SafeGetKeyPressed( keyMoveZPos ) ) {
					rotZ += ( SafeGetKeyPressed( KEY_LEFT_SHIFT ) ) ? moveChangeValue : moveChangeValue * 10;
					rotated = true;
				}
				if ( SafeGetKeyPressed( keyMoveZNeg ) ) {
					rotZ -= ( SafeGetKeyPressed( KEY_LEFT_SHIFT ) ) ? moveChangeValue : moveChangeValue * 10;
					rotated = true;
				}
			}

			// No? Then we're moving.
			else {
				if ( SafeGetKeyPressed( keyMoveXPos ) ) {
					posX += ( SafeGetKeyPressed( KEY_LEFT_SHIFT ) ) ? moveChangeValue : moveChangeValue * 10;
					moved = true;
				}
				if ( SafeGetKeyPressed( keyMoveXNeg ) ) {
					posX -= ( SafeGetKeyPressed( KEY_LEFT_SHIFT ) ) ? moveChangeValue : moveChangeValue * 10;
					moved = true;
				}
				if ( SafeGetKeyPressed( keyMoveYPos ) ) {
					posY += ( SafeGetKeyPressed( KEY_LEFT_SHIFT ) ) ? moveChangeValue : moveChangeValue * 10;
					moved = true;
				}
				if ( SafeGetKeyPressed( keyMoveYNeg ) ) {
					posY -= ( SafeGetKeyPressed( KEY_LEFT_SHIFT ) ) ? moveChangeValue : moveChangeValue * 10;
					moved = true;
				}
				if ( SafeGetKeyPressed( keyMoveZPos ) ) {
					posZ += ( SafeGetKeyPressed( KEY_LEFT_SHIFT ) ) ? moveChangeValue : moveChangeValue * 10;
					moved = true;
				}
				if ( SafeGetKeyPressed( keyMoveZNeg ) ) {
					posZ -= ( SafeGetKeyPressed( KEY_LEFT_SHIFT ) ) ? moveChangeValue : moveChangeValue * 10;
					moved = true;
				}
			}

			// Update the location and rotation.
			if ( moved ) ObjectReference::SetPosition( grabbedObj, posX, posY, posZ );
			if ( rotated ) ObjectReference::SetAngle( grabbedObj, rotX, rotY, rotZ );
			Wait( 10 );
		}

		// Must be called at the end of execution cycle.
		Wait(0);
	}
}

