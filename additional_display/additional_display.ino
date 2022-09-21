#include <CAN.h> // the OBD2 library depends on the CAN library
#include <OBD2.h>
#include <SPI.h>
//#include <Arduino.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#define SerialDebugging true
// Screen dimensions
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 128 // Change this to 96 for 1.27" OLED.

/**
 * Made with Marlin Bitmap Converter
 * https://marlinfw.org/tools/u8glib/converter.html
 *
 * This bitmap from the file 'exportmazda.bmp'
 */

//// CONFIGURATION
//// 320€
//String config_Display[9] = {"nothing", "mafAirFlowRatio", "consumption", "throttlePosition","shortTermFuel","fuelTankLevel","timingAdvanced","oxygenSensorFuelRatio","intakeAirTemperature"};
//// 350€
//String config_Display[9] = {"nothing", "engineCoolantTemperature", "oilTemperature", "oilPressure","voltage","consumption","fuelTankLevel","egt ","afr"};
//// 500€
String config_Display[9] = {"nothing", "engineCoolantTemperature", "afr", "egt","voltage","oilTemperature","oilPressure","timingAdvanced","oxygenSensorFuelRatio"};

float temp_oil_a = 0;
int temp_oil_b = 0;
int fuelPack = 0;
byte fuelSize = 0;
int engineCoolantTemperature = 0;
int vehicleSpeed = 0;
int intakeAirTemperature = 0;
float  mafAirFlowRatio = 0; // nie wiem jak to rozumiec
byte throttlePosition = 0;
byte fuelTankLevel = 0;
int egt = 0;
float voltage = 0;
int oilTemperature = 0;
float oilPressure = 0;
float afr = 0;
float consumption = 0;
float shortTermFuel = 0;
float timingAdvanced = 0;
float oxygenSensorFuelRatio = 0;
byte waterTemperatureWarning = 100; // celcjusze
byte airTempWarning = 50;
byte oilTemperatureWarning = 110; // celcjusze
byte oilPressureWarning = 11; // psi
byte fuelTankLevelWarning = 10; // %
byte voltageWarning = 12; // volty
bool celciush = true;
bool metric = true;
bool liter = true;
bool bars = true;
bool fuelTankLevelPercentage = false;
int analogPin = 2;
int raw = 0;
int Vin = 5;
float Vout = 0;
float R1 = 218;
float R2 = 0;
float buffer = 0;
int analogPin_1 = 0;
int raw_1 = 0;
//int Vin_1 = 5;
float Vout_1 = 0;
float R1_1 = 218;
float R2_1 = 0;
float buffer_1 = 0;

 
#pragma once

#define K2J077_BMPWIDTH  84

const unsigned char bitmap_k2j077[] PROGMEM = {
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00000000,B00000000,B11111111,B11111111,B11100000,B00000000,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00000000,B00001111,B11111111,B11111111,B11111110,B00000000,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00000000,B00111111,B11111111,B11111111,B11111111,B11000000,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00000000,B11111111,B11111000,B00000011,B11111111,B11110000,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00000011,B11111111,B00000000,B00000000,B00001111,B11111100,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00000111,B11111100,B00000000,B00000000,B00000011,B11111110,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00001111,B11110000,B00000000,B00000000,B00000000,B11111111,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00011111,B11100000,B00000000,B00000000,B00000000,B01111111,B10000000,B00000000,B00001111,
  B00000000,B00000000,B00111111,B10000000,B00000000,B00000000,B00000000,B00111111,B10000000,B00000000,B00001111,
  B00000000,B00000000,B00111111,B10000000,B00000000,B00000000,B00000000,B00111111,B11000000,B00000000,B00001111,
  B00000000,B00000000,B01111111,B11110000,B00000000,B00000000,B00000011,B11111111,B11000000,B00000000,B00001111,
  B00000000,B00000000,B01111111,B11111110,B00000000,B00000000,B00001111,B11111111,B11100000,B00000000,B00001111,
  B00000000,B00000000,B01111111,B11111111,B11000000,B00000000,B01111111,B11111111,B11100000,B00000000,B00001111,
  B00000000,B00000000,B01111111,B11111111,B11110000,B00000001,B11111111,B11111111,B11100000,B00000000,B00001111,
  B00000000,B00000000,B11111111,B11111111,B11111000,B00000011,B11111111,B11100111,B11100000,B00000000,B00001111,
  B00000000,B00000000,B11111110,B00111111,B11111110,B00000111,B11111111,B00000111,B11110000,B00000000,B00001111,
  B00000000,B00000000,B11111110,B00000111,B11111111,B00001111,B11111000,B00000111,B11110000,B00000000,B00001111,
  B00000000,B00000000,B11111110,B00000000,B01111111,B10011111,B11000000,B00000111,B11110000,B00000000,B00001111,
  B00000000,B00000000,B11111110,B00000000,B00011111,B10111111,B00000000,B00000111,B11110000,B00000000,B00001111,
  B00000000,B00000000,B11111110,B00000000,B00000111,B11111110,B00000000,B00000111,B11110000,B00000000,B00001111,
  B00000000,B00000000,B11111110,B00000000,B00000011,B11111000,B00000000,B00000111,B11100000,B00000000,B00001111,
  B00000000,B00000000,B01111110,B00000000,B00000001,B11110000,B00000000,B00000111,B11100000,B00000000,B00001111,
  B00000000,B00000000,B01111110,B00000000,B00000000,B11110000,B00000000,B00000111,B11100000,B00000000,B00001111,
  B00000000,B00000000,B01111111,B00000000,B00000000,B01100000,B00000000,B00001111,B11100000,B00000000,B00001111,
  B00000000,B00000000,B01111111,B00000000,B00000000,B01000000,B00000000,B00001111,B11000000,B00000000,B00001111,
  B00000000,B00000000,B00111111,B10000000,B00000000,B00000000,B00000000,B00011111,B11000000,B00000000,B00001111,
  B00000000,B00000000,B00111111,B10000000,B00000000,B00000000,B00000000,B00111111,B10000000,B00000000,B00001111,
  B00000000,B00000000,B00011111,B11000000,B00000000,B00000000,B00000000,B00111111,B10000000,B00000000,B00001111,
  B00000000,B00000000,B00001111,B11110000,B00000000,B00000000,B00000000,B11111111,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00000111,B11111000,B00000000,B00000000,B00000001,B11111110,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00000011,B11111111,B00000000,B00000000,B00001111,B11111100,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00000001,B11111111,B11110000,B00000001,B11111111,B11110000,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00000000,B01111111,B11111111,B11111111,B11111111,B11100000,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00000000,B00001111,B11111111,B11111111,B11111111,B00000000,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00000000,B00000000,B11111111,B11111111,B11110000,B00000000,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001111,
  B11111111,B11111111,B11100001,B11111111,B11100111,B11111111,B00111111,B11111111,B11000011,B11111111,B11001111,
  B11111111,B11111111,B11111011,B11111111,B11110111,B11111110,B11111111,B11111111,B11100111,B11111111,B11101111,
  B11111111,B11111111,B11111011,B11111111,B11111111,B11111101,B11111111,B11111111,B11110111,B11111111,B11111111,
  B11111111,B11111111,B11111101,B11111111,B11111111,B11110111,B11111111,B11111111,B11110011,B11111011,B11111111,
  B11111000,B01111100,B11111100,B00000000,B11111000,B00001111,B11110111,B11000001,B11111000,B00000001,B11111111,
  B11111000,B01111000,B01111111,B11111111,B11111000,B00111111,B11000111,B11000000,B11111111,B11111111,B11111111,
  B11111000,B11111000,B01111111,B11111111,B11111000,B01111111,B10000111,B11000000,B11111111,B11111111,B11111111,
  B11111000,B11111000,B01111111,B11111111,B11111001,B11111110,B00000111,B11000000,B11111111,B11111111,B11111111,
  B11111000,B11111000,B01111111,B11000000,B11111011,B11111000,B00000111,B10000001,B11111111,B10000001,B11111111,
  B11111000,B11111000,B01111111,B11111111,B11111111,B11110111,B11110111,B11111111,B11111111,B11111111,B11111111,
  B11111000,B11111000,B01111111,B11111111,B11111111,B11101111,B11110111,B11111111,B11111111,B11111111,B11111111,
  B11111000,B11111000,B01111111,B11111111,B11111111,B10011111,B11110111,B11111111,B11100111,B11111111,B11111111,
  B11111000,B11111100,B01111101,B11111111,B11111111,B01111111,B11110111,B11111111,B11000011,B11111111,B11111111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001111
};

