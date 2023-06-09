#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_err.h>
#include <dht/dht.h>

#define DHT_GPIO 5 // D1 pin

void temperature_task(void *arg)
{
    ESP_ERROR_CHECK(dht_init(DHT_GPIO, false));
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    while (1)
    {
        int humidity = 0;
        int temperature = 0;
        if (dht_read_data(DHT_TYPE_DHT11, DHT_GPIO, &humidity, &temperature) == ESP_OK) {
            printf("Humidity: %d Temperature: %d\n", humidity, temperature);
        } else {
            printf("Fail to get dht temperature data\n");
        }
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void app_main() {
    xTaskCreate(temperature_task, "temperature task", 2048, NULL, tskIDLE_PRIORITY, NULL);
}
