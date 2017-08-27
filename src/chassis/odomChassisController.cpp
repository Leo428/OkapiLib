#include "chassis/odomChassisController.h"
#include "odometry/odomMath.h"
#include <cmath>

namespace okapi {
  void OdomChassisControllerPid::driveToPoint(const float ix, const float iy, const bool ibackwards, const float ioffset) {
    DistanceAndAngle daa = OdomMath::computeDistanceAndAngleToPoint(ix, iy, Odometry::getState());

    if (ibackwards) {
      daa.theta += 180;
      daa.length *= -1;
    }

    if (std::abs(daa.length - ioffset) > moveThreshold) {
      ChassisControllerPid::pointTurn(daa.theta);
      ChassisControllerPid::driveStraight(daa.length - ioffset);
    }
  }

  void OdomChassisControllerPid::turnToAngle(const float iangle) {
    ChassisControllerPid::pointTurn(iangle - Odometry::getState().theta);
  }

  void OdomChassisControllerMP::driveToPoint(const float ix, const float iy, const bool ibackwards, const float ioffset) {
    DistanceAndAngle daa = OdomMath::computeDistanceAndAngleToPoint(ix, iy, Odometry::getState());

    if (ibackwards) {
      daa.theta += 180;
      daa.length *= -1;
    }

    if (std::abs(daa.length - ioffset) > moveThreshold) {
      ChassisControllerMP::pointTurn(daa.theta);
      ChassisControllerMP::driveStraight(daa.length - ioffset);
    }
  }

  void OdomChassisControllerMP::turnToAngle(const float iangle) {
    ChassisControllerMP::pointTurn(iangle - Odometry::getState().theta);
  }
}