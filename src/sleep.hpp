#ifndef __SLEEP_H__
#define __SLEEP_H__

struct Sleep {
  Sleep() : enabled(0), timeoutMs(0), preSleepFn(NULL), postWakeupFn(NULL) {}

  void kick() {
    lastKick = millis();
  }

  void setPreSleepFn(void (*fn)(void)) {
    preSleepFn = fn;
  }

  void setPostWakeupFn(void (*fn)(void)) {
    postWakeupFn = fn;
  }

  void deepSleep() {
    if (preSleepFn != NULL) preSleepFn();


    if (postWakeupFn != NULL) postWakeupFn();
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

private:
  bool enabled;
  uint16_t timeoutMs;
  uint32_t lastKick;
  void (*preSleepFn)(void);
  void (*postWakeupFn)(void);
};

#endif // __SLEEP_H__
