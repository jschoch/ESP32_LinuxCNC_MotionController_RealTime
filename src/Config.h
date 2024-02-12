#pragma once

#include <Arduino.h>
#include "Types.hpp"


/*==================================================================*/
// Serial baud rate
// OK to change, but the ESP32 boot text is 115200, so you will not see that is your
// serial monitor, sender, etc uses a different value than 115200
#define BAUD_RATE 115200

#define CONF_NUM_STEPPERS 3  /* Set how many motors you want to enable and update the stepper_config struct below with the motors you require */
/* !!!!Important!!!! Do not update the MAX_STEPPER define - this is set to 6 max and the size of the UDP RX/TX buffer is set accordingly to support up-to 6 max */

#define ENABLE_SERIAL_STATS // Runs a Core1 async task that prints stats to serial console
#define DEBUG_AXIS_MOVEMENTS /* Enables axis movement detailed debugging to aid troubleshooting of motor jitter or noise during prolonged movements  */
#define ENABLE_WIFI       /* Enable WIFI and connect to SSID configured below */

#define WIFI_ACCESSPOINTMODE
//#define WIFI_CLIENTMODE

#define CONF_WIFI_SSID "ESP32LCNCCtrl"
#define CONF_WIFI_PWD "LinuxCNCPassword1"

/* Ethernet config and IP Addressing */
const uint8_t mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
const IPAddress my_ip(192, 168, 10, 10); /* ESP32 Ethernet IP Address */
const IPAddress ip_host(192, 168, 10, 171); /* LinuxCNC Ethernet adapter IP must be configured as this */
const IPAddress gw(192, 168, 10, 254); /* Only useful if you connect ESP32 and LinuxCNC Host on same network segment with a router or another network */
const IPAddress subnetmask(255, 255, 255, 0);

/* Async UDP Client and Server is used to ensure bi-directional low-latency data streaming between ESP32 and LinuxCNC Host */
const uint16_t udpServerPort = 58427;  /* UDP Server port the ESP32 listens on. LinuxCNC HAL driver sends data to this port */
const uint16_t udpClientPort = 58428; /* UDP Client port the ESP32 connects to. LinuxCNC HAL driver runs a UDP server */

#ifdef ARDUINO_ESP32_EVB

  #define OUT_00_PIN    GPIO_NUM_NC
  #define OUT_01_PIN    GPIO_NUM_NC
  #define OUT_02_PIN    GPIO_NUM_33  // Relay #2 (Turns on when machine on)
  #define OUT_03_PIN    GPIO_NUM_NC
  #define OUT_04_PIN    GPIO_NUM_NC
  #define OUT_05_PIN    GPIO_NUM_NC
  
  // Axis X GPIO pin set
  #define X_DISABLE_PIN               GPIO_NUM_32 // # Shared Servo motor driver disable pin. Relay #1 on Olimex ESP32 EVB. Relay has 3.3v in common terminal and normally closed output goes to stepper drivers EN terminal
  #define X_DIRECTION_PIN             GPIO_NUM_12
  #define X_STEP_PIN                  GPIO_NUM_17

  // Axis Y GPIO pin set
  #define Y_DISABLE_PIN               GPIO_NUM_32
  #define Y_DIRECTION_PIN             GPIO_NUM_4
  #define Y_STEP_PIN                  GPIO_NUM_14
      
  // Axis Z GPIO pin set
  #define Z_DISABLE_PIN               GPIO_NUM_32
  #define Z_DIRECTION_PIN             GPIO_NUM_5
  #define Z_STEP_PIN                  GPIO_NUM_15

