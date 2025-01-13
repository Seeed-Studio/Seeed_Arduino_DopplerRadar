#include "BGT24LTR11.h"

#ifdef __AVR__
    #include <SoftwareSerial.h>
    SoftwareSerial SSerial(2, 3); // RX, TX
    #define COMSerial SSerial
    #define ShowSerial Serial

    BGT24LTR11<SoftwareSerial> BGT;
#endif

#if defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_ARCH_RP2350) || defined(ARDUINO_ARCH_RENESAS)
    #include <SoftwareSerial.h>
    SoftwareSerial SSerial(D7, D6); // RX, TX
    #define COMSerial SSerial
    #define ShowSerial Serial

    BGT24LTR11<SoftwareSerial> BGT;
#endif

#if defined(CONFIG_IDF_TARGET_ESP32C3) || defined(CONFIG_IDF_TARGET_ESP32C6) || defined(CONFIG_IDF_TARGET_ESP32S3)
    #define COMSerial Serial0
    #define ShowSerial Serial

    BGT24LTR11<HardwareSerial> BGT;
#endif

#ifdef SEEED_XIAO_M0
    #define COMSerial Serial1
    #define ShowSerial Serial

    BGT24LTR11<Uart> BGT;
#elif defined(ARDUINO_SAMD_VARIANT_COMPLIANCE)
    #define COMSerial Serial1
    #define ShowSerial SerialUSB

    BGT24LTR11<Uart> BGT;
#endif

#ifdef ARDUINO_ARCH_STM32F4
    #define COMSerial Serial
    #define ShowSerial SerialUSB

    BGT24LTR11<HardwareSerial> BGT;
#endif

#if defined(NRF52840_XXAA)
    #ifdef USE_TINYUSB
    #include <Adafruit_TinyUSB.h>
    #endif
    #define COMSerial Serial1
    #define ShowSerial Serial

    BGT24LTR11<Uart> BGT;
#endif

void setup() {
    // put your setup code here, to run once:
    ShowSerial.begin(9600);
    COMSerial.begin(115200);
    BGT.init(COMSerial);
    while (!ShowSerial);
#ifndef ARDUINO_ARCH_RENESAS
    while (!COMSerial);
#endif
    /*
        MODE 0 -->detection target mode
        MODE 1 -->I/Q ADC mode
    */
    //Set mode
    BGT.setMode(0);

    //set threshold
    while (!BGT.setThreshold(1024)) {
        ShowSerial.println("set threshold erro");
    }
    ShowSerial.println("set threshold success");
}

void loop() {
    // put your main code here, to run repeatedly:
    uint16_t threshold;
    //get threshold
    threshold = BGT.getThreshold();
    if (threshold != 0) {
        ShowSerial.print("get threshold :");
        ShowSerial.println(threshold);
    }
    delay(1000);
}
