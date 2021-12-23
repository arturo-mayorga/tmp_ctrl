#!/bin/bash

# for screen display
arduino-cli lib install "Adafruit GFX Library"
arduino-cli lib install "Adafruit SSD1306"

# for temperature sensor
arduino-cli lib install OneWire
arduino-cli lib install DallasTemperature
