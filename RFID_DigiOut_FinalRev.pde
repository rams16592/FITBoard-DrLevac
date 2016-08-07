/**
 * RFID Access Control
 *
 * Some of this code was inspired by Tom Igoe's RFID tutorial
 * From the ID-12 example code on the Arduino Playground
 * And HIGHLY based on Jonathan Oxer's project at:
 * http://www.practicalarduino.com/projects/medium/rfid-access-control
 */

// Set up the serial connection to the RFID reader module. In order to
// keep the Arduino TX and RX pins free for communication with a host,
// the sketch uses the SoftwareSerial library to implement serial
// communications on other pins.
#include <SoftwareSerial.h>

// The RFID module's TX pin needs to be connected to the Arduino. 

 #define rxPin 4 
 #define txPin 5 

// Create a software serial object for the connection to the RFID module
SoftwareSerial rfid = SoftwareSerial( rxPin, txPin );

// Set up outputs
#define futureOutput 12
#define ledPin 13

// Specify how long the output should be held.
#define unlockSeconds 2

// The tag database consists of two parts. The first part is an array of
// tag values with each tag taking up 5 bytes. The second is a list of
// names with one name for each tag (ie: group of 5 bytes). You can expand
// or shrink this as you see fit. Tags 2 and 3 are only there for example.
char* allowedTags[] = {
  "[INSERT IDENTIFIER HERE]",         // Tag 1
  "2900940E95",         // Tag 2
  "ABC123DE45",         // Tag 3
};

// List of names to associate with the matching tag IDs
char* tagName[] = {
  "[ADD YOUR NAME HERE]",      // Tag 1
  "Mark Trussell",      // Tag 2
  "NAME 3",       // Tag 3
};

// Check the number of tags defined
int numberOfTags = sizeof(allowedTags)/sizeof(allowedTags[0]);

int incomingByte = 0;    // To store incoming serial data

/**
 * Setup
 */
void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(futureOutput, OUTPUT);
  digitalWrite(futureOutput, LOW);

  Serial.begin(9600);   // Serial port for connection to host
  rfid.begin(9600);      // Serial port for connection to RFID module

  Serial.println("RFID Reader Initialized");
}

/**
 * Loop
 */
void loop() {
  byte i         = 0;
  byte val       = 0;
  byte checksum  = 0;
  byte bytesRead = 0;
  byte tempByte  = 0;
  byte tagBytes[6];    // "Unique" tags are only 5 bytes but we need an extra byte for the checksum
  char tagValue[10];

  // Read from the RFID module. Because this connection uses SoftwareSerial
  // there is no equivalent to the Serial.available() function, so at this
  // point the program blocks while waiting for a value from the module
  if((val = rfid.read()) == 2) {        // Check for header
    bytesRead = 0;
    while (bytesRead < 12) {            // Read 10 digit code + 2 digit checksum
      val = rfid.read();

      // Append the first 10 bytes (0 to 9) to the raw tag value
      if (bytesRead < 10)
      {
        tagValue[bytesRead] = val;
      }

      // Check if this is a header or stop byte before the 10 digit reading is complete
      if((val == 0x0D)||(val == 0x0A)||(val == 0x03)||(val == 0x02)) {
        break;                          // Stop reading
      }

      // Ascii/Hex conversion:
      if ((val >= '0') && (val <= '9')) {
        val = val - '0';
      }
      else if ((val >= 'A') && (val <= 'F')) {
        val = 10 + val - 'A';
      }

      // Every two hex-digits, add a byte to the code:
      if (bytesRead & 1 == 1) {
        // Make space for this hex-digit by shifting the previous digit 4 bits to the left
        tagBytes[bytesRead >> 1] = (val | (tempByte << 4));

        if (bytesRead >> 1 != 5) {                // If we're at the checksum byte,
          checksum ^= tagBytes[bytesRead >> 1];   // Calculate the checksum... (XOR)
        };
      } else {
        tempByte = val;                           // Store the first hex digit first
      };

      bytesRead++;                                // Ready to read next digit
    }

    // Send the result to the host connected via USB
    if (bytesRead == 12) {                        // 12 digit read is complete
      tagValue[10] = '\0';                        // Null-terminate the string

      Serial.print("Tag read: ");
      for (i=0; i<5; i++) {
        // Add a leading 0 to pad out values below 16
        if (tagBytes[i] < 16) {
          Serial.print("0");
        }
        Serial.print(tagBytes[i], HEX);
      }
      Serial.println();

      Serial.print("Checksum: ");
      Serial.print(tagBytes[5], HEX);
      Serial.println(tagBytes[5] == checksum ? " -- passed." : " -- error.");

      // Show the raw tag value
      Serial.print("VALUE: ");
      Serial.println(tagValue);

      // Search the tag database for this particular tag
      int tagId = findTag( tagValue );

      // Only fire the strike plate if this tag was found in the database
      if( tagId > 0 )
      {
        Serial.print("Authorized tag ID ");
        Serial.print(tagId);
        Serial.print(": unlocking for ");
        Serial.println(tagName[tagId - 1]);   // Get the name for this tag from the database
        unlock();                             // Fire the strike plate to open the lock
      } else {
        Serial.println("Tag not authorized");
      }
      Serial.println();     // Blank separator line in output
    }

    bytesRead = 0;
  }
}

/**
 * Fire the relay to activate the strike plate for the configured
 * number of seconds.
 */
void unlock() {
  digitalWrite(ledPin, HIGH);
  digitalWrite(futureOutput, HIGH);
  delay(unlockSeconds * 1000);
  digitalWrite(futureOutput, LOW);
  digitalWrite(ledPin, LOW);
}

/**
 * Search for a specific tag in the database
 */
int findTag( char tagValue[10] ) {
  for (int thisCard = 0; thisCard < numberOfTags; thisCard++) {
    // Check if the tag value matches this row in the tag database
    if(strcmp(tagValue, allowedTags[thisCard]) == 0)
    {
      // The row in the database starts at 0, so add 1 to the result so
      // that the card ID starts from 1 instead (0 represents "no match")
      return(thisCard + 1);
    }
  }
  // If we don't find the tag return a tag ID of 0 to show there was no match
  return(0);
}
