# import main
from machine import Pin, Timer


led = Pin("LED", Pin.OUT)

def blink():   
    tim = Timer()
    def tick(timer):
        global led
        led.toggle()
    tim.init(freq=10, mode=Timer.PERIODIC, callback=tick)


def fun():
    print("abc")


