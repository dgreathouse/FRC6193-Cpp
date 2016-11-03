#include "OI.h"

OI::OI()
{
	stickXbox = new Joystick(0);
}
Joystick * OI::GetXboxJoystick(){
	return stickXbox;
}

