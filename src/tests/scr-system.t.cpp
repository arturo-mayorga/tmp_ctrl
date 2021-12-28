#include <gtest/gtest.h>
#include "../app-state.h"
#include "../scr-system.h"
#include "../i-ssd-wrapper.h"

#include <vector>
#include <string>
#include <string.h>

#define SCR_R 4
#define SCR_C 21

class SsdWrapperTestImpl : public ISsdWrapper
{
private:
    std::vector<std::string> _log;
    int _currentTextSize = 1;
    int _currentTextColor = 0;
    int _cX = -1;
    int _cY = -1;
    char _scrTBuf[SCR_R][SCR_C];

public:
    virtual bool begin(uint8_t switchvcc, uint8_t i2caddr)
    {
        _log.push_back("begin");
        return true;
    }

    virtual void clearDisplay()
    {
        for (int r = 0; r < SCR_R; ++r)
        {
            for (int c = 0; c < SCR_C; ++c)
            {
                _scrTBuf[r][c] = ' ';
            }
        }
    }

    virtual void setTextSize(uint8_t s)
    {
        _currentTextSize = s;
    }

    virtual void setTextColor(uint16_t c)
    {
        _currentTextColor = c;
    }

    virtual void setCursor(int16_t x, int16_t y)
    {
        if (x == 0 && y == 0)
        {
            _cX = 0;
            _cY = 0;
        }
        else
        {
        }
    }

    virtual void println(const char *str)
    {
        print(str);
        _ln();
    }

    virtual void print(const char *str)
    {
        size_t len = strlen(str);

        for (size_t i = 0; i < len; ++i)
        {
            _print(str[i]);
        }
    }

    virtual void print(uint16_t v)
    {

        char buf[128];
        snprintf(buf, 128, "%d", v);
        print(buf);
    }

    virtual void display()
    {
    }

    void assertLogContents(std::vector<std::string> &inLog)
    {
        EXPECT_EQ(_log.size(), inLog.size());

        for (int i = 0; i < _log.size(); ++i)
        {
            EXPECT_STREQ(inLog[i].c_str(), _log[i].c_str());
        }
    }

    void assertScreen(const char *s1, const char *s2, const char *s3, const char *s4)
    {
        printf("---------------------\n");
        for (int r = 0; r < SCR_R; ++r)
        {
            for (int c = 0; c < SCR_C; ++c)
            {
                printf("%c", _scrTBuf[r][c]);
                // printf("t");
            }

            printf("|\n");
        }
        printf("---------------------\n");

        printf("\n");

        EXPECT_EQ(strlen(s1), SCR_C);
        EXPECT_EQ(strlen(s2), SCR_C);
        EXPECT_EQ(strlen(s3), SCR_C);
        EXPECT_EQ(strlen(s4), SCR_C);

        for (int i = 0; i < SCR_C; ++i)
        {
            EXPECT_EQ(_scrTBuf[0][i], s1[i]);
            EXPECT_EQ(_scrTBuf[1][i], s2[i]);
            EXPECT_EQ(_scrTBuf[2][i], s3[i]);
            EXPECT_EQ(_scrTBuf[3][i], s4[i]);
        }
    }

private:
    void _ln()
    {
        _cX = 0;
        _cY += _currentTextSize;
    }

    void _print(char c)
    {
        if (_cX + _currentTextSize - 1 <= SCR_C &&
            _cY + _currentTextSize - 1 <= SCR_R)
        {
            if (' ' != c)
            {
                if (_scrTBuf[_cY][_cX] != ' ')
                {
                    c = (char)'█'; // notify overdraw
                }

                _scrTBuf[_cY][_cX] = c;

                for (int i = 0; i < _currentTextSize; ++i)
                {
                    for (int j = 0; j < _currentTextSize; ++j)
                    {
                        if (0 == i)
                        {
                            if (0 != j)
                            {
                                _scrTBuf[_cY + i][_cX + j] = '<';
                            }
                        }
                        else
                        {
                            _scrTBuf[_cY + i][_cX + j] = '^';
                        }
                    }
                }
            }

            _cX += _currentTextSize;
        }
    }
};

