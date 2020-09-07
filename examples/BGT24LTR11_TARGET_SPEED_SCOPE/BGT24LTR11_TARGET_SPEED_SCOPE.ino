#include "BGT24LTR11.h"

#ifdef __AVR__
    #include <SoftwareSerial.h>
    SoftwareSerial SSerial(2, 3); // RX, TX
    #define COMSerial SSerial
    #define ShowSerial Serial

    BGT24LTR11<SoftwareSerial> BGT;
#endif

#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
    #define COMSerial Serial1
    #define ShowSerial SerialUSB

    BGT24LTR11<Uart> BGT;
#endif

#ifdef ARDUINO_ARCH_STM32F4
    #define COMSerial Serial
    #define ShowSerial SerialUSB

    BGT24LTR11<HardwareSerial> BGT;
#endif

void setup() {
    // put your setup code here, to run once:
    ShowSerial.begin(9600);
    COMSerial.begin(115200);
    BGT.init(COMSerial);
    while (!ShowSerial);
    while (!COMSerial);
    /*
        MODE 0 -->detection target mode
        MODE 1 -->I/Q ADC mode
    */
    BGT.setMode(0);
    //Set the speed detection range
    while (!BGT.setSpeedScope(512, 0));
}

void loop() {
    // put your main code here, to run repeatedly:
    uint16_t maxspeed, minspeed;

    //View speed range
    if (BGT.getSpeedScope(&maxspeed, &minspeed)) {
        ShowSerial.print("maximum speed: ");
        ShowSerial.print(maxspeed);
        ShowSerial.print("     Minimum Speed: ");
        ShowSerial.println(minspeed);
    }
    delay(1000);

}
