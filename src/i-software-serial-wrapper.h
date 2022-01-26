#ifndef i_software_serial_wrapper_h
#define i_software_serial_wrapper_h

class ISoftwareSerialWrapper
{
public:
    virtual void begin(long l) = 0;
    virtual int available() = 0;
    virtual char read() = 0;
    virtual void write(const char *s) = 0;
};

#endif