// The SSD1351 is connected like this (plus VCC plus GND)
const uint8_t   OLED_pin_scl_sck        = 13;
const uint8_t   OLED_pin_sda_mosi       = 11;
const uint8_t   OLED_pin_cs_ss          = 6; // changed
const uint8_t   OLED_pin_res_rst        = 8;
const uint8_t   OLED_pin_dc_rs          = 7;

// SSD1331 color definitions
const uint16_t  OLED_Color_Black        = 0x0000;
//const uint16_t  OLED_Color_Blue         = 0x001F;
const uint16_t  OLED_Color_Red          = 0xF800;
//const uint16_t  OLED_Color_Green        = 0x07E0;
//const uint16_t  OLED_Color_Cyan         = 0x07FF;
//const uint16_t  OLED_Color_Magenta      = 0xF81F;
//const uint16_t  OLED_Color_Yellow       = 0xFFE0;
const uint16_t  OLED_Color_White        = 0xFFFF;

// The colors we actually want to use
uint16_t        OLED_Text_Color         = OLED_Color_White;
uint16_t        OLED_Backround_Color    = OLED_Color_Black;


// Created by http://oleddisplay.squix.ch/ Consider a donation
// In case of problems make sure that you are using the font file with the correct version!
const uint8_t Roboto_Mono_Light_16Bitmaps[] PROGMEM = {

  // Bitmap Data:
  0x00, // ' '
  0xAA,0xAA,0x02, // '!'
  0xAA,0xAA, // '"'
  0x09,0x02,0x41,0x11,0xFE,0x12,0x04,0x81,0x20,0x48,0xFF,0x89,0x02,0x40,0x90, // '#'
  0x08,0x08,0x3C,0x42,0x42,0x42,0x40,0x30,0x0C,0x02,0x82,0x82,0x42,0x3C,0x08, // '$'
  0x70,0x24,0x89,0x22,0x48,0x74,0x01,0x00,0xB0,0x52,0x14,0x89,0x20,0x48,0x0C, // '%'
  0x38,0x22,0x11,0x08,0x84,0x81,0x81,0xC0,0x92,0x8D,0x43,0x31,0x8F,0x20, // '&'
  0xAA, // '''
  0x11,0x10,0x84,0x42,0x10,0x84,0x21,0x04,0x21,0x04,0x10, // '('
  0x88,0x42,0x22,0x22,0x22,0x22,0x24,0x48,0x80, // ')'
  0x08,0x04,0x32,0xC7,0x81,0x81,0x21,0x98, // '*'
  0x10,0x08,0x04,0x02,0x0F,0xF0,0x80,0x40,0x20,0x10,0x00, // '+'
  0x4A,0x40, // ','
  0xFC, // '-'
  0xD8, // '.'
  0x04,0x10,0x20,0x41,0x02,0x08,0x10,0x20,0x81,0x02,0x08,0x00, // '/'
  0x3C,0x46,0x42,0x82,0x86,0x8A,0x92,0xA2,0xC2,0x42,0x42,0x3C, // '0'
  0x17,0xA4,0x21,0x08,0x42,0x10,0x84,0x20, // '1'
  0x78,0xC4,0x82,0x82,0x04,0x04,0x08,0x10,0x20,0x20,0x40,0xFE, // '2'
  0x78,0x84,0x82,0x02,0x04,0x38,0x04,0x02,0x82,0x82,0xC4,0x78, // '3'
  0x04,0x06,0x05,0x02,0x82,0x42,0x21,0x11,0x08,0xFF,0x02,0x01,0x00,0x80, // '4'
  0x7C,0x80,0x80,0x80,0xF8,0x84,0x04,0x02,0x02,0x84,0x84,0x78, // '5'
  0x1C,0x20,0x40,0x40,0xBC,0xC6,0x82,0x82,0x82,0x82,0x46,0x3C, // '6'
  0xFE,0x02,0x02,0x04,0x04,0x08,0x08,0x08,0x10,0x10,0x20,0x20, // '7'
  0x3C,0x21,0x10,0x88,0x44,0x21,0xE1,0x08,0x84,0x81,0x40,0x90,0x87,0x80, // '8'
  0x38,0x44,0x82,0x82,0x82,0x82,0x46,0x3A,0x02,0x04,0x0C,0x30, // '9'
  0xD8,0x00,0x06,0xC0, // ':'
  0xD8,0x00,0x02,0x52,0x00, // ';'
  0x06,0x38,0xC0,0x60,0x18,0x06, // '<'
  0xFE,0x00,0x00,0xFE, // '='
  0xE0,0x18,0x06,0x0E,0x30,0xC0, // '>'
  0x79,0x0A,0x10,0x20,0x41,0x04,0x10,0x20,0x00,0x01,0x00, // '?'
  0x1E,0x08,0x44,0xC9,0x4A,0x52,0xA4,0xA9,0x2A,0x4A,0x54,0x96,0xC6,0x00,0x78, // '@'
  0x10,0x0C,0x06,0x05,0x02,0x41,0x21,0x10,0x84,0x7E,0x21,0x20,0x50,0x20, // 'A'
  0xF8,0x84,0x84,0x84,0x84,0xF8,0x84,0x82,0x82,0x82,0x84,0xF8, // 'B'
  0x3C,0x21,0x20,0x90,0x28,0x04,0x02,0x01,0x00,0x81,0x41,0x10,0x87,0x80, // 'C'
  0xF8,0x42,0x20,0x90,0x28,0x14,0x0A,0x05,0x02,0x81,0x41,0x21,0x1F,0x00, // 'D'
  0xFD,0x02,0x04,0x08,0x1F,0xA0,0x40,0x81,0x02,0x07,0xE0, // 'E'
  0xFD,0x02,0x04,0x08,0x10,0x3F,0x40,0x81,0x02,0x04,0x00, // 'F'
  0x3C,0x21,0x20,0x90,0x28,0x04,0x02,0x3D,0x02,0x81,0x40,0x90,0xC7,0x80, // 'G'
  0x82,0x82,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x82,0x82,0x82, // 'H'
  0xFC,0x40,0x81,0x02,0x04,0x08,0x10,0x20,0x40,0x87,0xE0, // 'I'
  0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x82,0x82,0xC4,0x38, // 'J'
  0x86,0x84,0x88,0x90,0xA0,0xE0,0xE0,0x90,0x88,0x88,0x84,0x82, // 'K'
  0x81,0x02,0x04,0x08,0x10,0x20,0x40,0x81,0x02,0x07,0xE0, // 'L'
  0xC2,0xC2,0xC6,0xA6,0xA6,0xAA,0x9A,0x92,0x82,0x82,0x82,0x82, // 'M'
  0x82,0xC2,0xC2,0xA2,0x92,0x92,0x8A,0x8A,0x86,0x86,0x82,0x82, // 'N'
  0x3C,0x23,0x20,0x90,0x48,0x14,0x0A,0x05,0x02,0x82,0x41,0x11,0x87,0x80, // 'O'
  0xF8,0x84,0x82,0x82,0x82,0x84,0xF8,0x80,0x80,0x80,0x80,0x80, // 'P'
  0x3C,0x21,0x20,0x90,0x28,0x14,0x0A,0x05,0x02,0x81,0x41,0x10,0x87,0x80,0x20,0x08, // 'Q'
  0xF8,0x84,0x84,0x84,0x84,0x84,0xF8,0x88,0x88,0x84,0x84,0x82, // 'R'
  0x3C,0x21,0x20,0xD0,0x04,0x01,0x80,0x30,0x04,0x01,0x40,0x90,0x87,0x80, // 'S'
  0xFF,0x08,0x04,0x02,0x01,0x00,0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x00, // 'T'
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x42,0x3C, // 'U'
  0x81,0x41,0x20,0x88,0x44,0x42,0x20,0x90,0x48,0x28,0x0C,0x06,0x02,0x00, // 'V'
  0x91,0x4C,0xA6,0x53,0x29,0x95,0x4A,0x98,0xCC,0x66,0x33,0x11,0x88,0x40, // 'W'
  0x81,0x21,0x19,0x04,0x81,0x80,0xC0,0x60,0x70,0x24,0x23,0x10,0x90,0x20, // 'X'
  0x83,0x41,0x10,0x88,0x82,0x41,0x40,0x60,0x20,0x10,0x08,0x04,0x02,0x00, // 'Y'
  0xFE,0x02,0x04,0x08,0x08,0x10,0x10,0x20,0x20,0x40,0x80,0xFE, // 'Z'
  0xD2,0x49,0x24,0x92,0x49,0x26, // '['
  0x81,0x01,0x02,0x02,0x04,0x08,0x08,0x10,0x20,0x20,0x40,0x40, // '\'
  0xE2,0x22,0x22,0x22,0x22,0x22,0x22,0x2E, // ']'
  0x20,0x61,0x42,0x44,0x91,0x80, // '^'
  0xFE, // '_'
  0x88, // '`'
  0x3C,0x42,0x42,0x02,0x3E,0x42,0x82,0xC6,0x7A, // 'a'
  0x81,0x02,0x07,0xC8,0x50,0xA1,0x42,0x85,0x0A,0x17,0xC0, // 'b'
  0x3C,0x42,0x42,0x80,0x80,0x80,0x42,0x42,0x3C, // 'c'
  0x02,0x02,0x02,0x3A,0x46,0x42,0x82,0x82,0x82,0x42,0x46,0x3A, // 'd'
  0x3C,0x42,0x42,0x82,0xFE,0x80,0x80,0x42,0x3C, // 'e'
  0x0F,0x08,0x04,0x02,0x0F,0xE0,0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,0x00, // 'f'
  0x3A,0x46,0x42,0x82,0x82,0x82,0x42,0x46,0x3A,0x02,0x46,0x3C, // 'g'
  0x81,0x02,0x07,0xC8,0x50,0xA1,0x42,0x85,0x0A,0x14,0x20, // 'h'
  0x30,0x00,0x00,0xF0,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0xFE, // 'i'
  0x18,0x00,0x3C,0x10,0x41,0x04,0x10,0x41,0x04,0x10,0x4E,0x00, // 'j'
  0x80,0x80,0x80,0x84,0x88,0x90,0xA0,0xE0,0x90,0x98,0x88,0x86, // 'k'
  0xF0,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0xFE, // 'l'
  0xF6,0x4C,0xA4,0x52,0x29,0x14,0x8A,0x45,0x22,0x91,0x00, // 'm'
  0xF9,0x0A,0x14,0x28,0x50,0xA1,0x42,0x84, // 'n'
  0x3C,0x21,0x20,0x90,0x28,0x14,0x0A,0x08,0x84,0x3C,0x00, // 'o'
  0xF9,0x1A,0x14,0x28,0x50,0xA1,0x46,0xF9,0x02,0x04,0x00, // 'p'
  0x3A,0x46,0x42,0x82,0x82,0x82,0x42,0x46,0x3A,0x02,0x02,0x02, // 'q'
  0xBB,0x08,0x20,0x82,0x08,0x20,0x80, // 'r'
  0x3C,0x42,0x42,0x60,0x1C,0x02,0x82,0x42,0x3C, // 's'
  0x10,0x10,0xFE,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x0E, // 't'
  0x85,0x0A,0x14,0x28,0x50,0xA1,0x46,0x74, // 'u'
  0x81,0x41,0x10,0x88,0x82,0x41,0x20,0xA0,0x30,0x10,0x00, // 'v'
  0xC8,0x93,0x24,0xC9,0x32,0x55,0x0C,0xC3,0x30,0x8C,0x22,0x00, // 'w'
  0xC3,0x23,0x09,0x03,0x01,0x00,0xC0,0x90,0x84,0xC3,0x00, // 'x'
  0x81,0x41,0x10,0x88,0x82,0x41,0x20,0x60,0x30,0x10,0x08,0x08,0x18,0x00, // 'y'
  0xFE,0x03,0x01,0x01,0x01,0x01,0x00,0x80,0x80,0xFF,0x00, // 'z'
  0x08,0x42,0x08,0x20,0x82,0x10,0x81,0x02,0x08,0x20,0x82,0x04,0x08, // '{'
  0xAA,0xAA,0xAA,0xA0, // '|'
  0x81,0x04,0x08,0x20,0x82,0x08,0x18,0x82,0x08,0x20,0x84,0x10,0x80 // '}'
};
const GFXglyph Roboto_Mono_Light_16Glyphs[] PROGMEM = {
// bitmapOffset, width, height, xAdvance, xOffset, yOffset
    {     0,   1,   1,  11,    0,    0 }, // ' '
    {     1,   2,  12,  11,    4,  -12 }, // '!'
    {     4,   4,   4,  11,    3,  -12 }, // '"'
    {     6,  10,  12,  11,    0,  -12 }, // '#'
    {    21,   8,  15,  11,    1,  -14 }, // '$'
    {    36,  10,  12,  11,    0,  -12 }, // '%'
    {    51,   9,  12,  11,    1,  -12 }, // '&'
    {    65,   2,   4,  11,    4,  -12 }, // '''
    {    66,   5,  17,  11,    3,  -13 }, // '('
    {    77,   4,  17,  11,    3,  -13 }, // ')'
    {    86,   9,   7,  11,    1,  -11 }, // '*'
    {    94,   9,   9,  11,    1,  -10 }, // '+'
    {   105,   3,   4,  11,    3,   -2 }, // ','
    {   107,   7,   1,  11,    2,   -6 }, // '-'
    {   108,   3,   2,  11,    4,   -2 }, // '.'
    {   109,   7,  13,  11,    2,  -12 }, // '/'
    {   121,   8,  12,  11,    1,  -12 }, // '0'
    {   133,   5,  12,  11,    2,  -12 }, // '1'
    {   141,   8,  12,  11,    1,  -12 }, // '2'
    {   153,   8,  12,  11,    1,  -12 }, // '3'
    {   165,   9,  12,  11,    1,  -12 }, // '4'
    {   179,   8,  12,  11,    2,  -12 }, // '5'
    {   191,   8,  12,  11,    1,  -12 }, // '6'
    {   203,   8,  12,  11,    1,  -12 }, // '7'
    {   215,   9,  12,  11,    1,  -12 }, // '8'
    {   229,   8,  12,  11,    1,  -12 }, // '9'
    {   241,   3,   9,  11,    4,   -9 }, // ':'
    {   245,   3,  11,  11,    4,   -9 }, // ';'
    {   250,   8,   6,  11,    1,   -8 }, // '<'
    {   256,   8,   4,  11,    1,   -7 }, // '='
    {   260,   8,   6,  11,    1,   -8 }, // '>'
    {   266,   7,  12,  11,    2,  -12 }, // '?'
    {   277,  10,  12,  11,    0,  -12 }, // '@'
    {   292,   9,  12,  11,    1,  -12 }, // 'A'
    {   306,   8,  12,  11,    2,  -12 }, // 'B'
    {   318,   9,  12,  11,    1,  -12 }, // 'C'
    {   332,   9,  12,  11,    1,  -12 }, // 'D'
    {   346,   7,  12,  11,    2,  -12 }, // 'E'
    {   357,   7,  12,  11,    2,  -12 }, // 'F'
    {   368,   9,  12,  11,    1,  -12 }, // 'G'
    {   382,   8,  12,  11,    1,  -12 }, // 'H'
    {   394,   7,  12,  11,    2,  -12 }, // 'I'
    {   405,   8,  12,  11,    1,  -12 }, // 'J'
    {   417,   8,  12,  11,    2,  -12 }, // 'K'
    {   429,   7,  12,  11,    2,  -12 }, // 'L'
    {   440,   8,  12,  11,    1,  -12 }, // 'M'
    {   452,   8,  12,  11,    1,  -12 }, // 'N'
    {   464,   9,  12,  11,    1,  -12 }, // 'O'
    {   478,   8,  12,  11,    2,  -12 }, // 'P'
    {   490,   9,  14,  11,    1,  -12 }, // 'Q'
    {   506,   8,  12,  11,    2,  -12 }, // 'R'
    {   518,   9,  12,  11,    1,  -12 }, // 'S'
    {   532,   9,  12,  11,    1,  -12 }, // 'T'
    {   546,   8,  12,  11,    1,  -12 }, // 'U'
    {   558,   9,  12,  11,    1,  -12 }, // 'V'
    {   572,   9,  12,  11,    1,  -12 }, // 'W'
    {   586,   9,  12,  11,    1,  -12 }, // 'X'
    {   600,   9,  12,  11,    1,  -12 }, // 'Y'
    {   614,   8,  12,  11,    1,  -12 }, // 'Z'
    {   626,   3,  16,  11,    4,  -13 }, // '['
    {   632,   7,  13,  11,    2,  -12 }, // '\'
    {   644,   4,  16,  11,    3,  -13 }, // ']'
    {   652,   7,   6,  11,    2,  -12 }, // '^'
    {   658,   8,   1,  11,    1,    0 }, // '_'
    {   659,   3,   2,  11,    4,  -12 }, // '`'
    {   660,   8,   9,  11,    1,   -9 }, // 'a'
    {   669,   7,  12,  11,    2,  -12 }, // 'b'
    {   680,   8,   9,  11,    1,   -9 }, // 'c'
    {   689,   8,  12,  11,    1,  -12 }, // 'd'
    {   701,   8,   9,  11,    1,   -9 }, // 'e'
    {   710,   9,  13,  11,    1,  -13 }, // 'f'
    {   725,   8,  12,  11,    1,   -9 }, // 'g'
    {   737,   7,  12,  11,    2,  -12 }, // 'h'
    {   748,   8,  12,  11,    2,  -12 }, // 'i'
    {   760,   6,  15,  11,    2,  -12 }, // 'j'
    {   772,   8,  12,  11,    2,  -12 }, // 'k'
    {   784,   8,  12,  11,    2,  -12 }, // 'l'
    {   796,   9,   9,  11,    1,   -9 }, // 'm'
    {   807,   7,   9,  11,    2,   -9 }, // 'n'
    {   815,   9,   9,  11,    1,   -9 }, // 'o'
    {   826,   7,  12,  11,    2,   -9 }, // 'p'
    {   837,   8,  12,  11,    1,   -9 }, // 'q'
    {   849,   6,   9,  11,    3,   -9 }, // 'r'
    {   856,   8,   9,  11,    1,   -9 }, // 's'
    {   865,   8,  11,  11,    1,  -11 }, // 't'
    {   876,   7,   9,  11,    2,   -9 }, // 'u'
    {   884,   9,   9,  11,    1,   -9 }, // 'v'
    {   895,  10,   9,  11,    0,   -9 }, // 'w'
    {   907,   9,   9,  11,    1,   -9 }, // 'x'
    {   918,   9,  12,  11,    1,   -9 }, // 'y'
    {   932,   9,   9,  11,    1,   -9 }, // 'z'
    {   943,   6,  17,  11,    3,  -13 }, // '{'
    {   956,   2,  14,  11,    4,  -12 }, // '|'
    {   960,   6,  17,  11,    3,  -13 } // '}'
};
const GFXfont Roboto_Mono_Light_16 PROGMEM = {
(uint8_t  *)Roboto_Mono_Light_16Bitmaps,(GFXglyph *)Roboto_Mono_Light_16Glyphs,0x20, 0x7E, 19};

