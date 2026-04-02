#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "espidf_baseline";

int myFunction(int x, int y) {
  return x + y;
}

extern "C" void app_main() {
  int result = myFunction(2, 3);
  ESP_LOGI(TAG, "myFunction(2,3) = %d", result);

  while (true) {
    ESP_LOGI(TAG, "Hello, World!");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}