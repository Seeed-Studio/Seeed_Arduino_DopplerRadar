#include "GBT24LTR11.h"

template <class T>
void GBT24LTR11<T>::init(T &serialPort)
{
    _serial = &serialPort;
}

/**************************************************************** 
 * Function Name: getSpeed
 * Description: Target acquisition speed
 * Parameters: None
 * Return: >0:success speed -1:fail
****************************************************************/
template <class T>
uint16_t GBT24LTR11<T>::getSpeed()
{
    uint16_t data[7] = {0};
    _serial->write(commandC1, 7);
    while (_serial->available() > 0)
    {
        if (_serial->read() == GBT24LTR11_MESSAGE_HEAD)
        {
            if (_serial->read() == GBT24LTR11_SEND_ADDRESS)
            {
                if (_serial->read() == GBT24LTR11_COMMAND_GET_TARGET)
                {
                    for (int i = 0; i < 7; i++)
                    {
                        data[i] = _serial->read();
                    }
                    return (data[2] * 256 + data[3]);
                }
            }
        }
        /* code */
    }
    return -1;
}

/**************************************************************** 
 * Function Name: getTargetState
 * Description: Get target state
 * Parameters: None
 * Return: 2:target approach   1:target leave  0:Not Found target
****************************************************************/
template <class T>
uint16_t GBT24LTR11<T>::getTargetState()
{
    uint16_t data[7] = {0};
    _serial->write(commandC1, 7);
    while (_serial->available() > 0)
    {
        if (_serial->read() == GBT24LTR11_MESSAGE_HEAD)
        {
            if (_serial->read() == GBT24LTR11_SEND_ADDRESS)
            {
                if (_serial->read() == GBT24LTR11_COMMAND_GET_TARGET)
                {
                    for (int i = 0; i < 7; i++)
                    {
                        data[i] = _serial->read();
                    }
                    //2 --> target approach
                    //1 --> target leave
                    //0 --> Not Found target
                    return data[4];
                }
            }
        }
        delay(20);
        /* code */
    }
    return 0;
}

/**************************************************************** 
 * Function Name: getIQADC
 * Description: Gets the I/Q information ADC value.
 * Parameters: I_d,Q_d,Store an array of I/Q information. len,The length of the array.
 * Return: 1:success  0:fail
****************************************************************/
template <class T>
uint8_t GBT24LTR11<T>::getIQADC(uint16_t I_d[], uint16_t Q_d[], uint16_t *len)
{
    while (_serial->available() > 0)
    {
        if (_serial->read() == GBT24LTR11_MESSAGE_HEAD)
        {
            if (_serial->read() == GBT24LTR11_SEND_ADDRESS)
            {
                if (_serial->read() == GBT24LTR11_COMMAND_GET_IQADC)
                {
                    uint16_t length_h, length_l, length;
                    length_h = _serial->read();
                    length_l = _serial->read();
                    length = length_h * 256 + length_l;
                    for (int i = 0; i < ((length - 2) / 2); i++)
                    {
                        I_d[i] = _serial->read();
                        Q_d[i] = _serial->read();
                    }
                    *len = (length - 2) / 2;
                    return 1;
                }
            }
        }
        /* code */
    }
    return 0;
}

