//VR Lab 'FIT-Board' Code
//Adam Perruzzi
//perruzzi.a@husky.neu.edu for questions
//edited by: shah.romil@husky.neu.edu

// Utilize Bluefruit UART Module
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <C:\Program Files (x86)\Arduino\examples\12.Adafruit_BluefruitLE_nRF51-master\Adafruit_BLE.h>
#include <C:\Program Files (x86)\Arduino\examples\12.Adafruit_BluefruitLE_nRF51-master\Adafruit_BluefruitLE_UART.h>
#include "BluefruitConfig.h"

// Inintialize Bluefruit Module
SoftwareSerial bluefruitSS = SoftwareSerial(BLUEFRUIT_SWUART_TXD_PIN, BLUEFRUIT_SWUART_RXD_PIN);

Adafruit_BluefruitLE_UART ble(bluefruitSS, BLUEFRUIT_UART_MODE_PIN,
                      BLUEFRUIT_UART_CTS_PIN, BLUEFRUIT_UART_RTS_PIN);

//LCD initialization
#include <LiquidCrystal.h> //Library to run the LCD
LiquidCrystal lcd(22, 24, 26, 28, 30, 32);


//Input pins [all digital, correspond to the magnets on top of the board]
const int humanPin00 = 0;//A0;      // the number of the top right human contact pin
const int humanPin01 = 0;//A1;     // the number of the top right human contact pin
const int humanPin02 = 0;//A2;     // the number of the top right human contact pin
const int humanPin03 = 0;//A3;     // the number of the top right human contact pin
const int humanPin04 = 0;//A4;     // the number of the top right human contact pin
const int humanPin05 = 0;//A5;     // the number of the top right human contact pin
const int humanPin10 = 0;//A6;     // the number of the top left human contact pin
const int humanPin11 = 0;//A7;     // the number of the top left human contact pin
const int humanPin12 = 0;//A8;     // the number of the top left human contact pin
const int humanPin13 = 0;//A9;      // the number of the top left human contact pin
const int humanPin14 = 0;//A10;     // the number of the top left human contact pin
const int humanPin15 = 0;//A11;     // the number of the top left human contact pin
const int humanPin20 = 0;//A12;     // the number of the bottom left human contact pin
const int humanPin21 = 0;//A13;     // the number of the bottom left human contact pin
const int humanPin22 = 0;//A14;     // the number of the bottom left human contact pin
const int humanPin23 = 0;//A15;     // the number of the bottom left human contact pin
const int humanPin24 = 0;//A16;     // the number of the bottom left human contact pin
const int humanPin25 = 0;//A17;     // the number of the bottom left human contact pin
const int humanPin30 = 0;//A18;     // the number of the bottom right human contact pin
const int humanPin31 = 0;//A19;     // the number of the bottom right human contact pin
const int humanPin32 = 0;//A20;     // the number of the bottom right human contact pin
const int humanPin33 = 0;//A21;     // the number of the bottom right human contact pin
const int humanPin34 = 0;//A22;     // the number of the bottom right human contact pin
const int humanPin35 = 0;//A23;     // the number of the bottom right human contact pin
const int humanPin40 = 0;//A40;    // the number of the 'I don't want to assign this button' human contact pin
const int A40 = humanPin40;

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


//Variables to store the input level from the selected buttons, once assigned
int buttonTopR = 0;         //read on up button
int buttonTopL = 0;       //read on down button
int buttonBotL = 0;       //read on down button
int buttonBotR = 0;       //read on down button
int buttonSpace = 0;       //read on down button


