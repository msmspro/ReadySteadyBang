#include "Arduino.h"

struct LedState {
  int pin;
  bool isOn = false;
};

class LedPanel {
  private:
    LedState ledsState[5];

  public:
    LedPanel(const int ledsPins[]) {
      for (int i = 0; i < 5; i++) {
        ledsState[i].pin = ledsPins[i];
      }

      applyLeds();
    }

    void blink(int ledNum, int delayMs) {
      ledsState[ledNum].isOn = !ledsState[ledNum].isOn;
      applyLeds();
      delay(delayMs);
      ledsState[ledNum].isOn = !ledsState[ledNum].isOn;
      applyLeds();
      delay(delayMs);
    }

    void blink(int ledsNums[], int arrSize, int delayMs) {
      switchAllLeds(false);
      switchLeds(true, ledsNums, arrSize);
      delay(delayMs);
      switchLeds(false, ledsNums, arrSize);
      delay(delayMs);
    }

    void blinkArrow (bool dir, int repeats) {
      switchAllLeds(false);

      for (int i = 0; i < repeats; i++) {
        for (int i = 0; i < 5; i++) {
          int ledNum = dir ? i : 4 - i;
          switchLed(true, ledNum);
          delay(80);
        }
        for (int i = 0; i < 5; i++) {
          int ledNum = dir ? i : 4 - i;
          switchLed(false, ledNum);
          delay(80);
        }
      }
    }

    void switchLed(bool isOn, int ledNum) {
      ledsState[ledNum].isOn = isOn;
      applyLeds();
    }

    void switchLeds(bool isOn, int ledsNums[], int arrSize) {
      for (int i = 0; i < arrSize; i++) {
        ledsState[ledsNums[i]].isOn = isOn;
      }
      applyLeds();
    }

    void switchAllLeds(bool isOn) {
      for (int i = 0; i < 5; i++) {
        ledsState[i].isOn = isOn;
      }
      applyLeds();
    }

    void blinkAllLeds(int duration) {
      switchAllLeds(false);
      delay(10);
      switchAllLeds(true);
      delay(duration);
      switchAllLeds(false);
      delay(duration);
    }

    void applyLeds() {
      for (int i = 0; i < 5; i++) {
        digitalWrite(ledsState[i].pin, ledsState[i].isOn);
      }
    }
};
