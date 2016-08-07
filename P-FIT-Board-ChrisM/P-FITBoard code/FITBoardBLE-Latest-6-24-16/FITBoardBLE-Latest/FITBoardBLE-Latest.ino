//#include <Adafruit_BLE.h>
//#include <Adafruit_BluefruitLE_UART.h>

//VR Lab 'FIT-Board' Code
//Adam Perruzzi
//perruzzi.a@husky.neu.edu for questions
//edited by: shah.romil@husky.neu.edu

// updated 6/24/16
// by Christopher Mohen
// mohen.c@husky.neu.edu

// Utilize Bluefruit UART Module
#include <Arduino.h>
#include <SoftwareSerial.h>
//#include <C:\Program Files (x86)\Arduino\examples\12.Adafruit_BluefruitLE_nRF51-master\Adafruit_BLE.h>
//#include <C:\Program Files (x86)\Arduino\examples\12.Adafruit_BluefruitLE_nRF51-master\Adafruit_BluefruitLE_UART.h>
#include <Adafruit_BLE.h>
#include <Adafruit_BluefruitLE_UART.h>
#include "BluefruitConfig.h"

// Inintialize Bluefruit Module
SoftwareSerial bluefruitSS = SoftwareSerial(BLUEFRUIT_SWUART_TXD_PIN, BLUEFRUIT_SWUART_RXD_PIN);

Adafruit_BluefruitLE_UART ble(bluefruitSS, BLUEFRUIT_UART_MODE_PIN,
                      BLUEFRUIT_UART_CTS_PIN, BLUEFRUIT_UART_RTS_PIN);

//LCD initialization
#include <LiquidCrystal.h> //Library to run the LCD
LiquidCrystal lcd(22, 24, 26, 28, 30, 32);


//Input pins [all digital, correspond to the magnets on top of the board]
const int humanPin00 = 23;//A0;      // the number of the top right human contact pin
const int humanPin01 = 25;//A1;     // the number of the top right human contact pin
const int humanPin02 = 27;//A2;     // the number of the top right human contact pin
const int humanPin03 = 29;//A3;     // the number of the top right human contact pin
const int humanPin04 = 31;//A4;     // the number of the top right human contact pin
const int humanPin05 = 33;//A5;     // the number of the top right human contact pin
const int humanPin10 = 34;//A6;     // the number of the top left human contact pin
const int humanPin11 = 35;//A7;     // the number of the top left human contact pin
const int humanPin12 = 36;//A8;     // the number of the top left human contact pin
const int humanPin13 = 37;//A9;      // the number of the top left human contact pin
const int humanPin14 = 38;//A10;     // the number of the top left human contact pin
const int humanPin15 = 39;//A11;     // the number of the top left human contact pin
const int humanPin20 = 40;//A12;     // the number of the bottom left human contact pin
const int humanPin21 = 41;//A13;     // the number of the bottom left human contact pin
const int humanPin22 = 42;//A14;     // the number of the bottom left human contact pin
const int humanPin23 = 43;//A15;     // the number of the bottom left human contact pin
const int humanPin24 = 44;//A16;     // the number of the bottom left human contact pin
const int humanPin25 = 45;//A17;     // the number of the bottom left human contact pin
const int humanPin30 = 46;//A18;     // the number of the bottom right human contact pin
const int humanPin31 = 47;//A19;     // the number of the bottom right human contact pin
const int humanPin32 = 48;//A20;     // the number of the bottom right human contact pin
const int humanPin33 = 49;//A21;     // the number of the bottom right human contact pin
const int humanPin34 = 50;//A22;     // the number of the bottom right human contact pin
const int humanPin35 = 51;//A23;     // the number of the bottom right human contact pin
const int humanPin40 = 52;//A41;    // another pin
const int humanPin41 = 53;//A41;    // the number of the 'I don't want to assign this button' human contact pin
const int noButton = humanPin41;

/*
//Output pins [all digital, ledPin for help debugging]
const int ledPin = 13;        // the number of the LED pin
const int makeyTopR = 12;       // the number of the Makey pin
const int makeyTopL = 11;     // the number of the down Makey pin
const int makeyBotL = 10;     // the number of the left Makey pin
const int makeyBotR = 9;     // the number of the right Makey pin
const int makeySpace = 8;     //the number of the space Makey pin
*/
const int ledPin = 13;        // the number of the LED pin
/*
const int makeyTopR = 6;       // the number of the Makey pin
const int makeyTopL = 5;     // the number of the down Makey pin
const int makeyBotL = 4;     // the number of the left Makey pin
const int makeyBotR = 3;     // the number of the right Makey pin
const int makeySpace = 2;     //the number of the space Makey pin
*/

