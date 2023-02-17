# Seeed_Arduino_Grove_DopplerRadar  [![Build Status](https://travis-ci.com/Seeed-Studio/Seeed_Arduino_DopplerRadar.svg?branch=master)](https://travis-ci.com/Seeed-Studio/Seeed_Arduino_DopplerRadar)

This library is for the DopplerRadar Board.

This DopplerRadar Board can get the speed of the target and the state of the target's movement.

## Hardware requirements

- e.g. Arduino Zero or other Arduino related board like ESP8266/ESP32
- (optional) Grove Shield and a cable
- Grove DopplerRadar(BGT24LTR11)

### Connection of the hardware

Connect the DopplerRadar Board to the serial port of the board. In this example, we use hardware serial as the serial port; If you have other software Serial ports on you board, you can also connect to it. But software serial port may cause data loss.

## Usage

- Git clone this resp to your Arduino IDE'S libraries directory.

- Open the demo "BGT24LTR11_DETECTION_TARGET" from examples directory in Arduino IDE.

- Start a project.  

- You can choose to use the hardware or software serial port.
  ```c++
      #define COMSerial Serial
      #define ShowSerial SerialUSB
      BGT24LTR11<HardwareSerial> BGT;
  ```

- Set the communication baud rate of the DopplerRadar module (115200).

- Then initialize BGT in the setup function.

- Set the working mode.
  ```c++
  void setup()
  {
    // put your setup code here, to run once:
    ShowSerial.begin(9600);
    COMSerial.begin(115200);
    BGT.init(COMSerial);
    while (!ShowSerial)
      ;
    while (!COMSerial)
      ;
    /*
     * MODE 0 -->detection target mode
     * MODE 1 -->I/Q ADC mode
     */
    while (!BGT.setMode(0))
      ;
  }

  ```
- Gets the speed value and target state.
  ```c++
  void loop()
  {
    // put your main code here, to run repeatedly:
    uint16_t state=0;
    ShowSerial.print("target speed:");
    ShowSerial.println(BGT.getSpeed());
    state = BGT.getTargetState();
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

  ```

## Methods
See [BGT24LTR11.h](./src/BGT24LTR11.h) for detailed descriptions.

* uint8_t getInfo(uint16_t* target_tate, uint16_t* speed);
* uint16_t getSpeed();
* uint16_t getTargetState();
* uint8_t getIQADC(uint16_t I_d[], uint16_t Q_d[], uint16_t* len);
* uint8_t setSpeedScope(uint16_t maxspeed, uint16_t minspeed);
* uint8_t getSpeedScope(uint16_t* maxspeed, uint16_t* minspeed);
* uint8_t setMode(uint16_t mode);
* uint8_t getMode();
* uint8_t setThreshold(uint16_t threshold);
* uint16_t getThreshold();
* uint16_t calculateChecksum(uint16_t *data, uint16_t data_length);
* uint16_t messageChecksum(uint16_t high_order, uint16_t low_order);

## License

See [LICENSE](./LICENSE).