/*
  // Axis A GPIO pin set
  #define A_DISABLE_PIN               GPIO_NUM_32
  #define A_DIRECTION_PIN             GPIO_NUM_16
  #define A_STEP_PIN                  GPIO_NUM_13
*/
#elif defined(ARDUINO_ESP32_POE)

  /* ETH PHY RESERVED GPIO
     12, 17, 18, 19, 21, 22, 23, 25, 26
    INPUT ONLY GPIO
     34, 35, 36, 39
     BOOTSTRAP GPIO
     0, 2
  */
  #define OUT_00_PIN    GPIO_NUM_NC
  #define OUT_01_PIN    GPIO_NUM_NC
  #define OUT_02_PIN    GPIO_NUM_NC // Relay #2
  #define OUT_03_PIN    GPIO_NUM_NC
  #define OUT_04_PIN    GPIO_NUM_NC
  #define OUT_05_PIN    GPIO_NUM_NC

  //#define OUT_02_PIN    GPIO_NUM_33 // Relay #2

  #define X_DISABLE_PIN               GPIO_NUM_13
  #define X_DIRECTION_PIN             GPIO_NUM_32
  #define X_STEP_PIN                  GPIO_NUM_33

  // Y GPIO pin set
  #define Y_DISABLE_PIN               GPIO_NUM_13
  #define Y_DIRECTION_PIN             GPIO_NUM_4
  #define Y_STEP_PIN                  GPIO_NUM_14
      
  // Axis Z GPIO pin set
  //#if defined(USR_Z_MOTOR)
  #define Z_DISABLE_PIN               GPIO_NUM_13
  #define Z_DIRECTION_PIN             GPIO_NUM_5
  #define Z_STEP_PIN                  GPIO_NUM_15

/*
  // Axis A GPIO pin set
  #define A_DISABLE_PIN               GPIO_NUM_32
  #define A_DIRECTION_PIN             GPIO_NUM_16
  #define A_STEP_PIN                  GPIO_NUM_13
*/
#elif defined(ARDUINO_ESP32_WT32_ETH01)

  #define OUT_00_PIN    GPIO_NUM_NC
  #define OUT_01_PIN    GPIO_NUM_NC
  #define OUT_02_PIN    GPIO_NUM_33 // Relay #2
  #define OUT_03_PIN    GPIO_NUM_NC
  #define OUT_04_PIN    GPIO_NUM_NC
  #define OUT_05_PIN    GPIO_NUM_NC

  // Axis X GPIO pin set    
  #define X_DISABLE_PIN               GPIO_NUM_5
  #define X_DIRECTION_PIN             GPIO_NUM_17
  #define X_STEP_PIN                  GPIO_NUM_12

  // Axis Y GPIO pin set
  #define Y_DISABLE_PIN               GPIO_NUM_5
  #define Y_DIRECTION_PIN             GPIO_NUM_4
  #define Y_STEP_PIN                  GPIO_NUM_14
      
  // Axis Z GPIO pin set
  #define Z_DISABLE_PIN               GPIO_NUM_5
  #define Z_DIRECTION_PIN             GPIO_NUM_33
  #define Z_STEP_PIN                  GPIO_NUM_15
  
  // Axis A GPIO pin set
  #define A_DISABLE_PIN               GPIO_NUM_5
  #define A_DIRECTION_PIN             GPIO_NUM_32
  #define A_STEP_PIN                  GPIO_NUM_2

