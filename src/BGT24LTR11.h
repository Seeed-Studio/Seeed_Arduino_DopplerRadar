#ifndef __BGT24LTR11__
#define __BGT24LTR11__
#include "Arduino.h"

//address code
#define BGT24LTR11_MESSAGE_HEAD 0x55
#define BGT24LTR11_RECEIVE_ADDRESS 0x2A
#define BGT24LTR11_SEND_ADDRESS 0xA2

//command code
#define BGT24LTR11_COMMAND_GET_TARGET 0xC1
#define BGT24LTR11_COMMAND_GET_IQADC 0xC2
#define BGT24LTR11_COMMAND_SET_SPEED_SCOPE 0xC3
#define BGT24LTR11_COMMAND_GET_SPEED_SCOPE 0xC4
#define BGT24LTR11_COMMAND_SET_MODE 0xC5
#define BGT24LTR11_COMMAND_GET_MODE 0xC6
#define BGT24LTR11_COMMAND_SET_THRESHOLD 0xC7
#define BGT24LTR11_COMMAND_GET_THRESHOLD 0xC8

// target state
#define BGT24LTR11_TARGET_APPROACH 0x02
#define BGT24LTR11_TARGET_LEAVE 0x01
#define BGT24LTR11_TARGET_NONE 0x00

//mode
#define BGT24LTR11_MODE_TARGET 0X00
#define BGT24LTR11_MODE_IQADC 0x01

template <class T>
class BGT24LTR11 {
  private:
    T* _serial;
    unsigned char commandC1[7] = {BGT24LTR11_MESSAGE_HEAD, BGT24LTR11_RECEIVE_ADDRESS,
                                  BGT24LTR11_COMMAND_GET_TARGET,
                                  0x00, 0x02, 0x01, 0x42
                                 };
    /* data */
  public:
    void init(T& serialPort);
    uint16_t getSpeed();
    uint16_t getTargetState();
    uint8_t getIQADC(uint16_t I_d[], uint16_t Q_d[], uint16_t* len);
    uint8_t setSpeedScope(uint16_t maxspeed, uint16_t minspeed);
    uint8_t getSpeedScope(uint16_t* maxspeed, uint16_t* minspeed);
    uint8_t setMode(uint16_t mode);
    uint8_t getMode();
    uint8_t setThreshold(uint16_t whreshold);
    uint16_t getThreshold();
    uint16_t calculateChecksum(uint16_t *data, uint16_t data_length);
    uint16_t messageChecksum(uint16_t high_order, uint16_t low_order);

};

#endif
