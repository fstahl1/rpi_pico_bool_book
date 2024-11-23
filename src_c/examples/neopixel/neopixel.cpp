
#include <stdio.h>
#include <cmath>
#include "pico/stdlib.h"
#include "WS2812.hpp"

#define LED_PIN 13
#define LED_LENGTH 1

int main()
{
    stdio_init_all();

    WS2812 led(LED_PIN, LED_LENGTH, pio0, 0, WS2812::FORMAT_RGB);


    int full = 0;

    while (true) {

        for (int iFade = 8; iFade < 100; iFade = iFade+5)
        {
            full = iFade;

            for (int i = 0; i < 6; i++) {
                for (int iTrans = 0; iTrans < full; iTrans++)
                {
                    if (i == 0) {
                        led.fill(WS2812::RGB(full, iTrans, 0));
                    } else if (i == 1) {
                        led.fill(WS2812::RGB(full-iTrans, full, 0));
                    } else if (i == 2) {
                        led.fill(WS2812::RGB(0, full, iTrans));
                    } else if (i == 3) {
                        led.fill(WS2812::RGB(0, full-iTrans, full));
                    } else if (i == 4) {
                        led.fill(WS2812::RGB(iTrans, 0, full));
                    } else if (i == 5) {
                        led.fill(WS2812::RGB(full, 0, full-iTrans));
                    }
                    led.show();
                    sleep_ms(125);
                }     
            }
        }
        

        // for (int iDim = 0; iDim < 64; iDim=iDim+5)
        // {
        //     for (int i = 0; i < 11; i++) {
        //         if (i == 0) {
        //             led.fill(WS2812::RGB(iDim, iDim/2, 0));
        //         } else if (i == 1) {
        //             led.fill(WS2812::RGB(iDim, iDim, 0));
        //         } else if (i == 2) {
        //             led.fill(WS2812::RGB(iDim/2, iDim, 0));
        //         } else if (i == 3) {
        //             led.fill(WS2812::RGB(0, iDim, 0));
        //         } else if (i == 4) {
        //             led.fill(WS2812::RGB(0, iDim, iDim/2));
        //         } else if (i == 5) {
        //             led.fill(WS2812::RGB(0, iDim, iDim));
        //         } else if (i == 6) {
        //             led.fill(WS2812::RGB(0, iDim/2, iDim));
        //         } else if (i == 7) {
        //             led.fill(WS2812::RGB(0, 0, iDim));
        //         } else if (i == 8) {
        //             led.fill(WS2812::RGB(iDim/2, 0, iDim));
        //         } else if (i == 9) {
        //             led.fill(WS2812::RGB(iDim, 0, iDim));
        //         } else if (i == 10) {
        //             led.fill(WS2812::RGB(iDim, 0, iDim/2));
        //         } else {
        //             led.fill(WS2812::RGB(iDim, 0, 0));
        //         }
        //         led.show();
        //         sleep_ms(250);
        //     }        

        // }
        
    }



    // // 0. Initialize LED strip
    // printf("0. Initialize LED strip");
    // WS2812 ledStrip(
    //     LED_PIN,            // Data line is connected to pin 0. (GP0)
    //     LED_LENGTH,         // Strip is 6 LEDs long.
    //     pio0,               // Use PIO 0 for creating the state machine.
    //     0,                  // Index of the state machine that will be created for controlling the LED strip
    //                         // You can have 4 state machines per PIO-Block up to 8 overall.
    //                         // See Chapter 3 in: https://datasheets.raspberrypi.org/rp2040/rp2040-datasheet.pdf
    //     WS2812::FORMAT_GRB  // Pixel format used by the LED strip
    // );

    // // 1. Set all LEDs to red!
    // printf("1. Set all LEDs to red!");
    // ledStrip.fill( WS2812::RGB(255, 0, 0) );
    // ledStrip.show();
    // sleep_ms(1000);

    // // 2. Set all LEDs to green!
    // printf("2. Set all LEDs to green!");
    // ledStrip.fill( WS2812::RGB(0, 255, 0) );
    // ledStrip.show();
    // sleep_ms(1000);

    // // 3. Set all LEDs to blue!
    // printf("3. Set all LEDs to blue!");
    // ledStrip.fill( WS2812::RGB(0, 0, 255) );
    // ledStrip.show();
    // sleep_ms(1000);

    // // 4. Set half LEDs to red and half to blue!
    // printf("4. Set half LEDs to red and half to blue!");
    // ledStrip.fill( WS2812::RGB(255, 0, 0), 0, LED_LENGTH / 2 );
    // ledStrip.fill( WS2812::RGB(0, 0, 255), LED_LENGTH / 2 );
    // ledStrip.show();
    // sleep_ms(1000);

    // // 5. Do some fancy animation
    // printf("5. Do some fancy animation");
    // while (true) {
    //     // Pick a random color
    //     uint32_t color = (uint32_t)rand();
    //     // Pick a random direction
    //     int8_t dir = (rand() & 1 ? 1 : -1);
    //     // Setup start and end offsets for the loop
    //     uint8_t start = (dir > 0 ? 0 : LED_LENGTH);
    //     uint8_t end = (dir > 0 ? LED_LENGTH : 0);
    //     for (uint8_t ledIndex = start; ledIndex != end; ledIndex += dir) {
    //         ledStrip.setPixelColor(ledIndex, color);
    //         ledStrip.show();
    //         sleep_ms(50);
    //     }
    // }

    return 0;
}





