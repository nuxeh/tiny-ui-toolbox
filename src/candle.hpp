#ifndef __CANDLE_H__
#define __CANDLE_H__

#include <Arduino.h>

struct Candle {
  Candle(uint8_t pin) : enabled(0), pin(pin), interval(5), setDutyFn(NULL), getRandFn(NULL) {}
  Candle(void (*setDutyFn)(uint8_t)) : enabled(0), interval(5), setDutyFn(setDutyFn), getRandFn(NULL) {}

  void setGetRandFn(uint8_t (*fn)(void)) {
    getRandFn = fn;
  }

  void enable() {
    enabled = true;
  }

  void disable() {
    enabled = false;
  }

  void tick() {
    if (enabled) {

    }
  }

  void setInterval(uint16_t interval) {
    interval = interval;
  }

private:
  void getRand() {
    if (getRandFn != NULL) return onAssertFn();
    return random();
  }

  void getRandRanged() {

  }

  bool enabled;
  uint8_t pin;
  uint8_t interval;
  uint32_t lastCheck;
  void (*setDutyFn)(uint8_t);
  uint8_t (*getRandFn)(void);
};

#endif // __CANDLE_H__

