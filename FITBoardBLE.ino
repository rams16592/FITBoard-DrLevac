

//VR Lab 'FIT-Board' Code
//Adam Perruzzi
//perruzzi.a@husky.neu.edu for questions

// Utilize Bluefruit UART Module
#include <Arduino.h>
#include <SoftwareSerial.h>
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


//Input pins [all analog, correspond to the magnets on top of the board]
const int humanPin = A0;      // the number of the top right human contact pin
const int humanPin2 = A1;     // the number of the middle right human contact pin
const int humanPin3 = A2;     // the number of the bottom right human contact pin
const int humanPin4 = A3;     // the number of the top center human contact pin
const int humanPin5 = A4;     // the number of the middle center human contact pin
const int humanPin6 = A5;     // the number of the bottom center human contact pin
const int humanPin7 = A6;     // the number of the top left human contact pin
const int humanPin8 = A7;     // the number of the middle left human contact pin
const int humanPin9 = 0;     // the number of the bottom left human contact pin
const int humanPin10 = 0;    // the number of the 'I don't want to assign this button' human contact pin


/*
//Output pins [all digital, ledPin for help debugging]
const int ledPin = 13;        // the number of the LED pin
const int makeyUp = 12;       // the number of the Makey pin
const int makeyLeft = 11;     // the number of the down Makey pin
const int makeyDown = 10;     // the number of the left Makey pin
const int makeyRight = 9;     // the number of the right Makey pin
const int makeySpace = 8;     //the number of the space Makey pin
*/
const int ledPin = 13;        // the number of the LED pin
const int makeyUp = 6;       // the number of the Makey pin
const int makeyLeft = 5;     // the number of the down Makey pin
const int makeyDown = 4;     // the number of the left Makey pin
const int makeyRight = 3;     // the number of the right Makey pin
const int makeySpace = 2;     //the number of the space Makey pin


//Variables to store the input level from each of the analog inputs
int buttonHuman = 0;
int buttonHuman2 = 0;
int buttonHuman3 = 0;
int buttonHuman4 = 0;
int buttonHuman5 = 0;
int buttonHuman6 = 0;
int buttonHuman7 = 0;
int buttonHuman8 = 0;
int buttonHuman9 = 0;
int buttonHuman10 = 0;


//Variables to store the input level from the selected buttons, once assigned
int buttonUp = 0;         //read on up button
int buttonLeft = 0;       //read on down button
int buttonDown = 0;       //read on down button
int buttonRight = 0;       //read on down button
int buttonSpace = 0;       //read on down button


