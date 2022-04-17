#include "esphome.h"
#include "i2cmaxsonar2.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"

namespace esphome {

static const char *const TAG = "I2CMAXSENSOR";

const uint8_t MAXSONAR_DEFAULT_ADDR = 0x70;
const uint8_t MAXSONAR_CMD_START = 81;
const uint8_t MAXSONAR_DEFAULT_DELAY = 100;
const uint8_t MAXSONAR_RESULT_LEN = 2;
const uint8_t MAXSONAR_SETUP_UNLOCK_1 = 170;
const uint8_t MAXSONAR_SETUP_UNLOCK_2 = 165; 

void I2CMaxSonarSensor2::setup() {
	Wire.begin();
}

void I2CMaxSonarSensor2::dump_config() {
  LOG_SENSOR("", "I2CMaxSonar", this);
  LOG_UPDATE_INTERVAL(this);
}

void I2CMaxSonarSensor2::update() {
  uint8_t data[2];
  
  // take reading
  Wire.beginTransmission(MAXSONAR_DEFAULT_ADDR);
  Wire.write(MAXSONAR_CMD_START);
  Wire.endTransmission();
  
  delay(MAXSONAR_DEFAULT_DELAY);
  
  // get reading
  Wire.requestFrom(MAXSONAR_DEFAULT_ADDR, MAXSONAR_RESULT_LEN);
   uint32_t distance_cm = 0;
  if (2 <= Wire.available()){
    distance_cm = Wire.read();
    distance_cm = distance_cm << 8;
    distance_cm |= Wire.read();
  }

  ESP_LOGI(TAG, "Data read: %dcm", distance_cm);

  if (distance_cm < 20) {
    ESP_LOGW(TAG, "Distance measurement out of range");
    this->publish_state(NAN);
  } else {
    this->publish_state(distance_cm / 100.0f);
  }
  this->status_clear_warning();
}

}  // namespace esphome
