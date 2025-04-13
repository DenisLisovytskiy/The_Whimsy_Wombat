
#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "69696";

struct data{
  int aileron_x;
  int elevator_y;
  int rudder_x;
  int flaps_y; 
  int chrust;
  };
data mydata;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();

}

void loop() {
  
  mydata.elevator_y = map(analogRead(A2), 0, 1023, 30, 150);
  mydata.rudder_x = map(analogRead(A3), 0, 1023, 30, 150);
  mydata.flaps_y = map(analogRead(A4), 0, 1023, 30, 150);
  mydata.aileron_x = map(analogRead(A1), 0, 1023, 30, 150);
  mydata.chrust = map(analogRead(A0), 0, 1023, 0, 180);
  radio.write(&mydata, sizeof(mydata)); 
  
}
