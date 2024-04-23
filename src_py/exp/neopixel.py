from neopixel import NeoPixel
from machine import Pin, Timer
from time import sleep
# import colorsys

# colorsys.hsv_to_rgb()

# ONE_THIRD = 1.0/3.0
# TWO_THIRD = 2.0/3.0
# ONE_SIXTH = 1.0/6.0

# def hls_to_rgb(h, l, s):
#     if s == 0.0:
#         return l, l, l
#     if l <= 0.5:
#         m2 = l * (1.0+s)
#     else:
#         m2 = l+s-(l*s)
#     m1 = 2.0*l - m2
#     out = (_v(m1, m2, h+ONE_THIRD), _v(m1, m2, h), _v(m1, m2, h-ONE_THIRD))
#     # out = tuple(255*(int)(elem) for elem in out)
#     return out

# def _v(m1, m2, hue):
#     hue = hue % 1.0
#     if hue < ONE_SIXTH:
#         return m1 + (m2-m1)*hue*6.0
#     if hue < 0.5:
#         return m2
#     if hue < TWO_THIRD:
#         return m1 + (m2-m1)*(TWO_THIRD-hue)*6.0
#     return m1

def hsv_to_rgb(h, s, v):
    if s == 0.0:
        return v, v, v
    i = int(h*6.0) # XXX assume int() truncates!
    f = (h*6.0) - i
    p = v*(1.0 - s)
    q = v*(1.0 - s*f)
    t = v*(1.0 - s*(1.0-f))
    i = i%6
    if i == 0:
        return v, t, p
    if i == 1:
        return q, v, p
    if i == 2:
        return p, v, t
    if i == 3:
        return p, q, v
    if i == 4:
        return t, p, v
    if i == 5:
        return v, p, q
    # Cannot get here

def tuple_float_to_int(t):
    return tuple(int(255*elem) for elem in t)

def conv_255_to_1(f):
    return f/255

pin = Pin(16, Pin.OUT)
np = NeoPixel(pin, 1)

# color1 = (255, 0, 0)
# color2 = (0, 255, 0)
# color3 = (0, 0, 255)

color_rgb1 = tuple_float_to_int(hsv_to_rgb(conv_255_to_1(255),1,1))
print(color_rgb1)
color_rgb2 = tuple_float_to_int(hsv_to_rgb(conv_255_to_1(50),1,1))
print(tuple_float_to_int(color_rgb2))
# color_rgb3 = hsv_to_rgb(0.4,1,1)
# print(color_rgb3)
# color_rgb4 = hsv_to_rgb(0.6,1,1)
# print(color_rgb4)

# np[0] = color

while(True):

    # for ii in range(10):
    for i in range(255):
        np.fill(tuple_float_to_int(hsv_to_rgb((conv_255_to_1(i)),1,0.4)))
        np.write()
        print(i)
        sleep(0.1)
        # sleep(0.001)

    # np.fill(color_rgb1)
    # print(color_rgb1)
    # np.write()

    # sleep(1)

    # np.fill(color_rgb2)
    # print(color_rgb2)
    # np.write()

    # sleep(1)

    # # np.fill(color_rgb3)
    # # np.write()

    # # sleep(1)


