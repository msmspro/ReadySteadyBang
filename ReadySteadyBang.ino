#include "LedPanel.cpp"

const int leds[5] = {8, 9, 10, 11, 12};
LedPanel theLedsPanel(leds);

bool isGameMoment = false;
int winner = 0;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT);
  }

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  attachInterrupt(0, []() -> void {if (isGameMoment) {isGameMoment = false;winner = 1;}}, FALLING);
  attachInterrupt(1, []() -> void {if (isGameMoment) {isGameMoment = false;winner = 2;}}, FALLING);
}

void loop() {
  if (isGameMoment) return;

  if (winner == 1) Serial.println("RED Player Win!!!");
  if (winner == 2) Serial.println("BLUE Player Win!!!");
  blinkToWinner();
  winner = 0;
  
  startNewGame();
}

void startNewGame() {
  welcomBlinks();
  showTrafficLights();
  isGameMoment = true;
}

void welcomBlinks() {
  delay(500);

  for (int i = 0; i < 25; i++) {
    theLedsPanel.switchAllLeds(true);
    delay(50);
    theLedsPanel.switchAllLeds(false);
    delay(50);
  }
  
  delay(500);
}

void showTrafficLights() {
  theLedsPanel.switchAllLeds(false);
  delay(random(1000, 2000));
  int redLeds[] = {2};
  theLedsPanel.switchLeds(true, redLeds, 1);
  delay(random(1000, 10000));
  int yellowLeds[] = {1, 3};
  theLedsPanel.switchLeds(true, yellowLeds, 2);
  delay(random(1000, 20000));
  int greenLeds[] = {0, 4};
  theLedsPanel.switchLeds(true, greenLeds, 2);
}

void blinkToWinner() {
  if (winner == 0) return;
  
  if (winner == 1) theLedsPanel.blinkArrow(false, 10);
  if (winner == 2) theLedsPanel.blinkArrow(true, 10);
}
