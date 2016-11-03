#include "Robot.h"
#include "CommandGroups/AutonomousCommandGroup.h"

/** Robot Initialization method.
 * First method in this file run after the robot is powered up.
 */
void Robot::RobotInit()
{
	m_disabledInitialized = false;
	m_autonomousInitialized = false;
	m_teleopInitialized = false;
	m_testInitialized = false;
	m_prevTimeStamp = 0;
	// Initialize all static references to you subsystems
	CommandBase::init();

}

/** Disabled Initialization.
 * This method is called once each time the robot enters Disabled mode.
 * You can use it to reset any subsystem information you want to clear when
 * the robot is disabled.
 */
void Robot::DisabledInit() {
	CommandBase::driveline->Disable();
}
/** Disabled Periodic.
 * This method is called continuously while the robot is in Disabled mode.
 *
 */
void Robot::DisabledPeriodic() {

	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	int index = (int) SmartDashboard::GetNumber("AutoPlayIndex", 0);
	AutonomousCommandGroup* dacg = new AutonomousCommandGroup(index);
	dacg->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {

}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {
	LiveWindow::GetInstance()->Run();
}
/**
 * No functional changes made to this file
 * Only overriden to report the timing of the called loops.
 * Checking issue for lost packets  and PID control in Autonomous
 */
void Robot::StartCompetition() {
	HALReport(HALUsageReporting::kResourceType_Framework,
			HALUsageReporting::kFramework_Iterative);

	LiveWindow *lw = LiveWindow::GetInstance();
	// first and one-time initialization
	SmartDashboard::init();
	NetworkTable::GetTable("LiveWindow")->GetSubTable("~STATUS~")->PutBoolean(
			"LW Enabled", false);
	RobotInit();

	// Tell the DS that the robot is ready to be enabled
	HALNetworkCommunicationObserveUserProgramStarting();

	// loop forever, calling the appropriate mode-dependent function
	lw->SetEnabled(false);
	while (true) {
		// Call the appropriate function depending upon the current robot mode
		if (IsDisabled()) {
			// call DisabledInit() if we are now just entering disabled mode from
			// either a different mode or from power-on
			if (!m_disabledInitialized) {
				lw->SetEnabled(false);
				DisabledInit();
				m_disabledInitialized = true;
				// reset the initialization flags for the other modes
				m_autonomousInitialized = false;
				m_teleopInitialized = false;
				m_testInitialized = false;
			}
			HALNetworkCommunicationObserveUserProgramDisabled();
			DisabledPeriodic();
		} else if (IsAutonomous()) {
			// call AutonomousInit() if we are now just entering autonomous mode from
			// either a different mode or from power-on
			if (!m_autonomousInitialized) {
				lw->SetEnabled(false);
				AutonomousInit();
				m_autonomousInitialized = true;
				// reset the initialization flags for the other modes
				m_disabledInitialized = false;
				m_teleopInitialized = false;
				m_testInitialized = false;
			}
			HALNetworkCommunicationObserveUserProgramAutonomous();
			AutonomousPeriodic();
		} else if (IsTest()) {
			// call TestInit() if we are now just entering test mode from
			// either a different mode or from power-on
			if (!m_testInitialized) {
				lw->SetEnabled(true);
				TestInit();
				m_testInitialized = true;
				// reset the initialization flags for the other modes
				m_disabledInitialized = false;
				m_autonomousInitialized = false;
				m_teleopInitialized = false;
			}
			HALNetworkCommunicationObserveUserProgramTest();
			TestPeriodic();
		} else {
			// call TeleopInit() if we are now just entering teleop mode from
			// either a different mode or from power-on
			if (!m_teleopInitialized) {
				lw->SetEnabled(false);
				TeleopInit();
				m_teleopInitialized = true;
				// reset the initialization flags for the other modes
				m_disabledInitialized = false;
				m_autonomousInitialized = false;
				m_testInitialized = false;
				Scheduler::GetInstance()->SetEnabled(true);
			}
			HALNetworkCommunicationObserveUserProgramTeleop();
			TeleopPeriodic();
		}
		// wait for driver station data so the loop doesn't hog the CPU
		m_ds.WaitForData();
		CalculateLoopTIme();
	}
}
void Robot::CalculateLoopTIme() {
	// Get the current time stamp from the FPGA. FPGA is the most accurate time that can be captured
	double time = Timer::GetFPGATimestamp();
	// Find the loop time by subtracting the previous time from the current time.
	double loopTime = time - m_prevTimeStamp;
	// Store the current time into the previous time for the next calculation
	m_prevTimeStamp = time;
	// Send it to the SmartDashboard for graphing
	// Data is not usable for the FTA, but it helps understand the issues with the FMS
	SmartDashboard::PutNumber("LoopTime", loopTime);
}

START_ROBOT_CLASS(Robot)

