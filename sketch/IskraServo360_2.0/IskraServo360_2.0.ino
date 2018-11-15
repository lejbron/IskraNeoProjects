/*	Микросервопривод постоянного вращения FS90R
	 button1 - варщение по часовой стрелке
	 button2 - вращение против часовой стрелки
*/

#include "OneButton.h" 
#include "Servo.h"

#define STEP_TIME 500

// Setup a new OneButton on pin A1.  
OneButton button1(A1, true);
// Setup a new OneButton on pin A2.  
OneButton button2(A2, true);

Servo scanServo;

// setup code here, to run once:
void setup() {
  // link the button 1 functions.
  button1.attachClick(click1);
  button1.attachLongPressStart(longPressStart1);
  button1.attachLongPressStop(longPressStop1);

  // link the button 2 functions.
  button2.attachClick(click2);
  button2.attachLongPressStart(longPressStart2);
  button2.attachLongPressStop(longPressStop2);
  
  // attaches the servo on pin 9 to the servo object
  scanServo.attach(9); 
} // setup

void loop() {
  // keep watching the push buttons:
  button1.tick();
  button2.tick();
}

// This function will be called when the button1 was pressed 1 time (and no 2. button press followed).
void click1() {
  stepRight(scanServo);
} // click1

// This function will be called once, when the button1 is pressed for a long time.
void longPressStart1() {
  moveRight(scanServo);
} // longPressStart1

// This function will be called once, when the button1 is released after beeing pressed for a long time.
void longPressStop1() {
  stopServo(scanServo);
} // longPressStop1

void click2() {
  stepLeft(scanServo);
} 

void longPressStart2() {
  moveLeft(scanServo);
} 

void longPressStop2() {
  stopServo(scanServo);
} 

// rotate clockwise full speed
void moveRight(Servo ms){
  ms.write(135); }

// rotate counterclockwise full speed 
void moveLeft(Servo ms){
  ms.write(45); } 

void stopServo(Servo ms){
  ms.write(90); }

void stepRight(Servo ms) {
  ms.write(135); // rotate clockwise full speed
  delay(STEP_TIME);
  ms.write(90);  // stop     
}

void stepLeft(Servo ms){
  ms.write(45); // rotate counterclockwise full speed
  delay(STEP_TIME);
  ms.write(90);  // stop     
}

/*lejbron*/