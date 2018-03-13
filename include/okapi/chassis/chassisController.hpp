/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef _OKAPI_CHASSISCONTROLLER_HPP_
#define _OKAPI_CHASSISCONTROLLER_HPP_

#include "okapi/chassis/chassisModel.hpp"
#include "okapi/control/pidController.hpp"
#include <memory>

namespace okapi {
  class ChassisController {
  public:
    ChassisController(const ChassisModelParams& imodelParams):
      model(imodelParams.make()) {}

    ChassisController(const std::shared_ptr<ChassisModel>& imodel):
      model(imodel) {}

    virtual ~ChassisController() = default;

    /**
     * Drives the robot straight.
     * 
     * @param itarget Distance to travel
     */
    virtual void driveStraight(const int itarget) = 0;

    /**
     * Turns the robot clockwise in place.
     * 
     * @param idegTarget Degrees to turn for
     */
    virtual void pointTurn(const float idegTarget) = 0;

    //Passed through to internal ChassisModel
    void driveForward(const int power) { model->driveForward(power); }
    void driveVector(const int distPower, const int anglePower) { model->driveVector(distPower, anglePower); }
    void turnClockwise(const int power) { model->turnClockwise(power); }
    void stop() { model->stop(); }
    void tank(const int leftVal, const int rightVal, const int threshold = 0) { model->tank(leftVal, rightVal, threshold); }
    void arcade(int verticalVal, int horizontalVal, const int threshold = 0) { model->arcade(verticalVal, horizontalVal, threshold); }
    void left(const int val) { model->left(val); }
    void leftTS(const int val) { model->leftTS(val); }
    void right(const int val) { model->right(val); }
    void rightTS(const int val) { model->rightTS(val); }
    std::valarray<int> getSensorVals() { return model->getSensorVals(); }

  protected:
    std::shared_ptr<ChassisModel> model;
  };

  class ChassisControllerPid : public virtual ChassisController {
  public:
    ChassisControllerPid(const ChassisModelParams& imodelParams,
      const PidControllerParams& idistanceParams, const PidControllerParams& iangleParams):
      ChassisController(imodelParams),
      distancePid(idistanceParams),
      anglePid(iangleParams) {}

    ChassisControllerPid(const std::shared_ptr<ChassisModel>& imodel,
      const PidControllerParams& idistanceParams, const PidControllerParams& iangleParams):
      ChassisController(imodel),
      distancePid(idistanceParams),
      anglePid(iangleParams) {}

    virtual ~ChassisControllerPid() {
      delete &distancePid;
      delete &anglePid;
    }

    /**
     * Drives the robot straight.
     * 
     * @param itarget Distance to travel
     */
    void driveStraight(const int itarget) override;

    /**
     * Turns the robot clockwise in place.
     * 
     * @param idegTarget Degrees to turn for
     */
    void pointTurn(float idegTarget) override;

  protected:
    PidController distancePid, anglePid;
  };
}

#endif