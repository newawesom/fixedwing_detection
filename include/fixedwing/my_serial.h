#ifndef __MY_SERIAL
#define __MY_SERIAL

#include<iostream>
#include<ros/ros.h>
#include<serial/serial.h>
/**
 * @brief 串口通讯类
 * @param to Timeout链接超时时间
 * @param pt 校验位
 * @param bt 传入数据长度
 * @param ft 数控控制流
 * @param st 终止位
 * @param sp 串口对象
*/
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
    /**
     * @brief 初始化函数
    */
    void My_Serial_Init();
    public:
    /**
     * @brief 无参构造函数
    */
    My_Serial();
    /**
     * @brief 向STM32F103C8T6发送数据
    */
    void sendData();
    /**
     * @brief 循环冗余校验
     * @param ptr buf数据数组
     * @param len 数据宽度
    */
    unsigned char getCrc8(unsigned char* ptr, unsigned short len);
};

#endif