// #include <stdio.h>
// #include "pico/stdlib.h"
// #include "hardware/pio.h"
// #include "hardware/clocks.h"
// #include "ws2812.pio.h"

// #define IS_RGBW false
// #define NUM_PIXELS 1
// #define WS2812_PIN 28

// static inline void put_pixel(uint32_t pixel_grb) {
//     pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
// }

// static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
//     return ((uint32_t)(r) << 8) |
//            ((uint32_t)(g) << 16) |
//            (uint32_t)(b);
// }

// int main() {
//     stdio_init_all();
    
//     PIO pio = pio0;
//     int sm = 0;
//     uint offset = pio_add_program(pio, &ws2812_program);

//     ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

//     while (1) {
//         // Cycle through red, green, and blue
//         put_pixel(urgb_u32(255, 0, 0));  // Red
//         sleep_ms(1000);
//         put_pixel(urgb_u32(0, 255, 0));  // Green
//         sleep_ms(1000);
//         put_pixel(urgb_u32(0, 0, 255));  // Blue
//         sleep_ms(1000);
//     }
// }



// #include <stdio.h>
// #include "pico/stdlib.h"
// #include "hardware/pio.h"

// #include "blink.pio.h"

// void blink_pin_forever(PIO pio, uint sm, uint offset, uint pin, uint freq) {
//     blink_program_init(pio, sm, offset, pin);
//     pio_sm_set_enabled(pio, sm, true);

//     printf("Blinking pin %d at %d Hz\n", pin, freq);

//     // PIO counter program takes 3 more cycles in total than we pass as
//     // input (wait for n + 1; mov; jmp)
//     pio->txf[sm] = (125000000 / (2 * freq)) - 3;
// }



// int main()
// {
//     stdio_init_all();

//     // PIO Blinking example
//     PIO pio = pio0;
//     uint offset = pio_add_program(pio, &blink_program);
//     printf("Loaded program at %d\n", offset);
    
//     #ifdef PICO_DEFAULT_LED_PIN
//     blink_pin_forever(pio, 0, offset, PICO_DEFAULT_LED_PIN, 3);
//     #else
//     blink_pin_forever(pio, 0, offset, 6, 3);
//     #endif
//     // For more pio examples see https://github.com/raspberrypi/pico-examples/tree/master/pio

//     while (true) {
//         printf("Hello, world!\n");
//         sleep_ms(1000);
//     }
// }