TEST(ScrSystem, MockChecker)
{
    SsdWrapperTestImpl device;

    device.clearDisplay();
    device.assertScreen(
        "                     ",
        "                     ",
        "                     ",
        "                     ");

    device.setCursor(0, 0);
    device.setTextSize(1);
    device.println("abc");
    device.assertScreen(
        "abc                  ",
        "                     ",
        "                     ",
        "                     ");

    device.clearDisplay();
    device.setCursor(0, 0);
    device.setTextSize(2);
    device.println("abc");
    device.assertScreen(
        "a<b<c<               ",
        "^^^^^^               ",
        "                     ",
        "                     ");

    device.clearDisplay();
    device.setCursor(0, 0);
    device.setTextSize(3);
    device.println("abc");
    device.assertScreen(
        "a<<b<<c<<            ",
        "^^^^^^^^^            ",
        "^^^^^^^^^            ",
        "                     ");

    device.clearDisplay();
    device.setCursor(0, 0);
    device.setTextSize(3);
    device.print(1234);
    device.assertScreen(
        "1<<2<<3<<4<<         ",
        "^^^^^^^^^^^^         ",
        "^^^^^^^^^^^^         ",
        "                     ");

    device.clearDisplay();
    device.setCursor(0, 0);
    device.setTextSize(3);
    device.println("abc");
    device.setTextSize(1);
    device.println("def");
    device.assertScreen(
        "a<<b<<c<<            ",
        "^^^^^^^^^            ",
        "^^^^^^^^^            ",
        "def                  ");
}

TEST(ScrSystem, NoInputNoVideo)
{
    SsdWrapperTestImpl device;
    AppState state;
    ScrSystem scrSystem(&state, &device);

    std::vector<std::string> log;

    scrSystem.setup();
    log.push_back("begin");
    device.assertLogContents(log);

    scrSystem.update(3000);
    device.assertScreen(
        "                     ",
        "                     ",
        "                     ",
        "                     ");

    scrSystem.update(3010);
    device.assertScreen(
        "                     ",
        "                     ",
        "                     ",
        "                     ");

    scrSystem.update(3100);
    device.assertScreen(
        "                     ",
        "                     ",
        "                     ",
        "                     ");

    scrSystem.update(4000);
    device.assertScreen(
        "                     ",
        "                     ",
        "                     ",
        "                     ");

    scrSystem.update(8000);
    device.assertScreen(
        "                     ",
        "                     ",
        "                     ",
        "                     ");
}

TEST(ScrSystem, ShowActualTempAndHide)
{
    SsdWrapperTestImpl device;
    AppState state;
    ScrSystem scrSystem(&state, &device);

    std::vector<std::string> log;

    state.input.inputButtonTime = 10;
    state.input.inputKnobTime = 9;

    scrSystem.setup();
    log.push_back("begin");

    state.currentTemp = 73;
    scrSystem.update(32);
    device.assertScreen(
        "heat                 ",
        "         7<<3<<`<<F<<",
        "AT       ^^^^^^^^^^^^",
        "         ^^^^^^^^^^^^");

    state.currentTemp = 74;
    scrSystem.update(300);
    device.assertScreen(
        "heat                 ",
        "         7<<4<<`<<F<<",
        "AT       ^^^^^^^^^^^^",
        "         ^^^^^^^^^^^^");

    state.currentTemp = 75;
    state.connectionStatus = 1;
    scrSystem.update(2000);
    device.assertScreen(
        "heat             cnnt",
        "         7<<5<<`<<F<<",
        "AT       ^^^^^^^^^^^^",
        "         ^^^^^^^^^^^^");

    state.currentTemp = 76;
    scrSystem.update(3000);
    device.assertScreen(
        "                     ",
        "                     ",
        "                     ",
        "                     ");
}

TEST(ScrSystem, ShowTargetTempAndHide)
{
    SsdWrapperTestImpl device;
    AppState state;
    ScrSystem scrSystem(&state, &device);

    std::vector<std::string> log;

    state.input.inputButtonTime = 10;
    state.input.inputKnobTime = 11;

    scrSystem.setup();
    log.push_back("begin");

    state.currentTemp = 73;
    state.targetTemp = 8;
    scrSystem.update(32);
    device.assertScreen(
        "heat                 ",
        "            8<<`<<F<<",
        "TT          ^^^^^^^^^",
        "            ^^^^^^^^^");

    state.currentTemp = 74;
    state.targetTemp = 9;
    scrSystem.update(300);
    device.assertScreen(
        "heat                 ",
        "            9<<`<<F<<",
        "TT          ^^^^^^^^^",
        "            ^^^^^^^^^");

    state.currentTemp = 75;
    state.targetTemp = 10;
    state.connectionStatus = 1;
    scrSystem.update(2000);
    device.assertScreen(
        "heat             cnnt",
        "         1<<0<<`<<F<<",
        "TT       ^^^^^^^^^^^^",
        "         ^^^^^^^^^^^^");

    state.currentTemp = 76;
    state.targetTemp = 11;
    scrSystem.update(3000);
    device.assertScreen(
        "                     ",
        "                     ",
        "                     ",
        "                     ");
}
