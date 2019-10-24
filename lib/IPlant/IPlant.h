/*
	IPlant.h - Library for describing plant auto-irrigation details.
	Created by lejbron, 16.10.2019
*/

#ifndef IPlant_h
#define IPlant_h

#define DEBUG_MODE true

#include "Arduino.h"

class IPlant
{
	public:
		IPlant(const byte fc28AnalogPin, const byte fc28DigitalPin,
			const byte mosfetPin, String plant_name);
    int getMositure();
		void waterPlant(int volume);

	private:
		int _fc28AnalogPin, _fc28DigitalPin, _mosfetPin;
		int _current_mositure;
		String _plant_name;
};

#endif
