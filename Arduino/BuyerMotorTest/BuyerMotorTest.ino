#include <LiquidCrystal_I2C.h>
#include <Stepper.h>
#include <Wire.h>
#include "Adafruit_VL6180X.h"

//Pin Definitions for hardware control
enum Pins { 
    LeftFeed = 38, RightFeed = 56, LeftChoice = 62, RightChoice = 24, //Motors
    LeftFeedStep = 54, RightFeedStep = 60, LeftChoiceStep = 46, RightChoiceStep = 26, //Stepper Controls
    LeftFeedDir = 55, RightFeedDir = 61, LeftChoiceDir = 48, RightChoiceDir = 28 //Directions
};
//Initialize sensor and display objects
Adafruit_VL6180X vl = Adafruit_VL6180X();  //VL6180X distance sensor object
Adafruit_VL6180X v2 = Adafruit_VL6180X();  //VL6180X distance sensor object
LiquidCrystal_I2C lcd(0x27, 16, 2);        //LCD for user feedback
LiquidCrystal_I2C lcd2(0x28, 16, 2);        //LCD for user feedback
const short speed = 700;                       //Movement speed (Higher number=slower speed)
String Tempval1;

void setup() {
  byte pins[] = { LeftFeed, RightFeed, LeftChoice, RightChoice, LeftFeedStep, RightFeedStep, LeftChoiceStep, RightChoiceStep, LeftFeedDir, RightFeedDir, LeftChoiceDir, RightChoiceDir};
  for (byte pin : pins) { pinMode(pin, OUTPUT); }  //Set all pins as outputs
  byte lowPins[] = { LeftFeed, RightFeed, LeftChoice, RightChoice };
  for (byte pin : lowPins) { digitalWrite(pin, LOW); }    //Disable motors initially
  digitalWrite(13, HIGH);                    //Turn on the onboard LED for debugging
}
void loop() {
  lcd.init();lcd.backlight();lcd.setCursor(0, 0); //Initialize LCD and turn on the backlight
  lcd2.init();lcd2.backlight();lcd2.setCursor(0, 0); //Initialize LCD and turn on the backlight
  PrintLCD("Feeding:","left card");Move1(LeftFeedDir,LeftFeedStep,0,100,speed);delay(1000);
  PrintLCD("Left choice:","left");Move1(LeftChoiceDir,LeftChoiceStep,0,100,speed);delay(1000);
  PrintLCD("Feeding:","left card");Move1(LeftFeedDir,LeftFeedStep,0,100,speed);delay(1000);
  PrintLCD("Left choice:","right");Move1(LeftChoiceDir,LeftChoiceStep,1,100,speed);delay(1000);

  PrintLCD2("Feeding:","right card");Move1(RightFeedDir,RightFeedStep,0,100,speed);delay(1000);
  PrintLCD2("Right choice:","left");Move1(RightChoiceDir,RightChoiceStep,0,100,speed);delay(1000);
  PrintLCD2("Feeding:","Right card");Move1(RightFeedDir,RightFeedStep,0,100,speed);delay(1000);
  PrintLCD2("Right choice:","right");Move1(RightChoiceDir,RightChoiceStep,1,100,speed);delay(1000);
}

//Function to move along the Z-axis with a specified direction and steps
void Move1(short motor,short motorstep, boolean dir, short steps, short speed1) {
  digitalWrite(motor, dir);
  for (short i = 0; i < steps; i++) { //Loop to perform the movement
    digitalWrite(motorstep, HIGH); delayMicroseconds(speed1);
    digitalWrite(motorstep,  LOW); delayMicroseconds(speed1);
  }
}

//Function to print a message to the LCD screen
void PrintLCD(String var1, String var2) {
  lcd.clear(); lcd.setCursor(0, 0); lcd.print(var1); lcd.setCursor(0, 1); lcd.print(var2);
}
void PrintLCD2(String var1, String var2) {
  lcd2.clear(); lcd2.setCursor(0, 0); lcd2.print(var1); lcd2.setCursor(0, 1); lcd2.print(var2);
}