// declare the display
Adafruit_SSD1351 oled =
    Adafruit_SSD1351(
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        &SPI,
        OLED_pin_cs_ss,
        OLED_pin_dc_rs,
        OLED_pin_res_rst
     );



float drawConsumption()
{
  return afr * mafAirFlowRatio * 60 / 1000;
}


void drawPercentage(uint16_t x, uint16_t y, uint16_t color)
{
    oled.setFont(&Roboto_Mono_Light_16);
    oled.setCursor(x, y);
    oled.print("%");
}

void drawVolume(uint16_t x, uint16_t y, uint16_t color)
{
    oled.setFont(&Roboto_Mono_Light_16);
    oled.setCursor(x, y);
    if (liter == true)
    {
          oled.print("l");
    }
    else
    {
          oled.print("G");
    }
}

void drawPressure(uint16_t x, uint16_t y, uint16_t color)
{
    oled.setFont(&Roboto_Mono_Light_16);
    oled.setCursor(x, y);
    if (bars == true)
    {
      oled.print("b");
    }else
    {
      oled.print("p");
    }
}

void drawSpeed(uint16_t x, uint16_t y, uint16_t color)
{
    oled.setFont();
    oled.setCursor(x, y);
    if (metric == true)
    {
      oled.print("kmh");
    }else
    {
      oled.print("mil");
    }
}

