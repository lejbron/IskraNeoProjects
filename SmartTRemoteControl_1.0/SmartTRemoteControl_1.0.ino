#include "IRremote.h"
#include "RotorTableR.h"

#define IR_RIGHT 0xFF5AA5
#define IR_LEFT 0xFF10EF
#define IR_SCAN_RIGHT 0xFF18E7
#define IR_SCAN_LEFT 0xFF4AB5
#define B_STOP 0xFF38C7
#define B_PRESSED 0xFFFFFFFF

#define MAX_HOLD_TIME 100 //miliseconds

#define SHOTS_COUNT 15

IRrecv irConsole(5);

decode_results irRes;

bool scanStopFlag = false;

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
  case IR_RIGHT:
        rotateT(true);
        rPressed = true;
        Serial.println("Right button press ");
        Serial.println(irRes.value, HEX ); 
        break;
  case IR_LEFT:
        rotateT(false);
        lPressed = true;
        Serial.println("Left button press ");
        Serial.println(irRes.value, HEX ); 
        break;
  case B_PRESSED:
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
  case IR_SCAN_RIGHT:
        scan(true);
        Serial.println("Right scan entered ");
        Serial.println(irRes.value, HEX ); 
        break;
    case IR_SCAN_LEFT:
        scan(false);
        Serial.println("Left scan entered ");
        Serial.println(irRes.value, HEX ); 
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

void scan(bool dir)
{
// Для каждого из необходимого количества снимков...
  for (int i = 0; i < SHOTS_COUNT; ++i) {
    if(!scanStopFlag) {
    // Поворачиваем столик на необходимое количество шагов
      if(dir)
        smartTable.stepRight();
      if(!dir)
        smartTable.stepLeft();
      irConsole.decode( &irRes );
      Serial.println(irRes.value, HEX);
      Serial.println("Stop try");
      if(irConsole.decode( &irRes ) && irRes.value == B_STOP) {
        Serial.println("Stop try");
        scanStopFlag = true;
        smartTable.turnOff();
      }
      irConsole.resume();
    }
  }
  
// После завершения съёмки отключаем двигатель
 scanStopFlag = false;
 smartTable.turnOff();
}

