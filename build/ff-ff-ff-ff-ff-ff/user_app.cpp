#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "kidbright32.h"
#include "devman.h"
#include "ports.h"
#include "button12.h"
#include "ldr.h"
#include "sound.h"
#include "ht16k33.h"
#include "lm73.h"
#include "mcp7940n.h"
#include <math.h>



// kbiot
#include "nvs_flash.h"
#include "wificontroller.h"
#include "kbiot.h"

#define KBSERIAL "FFFFFFFFFFFF"
#define CLIENTID "FFFFFFFFFFFF"
#define USERNAME "eb235fb41ecb7ef2101523c00ab82fb7" //replace with md5(K:your_board_mac_without_colon)
#define PASSWORD ""
#define CONFIG_WIFI_SSID ""
#define CONFIG_WIFI_PASSWORD ""

#define PI 3.14159265
// ===
// ==================================================================================
// on-board devices
// ==================================================================================
// i/o devices
PORTS ports = PORTS();
BUTTON12 button12 = BUTTON12();
LDR ldr = LDR();
SOUND sound = SOUND();
// i2c devices
HT16K33 ht16k33 = HT16K33(0, HT16K33_ONBOARD_ADDR);
LM73 lm73 = LM73(0, LM73_1_ONBOARD_ADDR);
MCP7940N mcp7940n = MCP7940N(0, MCP7940N_ONBOARD_ADDR);

// ==================================================================================
// plug-ins devices
// ==================================================================================




void iotTask(void *pvParameters) {
			 
			
			vTaskDelay(500 / portTICK_RATE_MS);
			vTaskDelete(NULL);
}


void user_app(void) {
    xTaskCreatePinnedToCore(iotTask, "iotTask", 4096, NULL, USERAPP_TASK_PRIORITY, NULL, KIDBRIGHT_RUNNING_CORE);
    srand(mcp7940n.get(5)); // random seed
      // setup
  while(1) {
    ht16k33.show((uint8_t *)"\x0\x0\x0\x2\xc\x30\x40\x80\x0\x0\x0\x0\x0\x0\x0\x0");
  }
  

      // create tasks

}

void vUserAppTask(void *pvParameters) {
  // init device manager
  devman_init();

  // ================================================================================
  // add on-board devices
  // ================================================================================
  // i/o devices
  devman_add((char *)"ports", DEV_IO, &ports);
  devman_add((char *)"button12", DEV_IO, &button12);
  devman_add((char *)"ldr", DEV_IO, &ldr);
  devman_add((char *)"sound", DEV_IO, &sound);
  // i2c0 devices
  devman_add((char *)"ht16k33", DEV_I2C0, &ht16k33);
  // i2c1 devices
  devman_add((char *)"lm73", DEV_I2C1, &lm73);
  devman_add((char *)"mcp7940n", DEV_I2C1, &mcp7940n);

  // ================================================================================
  // add plug-ins devices
  // ================================================================================
    
  

  // start device manager
  devman_start();

  // wait all devices initialized or error
  while (!devman_ready()) {
    vTaskDelay(100 / portTICK_RATE_MS);
  }

  // real user app
  user_app();

  // kill itself
  vTaskDelete(NULL);
}

void UartParser(char *line, char list[][MAX_UART_LINE_CHAR_COUNT], int len) {
  
}