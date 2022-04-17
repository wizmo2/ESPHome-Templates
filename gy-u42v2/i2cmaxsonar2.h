#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {

class I2CMaxSonarSensor2 : public sensor::Sensor, public PollingComponent {
 public:
  //I2CMaxSonarSensor2() : PollingComponent(15000) { }  // 1 hr for energy saving
  I2CMaxSonarSensor2(uint32_t update_interval) : PollingComponent(update_interval) { }
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA; }
  void update() override;
};

}  // namespace esphome