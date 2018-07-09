/**
 * @author Ryan Benasutti, WPI
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "test/tests/api/implMocks.hpp"
#include "okapi/api/control/util/settledUtil.hpp"
#include "okapi/api/device/motor/abstractMotor.hpp"
#include "okapi/api/util/abstractTimer.hpp"
#include <chrono>

namespace okapi {
MockMotor::MockMotor() = default;

void MockMotor::controllerSet(const double ivalue) {
}

int32_t MockMotor::moveAbsolute(const double iposition, const std::int32_t ivelocity) const {
  lastPosition = (int16_t)iposition;
  return 0;
}

int32_t MockMotor::moveRelative(const double iposition, const std::int32_t ivelocity) const {
  lastPosition += iposition;
  return 0;
}

double MockMotor::getTargetPosition() const {
  return 0;
}

double MockMotor::getPosition() const {
  return 0;
}

int32_t MockMotor::getTargetVelocity() const {
  return 0;
}

double MockMotor::getActualVelocity() const {
  return 0;
}

int32_t MockMotor::tarePosition() const {
  return 0;
}

int32_t MockMotor::setBrakeMode(const brakeMode imode) const {
  return 0;
}

int32_t MockMotor::setCurrentLimit(const std::int32_t ilimit) const {
  return 0;
}

int32_t MockMotor::setEncoderUnits(const encoderUnits iunits) const {
  return 0;
}

int32_t MockMotor::setGearing(const gearset igearset) const {
  return 0;
}

int32_t MockMotor::setReversed(const bool ireverse) const {
  return 0;
}

int32_t MockMotor::setVoltageLimit(const std::int32_t ilimit) const {
  return 0;
}

std::shared_ptr<ContinuousRotarySensor> MockMotor::getEncoder() const {
  return std::shared_ptr<ContinuousRotarySensor>();
}

std::int32_t MockMotor::moveVelocity(const std::int16_t ivelocity) const {
  lastVelocity = ivelocity;
  return 1;
}

std::int32_t MockMotor::moveVoltage(const std::int16_t ivoltage) const {
  lastVoltage = ivoltage;
  return 1;
}

MockTimer::MockTimer() : firstCalled(millis()), lastCalled(firstCalled), mark(firstCalled) {
}

QTime MockTimer::millis() const {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
           std::chrono::high_resolution_clock::now() - epoch)
           .count() *
         millisecond;
}

QTime MockTimer::getDt() {
  const QTime currTime = millis();
  const QTime dt = currTime - lastCalled;
  lastCalled = currTime;
  return dt;
}

QTime MockTimer::getStartingTime() const {
  return firstCalled;
}

QTime MockTimer::getDtFromStart() const {
  return millis() - firstCalled;
}

void MockTimer::placeMark() {
  mark = millis();
}

void MockTimer::placeHardMark() {
  if (hardMark == 0_ms)
    hardMark = millis();
}

QTime MockTimer::clearHardMark() {
  const QTime old = hardMark;
  hardMark = 0_ms;
  return old;
}

QTime MockTimer::getDtFromMark() const {
  return millis() - mark;
}

QTime MockTimer::getDtFromHardMark() const {
  return hardMark == 0_ms ? 0_ms : millis() - hardMark;
}

bool MockTimer::repeat(const QTime time) {
  if (repeatMark == 0_ms) {
    repeatMark = millis();
    return false;
  }

  if (millis() - repeatMark >= time) {
    repeatMark = 0_ms;
    return true;
  }

  return false;
}

bool MockTimer::repeat(const QFrequency frequency) {
  return repeat(QTime(1 / frequency.convert(Hz)));
}

ConstantMockTimer::ConstantMockTimer(const QTime idt) : dtToReturn(idt) {
}

QTime ConstantMockTimer::millis() const {
  return 0_ms;
}

QTime ConstantMockTimer::getDt() {
  return dtToReturn;
}

QTime ConstantMockTimer::getStartingTime() const {
  return 0_ms;
}

QTime ConstantMockTimer::getDtFromStart() const {
  return dtToReturn;
}

void ConstantMockTimer::placeMark() {
}

void ConstantMockTimer::placeHardMark() {
}

QTime ConstantMockTimer::clearHardMark() {
  return 0_ms;
}

QTime ConstantMockTimer::getDtFromMark() const {
  return dtToReturn;
}

QTime ConstantMockTimer::getDtFromHardMark() const {
  return dtToReturn;
}

bool ConstantMockTimer::repeat(QTime time) {
  return false;
}

bool ConstantMockTimer::repeat(QFrequency frequency) {
  return false;
}

std::unique_ptr<SettledUtil> createSettledUtilPtr(const double iatTargetError,
                                                  const double iatTargetDerivative,
                                                  const QTime iatTargetTime) {
  return std::make_unique<SettledUtil>(std::make_unique<MockTimer>(), iatTargetError,
                                       iatTargetDerivative, iatTargetTime);
}
} // namespace okapi