void drawDegree(uint16_t x, uint16_t y, uint16_t color, bool ask = true)
{
  oled.setFont(&Roboto_Mono_Light_16);
  oled.drawPixel(x, y - 11, color);
  oled.drawPixel(x, y - 10, color);
  oled.drawPixel(x, y - 9, color);
  
  oled.drawPixel(x + 1, y - 12, color);
  oled.drawPixel(x + 2, y - 12, color);
  oled.drawPixel(x + 3, y - 12, color);

  oled.drawPixel(x + 1, y - 8, color);
  oled.drawPixel(x + 2, y - 8, color);
  oled.drawPixel(x + 3, y - 8, color);

  oled.drawPixel(x + 4, y - 11, color);
  oled.drawPixel(x + 4, y - 10, color);
  oled.drawPixel(x + 4, y - 9, color);
  
  oled.setCursor(x + 6, y);
  if (ask == true)
  {
      if (celciush == true)
      {
          oled.print("C");
      }
      else
      {
          oled.print("F");
      }
  }

}


void printText(int font_size, bool custom_font, String text, int16_t x0, int16_t y0, uint16_t Color, byte decimal_value = 0, float value = 0)
{
  if (custom_font == true)
  {
    oled.setFont(&Roboto_Mono_Light_16);
  }
  else
  {
    oled.setFont();
  }
  oled.setTextSize(font_size);
  oled.setCursor(x0, y0);
  oled.setTextColor(Color);
  if (value == 0)
  {
    if (decimal_value == 0)
    {
        oled.print(text);
    }
    else
    {
        oled.print(value, decimal_value);
    }
  }
  else
  {
    oled.print(value, decimal_value);
  }

  oled.setTextColor(OLED_Text_Color);
}

