#ifndef DrivelineDefaultCommand_H
#define DrivelineDefaultCommand_H

#include "../CommandBase.h"
#include "WPILib.h"
#include "../OI.h"

class DrivelineDefaultCommand: public CommandBase
{
public:
	DrivelineDefaultCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
