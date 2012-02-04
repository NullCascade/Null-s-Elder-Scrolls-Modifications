// Script Dragon includes.
#include "common\skyscript.h"
#include "common\obscript.h"
#include "common\types.h"
#include "common\enums.h"
#include "common\plugin.h"
#include "common\nullCommon.h"

// Plugin entry point.
void
main(
	)
{
	// Show version.
	PrintNote( "Version %x.", Skyrim::GetVersion() );

	// Main execution loop.
	while ( true ) {
		Wait(100000);
	}
}