void setup() {
    Serial.begin(9600);
    oled.begin();
    oled.setRotation(0); // 0 to na liczniki  | 2 na LHD
    oled.fillScreen(OLED_Backround_Color);
    oled.setTextColor(OLED_Text_Color);
    oled.setFont(&Roboto_Mono_Light_16);
    oled.drawBitmap(22, 25, bitmap_k2j077, 84, 63, OLED_Color_White);
    

  while (true) {

    if (!OBD2.begin()) {
      //Serial.println(F("failed!"));

      delay(200);
    } else {
      //Serial.println(F("success"));
      break;
    }
  }

    oled.fillScreen(OLED_Backround_Color);

    delay(500);
    setupMain();

}

void setupMain()
{
  oled.fillScreen(OLED_Backround_Color);
  
  oled.drawLine(64, 0, 64, 128, OLED_Color_White);
  
  oled.drawLine(0, 32, 128, 32, OLED_Color_White);
  
  oled.drawLine(0, 64, 128, 64, OLED_Color_White);
  
  oled.drawLine(0, 96, 128, 96, OLED_Color_White);


  for (byte display_values = 1; display_values <= 8; display_values++)
  {
    byte pos_x;
    byte pos_y;
    if (display_values == 1 || display_values == 2)
    {
      pos_y = 22;
    }
    if (display_values == 3 || display_values == 4)
    {
      pos_y = 54;
    }
    if (display_values == 5 || display_values == 6)
    {
      pos_y = 86;
    }
    if (display_values == 7 || display_values == 8)
    {
      pos_y = 118;
    }
    if (config_Display[display_values] == "engineCoolantTemperature")
    {
      if ((display_values % 2) == 0)
      {
        pos_x = 68;
      }else
      {
        pos_x = 4;
      }
    printText(0, false, "WATER TEMP", pos_x, pos_y, OLED_Color_White);
    drawDegree((pos_x + 42), (pos_y - 6), OLED_Color_White);
    }
    if (config_Display[display_values] == "vehicleSpeed")
    {
      if ((display_values % 2) == 0)
      {
        pos_x = 76;
      }else
      {
        pos_x = 12;
      } 
    printText(0, false, "SPEED", pos_x, pos_y, OLED_Color_White);
    drawSpeed((pos_x + 28), (pos_y - 14), OLED_Color_White);
    }
    if (config_Display[display_values] == "intakeAirTemperature")
    {
      if ((display_values % 2) == 0)
      {
        pos_x = 72;
      }else
      {
        pos_x = 8;
      }
    drawDegree((pos_x + 38), (pos_y - 6), OLED_Color_White);
    printText(0, false, "AIR TEMP", pos_x, pos_y, OLED_Color_White);
    }
    if (config_Display[display_values] == "mafAirFlowRatio")
    {
      if ((display_values % 2) == 0)
      {
        pos_x = 72;
      }else
      {
        pos_x = 8;
      }
    printText(0, false, "AIR RATIO", pos_x, pos_y, OLED_Color_White);
    }
    if (config_Display[display_values] == "throttlePosition")
    {
      if ((display_values % 2) == 0)
      {
        pos_x = 68;
      }else
      {
        pos_x = 4;
      }
    drawPercentage((pos_x + 46), (pos_y - 6), OLED_Color_White);
    printText(0, false, "THROTTLE", pos_x, pos_y, OLED_Color_White);
    }
    if (config_Display[display_values] == "fuelTankLevel")
    {
      if ((display_values % 2) == 0)
      {
        pos_x = 68;
      }else
      {
        pos_x = 3;
      }
    if (fuelTankLevelPercentage == true)
    {
          drawPercentage((pos_x + 46), (pos_y - 6), OLED_Color_White);
    }
    else
    {
          drawVolume((pos_x + 46), (pos_y - 6), OLED_Color_White);
    }
    printText(0, false, "FUEL LEVEL", pos_x, pos_y, OLED_Color_White);
    }
    if (config_Display[display_values] == "egt")
    {
      if ((display_values % 2) == 0)
      {
        pos_x = 86;
      }else
      {
        pos_x = 22;
      }
    drawDegree((pos_x + 24), (pos_y - 6), OLED_Color_White);
    printText(0, false, "EGT", pos_x, pos_y, OLED_Color_White);
    }
    if (config_Display[display_values] == "voltage")
    {
      if ((display_values % 2) == 0)
      {
        pos_x = 76;
      }else
      {
        pos_x = 12;
      }
    printText(0, true, "V", (pos_x + 36), (pos_y - 6), OLED_Color_White);
    printText(0, false, "VOLTAGE", pos_x, pos_y, OLED_Color_White);
    }
    if (config_Display[display_values] == "oilTemperature")
    {
      if ((display_values % 2) == 0)
      {
        pos_x = 74;
      }else
      {
        pos_x = 10;
      }
    drawDegree((pos_x + 36), (pos_y - 6), OLED_Color_White);
    printText(0, false, "OIL TEMP", pos_x, pos_y, OLED_Color_White);
    }
    if (config_Display[display_values] == "oilPressure")
    {
      if ((display_values % 2) == 0)
      {
        pos_x = 70;
      }else
      {
        pos_x = 6;
      }
    drawPressure((pos_x + 46), (pos_y - 6), OLED_Color_White);
    printText(0, false, "OIL PRESS", pos_x, pos_y, OLED_Color_White);
    }
    if (config_Display[display_values] == "afr")
    {
      if ((display_values % 2) == 0)
      {
        pos_x = 80;
      }else
      {
        pos_x = 16;
      }
    printText(0, false, "AFR", pos_x, pos_y, OLED_Color_White);
    }
    if (config_Display[display_values] == "consumption")
    {
      if ((display_values % 2) == 0)
      {
        pos_x = 68;
      }else
      {
        pos_x = 3;
      }
    printText(0, false, "FUEL CONS.", pos_x, pos_y, OLED_Color_White);
    drawVolume((pos_x + 46), (pos_y - 6), OLED_Color_White);
    }
    if (config_Display[display_values] == "shortTermFuel")
    {
      if ((display_values % 2) == 0)
      {
        pos_x = 71;
      }else
      {
        pos_x = 5;
      }
    printText(0, false, "FUEL TERM", pos_x, pos_y, OLED_Color_White);
    drawPercentage((pos_x + 44), (pos_y - 6), OLED_Color_White);
    }
    if (config_Display[display_values] == "timingAdvanced")
    {
      if ((display_values % 2) == 0)
      {
        pos_x = 80;
      }else
      {
        pos_x = 14;
      }
    printText(0, false, "TIMING", pos_x, pos_y, OLED_Color_White);
    drawDegree((pos_x + 36), (pos_y - 6), OLED_Color_White, false);
    }
    if (config_Display[display_values] == "oxygenSensorFuelRatio")
    {
      if ((display_values % 2) == 0)
      {
        pos_x = 72;
      }else
      {
        pos_x = 5;
      }
    printText(0, false, "O2 SENSOR", pos_x, pos_y, OLED_Color_White);
    drawPercentage((pos_x + 44), (pos_y - 6), OLED_Color_White);
    }
  }
}

