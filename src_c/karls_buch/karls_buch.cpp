#include <stdio.h>
#include "pico/stdlib.h"

#include "modes.h"

#include "config.h"
#include "abstractModeIdentifier.h"
#include "adcModeIdentifier.h"

#include <iostream>
#include <iomanip>
#include <memory> // Include the memory header

#include "mcp3008.h"
#include "WS2812.hpp"
#include "colorConverter.cpp"

#define LED_PIN 12
#define LED_LENGTH 1


std::unique_ptr<AbstractModeIdentifier> modeIdentifier = std::make_unique<AdcModeIdentifier>();


int main(){
    
    stdio_init_all();

    WS2812 led(LED_PIN, LED_LENGTH, pio0, 0, WS2812::FORMAT_RGB);


    modeIdentifier->Initialize();

    const uint LED_PIN_INTERNAL = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN_INTERNAL);
    gpio_set_dir(LED_PIN_INTERNAL, GPIO_OUT);

    // const uint LED_PIN_1 = 12;
    // gpio_init(LED_PIN_1);
    // gpio_set_dir(LED_PIN_1, GPIO_OUT);
    
    const uint BUTTON_IN_1 = 20;
    gpio_init(BUTTON_IN_1);
    gpio_set_dir(BUTTON_IN_1, GPIO_IN);
    
    const uint BUTTON_IN_2 = 21;
    gpio_init(BUTTON_IN_2);
    gpio_set_dir(BUTTON_IN_2, GPIO_IN);


    bool isButton1Pressed = false;
    bool isButton2Pressed = false;


    Mode mode;

    int full;

    bool isLatchActive = false;


    // hsv hsvColor{0, 1, 0.4};
    // rgb rgbColor;
    
    // while (true)
    // {
    //     sleep_ms(150);
        
    //     if (hsvColor.h < 360)
    //     {
    //         hsvColor.h++;
    //     }
    //     else{
    //         hsvColor.h = 0;
    //     }
        
    //     rgbColor = hsv2rgb(hsvColor);
    //     rgbColor.r *= 255;
    //     rgbColor.g *= 255;
    //     rgbColor.b *= 255;

    //     std::cout << "r, g, b: " + 
    //     std::to_string(rgbColor.r) + ", " +
    //     std::to_string(rgbColor.g) + ", " +
    //     std::to_string(rgbColor.b) << std::endl;
    // }
    

    hsv hsvColor{0, 1, 0.2};
    rgb rgbColor;
    


    while (true){


        // for (int iFade = 8; iFade < 100; iFade = iFade+5){
        //     full = iFade;

        //     for (int i = 0; i < 6; i++) {
        //         for (int iTrans = 0; iTrans < full; iTrans++)
        //         {
        //             if (i == 0) {
        //                 led.fill(WS2812::RGB(full, iTrans, 0));
        //             } else if (i == 1) {
        //                 led.fill(WS2812::RGB(full-iTrans, full, 0));
        //             } else if (i == 2) {
        //                 led.fill(WS2812::RGB(0, full, iTrans));
        //             } else if (i == 3) {
        //                 led.fill(WS2812::RGB(0, full-iTrans, full));
        //             } else if (i == 4) {
        //                 led.fill(WS2812::RGB(iTrans, 0, full));
        //             } else if (i == 5) {
        //                 led.fill(WS2812::RGB(full, 0, full-iTrans));
        //             }
        //             led.show();
        //             sleep_ms(125);
        //         }     
        //     }
        // }

        // sleep_ms(300);



        sleep_ms(10);
        
        // if (hsvColor.h < 360)
        // {
        //     hsvColor.h++;
        // }
        // else{
        //     hsvColor.h = 0;
        // }
        //// hsvColor.h = 285;
        
        // rgbColor = hsv2rgb(hsvColor);
        // rgbColor.r *= 255;
        // rgbColor.g *= 255;
        // rgbColor.b *= 255;

        // std::cout << "r, g, b: " + 
        // std::to_string(rgbColor.r) + ", " +
        // std::to_string(rgbColor.g) + ", " +
        // std::to_string(rgbColor.b) << std::endl;


        // led.fill(WS2812::RGB(rgbColor.r, rgbColor.g, rgbColor.b));
        // led.show();






        modeIdentifier->PrintState();
        mode = modeIdentifier->IdentifyMode();

        isButton1Pressed = gpio_get(BUTTON_IN_1);
        isButton2Pressed = gpio_get(BUTTON_IN_2);
        
        if (mode == Mode::WIRE){
            if (isButton1Pressed){
                // gpio_put(LED_PIN_INTERNAL, 1);
                led.fill(WS2812::RGB(100, 0, 0));
            }
            else{
                // gpio_put(LED_PIN_INTERNAL, 0);
                led.fill(WS2812::RGB(0, 0, 0));
            }
        }
        if (mode == Mode::NOT){
            if (isButton1Pressed){
                // gpio_put(LED_PIN_INTERNAL, 1);
                led.fill(WS2812::RGB(0, 0, 0));
            }
            else{
                // gpio_put(LED_PIN_INTERNAL, 0);
                led.fill(WS2812::RGB(100, 50, 0));
            }
        }
        if (mode == Mode::AND){
            if (isButton1Pressed && isButton2Pressed){
                // gpio_put(LED_PIN_INTERNAL, 1);
                led.fill(WS2812::RGB(100, 100, 0));
            }
            else{
                // gpio_put(LED_PIN_INTERNAL, 0);
                led.fill(WS2812::RGB(0, 0, 0));
            }
        }
        else if (mode == Mode::OR){
            if (isButton1Pressed || isButton2Pressed){
                // gpio_put(LED_PIN_INTERNAL, 1);
                led.fill(WS2812::RGB(0, 100, 0));
            }
            else{
                // gpio_put(LED_PIN_INTERNAL, 0);
                led.fill(WS2812::RGB(0, 0, 0));
            }
        }
        else if (mode == Mode::XOR){
            if (isButton1Pressed != isButton2Pressed){
                // gpio_put(LED_PIN_INTERNAL, 1);
                led.fill(WS2812::RGB(0, 75, 100));
            }
            else{
                // gpio_put(LED_PIN_INTERNAL, 0);
                led.fill(WS2812::RGB(0, 0, 0));
            }
        }
        if (mode == Mode::LATCH){
            if (isButton1Pressed){
                isLatchActive = true;
            }
            if (isButton2Pressed){
                isLatchActive = false;
            }
            if (isLatchActive){
                // gpio_put(LED_PIN_INTERNAL, 1);
                led.fill(WS2812::RGB(100, 0, 100));
            }
            else{
                // gpio_put(LED_PIN_INTERNAL, 0);
                led.fill(WS2812::RGB(0, 0, 0));
            }
        }
        led.show();
    }

    return 0;
}


// int main()
// {
//     stdio_init_all();

//     // SPI initialisation. This example will use SPI at 1MHz.
//     spi_init(SPI_PORT, 1000*1000);
//     gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
//     gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
//     gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
//     gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
//     // Chip select is active-low, so we'll initialise it to a driven-high state
//     gpio_set_dir(PIN_CS, GPIO_OUT);
//     gpio_put(PIN_CS, 1);
//     // For more examples of SPI use see https://github.com/raspberrypi/pico-examples/tree/master/spi

//     while (true) {
//         printf("Hello, world!\n");
//         sleep_ms(1000);
//     }
// }
