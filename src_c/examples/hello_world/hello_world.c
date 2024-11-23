#include <stdio.h>
#include "pico/stdlib.h"


int main()
{
    stdio_init_all();

    while (true) {
        printf("Hello, world 1!\n");
        sleep_ms(1000);
        printf("Hello, world 2!\n");
        sleep_ms(1000);
    }
}