//Variables to assign pins
int pinUp;
int pinLeft;
int pinDown;
int pinRight;
int pinSpace;
 
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
  pinMode(humanPin, INPUT);
  pinMode(humanPin2, INPUT);
  pinMode(humanPin3, INPUT);
  pinMode(humanPin4, INPUT);
  pinMode(humanPin5, INPUT);
  pinMode(humanPin6, INPUT);
  pinMode(humanPin7, INPUT);
  pinMode(humanPin8, INPUT);
  pinMode(humanPin9, INPUT);
  pinMode(humanPin10, INPUT);

  
  //Initialize outputs
  pinMode(ledPin, OUTPUT);
  pinMode(makeyUp, OUTPUT);
  pinMode(makeyLeft, OUTPUT);
  pinMode(makeyDown, OUTPUT);
  pinMode(makeyRight, OUTPUT);
  pinMode(makeySpace, OUTPUT);


  //Set output on Makey pins to max value [Makey reads as "off"]
  analogWrite(makeyUp, 255);
  analogWrite(makeyLeft, 255);
  analogWrite(makeyDown, 255);
  analogWrite(makeyRight, 255);
  analogWrite(makeySpace, 255);


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


  //Assign up arrow

  //Opening message
  lcd.print (" Press up arrow ");
  lcd.setCursor(0,2);
  lcd.print ("or 'no button'");
  delay(500);

  while (1) //Loop until button assignment is made
  {
  //Read pin values
  buttonHuman = analogRead(humanPin);
  buttonHuman2 = analogRead(humanPin2);
  buttonHuman3 = analogRead(humanPin3);
  buttonHuman4 = analogRead(humanPin4);
  buttonHuman5 = analogRead(humanPin5);
  buttonHuman6 = analogRead(humanPin6);
  buttonHuman7 = analogRead(humanPin7);
  buttonHuman8 = analogRead(humanPin8);
  buttonHuman9 = analogRead(humanPin9);
  buttonHuman10 = analogRead(humanPin10);

  //Check to see which button is being pressed
  if (buttonHuman > 80) //Pressing A0
  {
    pinUp = humanPin;
    break;
  }
  if (buttonHuman2 > 80) //Pressing A1
  {
    pinUp = humanPin2;
    break;
  }
  if (buttonHuman3 > 80) //Pressing A2
  {
    pinUp = humanPin3;
    break;
  }
  if (buttonHuman4 > 80) //Pressing A3
  {
    pinUp = humanPin4;
    break;
  }
  if (buttonHuman5 > 80) //Pressing A4
  {
    pinUp = humanPin5;
    break;
  }
  if (buttonHuman6 > 80) //Pressing A5
  {
    pinUp = humanPin6;
    break;
  }
  if (buttonHuman7 > 80) //Pressing A6
  {
    pinUp = humanPin7;
    break;
  }
  if (buttonHuman8 > 80) //Pressing A7
  {
    pinUp = humanPin8;
    break;
  }
  if (buttonHuman9 > 80) //Pressing A8
  {
    pinUp = humanPin9;
    break;
  }
  if (buttonHuman10 > 80) //Pressing cancel
  {
    pinUp = A9;

    //Message that input was not chosen
    lcd.clear();
    lcd.print ("  You selected ");
    lcd.setCursor(0,2);
    lcd.print ("  'no button'");
    delay(1000);
    break;
  }
  }
  
  if (pinUp != A9) //Any pin selected
  {
    //Message that a button was successfully chosen
    lcd.clear();
    lcd.print ("     Button");
    lcd.setCursor(0,2);
    lcd.print ("    Selected!");
    delay(1000);
  }
  lcd.clear();

  
  //Assign left arrow

  //Opening message
  lcd.print ("Press left arrow");
  lcd.setCursor(0,2);
  lcd.print ("or 'no button'");
  delay(500);
  
  while (1) //Loop until button assignment is made
  {
  //Read pin values
  buttonHuman = analogRead(humanPin);
  buttonHuman2 = analogRead(humanPin2);
  buttonHuman3 = analogRead(humanPin3);
  buttonHuman4 = analogRead(humanPin4);
  buttonHuman5 = analogRead(humanPin5);
  buttonHuman6 = analogRead(humanPin6);
  buttonHuman7 = analogRead(humanPin7);
  buttonHuman8 = analogRead(humanPin8);
  buttonHuman9 = analogRead(humanPin9);
  buttonHuman10 = analogRead(humanPin10);

  //Check to see which button is being pressed
  if (buttonHuman > 80) //Pressing A0
  {
    pinLeft = humanPin;
    break;
  }
  if (buttonHuman2 > 80) //Pressing A1
  {
    pinLeft = humanPin2;
    break;
  }
  if (buttonHuman3 > 80) //Pressing A2
  {
    pinLeft = humanPin3;
    break;
  }
  if (buttonHuman4 > 80) //Pressing A3
  {
    pinLeft = humanPin4;
    break;
  }
  if (buttonHuman5 > 80) //Pressing A4
  {
    pinLeft = humanPin5;
    break;
  }
  if (buttonHuman6 > 80) //Pressing A5
  {
    pinLeft = humanPin6;
    break;
  }
  if (buttonHuman7 > 80) //Pressing A6
  {
    pinLeft = humanPin7;
    break;
  }
  if (buttonHuman8 > 80) //Pressing A7
  {
    pinLeft = humanPin8;
    break;
  }
  if (buttonHuman9 > 80) //Pressing A8
  {
    pinLeft = humanPin9;
    break;
  }
  if (buttonHuman10 > 80) //Pressing cancel
  {
    pinLeft = A9;

    //Message that input was not chosen
    lcd.clear();
    lcd.print ("  You selected ");
    lcd.setCursor(0,2);
    lcd.print ("  'no button'");
    delay(1000);
    break;
  }
  }
  
  if (pinLeft != A9) //Any pin selected
  {
    //Message that a button was successfully chosen
    lcd.clear();
    lcd.print ("Button");
    lcd.setCursor(0,2);
    lcd.print ("Selected!");
    delay(1000);
  }
  lcd.clear();


  //Assign down arrow

  //Opening message
  lcd.print ("Press down arrow");
  lcd.setCursor(0,2);
  lcd.print ("or 'no button'");
  delay(500);
  
  while (1) //Loop until button assignment is made
  {
  //Read pin values
  buttonHuman = analogRead(humanPin);
  buttonHuman2 = analogRead(humanPin2);
  buttonHuman3 = analogRead(humanPin3);
  buttonHuman4 = analogRead(humanPin4);
  buttonHuman5 = analogRead(humanPin5);
  buttonHuman6 = analogRead(humanPin6);
  buttonHuman7 = analogRead(humanPin7);
  buttonHuman8 = analogRead(humanPin8);
  buttonHuman9 = analogRead(humanPin9);
  buttonHuman10 = analogRead(humanPin10);

  //Check to see which button is being pressed
  if (buttonHuman > 80) //Pressing A0
  {
    pinDown = humanPin;
    break;
  }
  if (buttonHuman2 > 80) //Pressing A1
  {
    pinDown = humanPin2;
    break;
  }
  if (buttonHuman3 > 80) //Pressing A2
  {
    pinDown = humanPin3;
    break;
  }
  if (buttonHuman4 > 80) //Pressing A3
  {
    pinDown = humanPin4;
    break;
  }
  if (buttonHuman5 > 80) //Pressing A4
  {
    pinDown = humanPin5;
    break;
  }
  if (buttonHuman6 > 80) //Pressing A5
  {
    pinDown = humanPin6;
    break;
  }
  if (buttonHuman7 > 80) //Pressing A6
  {
    pinDown = humanPin7;
    break;
  }
  if (buttonHuman8 > 80) //Pressing A7
  {
    pinDown = humanPin8;
    break;
  }
  if (buttonHuman9 > 80) //Pressing A8
  {
    pinDown = humanPin9;
    break;
  }
  if (buttonHuman10 > 80) //Pressing cancel
  {
    pinDown = A9;

    //Message that input was not chosen
    lcd.clear();
    lcd.print ("  You selected ");
    lcd.setCursor(0,2);
    lcd.print ("  'no button'");
    delay(1000);
    break;
  }
  }
  
  if (pinDown != A9) //Any pin selected
  {
    //Message that a button was successfully chosen
    lcd.clear();
    lcd.print ("Button");
    lcd.setCursor(0,2);
    lcd.print ("Selected!");
    delay(1000);
  }
  lcd.clear();


  //Assign right arrow

  //Opening message
  lcd.print ("Press rght arrow");
  lcd.setCursor(0,2);
  lcd.print ("or 'no button'");
  delay(500);
  
  while (1) //Loop until button assignment is made
  {
  //Read pin values
  buttonHuman = analogRead(humanPin);
  buttonHuman2 = analogRead(humanPin2);
  buttonHuman3 = analogRead(humanPin3);
  buttonHuman4 = analogRead(humanPin4);
  buttonHuman5 = analogRead(humanPin5);
  buttonHuman6 = analogRead(humanPin6);
  buttonHuman7 = analogRead(humanPin7);
  buttonHuman8 = analogRead(humanPin8);
  buttonHuman9 = analogRead(humanPin9);
  buttonHuman10 = analogRead(humanPin10);

  //Check to see which button is being pressed
  if (buttonHuman > 80) //Pressing A0
  {
    pinRight = humanPin;
    break;
  }
  if (buttonHuman2 > 80) //Pressing A1
  {
    pinRight = humanPin2;
    break;
  }
  if (buttonHuman3 > 80) //Pressing A2
  {
    pinRight = humanPin3;
    break;
  }
  if (buttonHuman4 > 80) //Pressing A3
  {
    pinRight = humanPin4;
    break;
  }
  if (buttonHuman5 > 80) //Pressing A4
  {
    pinRight = humanPin5;
    break;
  }
  if (buttonHuman6 > 80) //Pressing A5
  {
    pinRight = humanPin6;
    break;
  }
  if (buttonHuman7 > 80) //Pressing A6
  {
    pinRight = humanPin7;
    break;
  }
  if (buttonHuman8 > 80) //Pressing A7
  {
    pinRight = humanPin8;
    break;
  }
  if (buttonHuman9 > 80) //Pressing A8
  {
    pinRight = humanPin9;
    break;
  }
  if (buttonHuman10 > 80) //Pressing cancel
  {
    pinRight = A9;

    //Message that input was not chosen
    lcd.clear();
    lcd.print ("  You selected ");
    lcd.setCursor(0,2);
    lcd.print ("  'no button'");
    delay(1000);
    break;
  }
  }
  
  if (pinRight != A9) //Any pin selected
  {
    //Message that a button was successfully chosen
    lcd.clear();
    lcd.print ("Button");
    lcd.setCursor(0,2);
    lcd.print ("Selected!");
    delay(1000);
  }
  lcd.clear();

  
  //Assign space button

  //Opening message
  lcd.print ("Press space bttn");
  lcd.setCursor(0,2);
  lcd.print ("or 'no button'");
  delay(500);
  
  while (1) //Loop until button assignment is made
  {
  //Read pin values
  buttonHuman = analogRead(humanPin);
  buttonHuman2 = analogRead(humanPin2);
  buttonHuman3 = analogRead(humanPin3);
  buttonHuman4 = analogRead(humanPin4);
  buttonHuman5 = analogRead(humanPin5);
  buttonHuman6 = analogRead(humanPin6);
  buttonHuman7 = analogRead(humanPin7);
  buttonHuman8 = analogRead(humanPin8);
  buttonHuman9 = analogRead(humanPin9);
  buttonHuman10 = analogRead(humanPin10);

  //Check to see which button is being pressed
  if (buttonHuman > 80) //Pressing A0
  {
    pinSpace = humanPin;
    break;
  }
  if (buttonHuman2 > 80) //Pressing A1
  {
    pinSpace = humanPin2;
    break;
  }
  if (buttonHuman3 > 80) //Pressing A2
  {
    pinSpace = humanPin3;
    break;
  }
  if (buttonHuman4 > 80) //Pressing A3
  {
    pinSpace = humanPin4;
    break;
  }
  if (buttonHuman5 > 80) //Pressing A4
  {
    pinSpace = humanPin5;
    break;
  }
  if (buttonHuman6 > 80) //Pressing A5
  {
    pinSpace = humanPin6;
    break;
  }
  if (buttonHuman7 > 80) //Pressing A6
  {
    pinSpace = humanPin7;
    break;
  }
  if (buttonHuman8 > 80) //Pressing A7
  {
    pinSpace = humanPin8;
    break;
  }
  if (buttonHuman9 > 80) //Pressing A8
  {
    pinSpace = humanPin9;
    break;
  }
  if (buttonHuman10 > 80) //Pressing cancel
  {
    pinSpace = A9;

    //Message that input was not chosen
    lcd.clear();
    lcd.print ("  You selected ");
    lcd.setCursor(0,2);
    lcd.print ("  'no button'");
    delay(1000);
    break;
  }
  }
  
  if (pinSpace != A9) //Any pin selected
  {
    //Message that a button was successfully chosen
    lcd.clear();
    lcd.print ("Button");
    lcd.setCursor(0,2);
    lcd.print ("Selected!");
    delay(1000);
  }
  lcd.clear();
}

