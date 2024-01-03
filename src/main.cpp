#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "drive.cpp"
#include "pros/motors.h"
#include "pros/api_legacy.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::Motor motorFR(14, false);
pros::Motor motorTR(11, false);
pros::Motor motorBR(10, false);
pros::Motor_Group rightMotors {motorFR, motorTR, motorBR};

pros::Motor motorFL(4, true);
pros::Motor motorTL(13, true);
pros::Motor motorBL(1, true);
pros::Motor_Group leftMotors {motorFL, motorTL, motorBL};

pros::Motor_Group allMotors {motorFL, motorTL, motorBL, motorFR, motorTR, motorBR};

pros::Motor cata(5, true);

void puncher() { // da puncha B)
	if (master.get_digital(DIGITAL_A)){
		cata.move_velocity(85); //change cata speed here !!
	} else{
		cata.move_velocity(0);
	};
}

Drivetrain testdrive(0.5, 0.7, 1, 0.5);

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

// runs drivetrain, input num between 0 and 1 for speed

void opcontrol() {
	while(true){
		testdrive.move(true, true);
		puncher();
	}
}