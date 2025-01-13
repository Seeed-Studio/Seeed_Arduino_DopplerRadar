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
    while (!BGT.setMode(0));
}

void loop() {
    // put your main code here, to run repeatedly:
    uint16_t state = 0;
    ShowSerial.print("target speed:");
    ShowSerial.println(BGT.getSpeed());
    state = BGT.getTargetState();
    //2 --> target approach
    //1 --> target leave
    //0 --> Not Found target
    if (state == 2) {
        ShowSerial.println("target approach");
    } else if (state == 1) {
        ShowSerial.println("target leave");
    }
    delay(200);
}