void loop() {
  //Read the state of the assigned inputs
  buttonUp = analogRead(pinUp);
  buttonLeft = analogRead(pinLeft);
  buttonDown = analogRead(pinDown);
  buttonRight = analogRead(pinRight);
  buttonSpace = analogRead(pinSpace);

  //If any input is pressed, light the LED, for testing purposes
  if (buttonUp > 70 || buttonLeft > 70 || buttonDown > 70 || buttonRight > 70 || buttonSpace > 70) //when any direction is touched
  {
    digitalWrite(ledPin, HIGH); // turn LED on
    //TODO: with full p-fit board make more swtich case like
    //ble.print("AT+BleKeyboardCode=");
  }
  else {
    digitalWrite(ledPin, LOW); // turn LED off
  }

  

  //Individual button actions
  if (buttonUp > 70) //Pressing up
  {
    analogWrite(makeyUp, 0); //turn on Makey up button
    ble.println("AT+BleKeyboardCode=00-00-52");
    ble.println("AT+BleKeyboardCode=00-00");
    
  }
  else { //Not pressing up
    analogWrite(makeyUp, 255); //turn off Makey up button
  }
  
  if (buttonLeft > 70) //Pressing left
  {
    analogWrite(makeyLeft, 0); //turn on Makey left button
    ble.println("AT+BleKeyboardCode=00-00-50");
    ble.println("AT+BleKeyboardCode=00-00");
  }
  else { //Not pressing left
    analogWrite(makeyLeft, 255); //turn off Makey left button
  }
  
  if (buttonDown > 70) //Pressing down
  {
    analogWrite(makeyDown, 0); //turn on Makey down button
    ble.println("AT+BleKeyboardCode=00-00-51");
    ble.println("AT+BleKeyboardCode=00-00");
  }
  else { //Not pressing down
    analogWrite(makeyDown, 255); //turn off Makey down button
  }

  if (buttonRight > 70) //Pressing right
  {
    analogWrite(makeyRight, 0); //turn on Makey right button
    ble.println("AT+BleKeyboardCode=00-00-4f");
    ble.println("AT+BleKeyboardCode=00-00");
  }
  else { //Not pressing right
    analogWrite(makeyRight, 255); //turn off Makey right button
  }

  if (buttonSpace > 70) //Pressing space
  {
    analogWrite(makeySpace, 0); //turn on Makey space button
    ble.println("AT+BleKeyboardCode=00-00-2c");
    ble.println("AT+BleKeyboardCode=00-00");

  }
  else { //Not pressing right
    analogWrite(makeySpace, 255); //turn off Makey space button
  }
}
