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
  //Set mode
  while(!GBT.setMode(0));
}

void loop() {
  // put your main code here, to run repeatedly:
  /*get mode
   * 1   detect the target mode
   * 2   Reported I/Q ADC
   * 0   fail
   */
  uint8_t mode;
  mode=GBT.getMode();
  if(mode==1){
    ShowSerial.println("detect the target mode");
  }else if(mode==2){
    ShowSerial.println("Reported I/Q ADC");
  }
  delay(1000);

}
