#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *MAIN = "MAIN_APP";

// extern "C" is used to prevent name mangling when the function is called from C code
extern "C" void app_main() {
  ESP_LOGI(MAIN, "Starting application...");

  while (true) {
    ESP_LOGI(MAIN, "Hello, World!");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}