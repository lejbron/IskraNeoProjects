/*
  Parts:
   - x1 https://amperka.ru/product/display-lcd-text-20x4-i2c-3v3-black-on-green
   - x1 https://amperka.ru/product/troyka-relay
   - x1 https://amperka.ru/product/arduino-troyka-shield
   - x1 https://amperka.ru/product/troyka-temperature-humidity-sensor-dht11
   - x2 https://amperka.ru/product/soil-moisture-sensor
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
#define DEBUG true
#define MINT_CRITICAL_MOS 45
#define ARAUCARIA_CRITICAL_MOS 45
#define VOLUME 20000
/*=========SETTINGS=========*/

/*=============PINS=============*/
#define DHTPIN 10

//fc28 analog pins
//int fc28_plant_pin1 = A1;
//int fc28_plant_pin2 = A2;

//int fc28DigitalPin1 = 11;
//int fc28DigitalPin2 = 12;

DHT dht(DHTPIN, DHT11);

int mosfetPin1 = 11;
int mosfetPin2 = 3;

LiquidCrystal_I2C lcd(0x27,20,4);
/*=============PINS=============*/

/*==================================PLANTS==================================*/

//IPlant mint(fc28_plant_pin1, fc28DigitalPin1, mosfetPin1, "Mint");
//IPlant araucaria(fc28_plant_pin2, fc28DigitalPin2, mosfetPin2, "Araucaria");

/*==================================PLANTS==================================*/

void setup()
{
  delay(2000);
  Serial.begin(9600);

  dht.begin();

  pinMode(mosfetPin1, OUTPUT);
  pinMode(mosfetPin2, OUTPUT);

  //digitalWrite(mosfetPin1, LOW);
  //digitalWrite(mosfetPin2, LOW);

  lcd.init();
  lcd.backlight();

  //getDHT11Data();
  Serial.println("Setup done");
  lcd.print("Setup done");
}

void loop()
{
  //getDHT11Data();
  //delay(5000);
  //lcd.clear();
  lcd.print("Water");
  digitalWrite(mosfetPin1, 1);
  delay(2000);
  digitalWrite(mosfetPin1, 0);
  lcd.print("Finished");
  delay(2000);
  lcd.clear();
  
}

void getDHT11Data()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  lcd.clear();

  if (isnan(h) || isnan(t)) {
    lcd.print("Reading error");
    if(DEBUG == true)
      Serial.println("Reading error");
  }
  else {
    lcd.setCursor(0, 0);
    lcd.print("Air:");
    lcd.print((int)h);
    lcd.print("%");
    lcd.print(" T:");
    lcd.print((int)t);
    lcd.print("C");

    if(DEBUG == true)
    {
      Serial.print("Air:");
      Serial.print((int)h);
      Serial.println("%");
      Serial.print(" T:");
      Serial.print((int)t);
      Serial.println("C");
    }
  }
}

/*lejbron*/
