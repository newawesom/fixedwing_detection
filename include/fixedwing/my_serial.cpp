#include"my_serial.h"
const unsigned char header[2] = {0x55, 0xaa};
const unsigned char ender[2] = {0x0d, 0x0a};
My_Serial::My_Serial()
{
    My_Serial::My_Serial_Init();
}
void My_Serial::My_Serial_Init()
{
    My_Serial::to = serial::Timeout::simpleTimeout(100);
    My_Serial::pt = serial::parity_t::parity_none;
    My_Serial::bt = serial::bytesize_t::eightbits;
    My_Serial::ft = serial::flowcontrol_t::flowcontrol_none;
    My_Serial::st = serial::stopbits_t::stopbits_one;
    My_Serial::sp.setPort("/dev/ttyUSB0");//设置端口
    My_Serial::sp.setBaudrate(115200);//设置波特率
    My_Serial::sp.setParity(My_Serial::pt);//设置校验位
    My_Serial::sp.setBytesize(My_Serial::bt);//设置发送的字节数
    My_Serial::sp.setFlowcontrol(My_Serial::ft);//设置数据控制流
    My_Serial::sp.setStopbits(My_Serial::st);//设置终止位
    My_Serial::sp.setTimeout(My_Serial::to);//串口设置timeout

    try
    {
        My_Serial::sp.open();
    }
    catch(serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open port.");
        return;
    }
    
}
void My_Serial::sendData()
{
    unsigned char buf[8] = {0};
    int i, length = 1;
    for(i = 0; i < 2; i++)
    {
        buf[i] = header[i];
    }
    buf[3] = length;
    buf[4] = 1;
    buf[4 + length] = getCrc8(buf, 3 + length);
    buf[5 + length] = ender[0];
    buf[6 + length] = ender[1];

    My_Serial::sp.write(buf, 8);
}
unsigned char My_Serial::getCrc8(unsigned char* ptr, unsigned short len)
{
    unsigned char crc;
    unsigned char i;
    crc = 0;
    while(len--)
    {
        crc ^= *ptr++;
        for(i = 0; i < 8; i++)
        {
            if(crc & 0x01)
                crc = (crc >> 1) ^ 0x8C;
            else
                crc >>= 1;
        }
    }
    return crc;  
}