//Variables to store the input level from each of the digital inputs

int buttonHuman00 = 0;
int buttonHuman01 = 0;
int buttonHuman02 = 0;
int buttonHuman03 = 0;
int buttonHuman04 = 0;
int buttonHuman05 = 0;
int buttonHuman10 = 0;
int buttonHuman11 = 0;
int buttonHuman12 = 0;
int buttonHuman13 = 0;
int buttonHuman14 = 0;
int buttonHuman15 = 0;
int buttonHuman20 = 0;
int buttonHuman21 = 0;
int buttonHuman22 = 0;
int buttonHuman23 = 0;
int buttonHuman24 = 0;
int buttonHuman25 = 0;
int buttonHuman30 = 0;
int buttonHuman31 = 0;
int buttonHuman32 = 0;
int buttonHuman33 = 0;
int buttonHuman34 = 0;
int buttonHuman35 = 0;
int buttonHuman40 = 0;
int buttonHuman41 = 0;


//Variables to store the input level from the selected buttons, once assigned
int buttonLeft = 0;         //read on up button
int buttonUp = 0;       //read on down button
int buttonDown = 0;       //read on down button
int buttonRight = 0;       //read on down button
int buttonSpace = 0;       //read on down button


//Variables to assign pins
int pinLeft;
int pinUp;
int pinDown;
int pinRight;
int pinSpace;

//Mux control pins
int val = readMux(15);
int s0 = 8;
int s1 = 9;
int s2 = 10;
int s3 = 11;

//Mux in "SIG" pin
int SIG_pin = 0;
 
void assign(int key, int pin){
	switch(key) {
		case 0:
			pinLeft = pin;
			break;
		case 1:
			pinUp = pin;
			break;
		case 2:
			pinDown = pin;
			break;
		case 3:
			pinRight = pin;
			break;
		case 4:
			pinSpace = pin;
			break;
	}
}


