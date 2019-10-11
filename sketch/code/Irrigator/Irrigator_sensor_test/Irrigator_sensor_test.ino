/* Калибровка подачи pH+/pH- в раствор

	 - x2 http://amperka.ru/product/solenoid-valve-normally-open
	 - x2 http://amperka.ru/product/troyka-mosfet-v2
	 - x2 http://rushim.ru/product_info.php?products_id=633
	 - x2 http://rushim.ru/product_info.php?products_id=2246
	   
*/

#include "OneButton.h"
#include "DHT.h" 

#define DHTPIN 0

OneButton button1(A4, true);
OneButton button2(A5, true);

int led_pin = 13;

int fc28DigitalPin1 = 1;
int fc28DigitalPin2 = 2;

int fc28AnalogPin1 = A1;
int fc28AnalogPin2 = A2;

DHT dht(DHTPIN, DHT11);

void setup()
{
  // открываем последовательный порт для мониторинга действий в программе
  Serial.begin(9600);
	
  button1.attachClick(click1); // get 1st fc28 data and DHT11 data
  button2.attachClick(click2); // get 2nd fc28 data
  //button1.attachDoubleClick(doubleclick1); 
  //button2.attachDoubleClick(doubleclick2); 

  pinMode(led_pin, OUTPUT);
  pinMode(fc28DigitalPin1, INPUT);
  pinMode(fc28DigitalPin2, INPUT);

  dht.begin();
}

void loop()
{
  button1.tick();
  button2.tick();
}

void click1() {
 getFC28AnalogData(fc28AnalogPin1);
 delay(1000);
 getFC28DigitalData(fc28DigitalPin1);
 delay(1000);
 getDHT11Data();
}

void click2() {
 getFC28AnalogData(fc28AnalogPin2);
 delay(1000);
 getFC28DigitalData(fc28DigitalPin2);
 delay(1000);
}

void getFC28AnalogData(int sensor_pin)
{
  int output_value;
  
  output_value= analogRead(sensor_pin);
  output_value = map(output_value,550,10,0,100);
  Serial.print("Mositure : ");
  Serial.print(output_value);
  Serial.println("%");
}

void getFC28DigitalData(int sensor_pin)
{
  if(digitalRead(sensor_pin) == HIGH){
    digitalWrite(led_pin, HIGH);
  } else {
    digitalWrite(led_pin, LOW);
  }
}

void getDHT11Data()
{
  float h = dht.readHumidity(); //Измеряем влажность
  float t = dht.readTemperature(); //Измеряем температуру
  if (isnan(h) || isnan(t)) {  // Проверка. Если не удается считать показания, выводится «Ошибка считывания», и программа завершает работу
    Serial.println("Ошибка считывания");
  }
  Serial.print("Влажность: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Температура: ");
  Serial.print(t);
  Serial.println(" *C "); //Вывод показателей на экран
}

/*void doubleclick1() {
 Serial.println("Current time: ");
 Serial.println(volume);
 Serial.println("ms"); 
}
void doubleclick2() {
 volume -= 10;
 Serial.println("Current time: " + volume + "ms"); 
}*/

/*lejbron*/
