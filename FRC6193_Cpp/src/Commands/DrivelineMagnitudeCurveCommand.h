#ifndef DrivelineMagnitudeCurveCommand_H
#define DrivelineMagnitudeCurveCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class DrivelineMagnitudeCurveCommand: public CommandBase
{
public:
	DrivelineMagnitudeCurveCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
