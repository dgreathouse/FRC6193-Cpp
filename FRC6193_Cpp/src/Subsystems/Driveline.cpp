#include "Driveline.h"
#include "../Commands/DrivelineDefaultCommand.h"
#include "../CommandBase.h"
#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"

#include "PIDController.h"
Driveline::Driveline() : PIDSubsystem("Driveline", 1.0,0.0,0.0,0.0)
{
	// Create new motor control objects
	m_leftFrontMotorController = new CANTalon(DRIVELINE_LEFT_FRONT_MOTORCONTROLLER_CANID);
	m_leftRearMotorController = new CANTalon(DRIVELINE_LEFT_REAR_MOTORCONTROLLER_CANID);
	m_rightRearMotorController = new CANTalon(DRIVELINE_RIGHT_REAR_MOTORCONTROLLER_CANID);
	m_rightFrontMotorController = new CANTalon(DRIVELINE_RIGHT_FRONT_MOTORCONTROLLER_CANID);

	// Invert the motors since all motors were wired backwards
	m_leftFrontMotorController->SetInverted(true);
	m_rightFrontMotorController->SetInverted(true);
	m_leftRearMotorController->SetInverted(true);
	m_rightRearMotorController->SetInverted(true);

	// Set the encoder counts per revolution
	//m_leftFrontMotorController->ConfigEncoderCodesPerRev(20);
	m_rightFrontMotorController->ConfigEncoderCodesPerRev(20);

	// Create a RobotDrive object with the new motor control objects
	m_robotDrive = new RobotDrive(m_leftFrontMotorController,m_leftRearMotorController,m_rightFrontMotorController,m_rightRearMotorController);
	m_robotDrive->SetSafetyEnabled(false);

	//m_leftFrontMotorController->SetPosition(0.0);
	m_rightFrontMotorController->SetPosition(0.0);

	// Set the default driveline PID mode to be MOVE
	m_drivelinePIDMode = DrivelinePIDMode::DRIVE;

	// Create a new Gyro to get angle.
	// This is the gyro plugged into the SPI port in the top right of the RoboRIO
	m_gyro = new ADXRS450_Gyro();

}

void Driveline::InitDefaultCommand()
{
	SetDefaultCommand(new DrivelineDefaultCommand());
}

void Driveline::Drive(){
	m_robotDrive->ArcadeDrive(GetY(CommandBase::oi->GetXboxJoystick()),0.0);

}
void Driveline::Drive(double move, double rotate){
	m_robotDrive->ArcadeDrive(move*-1.0,rotate);
}

/** Drive the robot at a set magnitude and curve
 *
 * @param magnitude
 * @param curve
 */
void Driveline::DriveMagnitudeCurve(double magnitude, double curve)
{
	m_robotDrive->Drive(magnitude, curve);
}

/** Return the PID sensor value that is used for control
 * This method is called periodically by the PIDController to get the
 * value of the sensor that is being used for the PIDController.
 *
 */
double Driveline::ReturnPIDInput(){
	if(m_drivelinePIDMode == DrivelinePIDMode::DRIVE){
		return GetDrivelineDistance() * DRIVELINE_ENCODER_INCHPERCNT;
	}else {
		return m_gyro->GetAngle();
	}
}
/** Use the PIDController output value to drive the robot.
 * Once the PIDController has calculated a value the output must be
 * used to move or rotate the robot
 *
 */
void Driveline::UsePIDOutput(double output){
	if(m_drivelinePIDMode == DrivelinePIDMode::DRIVE){
		Drive(output,0.0);
	}else {
		Drive(0.0,output);
	}
}
/** Set the PIDMode, configure PID settings and enable the PIDController
 *
 * @param mode
 * @param p
 * @param i
 * @param d
 * @param f
 */
void Driveline::SetPIDMode(DrivelinePIDMode mode, double p, double i, double d, double f){
	m_drivelinePIDMode = mode;
	GetPIDController()->Reset();
	ResetDrivelineDistance();
	GetPIDController()->SetPID(p,i,d,f);
	GetPIDController()->SetToleranceBuffer(4);
	Enable();
}
/** Get the move value from the joystick
 *
 * @param stick
 * @return
 */
double Driveline::GetY(Joystick *stick){
	float Left = stick->GetRawAxis(3);
	float Right = stick->GetRawAxis(2);
	return Right - Left;
}
/**
 * Reset the Driveline encoders to 0
 *
 */
void Driveline::ResetDrivelineDistance(){
	m_leftFrontMotorController->SetPosition(0.0);
	m_rightFrontMotorController->SetPosition(0.0);
}
/**
 * Assume they are both good and average them
 */
double Driveline::GetDrivelineDistance(){
	//return (m_rightFrontMotorController->GetEncPosition() + m_leftFrontMotorController->GetEncPosition())/2;
	return (m_rightFrontMotorController->GetEncPosition());
}

double Driveline::GetDrivelineSpeed(){
	//return (m_rightFrontMotorController->GetSpeed() + m_leftFrontMotorController->GetSpeed())/2;
	return (m_rightFrontMotorController->GetSpeed());
}
double Driveline::GetDrivelineCurrent(){
	return (m_rightFrontMotorController->GetOutputCurrent() + m_leftFrontMotorController->GetOutputCurrent()
			+ m_rightRearMotorController->GetOutputCurrent() + m_leftRearMotorController->GetOutputCurrent());
}
