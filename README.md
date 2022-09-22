
# Arduino additional display based on CAN and OBD2 

The display is showing the most popular parameters in cars. With this display you reduce the chances of your engine failing.


## Features

can values:

- Coolant Temperature
- Vehicle Speed
- Intake Air Temperature
- Maf Air Flow Ratio
- Throttle Position
- Fuel Tank Level
- Exhaust Gas Temperature
- Voltage
- Air Flow Ratio
- Fuel consumption
- Short Term Fuel
- Timing Advanced
- Oxygen Sensor Fuel Ratio

others:
- Oil Temperature
- Oil Pressure


## FAQ

#### Will the project continue?

If I can find the time and willingness to develop the project.

#### What can I expect in the next updates?

Everything is described in the roadmap tab.

#### Which cars is this display suitable for?

For all that have CAN buses.




## Authors

- [@Radivv](https://github.com/Radivv)


## Roadmap

- Fuel consumption in gallons

- More options

- Optimalization

## Pinout

| Arduino             | MCP2515Microchip MCP2515                                                                |
| ----------------- | ------------------------------------------------------------------ |
|VCC|5V|
|GND|GND|
|SCK|SCK|
|SO	|MISO|
|SI	|MOSI|
|CS	|10|
|INT|2|

``CS`` and ``INT`` pins can be changed by using ``CAN.setPins(cs, irq)``. ``INT`` pin is optional, it is only needed for receive callback mode. If ``INT`` pin is used, it must be interrupt capable via ``attachInterrupt(...)``.

NOTE: Logic level converters must be used for boards which operate at 3.3V.


| Arduino             | Oled 1.5 RGB WaveShark                                                               |
| ----------------- | ------------------------------------------------------------------ |
|VCC|5V|
|GND|GND|
|SCK|13|
|MOSI|11|
|CS	|6|
|RST|8|
|DC|7|

NOTE: Any combination of poor quality can cause a problem with the refreshing of the image on the display.


## Acknowledgements

 - [Arduino](https://www.arduino.cc/)
 - [sandeepmistry](https://github.com/sandeepmistry/arduino-OBD2)
 - [Adafruit](https://www.adafruit.com/)

## Screenshots

![App Screenshot](https://i.imgur.com/dx6H3Ve.jpg)
![App Screenshot](https://i.imgur.com/XybtggI.jpg)

