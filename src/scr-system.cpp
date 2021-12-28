#include "scr-system.h"

#define SSD1306_SWITCHCAPVCC 0x02

#define REFRESH_DELAY 30
#define SCREEN_HIDE_DELAY 2000

void drawTempNumber(ISsdWrapper *_scrDevice, int temp)
{
    _scrDevice->setCursor(0, 0);
    _scrDevice->println("");
    _scrDevice->setTextSize(3);

    _scrDevice->print("  ");

    if (temp < 100)
    {
        _scrDevice->print(" ");
    }

    if (temp < 10)
    {
        _scrDevice->print(" ");
    }

    _scrDevice->print(temp);
    _scrDevice->print("`F");
}

void ScrSystem::setup()
{
    _scrDevice->begin(SSD1306_SWITCHCAPVCC, 0x3C);
    _scrDevice->clearDisplay();
    _scrDevice->display();
}

void ScrSystem::update(unsigned long time)
{
    if (time - _lastUpdateTime > REFRESH_DELAY)
    {
        _scrDevice->clearDisplay();

        if (time - _state->input.inputButtonTime < SCREEN_HIDE_DELAY ||
            time - _state->input.inputKnobTime < SCREEN_HIDE_DELAY)
        {
            _scrDevice->setCursor(0, 0);
            _scrDevice->setTextSize(1);
            if (_state->connectionStatus)
            {
                _scrDevice->println("heat             cnnt");
            }
            else
            {
                _scrDevice->println("heat");
            }
            _scrDevice->println("");

            if (_state->input.inputButtonTime > _state->input.inputKnobTime)
            {
                _scrDevice->println("AT");

                drawTempNumber(_scrDevice, (int)_state->currentTemp);
            }
            else
            {
                _scrDevice->println("TT");

                drawTempNumber(_scrDevice, (int)_state->targetTemp);
            }
        }

        _scrDevice->display();
    }
}