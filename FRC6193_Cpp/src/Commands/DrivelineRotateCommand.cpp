#include <Commands/DrivelineRotateCommand.h>

DrivelineTurnCommand::DrivelineTurnCommand(double angle, double speed, double timeout, double percentTolerance, double p, double i, double d, double f)
{
	m_angle = angle;
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
void DrivelineTurnCommand::Initialize()
{
	// Input range must be set to +/- of the target value.
	driveline->SetInputRange(-m_angle,m_angle);
	driveline->SetOutputRange(-m_speed,m_speed);
	driveline->SetPercentTolerance(m_percentTolerance);
	driveline->ResetDrivelineDistance();
	driveline->SetSetpoint(m_angle);
	driveline->SetPIDMode(DrivelinePIDMode::TURN, m_p, m_i, m_d, m_f);

}

// Called repeatedly when this Command is scheduled to run
void DrivelineTurnCommand::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool DrivelineTurnCommand::IsFinished()
{
	SmartDashboard::PutNumber("DrivelineTurnPIDFinishTime",TimeSinceInitialized());
	if(driveline->OnTarget() || TimeSinceInitialized() > m_maxTimeout){
		SmartDashboard::PutBoolean("DrivelineTurnPIDFinished",true);
		return true;
	}else {
		SmartDashboard::PutBoolean("DrivelineTurnPIDFinished",false);
		return false;
	}
}

// Called once after isFinished returns true
void DrivelineTurnCommand::End()
{
	driveline->Disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DrivelineTurnCommand::Interrupted()
{
	End();
}
