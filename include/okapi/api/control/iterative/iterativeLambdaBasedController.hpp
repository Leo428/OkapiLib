/**
 * @author Ryan Benasutti, WPI
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef _OKAPI_ITERATIVELAMBDABASEDCONTROLLER_HPP_
#define _OKAPI_ITERATIVELAMBDABASEDCONTROLLER_HPP_

#include "okapi/api/control/iterative/iterativeController.hpp"
#include "okapi/api/util/timeUtil.hpp"
#include <functional>
#include <memory>

namespace okapi {
class IterativeLambdaBasedController : public IterativeController<double, double> {
  public:
  /**
   * An IterativeController that uses a lambda to implement the IterativeController interface.
   *
   * @param istepFunction A lambda that implement the IterativeController::step() method.
   */
  IterativeLambdaBasedController(std::function<double(double)> istepFunction,
                                 const TimeUtil &itimeUtil);

  /**
   * Do one iteration of the controller. Returns the reading in the range [-1, 1] unless the
   * bounds have been changed with setOutputLimits().
   *
   * @param inewReading new measurement
   * @return controller output
   */
  double step(double inewReading) override;

  /**
   * Sets the target for the controller.
   *
   * @param itarget new target position
   */
  void setTarget(double itarget) override;

  /**
   * Returns the last calculated output of the controller. Output is in the range [-1, 1]
   * unless the bounds have been changed with setOutputLimits().
   */
  double getOutput() const override;

  /**
   * Returns the last error of the controller.
   */
  double getError() const override;

  /**
   * Returns whether the controller has settled at the target. Determining what settling means is
   * implementation-dependent.
   *
   * @return whether the controller is settled
   */
  bool isSettled() override;

  /**
   * Set time between loops in ms.
   *
   * @param isampleTime time between loops
   */
  void setSampleTime(QTime isampleTime) override;

  /**
   * Set controller output bounds. Default bounds are [-1, 1].
   *
   * @param imax max output
   * @param imin min output
   */
  void setOutputLimits(double imax, double imin) override;

  /**
   * Resets the controller so it can start from 0 again properly. Keeps gains and limits from
   * before.
   */
  void reset() override;

  /**
   * Changes whether the controller is off or on. Turning the controller on after it was off will
   * cause the controller to move to its last set target, unless it was reset in that time.
   */
  void flipDisable() override;

  /**
   * Sets whether the controller is off or on. Turning the controller on after it was off will
   * cause the controller to move to its last set target, unless it was reset in that time.
   *
   * @param iisDisabled whether the controller is disabled
   */
  void flipDisable(bool iisDisabled) override;

  /**
   * Returns whether the controller is currently disabled.
   *
   * @return whether the controller is currently disabled
   */
  bool isDisabled() const override;

  /**
   * Get the last set sample time.
   *
   * @return sample time
   */
  QTime getSampleTime() const override;

  protected:
  QTime sampleTime = 10_ms;
  double target = 0;
  double error = 0;

  // Output bounds
  double output = 0;
  double outputMax = 1;
  double outputMin = -1;

  bool isOn = true;

  std::function<double(double)> stepFunction;
  std::unique_ptr<AbstractTimer> loopDtTimer;
  std::unique_ptr<SettledUtil> settledUtil;
};
} // namespace okapi

#endif