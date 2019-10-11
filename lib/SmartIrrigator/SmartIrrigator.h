/*
	SmartIrrigator.h - Library for
	Created by lejbron, .
*/

#ifndef SmartIrrigator_h
#define SmartIrrigator_h

#include "Arduino.h"

class SmartIrrigator
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
		void leftScan(IRrecv irrecv);*/
		void stopScan();


	private:
		//void scan(bool dir, IRrecv irrecv);
		int _stepPin, _directionPin, _enablePin;
		int _irrecvPin;
		decode_results _irRes;
		bool _scanStopFlag;
};

#endif
