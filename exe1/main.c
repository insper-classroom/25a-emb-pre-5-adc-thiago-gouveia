#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>

#include "pico/stdlib.h"
#include <stdio.h>

#include "hardware/gpio.h"
#include "hardware/adc.h"

void adc_1_task(void *p) {
    adc_init();
    adc_gpio_init(27);

    // 12-bit conversion, assume max value == ADC_VREF == 3.3 V
    const float conversion_factor = 3.3f / (1 << 12);

    uint16_t result;
    while (1) {
        adc_select_input(1); // Select ADC input 1 (GPIO27)
        result = adc_read();
        printf("voltage 1: %f V\n", result * conversion_factor);

        // CÓDIGO AQUI



        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

int main() {
    stdio_init_all();      

    adc_init();            

    adc_gpio_init(26);
    adc_gpio_init(27);

    while (true) {
        adc_select_input(0);
        uint16_t raw_0 = adc_read(); 
        float voltage_0 = raw_0 * (3.3f / (1 << 12));

        adc_select_input(1);
        uint16_t raw_1 = adc_read();
        float voltage_1 = raw_1 * (3.3f / (1 << 12));

        printf("voltage 1: %.6f V\n", voltage_0);
        printf("voltage 2: %.6f V\n\n", voltage_1);

        sleep_ms(1000);
    }

    return 0;
}