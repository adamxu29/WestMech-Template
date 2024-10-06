#include "main.h"
#include <cmath>

pros::Motor front_left(1, true);
pros::Motor back_left(2, true);
pros::Motor front_right(3, false);
pros::Motor back_right(4, false);

pros::Motor_Group left_drive(front_left, back_left);
pros::Motor_Group right_drive(front_right, back_right);

pros::IMU imu(5);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	
}


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
float wheel_size = 4.0;
float gear_ratio = 0.8;
int motor_cartridge = 600;

void drive_forward(float distance, int max_speed){
    double circumference = M_PI * wheel_size;
    
    current_position = (left_drive.at(0).get_position() + right_drive.at(0).get_position()) / 2;
    current_postition *= circumference / (motor_cartridge * gear_ratio);

    while(true){
        if(current_position = distance){
            break;
        }

        left_drive.move_velocity(12000 * (max_speed / 100));
        right_drive.move_velocity(12000 * (max_speed / 100));
    }
}

void autonomous() {
    left_drive.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
	right_drive.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);

    drive_forward(24, 75);
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
void opcontrol() {
	while(true){
        double left_power = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		double right_power = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) - controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		left_drive.move_voltage(left_power * (12000.0 / 127));
		right_drive.move_voltage(right_power * (12000.0 / 127));
    }
}
