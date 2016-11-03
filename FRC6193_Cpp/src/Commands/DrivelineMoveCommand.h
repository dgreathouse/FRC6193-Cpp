#ifndef DrivelineMoveCommand_H
#define DrivelineMoveCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class DrivelineMoveCommand: public CommandBase
{
private:
	double m_distance = 0;
	double m_maxTimeout = 0;
	double m_speed = 0;
	double m_percentTolerance = 0;
	double m_p = 0;
	double m_i = 0;
	double m_d = 0;
	double m_f = 0;
public:
	DrivelineMoveCommand(double distance, double speed, double maxTime, double percentTolerance, double p, double i, double d, double f);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
