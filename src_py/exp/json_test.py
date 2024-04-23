import json

with open("config.json") as json_file:
    config = json.load(json_file)

print(config["neopixel"]["rgb_color_page1"])