#include"ENU_Pole_tf.h"

double enu2pole_r(double enu_x, double enu_y)
{
    return sqrt(enu_x * enu_x + enu_y * enu_y);
}
double enu2pole_th(double enu_x, double enu_y)
{
    return atan(enu_y / enu_x);
}
double pole2enu_x(double pole_r, double pole_th)
{
    return pole_r * cos(pole_th);
}
double pole2enu_y(double pole_r, double pole_th)
{
    return pole_r * sin(pole_th);
}
