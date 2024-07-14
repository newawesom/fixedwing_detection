#ifndef __ENU_POLE_TF
#define __ENU_POLE_TF
#include<math.h>
#include<iostream>
/**
 * @brief 将ENU坐标转换为极坐标 R半径
 * @param enu_x ENU坐标系X坐标
 * @param enu_y ENU坐标系Y坐标 
*/
double enu2pole_r(double enu_x,double enu_y);
/**
 * @brief 将ENU坐标转换为极坐标 Theta角
 * @param enu_x ENU坐标系X坐标
 * @param enu_y ENU坐标系Y坐标
*/
double enu2pole_th(double enu_x,double enu_y);
/**
 * @brief 将极坐标转换为ENU坐标 X
 * @param pole_r 极坐标系R半径
 * @param pole_th 极坐标系Theta角
*/
double pole2enu_x(double pole_r,double pole_th);
/**
 * @brief 将极坐标转换为ENU坐标 Y
 * @param pole_r 极坐标系R半径
 * @param pole_th 极坐标系Theta角
*/
double pole2enu_y(double pole_r,double pole_th);

#endif