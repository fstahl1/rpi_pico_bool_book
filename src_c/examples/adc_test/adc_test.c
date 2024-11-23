#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "math.h"

int main()
{
    stdio_init_all();

    adc_init();
    // Make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(26);
    adc_gpio_init(27);

    printf("Hello, world!\n");

    const float conv = 1.0f / (1 << 12);

    float c2 = 5.389e-05;
    float c1 = 0.6327;
    float c0 = 38.14;

    float phi = c1/(2*c2);

    // float c2 = -1.32619208e-04;
    // float c1 = 1.66929986e+00;
    // float c0 = -4.20929448e+02;
 
    int count = 10;

    while (true) {

        uint16_t mean1 = 0;
        uint16_t mean2 = 0;
        uint16_t mean2raw = 0;

        const float conversion_factor = 3.3f / (1 << 12);

        // adc_select_input(0);
        // uint16_t res = adc_read();

        // printf("raw: 0x%03x, raw: %d, voltage: %f\n", res, res, res*conversion_factor);

        // sleep_ms(100);



        // printf("%f, %f\n", mean1 * conversion_factor, mean2 * conversion_factor);
        // printf("%d, %d\n", mean1, mean2);
        // printf("%f\n", mean1);

        for(int i=0; i<count; i++){
            // 12-bit conversion, assume max value == ADC_VREF == 3.3 V
            // Select ADC input 0 (GPIO26)
            adc_select_input(0);
            uint16_t result1 = adc_read();
            // printf("1: Raw value: 0x%03x, voltage: %f V\n", result1, result1 * conversion_factor);
            sleep_ms(20);

            adc_select_input(1);
            uint16_t result2 = adc_read();
            // printf("2: Raw value: 0x%03x, voltage: %f V\n", result2, result2 * conversion_factor);
            sleep_ms(20);

            mean1 += result1;
            mean2 += -phi + sqrt(pow(phi,2) - (c0-result2)/c2);
            mean2raw += result2;

            // mean2 += MIN((1<<12)-1, c2 * result2 * result2 + c1 * result2 + c0);
            // printf("1: %d, 2: %d\n", mean1, mean2);
        }

        mean1 /= count;
        mean2 /= count;
        mean2raw /= count;

        // printf("mean1: %d, mean2: %d\n", mean1, mean2);

        printf("%d, %d, %d\n", mean1, mean2, mean2raw);
        // printf("%d, %d\n", mean1, mean2);
        // printf("%f\n", mean1);
    }
}
