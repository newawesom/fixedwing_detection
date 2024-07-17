#ifndef __GLOBAL_2_ENU_TF
#define __GLOBAL_2_ENU_TF
#include<math.h>
#include<iostream>
#define EARTH_R 6371393
/**
    @brief 二维点类，有着x和y两个维度。
    @public
    @param double X
    @param double Y
**/
class point
{
    public:
    double x;
    double y;
    /**
    @brief 点类无参构造函数
    **/
    point();
    /**
    @brief 点类有参构造函数
    @param double X
    @param double Y
    **/
    point(double, double);
};
/**
    @brief 将地理绝对经纬度与ENU坐标进行转换
    @param _home HOME点坐标
    @param _d_world 经纬坐标差
    @param _enu ENU坐标
    @param _world 地理绝对经纬坐标
**/
class transf
{
    private:
    point _home;
    point _d_world;
    point _enu;
    point _world;
    public:
    /**
     * @brief 由点类构造转换类
     * @param point HOME点
     * **/
    transf(point);
    /**
     * @brief 有经纬坐标构造类
     * @param double 经度
     * @param double 纬度
    **/
    transf(double, double);
    /**
     * @brief 无参构造函数
    */
    transf();
    /**
     * @brief 拷贝构造函数
    */
    void settf(transf tf);
    /**
     * @brief 将ENU坐标转为经纬坐标
     * @param point 被转换的ENU坐标
    */
    point enu2world(point);
    /**
     * @brief 将经纬坐标转换为ENU坐标
     * @param point 被转换的经纬度坐标
    */
    point world2enu(point);
    /**
     * @brief 将弧度转为角度
     * @param double 被转换的弧度
    */
    double rad2deg(double);
    /**
     * @brief 将角度转为弧度
     * @param double 被转换的角度
    */
    double deg2rad(double);
};
#endif
