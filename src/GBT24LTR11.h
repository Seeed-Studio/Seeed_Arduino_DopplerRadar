#ifndef __GBT24LTR11__
#define __GBT24LTR11__
#include "Arduino.h"

//address code 
#define GBT24LTR11_MESSAGE_HEAD 0x55
#define GBT24LTR11_RECEIVE_ADDRESS 0x2A
#define GBT24LTR11_SEND_ADDRESS 0xA2

//command code
#define GBT24LTR11_COMMAND_GET_TARGET 0xC1
#define GBT24LTR11_COMMAND_GET_IQADC 0xC2
#define GBT24LTR11_COMMAND_SET_SPEED_SCOPE 0xC3
#define GBT24LTR11_COMMAND_GET_SPEED_SCOPE 0xC4
#define GBT24LTR11_COMMAND_SET_MODE 0xC5
#define GBT24LTR11_COMMAND_GET_MODE 0xC6 
#define GBT24LTR11_COMMAND_SET_THRESHOLD 0xC7
#define GBT24LTR11_COMMAND_GET_THRESHOLD 0xC8

// target state
#define GBT24LTR11_TARGET_APPROACH 0x02
#define GBT24LTR11_TARGET_LEAVE 0x01
#define GBT24LTR11_TARGET_NONE 0x00

//mode
#define GBT24LTR11_MODE_TARGET 0X00
#define GBT24LTR11_MODE_IQADC 0x01

template <class T>
class GBT24LTR11
{
private:
    T *_serial;
    unsigned char commandC1[7]={GBT24LTR11_MESSAGE_HEAD,GBT24LTR11_RECEIVE_ADDRESS,
                                GBT24LTR11_COMMAND_GET_TARGET,
                                0x00,0x02,0x01,0x42};
    /* data */
public:
    void init(T &serialPort);
    uint16_t getSpeed();
    uint16_t getTargetState();
    uint8_t getIQADC(uint16_t I_d[],uint16_t Q_d[],uint16_t *len);
    uint8_t setSpeedScope(uint16_t maxspeed,uint16_t minspeed);
    uint8_t getSpeedScope(uint16_t *maxspeed,uint16_t *minspeed);
    uint8_t setMode(uint16_t mode);
    uint8_t getMode();
    uint8_t setThreshold(uint16_t whreshold);
    uint16_t getThreshold();
};

#endif
