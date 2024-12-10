#include "adcModeIdentifier.h"

#include "hardware/spi.h"

#include "mcp3008.h"

#include <iostream>
#include <iomanip>
#include <pico/stdlib.h>

#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19

#define THRESHOLD 15

AdcModeIdentifier::AdcModeIdentifier() {}

void AdcModeIdentifier::Initialize() {
    MCP3008_Config mcp3008_config;
    // MCP3008 mcp3008();
    mcp3008.init(mcp3008_config);
}

Mode AdcModeIdentifier::IdentifyMode() {
    Mode mode;

    if (mcp3008.adc_read_channel(0) < THRESHOLD && 
        mcp3008.adc_read_channel(1) < THRESHOLD &&
        mcp3008.adc_read_channel(2) < THRESHOLD &&
        mcp3008.adc_read_channel(3) < THRESHOLD &&
        mcp3008.adc_read_channel(4) < THRESHOLD) {
        mode = Mode::WIRE;
    }
    if (mcp3008.adc_read_channel(0) > THRESHOLD && 
        mcp3008.adc_read_channel(1) < THRESHOLD &&
        mcp3008.adc_read_channel(2) < THRESHOLD &&
        mcp3008.adc_read_channel(3) < THRESHOLD &&
        mcp3008.adc_read_channel(4) < THRESHOLD) {
        mode = Mode::NOT;
    }
    if (mcp3008.adc_read_channel(0) > THRESHOLD && 
        mcp3008.adc_read_channel(1) > THRESHOLD &&
        mcp3008.adc_read_channel(2) < THRESHOLD &&
        mcp3008.adc_read_channel(3) < THRESHOLD &&
        mcp3008.adc_read_channel(4) < THRESHOLD) {
        mode = Mode::AND;
    }
    if (mcp3008.adc_read_channel(0) > THRESHOLD && 
        mcp3008.adc_read_channel(1) > THRESHOLD &&
        mcp3008.adc_read_channel(2) > THRESHOLD &&
        mcp3008.adc_read_channel(3) < THRESHOLD &&
        mcp3008.adc_read_channel(4) < THRESHOLD) {
        mode = Mode::OR;
    }
    if (mcp3008.adc_read_channel(0) > THRESHOLD && 
        mcp3008.adc_read_channel(1) > THRESHOLD &&
        mcp3008.adc_read_channel(2) > THRESHOLD &&
        mcp3008.adc_read_channel(3) > THRESHOLD &&
        mcp3008.adc_read_channel(4) < THRESHOLD) {
        mode = Mode::XOR;
    }
    if (mcp3008.adc_read_channel(0) > THRESHOLD && 
        mcp3008.adc_read_channel(1) > THRESHOLD &&
        mcp3008.adc_read_channel(2) > THRESHOLD &&
        mcp3008.adc_read_channel(3) > THRESHOLD &&
        mcp3008.adc_read_channel(4) > THRESHOLD) {
        mode = Mode::LATCH;
    }


    return mode;
}

void AdcModeIdentifier::PrintState() {
    // std::cout << "ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7" << std::endl;
    sleep_ms(100);
    for (uint8_t channel = 0; channel < MCP3008::NUM_CHANNELS; channel++) {
        std::cout << std::fixed << std::setw(4) << mcp3008.adc_read_channel(channel);
        if(channel < MCP3008::NUM_CHANNELS - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;

    // std::cout << std::endl;
}