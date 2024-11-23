#include <stdio.h>
#include <iostream>
#include <iomanip>

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "mcp3008.h"

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19

using std::cout;
using std::endl;

int main(){
    stdio_init_all();
    sleep_ms(1000);

    cout << endl
         << "***********************" << endl
         << "*** MCP3008 Example ***" << endl
         << "***********************" << endl
         << endl;


    cout << "Reading ADC values via SPI..." << endl;
    
    MCP3008_Config mcp3008_config;
    // mcp3008_config.spi_port = PICO_DEFAULT_SPI_INSTANCE;
    mcp3008_config.spi_port = spi0;
    
    cout << "PIN_MISO on GPIO" << mcp3008_config.spi_rx_gpio << endl;
    cout << "PIN_CS   on GPIO" << mcp3008_config.spi_cs_gpio   << endl;
    cout << "PIN_SCK  on GPIO" << mcp3008_config.spi_sck_gpio  << endl;
    cout << "PIN_MOSI on GPIO" << mcp3008_config.spi_tx_gpio << endl;

    MCP3008 mcp3008(mcp3008_config);

    cout << "ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7" << endl;

    while (true) {

        // sleep_ms(1000);

        for (uint8_t channel = 0; channel < MCP3008::NUM_CHANNELS; channel++) {

            cout << std::fixed << std::setw(4)
                << mcp3008.adc_read_channel(channel);
            
            if(channel < MCP3008::NUM_CHANNELS - 1) {
                cout << ", ";
            }
        }
        cout << endl;

        sleep_ms(500);
    }

    return 0;
}

// int main()
// {
    // stdio_init_all();

    // // SPI initialisation. This example will use SPI at 1MHz.
    // spi_init(SPI_PORT, 1000*1000);
    // gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    // gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
    // gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    // gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    // // Chip select is active-low, so we'll initialise it to a driven-high state
    // gpio_set_dir(PIN_CS, GPIO_OUT);
    // gpio_put(PIN_CS, 1);
    // // For more examples of SPI use see https://github.com/raspberrypi/pico-examples/tree/master/spi

    // while (true) {
    //     printf("Hello, world!\n");
    //     sleep_ms(1000);
    // }
// }