//Variables to assign pins
int pinTopR;
int pinTopL;
int pinBotL;
int pinBotR;
int pinSpace;
int pinUp;
 
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

  
  //Initialize outputs
  pinMode(ledPin, OUTPUT);

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


  //Assign top right arrow

  for (int i=0; i <5; i++){
    //Opening message
    if (i==0)
    {
      lcd.print ("Press top right");
    }
    else if (i==1)
    {
      lcd.print ("Press top left");
    }
    else if (i==2)
    {
      lcd.print ("Press bottom left");
    }
    else if (i==3)
    {
      lcd.print ("Press bottom right");
    }
    
    lcd.setCursor(0,2);
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
    if (buttonHuman00 == 1) //Pressing A00
    {
      lcd.clear();
      lcd.print ("TR 1/6");
      pinTopR = humanPin00;
      break;
    }
    if (buttonHuman01 == 1) //Pressing A01
    {
      lcd.clear();
      lcd.print ("TR 2/6");
      pinTopR = humanPin01;
      break;
    }
    if (buttonHuman02 == 1) //Pressing A02
    {
      lcd.clear();
      lcd.print ("TR 3/6");
      pinTopR = humanPin02;
      break;
    }
    if (buttonHuman03 == 1) //Pressing A03
    {
      lcd.clear();
      lcd.print ("TR 4/6");
      pinTopR = humanPin03;
      break;
    }
    if (buttonHuman04 == 1) //Pressing A04
    {
      lcd.clear();
      lcd.print ("TR 5/6");
      pinTopR = humanPin04;
      break;
    }
    if (buttonHuman05 == 1) //Pressing A05
    {
      lcd.clear();
      lcd.print ("TR 6/6");
      pinTopR = humanPin05;
      break;
    }
    if (buttonHuman10 == 1) //Pressing A10
    {
      lcd.clear();
      lcd.print ("TL 1/6");
      pinTopL = humanPin10;
      break;
    }
    if (buttonHuman11 == 1) //Pressing A11
    {
      lcd.clear();
      lcd.print ("TL 2/6");
      pinTopL = humanPin11;
      break;
    }
    if (buttonHuman12 == 1) //Pressing A12
    {
      lcd.clear();
      lcd.print ("TL 3/6");
      pinTopL = humanPin12;
      break;
    }
    if (buttonHuman13 == 1) //Pressing A13
    {
      lcd.clear();
      lcd.print ("TL 4/6");
      pinTopL = humanPin13;
      break;
    }
    if (buttonHuman14 == 1) //Pressing A14
    {
      lcd.clear();
      lcd.print ("TL 5/6");
      pinTopL = humanPin14;
      break;
    }
    if (buttonHuman15 == 1) //Pressing A15
    {
      lcd.clear();
      lcd.print ("TL 6/6");
      pinTopL = humanPin15;
      break;
    }
    if (buttonHuman20 == 1) //Pressing A20
    {
      lcd.clear();
      lcd.print ("BL 1/6");
      pinBotL = humanPin20;
      break;
    }
    if (buttonHuman21 == 1) //Pressing A21
    {
      lcd.clear();
      lcd.print ("BL 2/6");
      pinBotL = humanPin21;
      break;
    }
    if (buttonHuman22 == 1) //Pressing A22
    {
      lcd.clear();
      lcd.print ("BL 3/6");
      pinBotL = humanPin22;
      break;
    }
    if (buttonHuman23 == 1) //Pressing A23
    {
      lcd.clear();
      lcd.print ("BL 4/6");
      pinBotL = humanPin23;
      break;
    }
    if (buttonHuman24 == 1) //Pressing A24
    {
      lcd.clear();
      lcd.print ("BL 5/6");
      pinBotL = humanPin24;
      break;
    }
    if (buttonHuman25 == 1) //Pressing A25
    {
      lcd.clear();
      lcd.print ("BL 6/6");
      pinBotL = humanPin25;
      break;
    }
    if (buttonHuman30 == 1) //Pressing A30
    {
      lcd.clear();
      lcd.print ("BR 1/6");
      pinBotR = humanPin30;
      break;
    }
    if (buttonHuman31 == 1) //Pressing A31
    {
      lcd.clear();
      lcd.print ("BR 2/6");
      pinBotR = humanPin31;
      break;
    }
    if (buttonHuman32 == 1) //Pressing A32
    {
      lcd.clear();
      lcd.print ("BR 3/6");
      pinBotR = humanPin32;
      break;
    }
    if (buttonHuman33 == 1) //Pressing A33
    {
      lcd.clear();
      lcd.print ("BR 4/6");
      pinBotR = humanPin33;
      break;
    }
    if (buttonHuman34 == 1) //Pressing A34
    {
      lcd.clear();
      lcd.print ("BR 5/6");
      pinBotR = humanPin34;
      break;
    }
    if (buttonHuman35 == 1) //Pressing A35
    {
      lcd.clear();
      lcd.print ("BR 6/6");
      pinBotR = humanPin35;
      break;
    }
        
    if (buttonHuman40 == 1) //Pressing cancel
    {
      if (i == 0)
      {
        pinTopR = A40;
        pinUp = A40;
      }
      else if (i == 1)
      {
        pinTopL = A40;
        pinUp = A40;
      }
      else if (i == 2)
      {
        pinBotL = A40;
        pinUp = A40;
      }
      else if (i == 3)
      {
        pinBotR = A40;
        pinUp = A40;
      }
  
      //Message that input was not chosen
      lcd.clear();
      lcd.print ("  You selected ");
      lcd.setCursor(0,2);
      lcd.print ("  'no button'");
      delay(1000);
      break;
    }
    }
    
    if (pinUp != A40) //Any pin selected
    {
      //Message that a button was successfully chosen
      lcd.clear();
      lcd.print ("     Button");
      lcd.setCursor(0,2);
      lcd.print ("    Selected!");
      delay(1000);
    }
    lcd.clear();
  }
}
 

  
//  //Assign space button
//
//  //Opening message
//  lcd.print ("Press space bttn");
//  lcd.setCursor(0,2);
//  lcd.print ("or 'no button'");
//  delay(500);
//  
//  while (1) //Loop until button assignment is made
//  {
//  //Read pin values
//  buttonHuman1 = digitalRead(humanPin1);
//  buttonHuman2 = digitalRead(humanPin2);
//  buttonHuman3 = digitalRead(humanPin3);
//  buttonHuman4 = digitalRead(humanPin4);
//  buttonHuman5 = digitalRead(humanPin5);
//  buttonHuman6 = digitalRead(humanPin6);
//  buttonHuman7 = digitalRead(humanPin7);
//  buttonHuman8 = digitalRead(humanPin8);
//  buttonHuman9 = digitalRead(humanPin9);
//  buttonHuman10 = digitalRead(humanPin10);
//
//  //Check to see which button is being pressed
//  if (buttonHuman1 > 80) //Pressing A0
//  {
//    pinSpace = humanPin1;
//    break;
//  }
//  if (buttonHuman2 > 80) //Pressing A1
//  {
//    pinSpace = humanPin2;
//    break;
//  }
//  if (buttonHuman3 > 80) //Pressing A2
//  {
//    pinSpace = humanPin3;
//    break;
//  }
//  if (buttonHuman4 > 80) //Pressing A3
//  {
//    pinSpace = humanPin4;
//    break;
//  }
//  if (buttonHuman5 > 80) //Pressing A4
//  {
//    pinSpace = humanPin5;
//    break;
//  }
//  if (buttonHuman6 > 80) //Pressing A5
//  {
//    pinSpace = humanPin6;
//    break;
//  }
//  if (buttonHuman7 > 80) //Pressing A6
//  {
//    pinSpace = humanPin7;
//    break;
//  }
//  if (buttonHuman8 > 80) //Pressing A7
//  {
//    pinSpace = humanPin8;
//    break;
//  }
//  if (buttonHuman9 > 80) //Pressing A8
//  {
//    pinSpace = humanPin9;
//    break;
//  }
//  if (buttonHuman10 > 80) //Pressing cancel
//  {
//    pinSpace = A9;
//
//    //Message that input was not chosen
//    lcd.clear();
//    lcd.print ("  You selected ");
//    lcd.setCursor(0,2);
//    lcd.print ("  'no button'");
//    delay(1000);
//    break;
//  }
//  }
//  
//  if (pinSpace != A9) //Any pin selected
//  {
//    //Message that a button was successfully chosen
//    lcd.clear();
//    lcd.print ("Button");
//    lcd.setCursor(0,2);
//    lcd.print ("Selected!");
//    delay(1000);
//  }
//  lcd.clear();
//}