int drawFuel()
{
  //Serial.println(fuelSize);
  if (fuelSize == 30)
  {
    fuelSize = 0;
    int x = fuelPack / 30;
    fuelPack = 0;
    return x;
  }
  else
  {
   fuelSize = fuelSize + 1;
   fuelPack = fuelPack +  OBD2.pidRead(47);
   return 255;
  }
}

void loop() 
{
  //Serial.println("test");
   delay(500);

  if (!OBD2.begin())
  {
    return;  
  }

  raw = analogRead(analogPin);
  if(raw){
    buffer = raw * Vin;
    Vout = (buffer)/1024.0;
    buffer = (Vin/Vout) - 1;
    R2= R1 * buffer;
  }



  raw_1 = analogRead(analogPin_1);
  if(raw_1){
    buffer_1 = raw_1 * Vin;
    Vout_1 = (buffer_1)/1024.0;
    buffer_1 = (Vin/Vout_1) - 1;
    R2_1= R1_1 * buffer_1;
    oilPressure = (R2_1 * 0.0632) * 14.5038 ;
 }

    int val = 0;
    float start = 150;

    val = R2;

    for (int z = 0; z <= val; z++)
    {
      start = start * 0.99693;
    }

   temp_oil_a += start;
   
    temp_oil_b++;
    if (temp_oil_b == 10)
    {
      temp_oil_b = 0;
      oilTemperature = temp_oil_a / 11;
      //Serial.println(oil_temp);
      temp_oil_a = 0;
    }

 
      engineCoolantTemperature = OBD2.pidRead(5);
      vehicleSpeed = OBD2.pidRead(13);
      intakeAirTemperature = OBD2.pidRead(15);
      mafAirFlowRatio = OBD2.pidRead(16);
      throttlePosition = OBD2.pidRead(67);
      fuelTankLevel = OBD2.pidRead(47);
      egt = OBD2.pidRead(60);
      voltage = OBD2.pidRead(66);
      afr = OBD2.pidRead(68) * 14.6412885;
      consumption = drawConsumption(); // dorobic consumption zeby pokazywalo w glaonach
      if (consumption > 99)
      {
        consumption = 99;
      }
      shortTermFuel = OBD2.pidRead(7);
      timingAdvanced = OBD2.pidRead(14);
      oxygenSensorFuelRatio = OBD2.pidRead(52);

  for (byte display_values = 1; display_values <= 8; display_values++)
  {
    byte pos_x;
    byte pos_y;
    if (display_values == 1 || display_values == 2)
    {
      pos_y = 16;
    }
    if (display_values == 3 || display_values == 4)
    {
      pos_y = 49;
    }
    if (display_values == 5 || display_values == 6)
    {
      pos_y = 81;
    }
    if (display_values == 7 || display_values == 8)
    {
      pos_y = 113;
    }
    if (config_Display[display_values] == "engineCoolantTemperature")
    {
      uint16_t color = OLED_Color_White;
      if (engineCoolantTemperature > waterTemperatureWarning)
      {
       color = OLED_Color_Red; 
      }
      if ((display_values % 2) == 0)
      {
        pos_x = 72;
        
      }else
      {
        pos_x = 8;
      }
      if (celciush == false)
      {
        engineCoolantTemperature = (engineCoolantTemperature * 1.8 + 32);
      }
      oled.fillRect((pos_x - 2), (pos_y - 16), 40, 21, OLED_Color_Black);
      if (engineCoolantTemperature >= 100)
      {
              printText(0, true, String(engineCoolantTemperature), pos_x, pos_y, color);
      }
      else
      {
              printText(0, true, String(engineCoolantTemperature), pos_x + 6, pos_y, color);
      }
    }
    if (config_Display[display_values] == "vehicleSpeed")
    {
      
      if ((display_values % 2) == 0)
      {
        pos_x = 67;
        
      }else
      {
        pos_x = 2;
      }
      oled.fillRect((pos_x - 2), (pos_y - 16), 38, 21, OLED_Color_Black);
      if (vehicleSpeed >= 100)
      {
              printText(0, true, String(vehicleSpeed), pos_x, pos_y, OLED_Color_White);
      }
      else
      {
              printText(0, true, String(vehicleSpeed), pos_x + 8, pos_y, OLED_Color_White);
      }
    }
    if (config_Display[display_values] == "intakeAirTemperature")
    {
      uint16_t color = OLED_Color_White;
      if (intakeAirTemperature > airTempWarning)
      {
       color = OLED_Color_Red; 
      }
      if ((display_values % 2) == 0)
      {
        pos_x = 80;
        
      }else
      {
        pos_x = 15;
      }
      oled.fillRect((pos_x - 10), (pos_y - 16), 38, 21, OLED_Color_Black);
      if (celciush == false)
      {
        printText(0, true, String(intakeAirTemperature), pos_x - 4, pos_y, color, 0, intakeAirTemperature * 1.8 + 32);
      }
      else
      {
        printText(0, true, String(intakeAirTemperature), pos_x, pos_y, color, 0, intakeAirTemperature);
      }
    }
    if (config_Display[display_values] == "mafAirFlowRatio")
    {
      if ((display_values % 2) == 0)
      {
        pos_x = 67;
        
      }else
      {
        pos_x = 2;
      }
      oled.fillRect((pos_x - 2), (pos_y - 16), 63, 21, OLED_Color_Black);
      printText(0, true, String(mafAirFlowRatio), pos_x + 10, pos_y, OLED_Color_White, 1, mafAirFlowRatio); // tu dodac 1 : wartosc
    }
    if (config_Display[display_values] == "throttlePosition")
    {
      if ((display_values % 2) == 0)
      {
        pos_x = 80;
        
      }else
      {
        pos_x = 16;
      }
      oled.fillRect((pos_x - 12), (pos_y - 16), 44, 21, OLED_Color_Black);
      printText(0, true, String(throttlePosition), pos_x, pos_y, OLED_Color_White);
    }
    if (config_Display[display_values] == "fuelTankLevel")
    {
      uint16_t color = OLED_Color_White;
      if (fuelTankLevel < fuelTankLevelWarning)
      {
       color = OLED_Color_Red; 
      }
      if ((display_values % 2) == 0)
      {
        pos_x = 81;
        
      }else
      {
        pos_x = 16;
      }
      oled.fillRect((pos_x - 16), (pos_y - 16), 46, 21, OLED_Color_Black);
      if (fuelTankLevelPercentage == true)
      {
        printText(0, true, String(fuelTankLevel), pos_x, pos_y, color);
      }
      else
      {
        if (liter == true)
        {
                  printText(0, true, String(fuelTankLevel), pos_x + 4, pos_y, color, 0, float((fuelTankLevel * float(61))) / float(100));  
        }
        else
        {
                  printText(0, true, String(fuelTankLevel), pos_x + 4, pos_y, color, 0, float((fuelTankLevel * float(61))) / float(100) * float(0.264172));  
        }
      }
    }
    if (config_Display[display_values] == "egt")
    {
      if ((display_values % 2) == 0)
      {
        pos_x = 67;
        
      }else
      {
        pos_x = 2;
      }
      oled.fillRect((pos_x - 2), (pos_y - 16), 42, 21, OLED_Color_Black);
      if (celciush == false)
      {
        egt = (egt * 1.8 + 32);
      }
      String export_Egt = String(egt);
      if (egt >= 1000)
      {
              printText(0, true, export_Egt, pos_x, pos_y, OLED_Color_White, 1, float(float(egt) / float(1000)));
              printText(0, true, "K", (pos_x + 30), pos_y, OLED_Color_White);
      }
      else
      {
              printText(0, true, export_Egt, pos_x + 8, pos_y, OLED_Color_White);
      }
    }
    if (config_Display[display_values] == "voltage")
    {
      uint16_t color = OLED_Color_White;
      if (voltage < voltageWarning)
      {
       color = OLED_Color_Red; 
      }
      if ((display_values % 2) == 0)
      {
        pos_x = 67;
        
      }else
      {
        pos_x = 2;
      }
      oled.fillRect((pos_x - 2), (pos_y - 16), 46, 21, OLED_Color_Black);
      printText(0, true, String(voltage), pos_x, pos_y, color, 1, voltage);
    }
    if (config_Display[display_values] == "oilTemperature")
    {
      uint16_t color = OLED_Color_White;
      if (oilTemperature > oilTemperatureWarning)
      {
       color = OLED_Color_Red; 
      }
      if (celciush == false)
      {
       oilTemperature = (oilTemperature * 1.8 + 32);
      }
      if ((display_values % 2) == 0)
      {
        pos_x = 72;
        
      }else
      {
        pos_x = 8;
      }
      oled.fillRect((pos_x - 7), (pos_y - 16), 40, 21, OLED_Color_Black);
      if (oilTemperature <= 29)
      {
              printText(0, true, "-", pos_x + 8, pos_y, color);
      }
      else if (oilTemperature >= 100)
      {
              printText(0, true, String(oilTemperature), pos_x, pos_y, color);
      }
      else
      {
              printText(0, true, String(oilTemperature), pos_x + 8, pos_y, color);
      }
    }
    if (config_Display[display_values] == "oilPressure")
    {
      uint16_t color = OLED_Color_White;
      if (oilPressure < oilPressureWarning)
      {
       color = OLED_Color_Red; 
      }
      if ((display_values % 2) == 0)
      {
        pos_x = 67;
        
      }else
      {
        pos_x = 2;
      }
      oled.fillRect((pos_x - 2), (pos_y - 16), 48, 21, OLED_Color_Black);
      if (OBD2.pidRead(12) < 500)
      {
          printText(0, true, "-", pos_x + 16, pos_y, OLED_Color_White);
      }
      else if (bars == true)
      {
        printText(0, true, String(oilPressure), pos_x + 10, pos_y, color, 1, oilPressure * 0.0689476);
      }
      else
      {
        printText(0, true, String(oilPressure), pos_x + 16, pos_y, color, 0, oilPressure);
      }
    }
    if (config_Display[display_values] == "afr")
    {
      if ((display_values % 2) == 0)
      {
        pos_x = 67;
        
      }else
      {
        pos_x = 2;
      }
      oled.fillRect((pos_x - 2), (pos_y - 16), 60, 21, OLED_Color_Black);
      if (afr == 0)
      {
              printText(0, true, "-", pos_x + 16, pos_y, OLED_Color_White);
        
      }
      else
      {
              printText(0, true, String(afr), pos_x + 6, pos_y, OLED_Color_White, 1, afr);
      }
    }
    if (config_Display[display_values] == "consumption")
    {
      if ((display_values % 2) == 0)
      {
        pos_x = 67;
        
      }else
      {
        pos_x = 2;
      }
      oled.fillRect((pos_x - 2), (pos_y - 16), 46, 21, OLED_Color_Black);
      if (liter == false)
      {
        consumption = float(float(consumption) * float(0.264172));
      }
      if (consumption >= 10)
      {
              printText(0, true, "-", pos_x + 1, pos_y, OLED_Color_White, 1, consumption);
      }
      else
      {
              printText(0, true, "-", pos_x + 10, pos_y, OLED_Color_White, 1, consumption);
      }
    }
    if (config_Display[display_values] == "shortTermFuel")
    {
      if ((display_values % 2) == 0)
      {
        pos_x = 67;
        
      }else
      {
        pos_x = 2;
      }
      oled.fillRect((pos_x - 2), (pos_y - 16), 44, 21, OLED_Color_Black);
      if (shortTermFuel >= 10)
      {
              printText(0, true, "-", pos_x, pos_y, OLED_Color_White, 1, shortTermFuel);
      }
      else
      {
              printText(0, true, "-", pos_x + 12, pos_y, OLED_Color_White, 1, shortTermFuel);
      }
    }
    if (config_Display[display_values] == "timingAdvanced")
    {
      if ((display_values % 2) == 0)
      {
        pos_x = 67;
        
      }else
      {
        pos_x = 2;
      }
      oled.fillRect((pos_x - 2), (pos_y - 16), 44, 21, OLED_Color_Black);
      printText(0, true, "-", pos_x + 12, pos_y, OLED_Color_White, 0, timingAdvanced);
    }
    if (config_Display[display_values] == "oxygenSensorFuelRatio")
    {
      if ((display_values % 2) == 0)
      {
        pos_x = 67;
        
      }else
      {
        pos_x = 2;
      }
      oled.fillRect((pos_x - 2), (pos_y - 16), 44, 21, OLED_Color_Black);
      if (oxygenSensorFuelRatio >= 10)
      {
              printText(0, true, "-", pos_x, pos_y, OLED_Color_White, 1, oxygenSensorFuelRatio);
      }
      else
      {
              printText(0, true, "-", pos_x + 12, pos_y, OLED_Color_White, 1, oxygenSensorFuelRatio);
      }
    }
    }

  }
