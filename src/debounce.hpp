#ifndef __DEBOUNCE_H__
#define __DEBOUNCE_H__

#include <Arduino.h>

const uint8_t MASK = 0b11000111;

struct Debounce {
  Debounce(uint8_t pin) : enabled(0), pin(pin), interval(5), onAssertFn(NULL), onDessertFn(NULL) {}

  void setOnAssertdFn(void (*fn)(void)) {
    onAssertFn = fn;
  }

  void setOnDeassertFn(void (*fn)(void)) {
    onDessertFn = fn;
  }

  void dispatch() {
    if (onAssertFn != NULL && asserted()) onAssertFn();
    else if (onDessertFn != NULL && deasserted()) onDessertFn();
  }

  void enable() {
    enabled = true;
  }

  void disable() {
    enabled = false;
  }

  void tick() {
    uint32_t time = millis();
    if (enabled && time - lastCheck > interval) {
      advance(digitalRead(pin));
      dispatch();
      lastCheck = time;
    }
  }

  void setInterval(uint16_t interval) {
    interval = interval;
  }

private:
  uint8_t asserted() {
    uint8_t asserted = 0;
    if ((history & MASK) == 0b00000111) {
      asserted = 1;
      history = 0xFF;
    }
    return asserted;
  }

  uint8_t deasserted(){
    uint8_t deasserted = 0;
    if ((history & MASK) == 0b11000000) {
      deasserted = 1;
      history = 0x00;
    }
    return deasserted;
  }

  void advance(bool state) {
    history <<= 1;
    history |= state;
  }

  bool enabled;
  uint8_t pin;
  uint8_t interval;
  uint32_t lastCheck;
  void (*onAssertFn)(void);
  void (*onDessertFn)(void);
  uint8_t history = 0;
};

#endif // __DEBOUNCE_H__

