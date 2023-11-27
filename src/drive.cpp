#include "main.h"
#include "pros/misc.h"

class Drivetrain { // all the code for the drive in manual
    private:
        double joystickdeadband;
        double scalingweight;
        double turbodrivespeed;
        double standarddrivespeed;
        double drivespeed; //switches between turbo nd standard :)
        int drivedirection; // 1 or -1
        int power;
        int turn;
        int left;
        int right;

		// vvv functions that make the joystick less sensitive at lower values (prevents unintentional drift)
		// graph explanation --> https://www.desmos.com/calculator/l3oakkxwo7
		// thanks team a :D
		double cubicFunction(double input) {
			return ((scalingweight * input * input * input) + ((1.0 - scalingweight) * input));
		}
		double cubicDeadband(double input) {
			if (fabs(input) < joystickdeadband) {
				return 0.0;
			}else{
				return (
				(cubicFunction(input) - ((fabs(input)/input) * cubicFunction(joystickdeadband)))
				/(1.0 - cubicFunction(joystickdeadband))
				); // idek what this means but my brother said it makes a difference of 4 rpm :(
			}
		}

    public:
		Drivetrain(double deadband, double scaleWeight, double turboSpeed, double standardSpeed){
			joystickdeadband = deadband;
			scalingweight = scaleWeight;
			turbodrivespeed = turboSpeed;
			standarddrivespeed = standardSpeed;
			drivespeed = standarddrivespeed;
			drivedirection = 1;
		} // set deadband to 0 to not restrict the joystick, set scale weight to 0 to make joystick movement linear
        void move(bool speedSwitchEnabled, bool directionSwitchEnabled) {
            power = (master.get_analog(ANALOG_LEFT_Y))/0.635;
            turn = (master.get_analog(ANALOG_RIGHT_X))/0.635;
			std::cout << master.get_analog(ANALOG_LEFT_Y) << " <-- left joystick" << '\n';
			std::cout << power << " <-- left joystick divided by 0.635" << '\n';

            if (speedSwitchEnabled) {
                if (master.get_digital_new_press(DIGITAL_Y) && drivespeed == standarddrivespeed) {
                    drivespeed = turbodrivespeed;
                } else if (master.get_digital_new_press(DIGITAL_Y) && drivespeed == turbodrivespeed) {
                    drivespeed = standarddrivespeed;
                }
				std::cout << "speed multiplier: " << drivespeed << '\n';
            }

			// old equation to convert the joystick values to motor inputs
			// left = (power + (turn*drivespeed)) * drivespeed;
            // right = (power - (turn*drivespeed)) * drivespeed;

			// new equation
			// this one makes more sense to me
			left = (power + turn) * drivespeed;
            right = (power - turn) * drivespeed;

			std::cout << left << " <-- left motors velocity input" << '\n';
			std::cout << right << " <-- right motors velocity input" << '\n';

            if (directionSwitchEnabled) {
                if (master.get_digital_new_press(DIGITAL_X) && drivedirection == 1) {
                    drivedirection = -1;
                } else if (master.get_digital_new_press(DIGITAL_X) && drivedirection == -1) {
                    drivedirection = 1;
                }
				std::cout << "drive direction is now " << drivedirection << '\n';
            }

            leftMotors.move_velocity(drivedirection * (cubicDeadband(left)));
            rightMotors.move_velocity(drivedirection * (cubicDeadband(right)));

			std::cout << "left motor total vel " << (drivedirection * (cubicDeadband(left))) << '\n';
			std::cout << "right motor total vel " << (drivedirection * (cubicDeadband(right))) << '\n';

        }
};