void loop() {
  //Read the state of the assigned inputs
  buttonTopR = digitalRead(pinTopR);
  buttonTopL = digitalRead(pinTopL);
  buttonBotL = digitalRead(pinBotL);
  buttonBotR = digitalRead(pinBotR);
  //buttonSpace = digitalRead(pinSpace);

  //If any input is pressed, light the LED, for testing purposes
  if (buttonTopR == 1 || buttonTopL == 1 || buttonBotL == 1 || buttonBotR == 1) //when any direction is touched
  {
    digitalWrite(ledPin, HIGH); // turn LED on
    //TODO: with full p-fit board make more swtich case like
    //ble.print("AT+BleKeyboardCode=");
  }
  else {
    digitalWrite(ledPin, LOW); // turn LED off
  }
  

  //Individual button actions
  if (buttonTopR == 1) //Pressing up
  {
    ble.println("AT+BleKeyboardCode=00-00-52");
    ble.println("AT+BleKeyboardCode=00-00");
  }
  if (buttonTopL == 1) //Pressing left
  {
    ble.println("AT+BleKeyboardCode=00-00-50");
    ble.println("AT+BleKeyboardCode=00-00");
  }
  if (buttonBotL == 1) //Pressing down
  {
    ble.println("AT+BleKeyboardCode=00-00-51");
    ble.println("AT+BleKeyboardCode=00-00");
  }
  if (buttonBotR == 1) //Pressing right
  {
    ble.println("AT+BleKeyboardCode=00-00-4f");
    ble.println("AT+BleKeyboardCode=00-00");
  }
  if (buttonSpace == 1) //Pressing space
  {
    ble.println("AT+BleKeyboardCode=00-00-2c");
    ble.println("AT+BleKeyboardCode=00-00");
  }
}