/**************************************************************** 
 * Function Name: setSpeedScope
 * Description: Set the detection speed range.
 * Parameters: maxspeed,minspeed 0-65535
 * Return: 1:success  0:fail
****************************************************************/
template <class T>
uint8_t GBT24LTR11<T>::setSpeedScope(uint16_t maxspeed, uint16_t minspeed)
{
    uint16_t data[8] = {0};
    uint16_t len = 0;
    unsigned char commandC3[11] = {0x55, 0x2A, 0xC3, 0x00, 0x06, 0x02, 0x09, 0x01, 0x03, 0x01, 0x57};
    if ((maxspeed > 65535) || (minspeed < 0) || (maxspeed < minspeed))
    {
        return 0;
    }
    commandC3[5] = maxspeed / 256;
    commandC3[6] = maxspeed % 256;
    commandC3[7] = minspeed / 256;
    commandC3[8] = minspeed % 256;
    for (int i = 0; i < 9; i++)
    {
        len += commandC3[i];
    }
    commandC3[9] = len / 256;
    commandC3[10] = len % 256;
    _serial->write(commandC3, 11);
    while (_serial->available() > 0)
    {
        if (_serial->read() == GBT24LTR11_MESSAGE_HEAD)
        {
            if (_serial->read() == GBT24LTR11_SEND_ADDRESS)
            {
                if (_serial->read() == GBT24LTR11_COMMAND_SET_SPEED_SCOPE)
                {
                    for (int i = 0; i < 8; i++)
                    {
                        data[i] = _serial->read();
                    }
                    if (((data[2] * 256 + data[3]) == maxspeed) && ((data[4] * 256 + data[5]) == minspeed))
                    {
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
            }
        }
        /* code */
    }
    return 0;
}

/**************************************************************** 
 * Function Name: getSpeedScope
 * Description: Get the detection speed range.
 * Parameters: maxspeed,minspeed 
 * Return: 1:success  0:fail
****************************************************************/
template <class T>
uint8_t GBT24LTR11<T>::getSpeedScope(uint16_t *maxspeed, uint16_t *minspeed)
{
    unsigned char commandC4[7] = {0x55, 0x2A, 0xC4, 0x00, 0x02, 0x01, 0x45};
    uint16_t data[8] = {0};
    _serial->write(commandC4, 7);
    while (_serial->available() > 0)
    {
        if (_serial->read() == GBT24LTR11_MESSAGE_HEAD)
        {
            if (_serial->read() == GBT24LTR11_SEND_ADDRESS)
            {
                if (_serial->read() == GBT24LTR11_COMMAND_GET_SPEED_SCOPE)
                {
                    for (int i = 0; i < 8; i++)
                    {
                        data[i] = _serial->read();
                    }
                    *maxspeed = data[2] * 256 + data[3];
                    *minspeed = data[4] * 256 + data[5];
                    return 1;
                }
            }
        }
        /* code */
    }
    return 0;
}

/**************************************************************** 
 * Function Name: setMode
 * Description: Set module mode.
 * Parameters: 1:Gets the I/Q information ADC value mode. 0:To detect the target mode.
 * Return: 1:success  0:fail
****************************************************************/
template <class T>
uint8_t GBT24LTR11<T>::setMode(uint16_t mode)
{
    if (mode > 1 || mode < 0)
    {
        return 0;
    }
    unsigned char commandC5[8] = {0x55, 0x2A, 0xC5, 0x00, 0x03, 0x00, 0x01, 0x47};
    if (mode == 1)
    {
        commandC5[5] = 0x01;
        commandC5[7] = 0x48;
    }
    uint16_t data[5] = {0};
    _serial->write(commandC5, 8);
    while (_serial->available() > 0)
    {
        if (_serial->read() == GBT24LTR11_MESSAGE_HEAD)
        {
            if (_serial->read() == GBT24LTR11_SEND_ADDRESS)
            {
                if (_serial->read() == GBT24LTR11_COMMAND_SET_MODE)
                {
                    for (int i = 0; i < 5; i++)
                    {
                        data[i] = _serial->read();
                    }
                    if (data[2] == mode)
                    {
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
            }
        }
        /* code */
    }
    return 0;
}

/**************************************************************** 
 * Function Name: getMode
 * Description: Get module mode.
 * Parameters: none.
 * Return: 1:detect the target mode  2:Reported I/Q ADC  0:fail
****************************************************************/
template <class T>
uint8_t GBT24LTR11<T>::getMode()
{
    unsigned char commandC6[7] = {0x55, 0x2A, 0xC6, 0x00, 0x02, 0x01, 0x47};
    uint16_t data[5] = {0};
    _serial->write(commandC6, 7);
    while (_serial->available() > 0)
    {
        if (_serial->read() == GBT24LTR11_MESSAGE_HEAD)
        {
            if (_serial->read() == GBT24LTR11_SEND_ADDRESS)
            {
                if (_serial->read() == GBT24LTR11_COMMAND_GET_MODE)
                {
                    for (int i = 0; i < 5; i++)
                    {
                        data[i] = _serial->read();
                    }
                    //return 1 ---> detect the target mode
                    //return 2 ---> Reported I/Q ADC
                    //return 0 ---> fail
                    if (data[2] == 0)
                    {
                        return 1;
                    }
                    else if (data[2] == 1)
                    {
                        return 2;
                    }
                    else
                    {
                        return 0;
                    }
                }
            }
        }
        /* code */
    }
    return 0;
}

/**************************************************************** 
 * Function Name: setThreshold
 * Description: Set threshold.
 * Parameters: threshold.
 * Return: 1:success  0:fail
****************************************************************/
template <class T>
uint8_t GBT24LTR11<T>::setThreshold(uint16_t threshold)
{
    int len = 0;
    uint16_t data[8] = {0};
    unsigned char commandC7[11] = {0x55, 0x2A, 0xC7, 0x00, 0x06, 0x00, 0x00, 0x04, 0x00, 0x01, 0x50};
    commandC7[5] = threshold / 256 / 256 / 256 % 256;
    commandC7[6] = threshold / 256 / 256 % 256;
    commandC7[7] = threshold / 256 % 256;
    commandC7[8] = threshold % 256;
    for (int i = 0; i < 9; i++)
    {
        len += commandC7[i];
    }
    commandC7[9] = len / 256 % 256;
    commandC7[10] = len % 256;
    _serial->write(commandC7, 11);
    while (_serial->available() > 0)
    {
        if (_serial->read() == GBT24LTR11_MESSAGE_HEAD)
        {
            if (_serial->read() == GBT24LTR11_SEND_ADDRESS)
            {
                if (_serial->read() == GBT24LTR11_COMMAND_SET_THRESHOLD)
                {
                    for (int i = 0; i < 8; i++)
                    {
                        data[i] = _serial->read();
                    }
                    uint16_t thr = data[2] * 256 * 256 * 256 + data[3] * 256 * 256 + data[4] * 256 + data[5];
                    if (thr == threshold)
                    {
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
            }
        }
        /* code */
    }
    return 0;
}

/**************************************************************** 
 * Function Name: getThreshold
 * Description: Get threshold.
 * Parameters: None.
 * Return: 1:success  0:fail
****************************************************************/
template <class T>
uint16_t GBT24LTR11<T>::getThreshold()
{
    unsigned char commandC8[7] = {0x55, 0x2A, 0xC8, 0x00, 0x02, 0x01, 0x49};
    uint16_t data[8] = {0};
    _serial->write(commandC8, 7);
    while (_serial->available() > 0)
    {
        if (_serial->read() == GBT24LTR11_MESSAGE_HEAD)
        {
            if (_serial->read() == GBT24LTR11_SEND_ADDRESS)
            {
                if (_serial->read() == GBT24LTR11_COMMAND_GET_THRESHOLD)
                {
                    for (int i = 0; i < 8; i++)
                    {
                        data[i] = _serial->read();
                    }
                    uint16_t whr = 0;
                    whr = data[2] * 256 * 256 * 256 + data[3] * 256 * 256 + data[4] * 256 + data[5];
                    return whr;
                }
            }
        }
        /* code */
    }
    return 0;
}

#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
template class GBT24LTR11<Uart>;
#endif
template class GBT24LTR11<HardwareSerial>;

#ifdef __AVR__
#include <SoftwareSerial.h>
template class GBT24LTR11<SoftwareSerial>;
#endif
