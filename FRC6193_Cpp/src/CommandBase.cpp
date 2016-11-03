#include "CommandBase.h"
#include "Subsystems/Driveline.h"
#include "Commands/Scheduler.h"

// Initialize a single static instance of all of your subsystems to NULL

//std::unique_ptr<ExampleSubsystem> CommandBase::examplesubsystem;

//Arm* CommandBase::arm = NULL;
//Lift* CommandBase::lift = NULL;
//Turret* CommandBase::turret = NULL;
Driveline* CommandBase::driveline = NULL;
OI* CommandBase::oi = NULL;
//RoboRIOClient* CommandBase::piTcpClient = NULL;

CommandBase::CommandBase(const std::string &name) : Command(name)
{
}

CommandBase::CommandBase() :
		Command()
{

}

void CommandBase::init()
{
	// Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	//examplesubsystem.reset(new ExampleSubsystem());
//	arm = new Arm();
//	lift = new Lift();
//	turret = new Turret();
	driveline = new Driveline();
	oi = new OI();
//	piTcpClient = new RoboRIOClient();
}