void setup() {  //Setup code, runs once when the board is turned on
  //pinMode(BLUEFRUIT_UART_MODE_PIN, OUTPUT);
  //digitalWrite(BLUEFRUIT_UART_MODE_PIN, HIGH);
  Serial.begin(115200);
  ble.begin(VERBOSE_MODE);
  ble.echo(false);
  ble.info();
  ble.sendCommandCheckOK(F("AT+GAPDEVNAME=P-FIT Board"));
  ble.sendCommandCheckOK(F("AT+BleHIDEn=On"));
  Serial.print(F("Connected"));
  
  //Initialize [human] inputs
  pinMode(humanPin00, INPUT);
  pinMode(humanPin01, INPUT);
  pinMode(humanPin02, INPUT);
  pinMode(humanPin03, INPUT);
  pinMode(humanPin04, INPUT);
  pinMode(humanPin05, INPUT);
  pinMode(humanPin10, INPUT);
  pinMode(humanPin11, INPUT);
  pinMode(humanPin12, INPUT);
  pinMode(humanPin13, INPUT);
  pinMode(humanPin14, INPUT);
  pinMode(humanPin15, INPUT);
  pinMode(humanPin20, INPUT);
  pinMode(humanPin21, INPUT);
  pinMode(humanPin22, INPUT);
  pinMode(humanPin23, INPUT);
  pinMode(humanPin24, INPUT);
  pinMode(humanPin25, INPUT);
  pinMode(humanPin30, INPUT);
  pinMode(humanPin31, INPUT);
  pinMode(humanPin32, INPUT);
  pinMode(humanPin33, INPUT);
  pinMode(humanPin34, INPUT);
  pinMode(humanPin35, INPUT);
  pinMode(humanPin40, INPUT);
  pinMode(humanPin41, INPUT);

  
  //Initialize LED debug output
  pinMode(ledPin, OUTPUT);
  /*
  pinMode(makeyTopR, OUTPUT);
  pinMode(makeyTopL, OUTPUT);
  pinMode(makeyBotL, OUTPUT);
  pinMode(makeyBotR, OUTPUT);
  pinMode(makeySpace, OUTPUT);
  */

  //Set output on Makey pins to max value [Makey reads as "off"]
  /*
  digitalWrite(makeyTopR, HIGH);
  digitalWrite(makeyTopL, HIGH);
  digitalWrite(makeyBotL, HIGH);
  digitalWrite(makeyBotR, HIGH);
  digitalWrite(makeySpace, HIGH);
  */

  //LCD welcome message
  lcd.begin(16, 2);
  lcd.print (" Welcome to the");
  lcd.setCursor(0,2);
  lcd.print ("    FitBoard");
  delay(2000);
  lcd.clear();
  delay(500);
  
  lcd.print (" Please select");
  lcd.setCursor(0,2);
  lcd.print ("     inputs");
  delay(2000);
  lcd.clear();
  delay(500);

  pinMode(s0,OUTPUT);
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);

  digitalWrite(s0,LOW);
  digitalWrite(s1,LOW);
  digitalWrite(s2,LOW);
  digitalWrite(s3,LOW);

  //Assign top right arrow

  for (int i=0; i <5; i++){
    //Opening message
    switch(i) {
	  case 0:
      lcd.print ("Press left");
	    break;
    case 1:
      lcd.print ("Press up");
	    break;
    case 2:
      lcd.print ("Press down");
      break;
    case 3:
      lcd.print ("Press right");
      break;
    case 4:
		  lcd.print ("Press space");
		  break;
    }
    lcd.setCursor(0,4);
    lcd.print ("or 'no button'");
    delay(6000);
  
    while (1) //Loop until button assignment is made
    {
    //Read pin values
    buttonHuman00 = digitalRead(humanPin00);
    buttonHuman01 = digitalRead(humanPin01);
    buttonHuman02 = digitalRead(humanPin02);
    buttonHuman03 = digitalRead(humanPin03);
    buttonHuman04 = digitalRead(humanPin04);
    buttonHuman05 = digitalRead(humanPin05);
    buttonHuman10 = digitalRead(humanPin10);
    buttonHuman11 = digitalRead(humanPin11);
    buttonHuman12 = digitalRead(humanPin12);
    buttonHuman13 = digitalRead(humanPin13);
    buttonHuman14 = digitalRead(humanPin14);
    buttonHuman15 = digitalRead(humanPin15);
    buttonHuman20 = digitalRead(humanPin20);
    buttonHuman21 = digitalRead(humanPin21);
    buttonHuman22 = digitalRead(humanPin22);
    buttonHuman23 = digitalRead(humanPin23);
    buttonHuman24 = digitalRead(humanPin24);
    buttonHuman25 = digitalRead(humanPin25);
    buttonHuman30 = digitalRead(humanPin30);
    buttonHuman31 = digitalRead(humanPin31);
    buttonHuman32 = digitalRead(humanPin32);
    buttonHuman33 = digitalRead(humanPin33);
    buttonHuman34 = digitalRead(humanPin34);
    buttonHuman35 = digitalRead(humanPin35);
    buttonHuman40 = digitalRead(humanPin40);
  
    //Check to see which button is being pressed
    if (!buttonHuman00) //Pressing A00
    {
	  assign(i, humanPin00);
      break;
    }
    if (!buttonHuman01) //Pressing A01
    {
      assign(i, humanPin01);
	  break;
    }
    if (!buttonHuman02) //Pressing A02
    {
      assign(i, humanPin02);
	  break;
    }
    if (!buttonHuman03) //Pressing A03
    {
      assign(i, humanPin03);
	  break;
    }
    if (!buttonHuman04) //Pressing A04
    {
      assign(i, humanPin04);
	  break;
    }
    if (!buttonHuman05) //Pressing A05
    {
      assign(i, humanPin05);
	  break;
    }
    if (!buttonHuman10) //Pressing A10
    {
      assign(i, humanPin10);
	  break;
    }
    if (!buttonHuman11) //Pressing A11
    {
      assign(i, humanPin12);
	  break;
    }
    if (!buttonHuman12) //Pressing A12
    {
      assign(i, humanPin13);
	  break;
    }
    if (!buttonHuman13) //Pressing A13
    {
      assign(i, humanPin14);
	  break;
    }
    if (!buttonHuman14) //Pressing A14
    {
	  assign(i, humanPin15);
	  break;
    }
    if (!buttonHuman15) //Pressing A15
    {
      assign(i, humanPin15);
	  break;
    }
    if (!buttonHuman20) //Pressing A20
    {
      assign(i, humanPin20);
	  break;
    }
    if (!buttonHuman21) //Pressing A21
    {
	  assign(i, humanPin21);
	  break;
    }
    if (!buttonHuman22) //Pressing A22
    {
	  assign(i, humanPin22);
	  break;
    }
    if (!buttonHuman23) //Pressing A23
    {
	  assign(i, humanPin23);
	  break;
    }
    if (!buttonHuman24) //Pressing A24
    {
	  assign(i, humanPin24);
	  break;
    }
    if (!buttonHuman25) //Pressing A25
    {
	  assign(i, humanPin25);
	  break;
    }
    if (!buttonHuman30) //Pressing A30
    {
	  assign(i, humanPin30);
	  break;
    }
    if (!buttonHuman31) //Pressing A31
    {
	  assign(i, humanPin31);
	  break;
    }
    if (!buttonHuman32) //Pressing A32
    {
	  assign(i, humanPin32);
	  break;
    }
    if (!buttonHuman33) //Pressing A33
    {
	  assign(i, humanPin33);
	  break;
    }
    if (!buttonHuman34) //Pressing A34
    {
	  assign(i, humanPin34);
	  break;
    }
    if (!buttonHuman35) //Pressing A35
    {
	  assign(i, humanPin35);
	  break;
    }
        
    /*
	//
	// Need to figure out which pin is cancel button
	// Or determine what physical button on board we
	// want to make cancel button
	//
    if (!buttonHuman41) //Pressing cancel
    {
      if (i == 0)
      {
        pinLeft = 8;
      }
      else if (i == 1)
      {
        pinUp = 8;
      }
      else if (i == 2)
      {
        pinDown = 8;
      }
      else if (i == 3)
      {
        pinRight = 8;
      }
      else if (i == 4) {
        pinSpace = 8;
      }
  
      //Message that input was not chosen
      lcd.clear();
      lcd.print ("  You selected ");
      lcd.setCursor(0,2);
      lcd.print ("  'no button'");
      delay(1000);
      break;
    } */
    delay(5);
    }
    
    //Message that a button was successfully chosen
    lcd.clear();
    lcd.print ("     Button");
    lcd.setCursor(0,2);
    lcd.print ("    Selected!");
    delay(1000);
    lcd.clear();  
  }
}

