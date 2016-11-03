#include "../Subsystems/Driveline.h"
#include "DrivelineDefaultCommand.h"
#include "../OI.h"
DrivelineDefaultCommand::DrivelineDefaultCommand()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(driveline);
}

// Called just before this Command runs the first time
void DrivelineDefaultCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void DrivelineDefaultCommand::Execute()
{

	driveline->Drive();
}

// Make this return true when this Command no longer needs to run execute()
bool DrivelineDefaultCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void DrivelineDefaultCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DrivelineDefaultCommand::Interrupted()
{

}
