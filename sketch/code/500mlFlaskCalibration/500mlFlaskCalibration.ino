/* Калибровка подачи pH+/pH- в раствор

	 - x2 http://amperka.ru/product/solenoid-valve-normally-open
	 - x2 http://amperka.ru/product/troyka-mosfet-v2
	 - x2 http://rushim.ru/product_info.php?products_id=633
	 - x2 http://rushim.ru/product_info.php?products_id=2246
	   
*/

#include "OneButton.h" 

OneButton button1(A1, true);
//OneButton button2(A2, true);

int mosfetPin1 = 1;    // Connect the MOSFeT Gate (first pin on the left, when writing on the chip is facing you) to Arduino pin 2
//int mosfetPin2 = 2;

int volume = 60000;

void setup()
{
  // открываем последовательный порт для мониторинга действий в программе
  Serial.begin(9600);
	
  button1.attachClick(click1); // открыть клапан 1-ой колбы
  //button2.attachClick(click2); // открыть клапан 2-ой колбы 
  button1.attachDoubleClick(doubleclick1); // увеличить время ожидания
  //button2.attachDoubleClick(doubleclick2); // уменьшить время ожидания
  
  pinMode(mosfetPin1, OUTPUT);
  //pinMode(mosfetPin2, OUTPUT);
  
  digitalWrite(mosfetPin1, LOW);
  //digitalWrite(mosfetPin2, LOW);
}

void loop()
{
  button1.tick();
  //button2.tick();
}

void click1() {
 digitalWrite(mosfetPin1, HIGH);
 delay(volume); 
 digitalWrite(mosfetPin1, LOW);
 Serial.println("First flusk with ");
 Serial.println(volume); 
 Serial.println("ms constnat");
}

void doubleclick1() {
 volume += 1000;
 Serial.println("Current time: ");
 Serial.println(volume);
 Serial.println("ms"); 
}

/*void click2() {
 digitalWrite(mosfetPin2, HIGH);
 delay(volume); 
 digitalWrite(mosfetPin2, LOW); 
 Serial.println("Second flusk with " + volume + "ms constnat");
}

void doubleclick2() {
 volume -= 10;
 Serial.println("Current time: " + volume + "ms"); 
}*/

/*lejbron*/
