from machine import Pin
from time import sleep
import neopixel
import json

with open("config.json") as json_file:
    json_data = json.load(json_file)

neopixel_pin = Pin(json_data["neopixel"]["output_pin"], Pin.OUT)

sensor1_pin = Pin(2, Pin.IN, Pin.PULL_DOWN)
sensor2_pin = Pin(3, Pin.IN, Pin.PULL_DOWN)
sensor3_pin = Pin(4, Pin.IN, Pin.PULL_DOWN)
sensor4_pin = Pin(5, Pin.IN, Pin.PULL_DOWN)

button1_pin = Pin(14, Pin.IN, Pin.PULL_DOWN)
button2_pin = Pin(15, Pin.IN, Pin.PULL_DOWN)

cycle_time = 1e-3

output = 0

easter_egg_counter = 0

while True:

    # if():
    #     easter_egg_counter += 1
    #     if(easter_egg_counter > 3000):
    #         while(sensor1_pin.value() == 0 && ...)
    #             easter_egg_mode()
    # else:
    #     easter_egg_counter = 0

    if(sensor1_pin.value() == 1 and
       sensor2_pin.value() == 0 and
       sensor3_pin.value() == 0 and
       sensor4_pin.value() == 0):
        output = button1_pin.value() and button2_pin.value()
    elif(sensor1_pin.value() == 1 and
       sensor2_pin.value() == 1 and
       sensor3_pin.value() == 0 and
       sensor4_pin.value() == 0):
        output = button1_pin.value() or button2_pin.value()
    elif(sensor1_pin.value() == 1 and
       sensor2_pin.value() == 1 and
       sensor3_pin.value() == 1 and
       sensor4_pin.value() == 0):
        output = button1_pin.value() ^ button2_pin.value()
    elif(sensor1_pin.value() == 1 and
       sensor2_pin.value() == 1 and
       sensor3_pin.value() == 1 and
       sensor4_pin.value() == 1):
        if button1_pin.value():
            output = 1
        if button2_pin.value():
            output = 0
    else:
        output = 0
        
    neopixel_pin.value(output)

    sleep(cycle_time)


# def easter_egg_mode():
#     pass