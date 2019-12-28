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

void setup()
{
  // put your setup code here, to run once:
  ShowSerial.begin(9600);
  COMSerial.begin(115200);
  GBT.init(COMSerial);
  while (!ShowSerial)
    ;
  while (!COMSerial)
    ;
  /*
   * MODE 0 -->detection target mode
   * MODE 1 -->I/Q ADC mode
   * 
   */
  while (!GBT.setMode(0))
    ;
}

void loop()
{
  // put your main code here, to run repeatedly:
  uint16_t state=0;
  ShowSerial.print("target speed:");
  ShowSerial.println(GBT.getSpeed());
  state = GBT.getTargetState();
  //2 --> target approach
  //1 --> target leave
  //0 --> Not Found target
  if (state == 2)
  {
    ShowSerial.println("target approach");
  }
  else if (state == 1)
  {
    ShowSerial.println("target leave");
  }
  delay(200);
}
