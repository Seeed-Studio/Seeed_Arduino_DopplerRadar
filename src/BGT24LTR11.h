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
#define BGT24LTR11_MODE_TARGET 0x00
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
    /****************************************************************
    Function Name: init
    Description: hand over serial port where module is connected to
    Parameters: serialPort
    Return: void
    ****************************************************************/
    void init(T& serialPort);

    /****************************************************************
    Function Name: getInfo
    Description: Get target state and speed in one call
    Parameters: targetState, speed
    Return: 1:success 0:fail
    ****************************************************************/
    uint8_t getInfo(uint16_t* target_tate, uint16_t* speed);

    /****************************************************************
    Function Name: getSpeed
    Description: Target acquisition speed
    Parameters: None
    Return: >0:success speed -1:fail
    ****************************************************************/
    uint16_t getSpeed();

    /****************************************************************
    Function Name: getTargetState
    Description: Get target state
    Parameters: None
    Return: 2:target approach   1:target leave  0:Not Found target or error
    ****************************************************************/
    uint16_t getTargetState();

    /****************************************************************
    Function Name: getIQADC
    Description: Gets the I/Q information ADC value.
    Parameters: I_d,Q_d,Store an array of I/Q information. len,The length of the array.
    Return: 1:success  0:fail
    ****************************************************************/
    uint8_t getIQADC(uint16_t I_d[], uint16_t Q_d[], uint16_t* len);

    /****************************************************************
        Function Name: setSpeedScope
        Description: Set the detection speed range.
        Parameters: maxspeed,minspeed 0-65535
        Return: 1:success  0:fail
    ****************************************************************/
    uint8_t setSpeedScope(uint16_t maxspeed, uint16_t minspeed);

    /****************************************************************
        Function Name: getSpeedScope
        Description: Get the detection speed range.
        Parameters: maxspeed,minspeed
        Return: 1:success  0:fail
    ****************************************************************/
    uint8_t getSpeedScope(uint16_t* maxspeed, uint16_t* minspeed);

    /****************************************************************
        Function Name: setMode
        Description: Set module mode.
        Parameters: 1:Gets the I/Q information ADC value mode. 0:To detect the target mode.
        Return: 1:success  0:fail
    ****************************************************************/
    uint8_t setMode(uint16_t mode);

    /****************************************************************
    Function Name: getMode
    Description: Get module mode.
    Parameters: none.
    Return: 1:detect the target mode  2:Reported I/Q ADC  0:fail
    ****************************************************************/
    uint8_t getMode();

    /****************************************************************
        Function Name: setThreshold
        Description: Set threshold which determines detection range.
        Parameters: threshold.
        Return: 1:success  0:fail
    ****************************************************************/
    uint8_t setThreshold(uint16_t threshold);

    /****************************************************************
        Function Name: getThreshold
        Description: Get threshold which determines detection range.
        Parameters: None.
        Return: 1:success  0:fail
    ****************************************************************/
    uint16_t getThreshold();

    /****************************************************************
    Function Name: calculateChecksum
    Description: Calculate checksum from data bytes
    Parameters: data, pointer to uint16_t data array. data_length, length of array to calculate checksum over
    Return: uint16_t value of checksum
    ****************************************************************/
    uint16_t calculateChecksum(uint16_t *data, uint16_t data_length);

    /****************************************************************
    Function Name: messageChecksum
    Description: Transform checksum from message to single value
    Parameters: high_order, low_order, last two checksum bytes from the message
    Return: uint16_t value of checksum
    ****************************************************************/
    uint16_t messageChecksum(uint16_t high_order, uint16_t low_order);

};

#endif
