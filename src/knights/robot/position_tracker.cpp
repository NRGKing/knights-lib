#include "knights/robot/position_tracker.h"

using namespace knights;

Position_Tracker::Position_Tracker(pros::Rotation *rotation, float wheel_diameter, float gear_ratio, float offset) 
    : rotation(rotation), wheel_diameter(wheel_diameter), gear_ratio(gear_ratio), offset(offset) {
};

Position_Tracker::Position_Tracker(pros::adi::Encoder *adi_encoder, float wheel_diameter, float gear_ratio, float offset) 
    : adi_encoder(adi_encoder), wheel_diameter(wheel_diameter), gear_ratio(gear_ratio), offset(offset) {
};

Position_Tracker::Position_Tracker(pros::Motor *motor, float wheel_diameter, float gear_ratio, float offset) 
    : motor(motor), wheel_diameter(wheel_diameter), gear_ratio(gear_ratio), offset(offset) {
};

float Position_Tracker::get_distance_travelled() {
    if (this->rotation != NULL) {
        return this->rotation->get_position() * ((this->wheel_diameter * this->gear_ratio * M_PI) / 36000); // this works in centidegrees
    } else if (this->adi_encoder != NULL) {
        return this->adi_encoder->get_value() * ((this->wheel_diameter * this->gear_ratio * M_PI) / 360);
    } else if (this->motor != NULL) {
        return this->motor->get_position() * ((this->wheel_diameter * this->gear_ratio * M_PI) / 360);
    } else {
        return 0.0;
    }
}

Position_Tracker_Group::Position_Tracker_Group(knights::Position_Tracker *right, knights::Position_Tracker *left, knights::Position_Tracker *front, knights::Position_Tracker *back)
    : right_tracker(right), left_tracker(left), front_tracker(front), back_tracker(back) {
}

Position_Tracker_Group::Position_Tracker_Group(knights::Position_Tracker *right, knights::Position_Tracker *left, knights::Position_Tracker *back)
    : right_tracker(right), left_tracker(left), back_tracker(back) {
}

Position_Tracker_Group::Position_Tracker_Group(knights::Position_Tracker *right, knights::Position_Tracker *left)
    : right_tracker(right), left_tracker(left) {
}

Position_Tracker_Group::Position_Tracker_Group(knights::Position_Tracker *middle, knights::Position_Tracker *back, pros::IMU *inertial)
    : right_tracker(middle), back_tracker(back), inertial(inertial) {
}

void Position_Tracker::reset() {
    if (this->rotation != NULL) {
        this->rotation->reset_position();
        return;
    } else if (this->adi_encoder != NULL) {
        this->adi_encoder->reset();
        return;
    } else if (this->motor != NULL) {
        this->motor->set_zero_position(0.0);
        return;
    }
}

float Position_Tracker::get_offset() {
    return this->offset;
}