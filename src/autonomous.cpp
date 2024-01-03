#include "main.h"
#include "pros/misc.h"
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
void autonomous() {
	//
	allMotors.move_velocity(180);
	pros::delay(550);
	allMotors.move_velocity(-360);
	pros::delay(500);
	allMotors.move_velocity(0);

	// skills auton:
	// cata.move_velocity(85);
}