#include "DrivelineMoveCommand.h"

DrivelineMoveCommand::DrivelineMoveCommand(double distance, double speed, double timeout, double percentTolerance, double p, double i, double d, double f)
{
	m_distance = distance;
	m_maxTimeout = timeout;
	m_speed = speed;
	m_percentTolerance = percentTolerance;
	m_p = p;
	m_i = i;
	m_d = d;
	m_f = f;
	Requires(driveline);
}

// Called just before this Command runs the first time
void DrivelineMoveCommand::Initialize()
{
	// Input range must be set to +/- of the target value.
	driveline->SetInputRange(-m_distance,m_distance);
	driveline->SetOutputRange(-m_speed,m_speed);
	driveline->SetPercentTolerance(m_percentTolerance);
	driveline->SetSetpoint(m_distance);
	driveline->SetPIDMode(DrivelinePIDMode::DRIVE, m_p, m_i, m_d, m_f);

}

// Called repeatedly when this Command is scheduled to run
void DrivelineMoveCommand::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool DrivelineMoveCommand::IsFinished()
{
	SmartDashboard::PutNumber("DrivelineDrivePIDFinishTime",TimeSinceInitialized());
	if(driveline->OnTarget() || TimeSinceInitialized() > m_maxTimeout){
		SmartDashboard::PutBoolean("DrivelineDrivePIDFinished",true);
		return true;
	}else {
		SmartDashboard::PutBoolean("DrivelineDrivePIDFinished",false);
		return false;
	}

}

// Called once after isFinished returns true
void DrivelineMoveCommand::End()
{
	driveline->Disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DrivelineMoveCommand::Interrupted()
{
	End();
}
