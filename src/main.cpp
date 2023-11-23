#include "main.h"
#include "pros/misc.h"
// #include "okapi/api.hpp"
// using namespace okapi;
// using namespace std;

 pros::Motor motorFR(7);
 //pros::Motor motorTR();
 pros::Motor motorBR(10);
 pros::Motor_Group rightMotors {motorFR, motorTR, motorBR};

 pros::Motor motorFL(1);
 //pros::Motor motorTL();
 pros::Motor motorBL(2);
 pros::Motor_Group leftMotors {motorFL, motorTL, motorBL};

 pros::Motor cata(5, true);

 pros::Controller master(pros::E_CONTROLLER_MASTER);

 int turboswitch = 0;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	cata.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
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

void competition_initialize() {
}

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

void driveTrainAll(int switchtoggle) {
	int power = master.get_analog(ANALOG_LEFT_Y);
    int turn = master.get_analog(ANALOG_RIGHT_X);
	int left;
	int right;
	turboswitch = switchtoggle;
	if (turboswitch == 0){
		left = (-1*(power + ((turn)*0.9)))*0.9;
		right = (power - ((turn)*0.9))*0.9;
	} else if (turboswitch == 1){
		left = (-1*(power + ((turn)*1)))*1;
		right = (power - ((turn)*1))*1;
	}
    leftMotors.move_velocity(left);
    rightMotors.move_velocity(right);
}

void catapultAll() {
	if (master.get_digital(DIGITAL_A)){
	cata.move_velocity(85);
	} else{
	cata.move_velocity(0);
	};
}

void opcontrol() {
	while(true){
		if (master.get_digital(DIGITAL_Y) && turboswitch == 1){
			driveTrainAll(0);
		} else if (master.get_digital(DIGITAL_Y) && turboswitch == 0){
			driveTrainAll(1);
		}
		catapultAll();
	}
}