#elif defined(ARDUINO_ESP32_MKS_DLC32)
  #include "Pins.h"
  #include "I2SOut.h"
  
  #define OUT_00_PIN    GPIO_NUM_NC
  #define OUT_01_PIN    GPIO_NUM_NC
  #define OUT_02_PIN    GPIO_NUM_NC
  #define OUT_03_PIN    GPIO_NUM_NC
  #define OUT_04_PIN    GPIO_NUM_NC
  #define OUT_05_PIN    GPIO_NUM_NC

  //#define _ASYNC_UDP_ESP32_ETHERNET_LOGLEVEL_            1
  //#define _ETHERNET_WEBSERVER_LOGLEVEL_ 1
  #define ASYNC_UDP_ESP32_ETHERNET_DEBUG_PORT      Serial
  
  #define ESP32_Ethernet_onEvent            ESP32_W5500_onEvent
  #define ESP32_Ethernet_waitForConnect     ESP32_W5500_waitForConnect
  #define ETH_SPI_HOST                      VSPI_HOST

  #define W5500_CS_PIN                GPIO_NUM_0 
  #define W5500_INT_PIN               GPIO_NUM_4 

  #define USE_I2S_OUT

  // I2S pins set
  #define I2S_OUT_BCK                 GPIO_NUM_16
  #define I2S_OUT_WS                  GPIO_NUM_17
  #define I2S_OUT_DATA                GPIO_NUM_21
      

  //#define IIC_SCL                     GPIO_NUM_4
  //#define IIC_SDA                     GPIO_NUM_0

  #define BEEPER					            I2SO(7)

  // X I2S pin set    
  #define X_DISABLE_PIN               I2SO(0)
  #define X_DIRECTION_PIN             I2SO(2)
  #define X_STEP_PIN                  GPIO_NUM_25 // LCD_CS EXP1 PIN7

  // Y I2S pin set
  #define Y_DISABLE_PIN               I2SO(0)
  #define Y_DIRECTION_PIN             I2SO(6)
  #define Y_STEP_PIN                  GPIO_NUM_26 // LCD_TOUCH_CS EXP1 PIN5
      
  // Z I2S pin set
  #define Z_DISABLE_PIN               I2SO(0)
  #define Z_DIRECTION_PIN             I2SO(4)
  #define Z_STEP_PIN                  GPIO_NUM_27 // LCD_RST EXP1 Pin4


#elif defined(ARDUINO_LOLIN_S2_MINI)

  #define OUT_00_PIN    GPIO_NUM_NC
  #define OUT_01_PIN    GPIO_NUM_NC
  #define OUT_02_PIN    GPIO_NUM_33 // Relay #2
  #define OUT_03_PIN    GPIO_NUM_NC
  #define OUT_04_PIN    GPIO_NUM_NC
  #define OUT_05_PIN    GPIO_NUM_NC

  // Axis X GPIO pin set
  #define X_DISABLE_PIN               GPIO_NUM_5
  #define X_DIRECTION_PIN             GPIO_NUM_17
  #define X_STEP_PIN                  GPIO_NUM_12

  // Axis Y GPIO pin set
  #define Y_DISABLE_PIN               GPIO_NUM_5
  #define Y_DIRECTION_PIN             GPIO_NUM_4
  #define Y_STEP_PIN                  GPIO_NUM_14
      
  // Axis Z GPIO pin set
  //#if defined(USR_Z_MOTOR)
  #define Z_DISABLE_PIN               GPIO_NUM_5
  #define Z_DIRECTION_PIN             GPIO_NUM_33
  #define Z_STEP_PIN                  GPIO_NUM_15
  
  // Axis A GPIO pin set
  #define C_DISABLE_PIN               GPIO_NUM_5
  #define C_DIRECTION_PIN             GPIO_NUM_32
  #define C_STEP_PIN                  GPIO_NUM_2

#endif

/* Stepper Motor Configs */

