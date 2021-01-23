/*
	IPlant.h - Library for describing plant auto-irrigation details.
	Created by lejbron, 16.10.2019
*/

#include "Arduino.h"
#include "IPlant.h"

IPlant::IPlant(const byte fc28AnalogPin, const byte fc28DigitalPin,
   const byte mosfetPin, String plant_name)
{
  pinMode(mosfetPin, OUTPUT);

	_fc28AnalogPin=fc28AnalogPin;
  _fc28AnalogPin=fc28DigitalPin;
	_mosfetPin=mosfetPin;
	_plant_name=plant_name;

	if(DEBUG_MODE  == true)
  {
    Serial.begin(9600);
  }
}

String IPlant::getName()
{
  if (DEBUG_MODE == true)
  {
    Serial.print(_plant_name);
    Serial.println("%");
  }

  return _plant_name;
}

int IPlant::getMositure()
{
  int mos_value;

  mos_value= analogRead(_fc28AnalogPin);
  mos_value = map(mos_value,550,10,0,100);

  if (DEBUG_MODE == true)
  {
    Serial.print(_plant_name);
    Serial.print(" mositure: ");
    Serial.print(mos_value);
    Serial.println("%");
  }

  return mos_value;
}

void IPlant::waterPlant(int volume)
{
  digitalWrite(_mosfetPin, HIGH);
  delay(volume);
  digitalWrite(_mosfetPin, LOW);
  
  if (DEBUG_MODE == true)
  {
    Serial.print(_plant_name);
    Serial.println(" watered sucessfully.");
  }
}
