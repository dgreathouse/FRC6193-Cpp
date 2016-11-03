/*
 * Robot.h
 *
 *  Created on: Oct 26, 2016
 *      Author: great
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

#include "WPILib.h"
#include "Commands/Command.h"
#include "CommandBase.h"
/** Main robot starting point.
 * This class inherits from the IterativeRobot class.
 * The Field Management System will call the methods in this class during competition.
 * The order of calling is as follows:
 * 1. DisableInit() -> Called once after robot is powered on.
 * 2. DisablePeriodic() -> Continuously called while waiting on field.
 * 3. AutonomousInit() -> Called once when entering autonomous mode
 * 4. AutonomousPeriodic() -> Called periodically until the end of autonomous mode
 * 5. DisableInit() -> Called once
 * 6. DisablePeriodic() -> Continuously for a short period of time before teleop
 * 7. TeleopInit() -> Called once before entering Teleop
 * 8. TeleopPeriodic() -> Called periodically until end of match
 * 9. DisableInit() -> Called once
 * 10. DisablePeriodic() -> Called continuously while power is still on.
 *
 * The rate of all periodic function calls is ~50ms.
 * The function calls have a priority of about 5 on a 0 to 10 priority scale.
 * The DriveStation runs in a separate thread and has a higher priority and is called more often.
 * The PID run in another loop. I think, still searching code.
 */
class Robot : public IterativeRobot
{
public:
	bool m_disabledInitialized;
	bool m_autonomousInitialized;
	bool m_teleopInitialized;
	bool m_testInitialized;
	double m_prevTimeStamp;
private:


	void RobotInit();
	void DisabledInit();
	void DisabledPeriodic();
	void AutonomousInit();
	void AutonomousPeriodic();
	void TeleopInit();
	void TeleopPeriodic();
	void TestPeriodic();
	void StartCompetition();
	void CalculateLoopTIme();
};




#endif /* SRC_ROBOT_H_ */
