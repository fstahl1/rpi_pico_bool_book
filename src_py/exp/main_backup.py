from machine import Pin
from time import sleep

led_pin = Pin("LED", Pin.OUT)

sensor1_pin = Pin(2, Pin.IN, Pin.PULL_DOWN)
sensor2_pin = Pin(3, Pin.IN, Pin.PULL_DOWN)
sensor3_pin = Pin(4, Pin.IN, Pin.PULL_DOWN)
sensor4_pin = Pin(5, Pin.IN, Pin.PULL_DOWN)

button1_pin = Pin(14, Pin.IN, Pin.PULL_DOWN)
button2_pin = Pin(15, Pin.IN, Pin.PULL_DOWN)

output = 0

while True:

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
        
    led_pin.value(output)
