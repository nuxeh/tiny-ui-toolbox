#ifndef __DEBOUNCE_H__
#define __DEBOUNCE_H__

#include <Arduino.h>

#define ACTIVE_HIGH true
#define ACTIVE_LOW false

const uint8_t MASK = 0b11000111;

struct Debounce {
  Debounce(uint8_t pin) : enabled(0), pin(pin), interval(5), onAssertFn(NULL), onDessertFn(NULL), activeState(0) {}
  Debounce(uint8_t pin, bool state) : enabled(0), pin(pin), interval(5), onAssertFn(NULL), onDessertFn(NULL), activeState(state) {}

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

  void begin() {
    if (activeState) {
      pinMode(pin, INPUT);
    } else {
      pinMode(pin, INPUT_PULLUP);
    }
    enable();
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
      bool rawState = digitalRead(pin);
      if (activeState) {
        advance(rawState);
      } else {
        advance(!rawState);
      }
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
  uint8_t history;
  bool activeState;
};

#endif // __DEBOUNCE_H__

