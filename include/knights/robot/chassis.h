#pragma once

#ifndef _CHASSIS_H
#define _CHASSIS_H

#include "api.h"

#include "knights/robot/drivetrain.h"
#include "knights/robot/position_tracker.h"
#include "knights/util/position.h"


namespace knights {

    class Robot_Chassis {
        private:
            Drivetrain *drivetrain; // the drivetrain to use for the chassis
            Position_Tracker_Group *pos_trackers; // the sensors to use for location tracking
            pros::IMU *inertial; // the inertial sensor to use for heading tracking
            Pos curr_position; // the current position of the robot

            // previous values of the sensors for odometry control
            float prevRight = 0;
            float prevLeft = 0;
            float prevFront = 0;
            float prevBack = 0;
        public:
            // @brief create a robot chassis with provided parameters
            // @param drivetrain the drivetrain to use for the chassis
            // @param pos_trackers the sensors to use for location tracking
            // @param inertial the inertial sensor to use for heading tracking
            Robot_Chassis(Drivetrain *drivetrain, Position_Tracker_Group *pos_trackers, pros::IMU *inertial);

            // @brief set the position of the chassis
            // @param x the desired x
            // @param y the desired y
            // @param heading the desired heading
            void set_position(float x, float y, float heading);

            // @brief update the position of a chassis using its tracking wheels
            void update_position();

    };
}

#endif