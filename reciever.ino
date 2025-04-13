#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

Servo ESC; 
Servo ail_l;
Servo ail_r;
Servo elevator;
Servo rudder;
Servo flap_l;
Servo flap_r;

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
//3 4 5 6 9 10 free pins
void setup() {
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  ESC.attach(10 ,1000,2000);
  ail_l.attach(3);
  ail_r.attach(4);
  elevator.attach(5);
  rudder.attach(6);
  flap_l.attach(9);
  flap_r.attach(2);
}

void loop() {
if (radio.available()) {
    radio.read(&mydata, sizeof(mydata)); // Read the whole data and store it into the 'data' structure

    ESC.write(mydata.chrust);
    ail_l.write(mydata.aileron_x);
    ail_r.write(mydata.aileron_x);
    elevator.write(mydata.elevator_y);
    flap_l.write(mydata.flaps_y);
    flap_r.write(mydata.flaps_y);
    rudder.write(mydata.rudder_x);
  }
}
