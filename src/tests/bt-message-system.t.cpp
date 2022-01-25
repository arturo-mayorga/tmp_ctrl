#include <gtest/gtest.h>
#include "../app-state.h"
#include "../bt-message-system.h"
#include "../i-software-serial-wrapper.h"
#include "logger-test-impl.h"

#include <deque>

class SoftwareSerialWrapperTestImpl : public ISoftwareSerialWrapper
{
private:
    std::deque<char> _buffer;

public:
    long baudRate;

    virtual void begin(long l)
    {
        baudRate = l;
    }
    virtual int available()
    {
        return (int)_buffer.size();
    }
    virtual char read()
    {
        if (_buffer.size() > 0)
        {
            char c = _buffer.front();
            _buffer.pop_front();
            return c;
        }

        return -1;
    }
    virtual void write(const char *s)
    {
        for (int i = 0; i < strlen(s); i++)
        {
            _buffer.push_back(s[i]);
        }
    }
    void copyInternalBuffer(char *buffer)
    {
        int i = 0;
        for (; i < _buffer.size(); i++)
        {
            buffer[i] = _buffer[i];
        }
        buffer[i] = 0;
        
    }
    void clear(){
        _buffer.clear();
    }
};

TEST(BtMessageSystem, SoftwareSerialMock)
{
    SoftwareSerialWrapperTestImpl serial;
    serial.begin(1234);
    EXPECT_EQ(serial.baudRate, 1234);

    const char *qwerty = "qwerty";
    serial.write(qwerty);
    EXPECT_EQ(serial.available(), strlen(qwerty));

    EXPECT_EQ(serial.read(), 'q');
    EXPECT_EQ(serial.read(), 'w');
    EXPECT_EQ(serial.read(), 'e');
    EXPECT_EQ(serial.read(), 'r');
    EXPECT_EQ(serial.read(), 't');
    EXPECT_EQ(serial.read(), 'y');
    EXPECT_EQ(serial.read(), -1);
}

TEST(BtMessageSystem, Setup)
{
    AppState state;
    LoggerTestImpl logger;
    SoftwareSerialWrapperTestImpl serial;
    state.knobPercentage = 34;

    BtMessageSystem btController(&state, &logger, &serial, BtMode::controller, 1234);

    // setup initializes software serial.
    btController.setup();
    EXPECT_EQ(serial.baudRate, 1234);

    // when in controller mode, it should also capture initial knobPercentage.
    // explicitly expect no messages sent unless knobPercentage changes
    btController.update(2001);
    EXPECT_EQ(serial.available(), 0);

    state.knobPercentage = 42;
    btController.update(5001);
    EXPECT_TRUE(serial.available() > 0);
}

TEST(BtMessageSystem, knobUpdateMessage)
{
    AppState state;
    LoggerTestImpl logger;
    SoftwareSerialWrapperTestImpl serial;
    state.knobPercentage = 0;

    BtMessageSystem btController(&state, &logger, &serial, BtMode::controller, 1234);

    btController.setup();

    // check that correct messages are sent to serial when updates are made
    state.knobPercentage = 42.253f;
    btController.update(2001);

    char buffer[100];
    serial.copyInternalBuffer(buffer);
    EXPECT_STREQ(buffer, "{K:42253}");

    state.knobPercentage = 3.987f;
    serial.clear();
    btController.update(5000);
    serial.copyInternalBuffer(buffer);
    EXPECT_STREQ(buffer, "{K:3987}");
}

TEST(BtMessageSystem, MessagesAreSendAndUnderstoodBetweenControllerAndServo)
{
    AppState controller_state;
    AppState servo_state;
    LoggerTestImpl logger;
    SoftwareSerialWrapperTestImpl serial;
    controller_state.knobPercentage = 0;
    servo_state.knobPercentage = 0;

    BtMessageSystem btController(&controller_state, &logger, &serial, BtMode::controller, 1234);
    BtMessageSystem btServo(&servo_state, &logger, &serial, BtMode::servo, 1234);

    btController.setup();
    btServo.setup();

    // check that correct messages are sent to serial when updates are made
    controller_state.knobPercentage = 42.253f;
    btController.update(2001);
    btServo.update(2001);
    
    EXPECT_EQ(controller_state.knobPercentage, servo_state.knobPercentage);

    controller_state.knobPercentage = 2.514f;
    btController.update(2001*2);
    btServo.update(2001*2);
    
    EXPECT_EQ(controller_state.knobPercentage, servo_state.knobPercentage);
}