const struct stepper_config_s stepper_config[MAX_STEPPER] = {
    {
      // stepper 1 shall be connected to 
      step : X_STEP_PIN,
#ifdef ARDUINO_ESP32_EVB  /* Inverted motor enable pin for Olimex ESP32-EVB board to Relay#1 NC terminal */
      enable_low_active : PIN_UNDEFINED,
      enable_high_active : X_DISABLE_PIN,
#else
      enable_low_active : X_DISABLE_PIN,
      enable_high_active : PIN_UNDEFINED,
#endif
      direction : X_DIRECTION_PIN,
      dir_change_delay : 1000,
      direction_high_count_up : true,
      auto_enable : false,
      on_delay_us : 5000,
      off_delay_ms : 5
    },
    {
      // stepper 2 shall be connected to 
      step : Y_STEP_PIN,
#ifdef ARDUINO_ESP32_EVB
      enable_low_active : PIN_UNDEFINED,
      enable_high_active : Y_DISABLE_PIN,
#else
      enable_low_active : Y_DISABLE_PIN,
      enable_high_active : PIN_UNDEFINED,
#endif
      direction : Y_DIRECTION_PIN,
      dir_change_delay : 1000,
      direction_high_count_up : true,
      auto_enable : false,
      on_delay_us : 2000,
      off_delay_ms : 5
    },
    {
      // stepper 3 shall be connected to 
      step : Z_STEP_PIN,
#ifdef ARDUINO_ESP32_EVB
      enable_low_active : PIN_UNDEFINED,
      enable_high_active : Z_DISABLE_PIN,
#else
      enable_low_active : Z_DISABLE_PIN,
      enable_high_active : PIN_UNDEFINED,
#endif
      direction : Z_DIRECTION_PIN,
      dir_change_delay : 1000,
      direction_high_count_up : true,
      auto_enable : false,
      on_delay_us : 2000,
      off_delay_ms : 5
    },
    // {
    //   // stepper 4 shall be connected to 
    //   step : C_STEP_PIN,
    //   enable_low_active : PIN_UNDEFINED,
    //   enable_high_active : C_DISABLE_PIN,
    //   direction : C_DIRECTION_PIN,
    //   dir_change_delay : 600,
    //   direction_high_count_up : true,
    //   auto_enable : false,
    //   on_delay_us : 2000,
    //   off_delay_ms : 5
    // }
};

/* INPUT Configs */

const struct inputPin_Config_s inputPinsConfig[7] = {
    {
      name : "Unused",
      udp_in_num : 0,
      pin_mode : INPUT_PULLUP,
      gpio_number : GPIO_NUM_NC, // Not connected
      register_address : GPIO_IN_REG,
      register_bit : 0,
      fb_input_mask : IO_00
    },
    {
      name : "Mpg1",
      udp_in_num : 1,
      pin_mode : INPUT_PULLUP,
      gpio_number : GPIO_NUM_NC, // Not connected
      register_address : GPIO_IN_REG,
      register_bit : 0,
      fb_input_mask : IO_01
    },
    {
      name : "TouchProbe",
      udp_in_num : 2,
      pin_mode : INPUT_PULLDOWN,
#ifdef ARDUINO_ESP32_EVB
      gpio_number : GPIO_NUM_16,
#else
      gpio_number : GPIO_NUM_NC,
#endif
      register_address : GPIO_IN_REG,
      register_bit : BIT16,
      fb_input_mask : IO_02
    },
    {
      name : "TLProbe",
      udp_in_num : 3,
      pin_mode : INPUT_PULLDOWN,
#ifdef ARDUINO_ESP32_EVB
      gpio_number : GPIO_NUM_39,
#else
      gpio_number : GPIO_NUM_NC,
#endif
      register_address : GPIO_IN1_REG,
      register_bit : BIT7,
      fb_input_mask : IO_03
    },
    {
      name : "Z Endstop",
      udp_in_num : 4,
      pin_mode : INPUT_PULLUP,
#ifdef ARDUINO_ESP32_EVB
      gpio_number : GPIO_NUM_34,
#else
      gpio_number : GPIO_NUM_34,
#endif
      register_address : GPIO_IN1_REG,
      register_bit : BIT2,
      fb_input_mask : IO_04
    },
    {
      name : "X Endstop",
      udp_in_num : 5,
      pin_mode : INPUT_PULLUP,
#ifdef ARDUINO_ESP32_EVB
      gpio_number : GPIO_NUM_35,
#else
      gpio_number : GPIO_NUM_NC,
#endif
      register_address : GPIO_IN1_REG,
      register_bit : BIT3,
      fb_input_mask : IO_05
    },
    {
      name : "Y Endstop",
      udp_in_num : 6,
      pin_mode : INPUT_PULLUP,
#ifdef ARDUINO_ESP32_EVB
      gpio_number : GPIO_NUM_36,
#else
      gpio_number : GPIO_NUM_NC,
#endif
      register_address : GPIO_IN1_REG,
      register_bit : BIT4,
      fb_input_mask : IO_06
    },
};

