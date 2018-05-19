#include <IRremote.h>
#include "RotorTableR.h"

#define MAX_TIME 150 // max ms between codes
#define LED_PIN 13
long lastPressTime = 0;
int state = LOW;

const byte stepPin = 3;
const byte directionPin = 4;
const byte enablePin = 2;

IRrecv irrecv(5);
decode_results results;

RotorTableR smartTable (stepPin, directionPin, enablePin, irrecv);

void setup()
{
  Serial.begin(9600); // выставляем скорость COM порта
  pinMode(LED_PIN, OUTPUT);  // Status on pin 3 LED
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.value == 0xFFFFFFFF) {  // Can check for a specific button here
      if (state == LOW) { 
        state = HIGH;  // Button pressed, so set state to HIGH
        smartTable.stepRight();
        Serial.println( results.value, HEX ); // печатаем данные
      }
      moveRight();
      lastPressTime = millis();
    }
    irrecv.resume(); // Receive the next value
    Serial.println( results.value, HEX ); // печатаем данные
  }
  if (state == HIGH && millis() - lastPressTime > MAX_TIME) {
    state = LOW; // Haven't heard from the button for a while, so not pressed
    //digitalWrite(LED_PIN, LOW);
  }
}

void moveRight() {
  Serial.println("=== Clockwise move func entered ===");
// Задаём направление вращения по часовой стрелке
  smartTable.setClockwiseDir();
  while(1) {
    smartTable.stepRight();
    if(irrecv.decode(&results)) {
      Serial.println(results.value, HEX );
      irrecv.resume();
    } else {
        smartTable.turnOff();
        Serial.println("Stop press");
        break;
    }
  }
  smartTable.turnOff();
  Serial.println("=== Clockwise move func end ===");
}
