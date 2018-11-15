/*
	RotorTableR.h - Library for remote control of stepper motor by IR console.
	Created by lejbron, May 10.05.2018.
*/

#include "Arduino.h"
#include "RotorTableR.h"

RotorTableR::RotorTableR(const byte stepPin, const byte directionPin, const byte enablePin)
{
	//irrecv.enableIRIn();
	
	pinMode(stepPin, OUTPUT);
	pinMode(directionPin, OUTPUT);
	pinMode(enablePin, OUTPUT);
	
	_stepPin=stepPin;
	_directionPin=directionPin;
	_enablePin=enablePin;
	
	//for debug logging
	Serial.begin(9600); // выставляем скорость COM порта
}

void RotorTableR::motorStep()
{
	digitalWrite(_stepPin, HIGH);
    delay(DELAY_TIME);
 
    digitalWrite(_stepPin, LOW);
    delay(DELAY_TIME);
}

void RotorTableR::setClockwiseDir()
{
	digitalWrite(_enablePin, HIGH);
	digitalWrite(_directionPin, HIGH);
}

void RotorTableR::setCounterClockwiseDir()
{
	digitalWrite(_enablePin, HIGH);
	digitalWrite(_directionPin, LOW);
}

void RotorTableR::turnOff()
{
	digitalWrite(_enablePin, LOW);
}

void RotorTableR::stepRight() {
  Serial.println("=== Clockwise step func entered ===");
// Задаём направление вращения по часовой стрелке
  digitalWrite(_enablePin, HIGH);
  digitalWrite(_directionPin, HIGH);
 
// Делаем STEP_COUNT шагов
  for (int i = 0; i < STEP_COUNT; ++i) 
    motorStep();

  digitalWrite(_enablePin, LOW);
  Serial.println("=== Clockwise step func end ===");
}

void RotorTableR::stepLeft() {
  Serial.println("=== CounterClockwise step func entered ===");
  //Задаём направление вращения против часовой стрелки
  digitalWrite(_enablePin, HIGH);
  digitalWrite(_directionPin, LOW);
 
// Делаем STEP_COUNT шагов
  for (int i = 0; i < STEP_COUNT; ++i) 
    motorStep();

  digitalWrite(_enablePin, LOW);
  Serial.println("=== CounterClockwise step func end ===");
}

/*void RotorTableR::stopScan()
{
	Serial.println("Stop func entered");
	_scanStopFlag = true;
	digitalWrite(_stepPin, LOW);
	digitalWrite(_enablePin, LOW);
}

void RotorTableR::rightScan(IRrecv irrecv)
{
	_scanStopFlag = false;
	scan(true, irrecv);
}

void RotorTableR::leftScan(IRrecv irrecv)
{
	_scanStopFlag = false;
	scan(false, irrecv);
}

void RotorTableR::scan(bool dir, IRrecv irrecv)
{
	irrecv.enableIRIn();
//включаем двигатель
	digitalWrite(_enablePin, HIGH);
// Для каждого из необходимого количества снимков...
	for (int i = 0; i < SHOTS_COUNT; ++i) {
		if(!_scanStopFlag) {
      // Поворачиваем столик на необходимое количество шагов
		if(dir)
			stepRight();
		if(!dir)
			stepLeft();
		if(irrecv.decode( &_irRes ) && _irRes.value == B_STOP) {
			Serial.println("Stop try");
			stopScan();
		}
		irrecv.resume();
    }
  }
  
// После завершения съёмки отключаем двигатель
 digitalWrite(_enablePin, LOW);
}*/