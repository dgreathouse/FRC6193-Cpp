#ifndef Driveline_H
#define Driveline_H

#include "../Lib/DrivelinePIDMode.h"
#include "WPILib.h"

/** Driveline PID Subsystem: Used to drive the main wheels.
 *
 */
class Driveline: public PIDSubsystem
{
private:
	RobotDrive *m_robotDrive;
	CANTalon *m_leftFrontMotorController;
	CANTalon *m_rightFrontMotorController;
	CANTalon *m_leftRearMotorController;
	CANTalon *m_rightRearMotorController;

	ADXRS450_Gyro *m_gyro;
	DrivelinePIDMode m_drivelinePIDMode;

protected:


public:
	Driveline();
	void InitDefaultCommand();
	void Drive();
	void Drive(double move, double rotate);
	void DriveMagnitudeCurve(double magnitude, double curve);
	void SetPIDMode(DrivelinePIDMode mode, double p, double i, double d, double f);
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	double GetDrivelineDistance();
	void ResetDrivelineDistance();
	double GetDrivelineSpeed();
	double GetDrivelineCurrent();
	double GetY(Joystick *stick);
};

#endif
