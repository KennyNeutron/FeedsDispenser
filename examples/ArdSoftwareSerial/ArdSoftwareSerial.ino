#include <SoftwareSerial.h>

#define rxPin 3
#define txPin 2

// Set up a new SoftwareSerial object
SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);

void setup() {
  Serial.begin(9600);
  // Define pin modes for TX and RX
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  // Set the baud rate for the SoftwareSerial object
  mySerial.begin(9600);
  Serial.println("start");
}

void loop() {
  mySerial.println("Hello");
  delay(1000);
}
