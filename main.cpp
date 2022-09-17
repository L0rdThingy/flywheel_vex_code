/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\josh0                                            */
/*    Created:      Sat Sep 17 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// fly                  motor         1               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

bool enable_flyPIDf;

double error;
double target;
double input;
double derivative;
double prev_error;
double final_power;
double kp;
double kd;
double kf;

double get_vel() { return fly.velocity(rpm); }
void set_rpm(double input) { target = input; }

void set_fly_constants(double KP, double KD, double KF) {
  kp = KP;
  kd = KD;
  kf = KF;
}

int flyPID () {
  
  while (enable_flyPIDf) {
    error = target - get_vel(); //proportion
    derivative = error - prev_error;
    prev_error = error;

    final_power = (error * kp) + (derivative * kd) + (target * kf);
    if (final_power < 0) final_power = 0;

    //fly.spin(fwd, (final_power * (12000.0 / 12.0), voltageUnits::volt));

    vex::task::sleep(10);
  }
  return 1;
}





int main() {

  vex::task fly(flyPID);

  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
}
