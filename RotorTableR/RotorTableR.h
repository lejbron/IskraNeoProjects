/*
	RotorTableR.h - Library for remote control of stepper motor by IR console.
	Created by lejbron, May 10.05.2018.
*/

#ifndef RotorTableR_h
#define RotorTableR_h

#include "Arduino.h"
#include "IRremote.h"

//скорость шага двигателя
#define DELAY_TIME 4
//контроль вращения
#define STEP_COUNT 20
/*//количество снимков 
#define SHOTS_COUNT 5

//scan delays control - in miliseconds
#define D_TABLE_STOP 500
#define D_PHOTO_TAKE 200
#define D_PHOTO_SAVE 1000 */

class RotorTableR 
{
	public:
		RotorTableR(const byte stepPin, const byte directionPin, const byte enablePin);
		void motorStep();
		void setClockwiseDir();
		void setCounterClockwiseDir();
		void turnOff();
		void stepRight();
		void stepLeft();
		/*void rightScan(IRrecv irrecv);
		void leftScan(IRrecv irrecv);
		void stopScan();*/
		
	
	private:
		/*void scan(bool dir, IRrecv irrecv);*/
		int _stepPin, _directionPin, _enablePin;
		int _irrecvPin;
		decode_results _irRes;
		bool _scanStopFlag;
};

#endif