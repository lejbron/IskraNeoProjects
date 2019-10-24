/*

	 - x2 http://amperka.ru/product/solenoid-valve-normally-open
	 - x2 http://amperka.ru/product/troyka-mosfet-v2
	 - x2 http://rushim.ru/product_info.php?products_id=633
	 - x2 http://rushim.ru/product_info.php?products_id=2246

*/

#include "DHT.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"

#include "IPlant.h"

/*=========SETTINGS=========*/
#define DEBUG false
#define CRITICAL_MOS 45
#define VOLUME 20000
/*=========SETTINGS=========*/

/*=============PINS=============*/
#define DHTPIN 7
#define RELAY_PIN 2

//fc28 analog pins
int fc28_plant_pin1 = A1;
int fc28_plant_pin2 = A2;

int fc28DigitalPin1 = 5;
int fc28DigitalPin2 = 6;

DHT dht(DHTPIN, DHT11);

int mosfetPin1 = 0;
int mosfetPin2 = 1;

LiquidCrystal_I2C lcd(0x27,20,4);


bool f_stop=false;

/*=============PINS=============*/

/*==================================PLANTS==================================*/

IPlant mint(fc28_plant_pin1, fc28DigitalPin1, mosfetPin1, "Mint");
IPlant araucaria(fc28_plant_pin2, fc28DigitalPin2, mosfetPin2, "Araucaria");

/*==================================PLANTS==================================*/

void setup()
{
  if (DEBUG == true)
	{
		Serial.begin(9600);
	}

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  dht.begin();
  
  pinMode(mosfetPin1, OUTPUT);
  pinMode(mosfetPin2, OUTPUT);

  /*digitalWrite(mosfetPin1, LOW);
  digitalWrite(mosfetPin2, LOW);*/
}

void loop()
{
  if (!f_stop)
  {
    //delay(3000);
    //sensorsData();
    f_stop = true;  
  }
  digitalWrite(RELAY_PIN, LOW);
}

void sensorsData()
{
  lcd.init();
  
  lcd.setCursor(0, 2);
  lcd.print(mint.getName());
  lcd.print(" mos: ");
  lcd.print(mint.getMositure());

  lcd.setCursor(0, 3);
  lcd.print(araucaria.getName());
  lcd.print(" mos: ");
  lcd.print(araucaria.getMositure());

  getDHT11Data();

  lcd.noDisplay();
  digitalWrite(RELAY_PIN, LOW);
}

void irrigation()
{

    if(mint.getMositure() < CRITICAL_MOS)
      mint.waterPlant(RELAY_PIN, VOLUME);
    if(araucaria.getMositure() < CRITICAL_MOS)
      araucaria.waterPlant(RELAY_PIN, VOLUME);

}

void getDHT11Data()
{
  dht.begin();

  float h = dht.readHumidity(); //Измеряем влажность
  float t = dht.readTemperature(); //Измеряем температуру
  if (isnan(h) || isnan(t)) {  // Проверка. Если не удается считать показания, выводится «Ошибка считывания», и программа завершает работу
    lcd.print("Reading error");
    if(DEBUG == true)
      Serial.println("Reading error");
  }
  else {
    lcd.setCursor(0, 0);
    lcd.print("Air: ");
    lcd.print((int)h);
    lcd.print(" %");
    lcd.print(" T: ");
    lcd.print((int)t);
    lcd.print("C");

    if(DEBUG == true)
    {
      Serial.print("Влажность: ");
      Serial.print(h);
      Serial.print(" %\t");
      Serial.print("Температура: ");
      Serial.print(t);
      Serial.println(" *C ");
    }
  }
}

/*lejbron*/
