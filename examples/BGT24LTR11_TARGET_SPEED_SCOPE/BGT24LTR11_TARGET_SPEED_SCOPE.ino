#include "GBT24LTR11.h"

#ifdef __AVR__
#include <SoftwareSerial.h>
SoftwareSerial SSerial(2, 3); // RX, TX
#define COMSerial SSerial
#define ShowSerial Serial

GBT24LTR11<SoftwareSerial> GBT;
#endif

#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
#define COMSerial Serial
#define ShowSerial SerialUSB

GBT24LTR11<Uart> GBT;
#endif

#ifdef ARDUINO_ARCH_STM32F4
#define COMSerial Serial
#define ShowSerial SerialUSB

GBT24LTR11<HardwareSerial> GBT;
#endif

void setup() {
  // put your setup code here, to run once:
  ShowSerial.begin(9600);
  COMSerial.begin(115200);
  GBT.init(COMSerial);
  while(!ShowSerial);
  while(!COMSerial);
  /*
     MODE 0 -->detection target mode
     MODE 1 -->I/Q ADC mode
  */
  GBT.setMode(0);
  //Set the speed detection range
  while (!GBT.setSpeedScope(512, 0));
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t maxspeed, minspeed;

  //View speed range
  if (GBT.getSpeedScope(&maxspeed, &minspeed)) {
    ShowSerial.print("maximum speed: ");
    ShowSerial.print(maxspeed);
    ShowSerial.print("     Minimum Speed: ");
    ShowSerial.println(minspeed);
  }
  delay(1000);

}
