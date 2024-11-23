#include "pico/stdlib.h"
#include "stdio.h"

// bool global_flag = false;

// void gpio_callback(uint gpio, uint32_t events){
//     global_flag = true;
// }


int main(){

    stdio_init_all();

    const uint LED_PIN_INTERNAL = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN_INTERNAL);
    gpio_set_dir(LED_PIN_INTERNAL, GPIO_OUT);

    // const uint LED_PIN_1 = 15;
    // gpio_init(LED_PIN_1);
    // gpio_set_dir(LED_PIN_1, GPIO_OUT);
    
    const uint BUTTON_IN_1 = 14;
    gpio_init(BUTTON_IN_1);
    gpio_set_dir(BUTTON_IN_1, GPIO_IN);
    
    const uint BUTTON_IN_2 = 15;
    gpio_init(BUTTON_IN_2);
    gpio_set_dir(BUTTON_IN_2, GPIO_IN);

    const uint SENSOR_IN_1 = 2;
    gpio_init(SENSOR_IN_1);
    gpio_set_dir(SENSOR_IN_1, GPIO_IN);
    const uint SENSOR_IN_2 = 3;
    gpio_init(SENSOR_IN_2);
    gpio_set_dir(SENSOR_IN_2, GPIO_IN);
    const uint SENSOR_IN_3 = 4;
    gpio_init(SENSOR_IN_3);
    gpio_set_dir(SENSOR_IN_3, GPIO_IN);
    const uint SENSOR_IN_4 = 5;
    gpio_init(SENSOR_IN_4);
    gpio_set_dir(SENSOR_IN_4, GPIO_IN);

    // const uint IRQ_IN = 0;
    // gpio_init(IRQ_IN);
    // gpio_set_dir(IRQ_IN, GPIO_IN);

    bool is_button1_pressed = false;
    bool is_button2_pressed = false;

    bool is_sensor1_in_on = false;
    bool is_sensor2_in_on = false;
    bool is_sensor3_in_on = false;
    bool is_sensor4_in_on = false;

    // gpio_set_irq_enabled_with_callback(2, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &gpio_callback);

    while (true)
    {
        printf("hi there \n");

            if (is_button1_pressed || is_button2_pressed)
            {
                gpio_put(LED_PIN_INTERNAL, 1);
                gpio_put(LED_PIN_INTERNAL, 1);
            }
            else{
                gpio_put(LED_PIN_INTERNAL, 0);
                gpio_put(LED_PIN_INTERNAL, 0);
            }

        // if (global_flag)
        // {
        //     gpio_put(LED_PIN_INTERNAL, 1);
        //     continue;
        // }
        

        is_button1_pressed = gpio_get(BUTTON_IN_1);
        is_button2_pressed = gpio_get(BUTTON_IN_2);
        
        is_sensor1_in_on = gpio_get(SENSOR_IN_1);
        is_sensor2_in_on = gpio_get(SENSOR_IN_2);
        is_sensor3_in_on = gpio_get(SENSOR_IN_3);
        is_sensor4_in_on = gpio_get(SENSOR_IN_4);
        
        if (is_sensor1_in_on)
        {
            if (is_button1_pressed && is_button2_pressed)
            {
                gpio_put(LED_PIN_INTERNAL, 1);
                gpio_put(LED_PIN_INTERNAL, 1);
            }
            else{
                gpio_put(LED_PIN_INTERNAL, 0);
                gpio_put(LED_PIN_INTERNAL, 0);
            }
        }
        if (is_sensor2_in_on)
        {
            if (is_button1_pressed || is_button2_pressed)
            {
                gpio_put(LED_PIN_INTERNAL, 1);
                gpio_put(LED_PIN_INTERNAL, 1);
            }
            else{
                gpio_put(LED_PIN_INTERNAL, 0);
                gpio_put(LED_PIN_INTERNAL, 0);
            }
        }
        if (is_sensor3_in_on)
        {
            if (is_button1_pressed ^ is_button2_pressed)
            {
                gpio_put(LED_PIN_INTERNAL, 1);
                gpio_put(LED_PIN_INTERNAL, 1);
            }
            else{
                gpio_put(LED_PIN_INTERNAL, 0);
                gpio_put(LED_PIN_INTERNAL, 0);
            }
        }
        if (is_sensor4_in_on)
        {
            if (is_button1_pressed)
            {
                gpio_put(LED_PIN_INTERNAL, 1);
                gpio_put(LED_PIN_INTERNAL, 1);
            }
            if (is_button2_pressed)
            {
                gpio_put(LED_PIN_INTERNAL, 0);
                gpio_put(LED_PIN_INTERNAL, 0);
            }
        }
        
    }
    
}
