#ifndef AutonomousCommandGroup_H
#define AutonomousCommandGroup_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "Commands/DrivelineMoveCommand.h"
#include "Commands/DrivelineRotateCommand.h"
#include "Commands/DrivelineMagnitudeCurveCommand.h"


class AutonomousCommandGroup: public CommandGroup
{
public:
	AutonomousCommandGroup(int index);
};

#endif
