#include "IRremote.h"
#include "RotorTableR.h"

#define MAX_HOLD_TIME 100 //miliseconds

IRrecv irConsole(5);

decode_results irRes;

// Troyka-Stepper подключён к следующим пинам:
const byte stepPin = 3;
const byte directionPin = 4;
const byte enablePin = 2;

// Necessary for long press button control
bool rPressed = false, lPressed = false;
int rState = LOW, lState = LOW;
long lastPressTime = 0;

RotorTableR smartTable (stepPin, directionPin, enablePin);

void setup() {
  Serial.begin(9600); // выставляем скорость COM порта
  irConsole.enableIRIn(); // запускаем прием
}

void loop() {
  if ( irConsole.decode( &irRes )) { // если данные пришли
    switch ( irRes.value ) {
//шаг по часовой стрелке
  case 0xFF5AA5:
        rotateT(true);
        rPressed = true;
        Serial.println("Right button press ");
        Serial.println(irRes.value, HEX ); 
        break;
  case 0xFF10EF:
        rotateT(false);
        lPressed = true;
        Serial.println("Left button press ");
        Serial.println(irRes.value, HEX ); 
        break;
  case 0xFFFFFFFF:
        if (rState == LOW && rPressed) { 
          rState = HIGH;  // Button pressed, so set state to HIGH
          rotateT(true);
        }
        else if (lState == LOW && lPressed) { 
          lState = HIGH;  // Button pressed, so set state to HIGH
          rotateT(false);
        }        
        lastPressTime = millis();
        break;
    }    
    irConsole.resume(); // принимаем следующую команду
  }
  if (rState == HIGH && millis() - lastPressTime > MAX_HOLD_TIME) {
    rState = LOW; // Haven't heard from the button for a while, so not pressed
    rPressed = false;
    Serial.println("Right button flags dropped");
  }
  else if (lState == HIGH && millis() - lastPressTime > MAX_HOLD_TIME) {
    lState = LOW; // Haven't heard from the button for a while, so not pressed
    lPressed = false;
    Serial.println("Left button flags dropped");
  }
}

// true - clockwise
// false - counterclockwise
void rotateT(bool dir) {
  Serial.println("=== Table rotation func entered ===");
// Задаём направление вращения 
  if(dir) {
    Serial.println("* Clockwise directrion >>>");
    smartTable.setClockwiseDir(); }
  else {
    Serial.println("* CounterClockwise directrion <<<");
    smartTable.setCounterClockwiseDir(); }
    
  while(1) {
    if(dir)
      smartTable.stepRight();
    else
      smartTable.stepLeft();
    if(irConsole.decode(&irRes)) {
      Serial.println(irRes.value, HEX );
      irConsole.resume();
    } else {
      smartTable.turnOff();
      Serial.println("Stop press");
      break;
    }
  }
 
  Serial.println("=== Clockwise move func end ===");
}
