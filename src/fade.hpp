#ifndef __FADE_H__
#define __FADE_H__

#include <Arduino.h>

template <typename T = uint8_t>
struct Fade {
  Fade(uint8_t pin) : pin(pin), targetBrightness(0) {};
  Fade(void (*setDutyFn)(T)) : setDutyFn(setDutyFn), targetBrightness(0) {};

  void fadeTo(T brightness, uint16_t milliseconds) {
    targetBrightness = brightness;
    countSinceSet = 0;
    fadeInterval = milliseconds / difference(brightness, currentBrightness);
  }

  void breathe(uint16_t periodMs) {

  }

  void smoothFlash(uint16_t periodMs) {

  }

  void tick() {
    if (currentBrightness != targetBrightness) {
      if (millis() - lastUpdate > fadeInterval) {
        if (currentBrightness < targetBrightness) {
          setDuty(currentBrightness + 1);
        } else if (currentBrightness > targetBrightness) {
          setDuty(currentBrightness - 1);
        }
        lastUpdate = millis();
      }
    }
  }

  void begin() {
    pinMode(pin, OUTPUT);
  }

private:
  void setDuty(T duty) {
    currentBrightness = duty;

    if (setDutyFn != NULL) {
      setDutyFn(duty);
    } else {
      analogWrite(pin, duty);
    }
  }

  T difference(T a, T b) {
    if (a == 0) { // ?
      return b;
    } else if (a > b) {
      return a - b;
    } else {
      return b - a;
    }
  }

  uint8_t pin;
  T currentBrightness;
  T targetBrightness;
  T countSinceSet;
  uint16_t fadeInterval;
  uint32_t lastUpdate;
  void (*setDutyFn)(T);
};

//typedef Fade<uint8_t> 8BitFade;

#endif // __FADE_H__
