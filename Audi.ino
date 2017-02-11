#include <SoftwareSerial.h>

int CapPin = 7;
SoftwareSerial AudiSerial(10, 11); // RX, TX
boolean state, lastState;

void setup() {
  pinMode(CapPin, INPUT);
  state = digitalRead(CapPin);
  lastState = state;
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    Serial.read(); // wait for serial port to connect. Needed for native USB port only
  }

  // set the data rate for the SoftwareSerial port
  AudiSerial.begin(9600);
  Serial.println("Waiting for the event");
}

void loop() { // run over and over

  lastState = state;
  state = digitalRead(CapPin);
  
  if ( state != lastState ) {
    Serial.println("Event is triggered");
    AudiSerial.write("AT+CMGF=1\r\n");
    delay(2000);
    AudiSerial.write("AT+CMGS=\"xxxxxxxxxx\"\r\n");
    delay(500);
    AudiSerial.write("Switch was turned ");
    AudiSerial.write(state ? "on" : "off");
    AudiSerial.write(0x1A);
    Serial.println("Finish to sent message");
  }

  delay(1000);
}
