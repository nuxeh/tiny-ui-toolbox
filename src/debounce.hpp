#ifndef __DEBOUNCE_H__
#define __DEBOUNCE_H__

#include <Arduino.h>

struct Debounce {
  Debounce(uint8_t pin) : enabled(0), pin(pin), interval(5), onAssertFn(NULL), onDessertFn(NULL) {}

  void setOnAssertdFn(void (*fn)(void)) {
    onAssertFn = fn;
  }

  void setOnDeassertFn(void (*fn)(void)) {
    onDessertFn = fn;
  }

  void deepDebounce() {
    if (onAssertFn != NULL) onAssertFn();


    if (onDessertFn != NULL) onDessertFn();
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
  bool enabled;
  uint8_t pin;
  uint8_t interval;
  uint32_t lastCheck;
  void (*onAssertFn)(void);
  void (*onDessertFn)(void);
};

#endif // __DEBOUNCE_H__

