#include "main.h"
// #include "okapi/api.hpp"
// using namespace okapi;
// using namespace std;

pros::Motor motorFR(7);
pros::Motor motorBR(10);
pros::Motor motorLF(1);
pros::Motor motorLB(2);
pros::Motor rCata(5, true);
pros::Motor lCata(3);
pros::Controller master(pros::E_CONTROLLER_MASTER);


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {

rCata.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
lCata.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

/*void driveTrainRight()
{
	motorFR = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
	motorFB = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

}

void driveTrainLeft()
{
	motorLF = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	motorLB = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
}*/

void driveTrainAll()
{
	int power = master.get_analog(ANALOG_LEFT_Y);
    int turn = master.get_analog(ANALOG_LEFT_X);
    int left = (-1*(power + ((turn)*0.6)))*0.6;
    int right = (power - ((turn)*0.6))*0.6;
    motorLF.move(left);
	motorLB.move(left);
    motorFR.move(right);
	motorBR.move(right);
}

void catapultAll()
{
	if (master.get_digital(DIGITAL_A)){
	rCata.move_velocity(50);
	lCata.move_velocity(50);
	 } else
	{
	rCata.move_velocity(0);
	lCata.move_velocity(0);
	};
}

void opcontrol() {



while(true)
{
driveTrainAll();
catapultAll();
}

	// shared_ptr<ChassisController> drive =
	// 	ChassisControllerBuilder()
	// 		.withMotors(1, -10)
	// 		.withDimensions(AbstractMotor::gearset::green, {{4_in, 14.75_in}, imev5GreenTPR})
    //         .build();

	// printf("Chassis Controller Built\n")

	// Controller controller;

	// ControllerButton armUpButton(ControllerDigital::A);
	// ControllerButton armDownButton(ControllerDigital::B);
	// ControllerButton clawCloseButton( ControllerDigital::X);
	// ControllerButton clawOpenButton( ControllerDigital::Y);
	// ControllerButton clawCloseSmallButton(ControllerDigital::up);
	// ControllerButton clawOpenSmallButton(ControllerDigital::down);
	// Motor rarmMotor(9);
	// Motor larmMotor(-13);
	// Motor clawMotor(15);

	// MotorGroup arm ({
	// 	rarmMotor,
	// 	larmMotor
	// });


	// while (true) {
	// 	drive->getModel()->tank(controller.getAnalog(ControllerAnalog::leftY),
	// 							controller.getAnalog(ControllerAnalog::rightY));


	// 	if (armUpButton.isPressed()) {
	// 		arm.moveVoltage(6000);
	// 	} else if (armDownButton.isPressed()) {
	// 		arm.moveVoltage(-6000);
	// 	} else {
	// 		arm.moveVoltage(0);
	// 	}	

	// 	if(clawCloseButton.isPressed()){
	// 		clawMotor.moveVoltage(6000);

	// 	} else if (clawOpenButton.isPressed()){
	// 		clawMotor.moveVoltage(-6000);
	// 	}else{
	// 		clawMotor.moveVoltage(0);
	// 	}

	// 	if(clawCloseSmallButton.isPressed()){
	// 		clawMotor.moveVoltage(3000);

	// 	} else if (clawOpenSmallButton.isPressed()){
	// 		clawMotor.moveVoltage(-3000);
	// 	}else{
	// 		clawMotor.moveVoltage(0);
	// 	}

	// 	pros::delay(10);				
	// }
}