void loop() {
  //Read the state of the assigned inputs
  buttonLeft = digitalRead(pinLeft);
  buttonUp = digitalRead(pinUp);
  buttonDown = digitalRead(pinDown);
  buttonRight = digitalRead(pinRight);
  buttonSpace = digitalRead(pinSpace);
  Serial.print(buttonLeft);
  Serial.print(", ");
  Serial.print(buttonUp);
  Serial.print(", ");
  Serial.print(buttonDown);
  Serial.print(", ");
  Serial.print(buttonRight);
  Serial.print(", ");
  Serial.print(buttonSpace);
  Serial.println("");
  //If any input is pressed, light the LED, for testing purposes
  if (!buttonLeft || !buttonUp || !buttonDown || !buttonRight || !buttonSpace) //when any direction is touched
  {
    digitalWrite(ledPin, HIGH); // turn LED on
    //TODO: with full p-fit board make more swtich case like
    //ble.print("AT+BleKeyboardCode=");
  }
  else {
    digitalWrite(ledPin, LOW); // turn LED off
  }

  

  //Individual button actions
  if (!buttonLeft) //Pressing up
  {
    //digitalWrite(makeyTopR, LOW); //turn on Makey up button
    ble.println("AT+BleKeyboardCode=00-00-52");
    ble.println("AT+BleKeyboardCode=00-00");
    
  }
  else { //Not pressing up
    //digitalWrite(makeyTopR, HIGH); //turn off Makey up button
  }
  
  if (!buttonUp) //Pressing left
  {
    //digitalWrite(makeyTopL, LOW); //turn on Makey left button
    ble.println("AT+BleKeyboardCode=00-00-50");
    ble.println("AT+BleKeyboardCode=00-00");
  }
  else { //Not pressing left
    //digitalWrite(makeyTopL, HIGH); //turn off Makey left button
  }
  
  if (!buttonDown) //Pressing down
  {
    //digitalWrite(makeyBotL, LOW); //turn on Makey down button
    ble.println("AT+BleKeyboardCode=00-00-51");
    ble.println("AT+BleKeyboardCode=00-00");
  }
  else { //Not pressing down
    //digitalWrite(makeyBotL, HIGH); //turn off Makey down button
  }

  if (!buttonRight) //Pressing right
  {
    //digitalWrite(makeyBotR, LOW); //turn on Makey right button
    ble.println("AT+BleKeyboardCode=00-00-4f");
    ble.println("AT+BleKeyboardCode=00-00");
  }
  else { //Not pressing right
    //digitalWrite(makeyBotR, HIGH); //turn off Makey right button
  }

  if (!buttonSpace) //Pressing space
  {
    //digitalWrite(makeySpace, LOW); //turn on Makey space button
    ble.println("AT+BleKeyboardCode=00-00-2c");
    ble.println("AT+BleKeyboardCode=00-00");

  }
  else { //Not pressing right
    //digitalWrite(makeySpace, HIGH); //turn off Makey space button
  }
  delay(10);
}
