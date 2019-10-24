/* Калибровка подачи pH+/pH- в раствор

	 - x2 http://amperka.ru/product/solenoid-valve-normally-open
	 - x2 http://amperka.ru/product/troyka-mosfet-v2
	 - x2 http://rushim.ru/product_info.php?products_id=633
	 - x2 http://rushim.ru/product_info.php?products_id=2246
	   
*/

#include "OneButton.h" 

OneButton button1(A4, true);
OneButton button2(A5, true);

int mosfetPin1 = 11;    // Connect the MOSFeT Gate (first pin on the left, when writing on the chip is facing you) to Arduino pin 2
int mosfetPin2 = 12;

int volume = 7000;

void setup()
{
  // открываем последовательный порт для мониторинга действий в программе
  Serial.begin(9600);
	
  button1.attachClick(click1); // открыть клапан 1-ой колбы
  button2.attachClick(click2); // открыть клапан 2-ой колбы 
  button1.attachDoubleClick(doubleclick1); // увеличить время ожидания
  button2.attachDoubleClick(doubleclick2); // уменьшить время ожидания
  
  pinMode(mosfetPin1, OUTPUT);
  pinMode(mosfetPin2, OUTPUT);
  
  digitalWrite(mosfetPin1, LOW);
  digitalWrite(mosfetPin2, LOW);
}

void loop()
{
  button1.tick();
  button2.tick();
}

void click1() {
 digitalWrite(mosfetPin1, HIGH);
 delay(volume); 
 digitalWrite(mosfetPin1, LOW);
 Serial.println("First flusk with ");
 Serial.println(volume); 
 Serial.println("ms constnat");
}

void click2() {
 digitalWrite(mosfetPin2, HIGH);
 delay(volume); 
 digitalWrite(mosfetPin2, LOW);
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

void doubleclick2() {
 volume -= 1000;
 Serial.println("Current time: ");
 Serial.println(volume);
 Serial.println("ms"); 
}

/*lejbron*/
