#include <stdio.h>
#include "pico/stdlib.h"

#include <iostream>
#include <iomanip>
#include <memory> // Include the memory header

#include "abstractModeIdentifier.h"
#include "adcModeIdentifier.h"

#include "mcp3008.h"
#include "WS2812.hpp"
#include "colorConverter.cpp"

#include "modes.h"
#include "easterEggStates.h"

#include "config.h"


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

    const uint BUTTON_IN_1 = 20;
    gpio_init(BUTTON_IN_1);
    gpio_set_dir(BUTTON_IN_1, GPIO_IN);
    
    const uint BUTTON_IN_2 = 21;
    gpio_init(BUTTON_IN_2);
    gpio_set_dir(BUTTON_IN_2, GPIO_IN);


    bool isButton1Pressed = false;
    bool isButton2Pressed = false;


    Mode mode;

    bool isLatchActive = false;

    int delayMs = 5;

    EeState eeState = EeState::IDLE;
    void easterEgg(WS2812 led);
    int eeTimerStartVal = 0;
    int eeTimer;

    int value = 60;

    while (true){

        sleep_ms(delayMs);
        

        modeIdentifier->PrintState();
        mode = modeIdentifier->IdentifyMode();

        isButton1Pressed = gpio_get(BUTTON_IN_1);
        isButton2Pressed = gpio_get(BUTTON_IN_2);
        
        if (mode == Mode::WIRE){
            if (isButton1Pressed){
                // gpio_put(LED_PIN_INTERNAL, 1);
                led.fill(WS2812::RGB(value, 0, 0)); // red
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
                led.fill(WS2812::RGB(value, value, 0)); // yellow
            }
        }
        if (mode == Mode::AND){
            if (isButton1Pressed && isButton2Pressed){
                // gpio_put(LED_PIN_INTERNAL, 1);
                led.fill(WS2812::RGB(0, value, 0)); // green
            }
            else{
                // gpio_put(LED_PIN_INTERNAL, 0);
                led.fill(WS2812::RGB(0, 0, 0));
            }
        }
        else if (mode == Mode::OR){
            if (isButton1Pressed || isButton2Pressed){
                // gpio_put(LED_PIN_INTERNAL, 1);
                led.fill(WS2812::RGB(0, value, value)); // cyan
            }
            else{
                // gpio_put(LED_PIN_INTERNAL, 0);
                led.fill(WS2812::RGB(0, 0, 0));
            }
        }
        else if (mode == Mode::XOR){
            if (isButton1Pressed != isButton2Pressed){
                // gpio_put(LED_PIN_INTERNAL, 1);
                led.fill(WS2812::RGB(0, 0, value)); // blue
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
                led.fill(WS2812::RGB(value, 0, value)); // magenta
            }
            else{
                // gpio_put(LED_PIN_INTERNAL, 0);
                led.fill(WS2812::RGB(0, 0, 0));
            }
        }
        led.show();


        switch (eeState)
        {
        case EeState::IDLE:
            // std::cout << "IDLE" << std::endl;
            eeTimer = eeTimerStartVal;
            if (isButton1Pressed && isButton2Pressed)
            {
                eeState = EeState::BIN3;
            }
            break;
        case EeState::BIN3:
            // std::cout << "BIN3" << std::endl;
            if (isButton1Pressed && isButton2Pressed)
            {
                eeState = EeState::BIN3;
            }
            else if (isButton2Pressed)
            {
                eeState = EeState::BIN2;
            }
            else
            {
                eeState = EeState::IDLE;
            }
            break;
        case EeState::BIN2:
            // std::cout << "BIN2" << std::endl;
            if (isButton2Pressed && !isButton1Pressed)
            {
                eeState = EeState::BIN2;
            }
            if (!isButton1Pressed && !isButton2Pressed)
            {
                eeState = EeState::BIN2_0;
            }
            if (isButton1Pressed && isButton2Pressed)
            {
                eeState = EeState::BIN2_3;
            }
            if (isButton1Pressed && !isButton2Pressed)
            {
                eeState = EeState::BIN1;
            }
            break;
        case EeState::BIN2_0:
            // std::cout << "BIN2_0" << std::endl;
            if (!isButton1Pressed && !isButton2Pressed)
            {
                eeTimer--;
            }
            else if (!isButton1Pressed && isButton2Pressed)
            {
                eeState = EeState::IDLE;
            }
            else if (isButton1Pressed && !isButton2Pressed)
            {
                eeState = EeState::BIN1;
            }
            else{
                eeState = IDLE;
            }
            if (eeTimer <= 0)
            {
                eeState = EeState::IDLE;
            }
            break;
        case EeState::BIN2_3:
            // std::cout << "BIN2_3" << std::endl;
            if (isButton1Pressed && isButton2Pressed)
            {
                eeTimer--;
            }
            else if (isButton1Pressed && !isButton2Pressed)
            {
                eeState = EeState::BIN1;
            }
            else
            {
                eeState = EeState::IDLE;
            }
            if (eeTimer <= 0)
            {
                eeState = EeState::IDLE;
            }
            break;
        case EeState::BIN1:
            // std::cout << "BIN1" << std::endl;
            if (isButton1Pressed && !isButton2Pressed)
            {
                eeState = EeState::BIN1;
            }
            else if (!isButton1Pressed && !isButton2Pressed)
            {
                eeState = EeState::EASTER;
            }
            else
            {
                eeState = EeState::IDLE;
            }
            break;
        case EeState::EASTER:
            // std::cout << "EASTER!" << std::endl;
            easterEgg(led);
            eeState = EeState::IDLE;
            break;
        default:
            eeState = EeState::IDLE;
            break;
        }

    }
    return 0;
}


void easterEgg(WS2812 led){
    
    hsv hsvColor{0, 1, 0.4};
    rgb rgbColor;
    
    for (size_t i = 0; i < 1000; i++)
    {
        
        if (hsvColor.h < 360)
        {
            hsvColor.h++;
        }
        else{
            hsvColor.h = 0;
        }
        // hsvColor.h = 285;

        rgbColor = hsv2rgb(hsvColor);
        rgbColor.r *= 255;
        rgbColor.g *= 255;
        rgbColor.b *= 255;

        std::cout << "r, g, b: " + 
        std::to_string(rgbColor.r) + ", " +
        std::to_string(rgbColor.g) + ", " +
        std::to_string(rgbColor.b) << std::endl;


        led.fill(WS2812::RGB(rgbColor.r, rgbColor.g, rgbColor.b));
        led.show();
    }
}
