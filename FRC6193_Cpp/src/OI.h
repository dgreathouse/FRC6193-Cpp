#ifndef OI_H
#define OI_H

#include "WPILib.h"
/** Operator Interface
 *
 */
class OI
{
private:
Joystick *stickXbox;

public:
	OI();
	Joystick* GetXboxJoystick();
};

#endif
