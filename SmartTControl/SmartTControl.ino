/*
Two Buttons for Stepper Motor control

 lejbron
 */

#include "OneButton.h"

//контроль вращения
#define STEP_COUNT 50
//количество снимков 
#define SHOTS_COUNT 5

#define SHOT 12
#define SHOT_LED 11

//scan delays control - in miliseconds
#define D_TABLE_STOP 500
#define D_PHOTO_TAKE 200
#define D_PHOTO_SAVE 1000 

OneButton shotCntrlB(A0, true);

// motor Control Buttons
OneButton mRightCntrlB(A1, true);  
OneButton mLeftCntrlB(A2, true);

// Scan process - left / right modes
OneButton scanRightB(A3, true);
OneButton scanLeftB(A4, true);

// Troyka-Stepper подключён к следующим пинам:
const byte enablePin = 2;
const byte stepPin = 3;
const byte directionPin = 4;
 
// Выдержка для регулировки скорости вращения
int delayTime = 10;
// Флаг использования автоспуска
bool shotFlag = false;
//Флаг ручной остановки сканирования
bool scanStopFlag = false;

void setup() { 
  shotCntrlB.attachClick(autoShotUsage);
  
  mRightCntrlB.attachClick(click1);
  mRightCntrlB.attachLongPressStart(longPressStart1);
  mRightCntrlB.attachLongPressStop(longPressStop1);
  mRightCntrlB.attachDuringLongPress(longPress1);
  
  mLeftCntrlB.attachClick(click2);
  mLeftCntrlB.attachLongPressStart(longPressStart2);
  mLeftCntrlB.attachLongPressStop(longPressStop2);
  mLeftCntrlB.attachDuringLongPress(longPress2);

  scanRightB.attachClick(rightScan);
  scanRightB.attachDoubleClick(stopScan);
  scanLeftB.attachClick(leftScan);
 // scanLeftB.attachDoubleClick(stopScan);
  
  pinMode(stepPin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  pinMode(enablePin, OUTPUT);

  pinMode(SHOT, OUTPUT);
  pinMode(SHOT_LED, OUTPUT);
}

void loop() {
  // keep watching the push buttons:
  shotCntrlB.tick();
  mRightCntrlB.tick();
  mLeftCntrlB.tick();
  scanRightB.tick();
  scanLeftB.tick();
} 

void click1() {
  digitalWrite(enablePin, HIGH);
  stepLeft();
  digitalWrite(enablePin, LOW);
} 

void longPressStart1() {
  digitalWrite(enablePin, HIGH);
  digitalWrite(directionPin, LOW);
  motorStep();
} 

void longPress1() {
  motorStep();
} 

void longPressStop1() {
  digitalWrite(stepPin, LOW);
  digitalWrite(enablePin, LOW);
} 

void click2() {
  digitalWrite(enablePin, HIGH);
  stepRight();
  digitalWrite(enablePin, LOW);
}

void longPressStart2() {
  digitalWrite(enablePin, HIGH);
  digitalWrite(directionPin, HIGH);
  motorStep();
} 
void longPress2() {
  motorStep();
} 

void longPressStop2() {
  digitalWrite(stepPin, LOW);
  digitalWrite(enablePin, LOW);
} 

void stepRight() {
// Задаём направление вращения по часовой стрелке
  digitalWrite(directionPin, HIGH);
 
// Делаем STEP_COUNT шагов
  for (int i = 0; i < STEP_COUNT; ++i) 
    motorStep();
}

void stepLeft() {
  //Задаём направление вращения против часовой стрелки
  digitalWrite(directionPin, LOW);
 
// Делаем STEP_COUNT шагов
  for (int i = 0; i < STEP_COUNT; ++i) 
    motorStep();
}

void motorStep() {
    digitalWrite(stepPin, HIGH);
    delay(delayTime);
 
    digitalWrite(stepPin, LOW);
    delay(delayTime);
}

void autoShotUsage()
{
  if(shotFlag) 
    digitalWrite(SHOT_LED, LOW);
  else 
    digitalWrite(SHOT_LED, HIGH);
  
  shotFlag = !shotFlag;
}

void rightScan() {
  scanStopFlag = false;
  scan(true);
}

void leftScan() {
  scanStopFlag = false;
  scan(false);
}

//dir --> direction : true - RIGHT / false - LEFT
void scan(bool dir) 
{
  //включаем двигатель
  digitalWrite(enablePin, HIGH);
  
  // Для каждого из необходимого количества снимков...
  for (int i = 0; i < SHOTS_COUNT; ++i) {
    if(!scanStopFlag) {
      // Ждём 500 мс, чтобы столик остановился
      delay(D_TABLE_STOP);
      
      if(shotFlag) {
        // Замыкаем реле, происходит съёмка
        digitalWrite(SHOT, HIGH);
        delay(D_PHOTO_TAKE);
        // Размыкаем реле
        digitalWrite(SHOT, LOW);
      }  
      // Выдержка, чтобы фотоаппарат успел записать снимок на карту
      delay(D_PHOTO_SAVE);
 
      // Поворачиваем столик на необходимое количество шагов
      if(dir)
        stepRight();
      if(!dir)
        stepLeft();
    }
  }
  
// После завершения съёмки отключаем двигатель
 digitalWrite(enablePin, LOW);
}

void stopScan()
{
  scanStopFlag = true;
  digitalWrite(SHOT_LED, HIGH);
  delay(200);
  digitalWrite(SHOT_LED, LOW);
  digitalWrite(stepPin, LOW);
  digitalWrite(enablePin, LOW);
}

