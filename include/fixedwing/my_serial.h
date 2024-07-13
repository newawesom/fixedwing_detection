#ifndef __MY_SERIAL
#define __MY_SERIAL

#include<iostream>
#include<ros/ros.h>
#include<serial/serial.h>

class My_Serial
{
    private:
    serial::Timeout to;
    serial::parity_t pt;
    serial::bytesize_t bt;
    serial::flowcontrol_t ft;
    serial::stopbits_t st;
    serial::Serial sp;
    private:
    void My_Serial_Init();
    public:
    My_Serial();
    ~My_Serial();
    bool sendData();
    unsigned char getCrc8(unsigned char* ptr, unsigned short len);
};

#endif