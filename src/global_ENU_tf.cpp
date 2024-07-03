#include"../include/fixedwing/global_ENU_tf.h"

transf::transf(point home)
{
    _home = home;
}
transf::transf(double x,double y)
{
    _home.x = x;
    _home.y = y;
}
transf::transf()
{
    _home = point();
}
void transf::settf(transf tf)
{
    _home = tf._home;
}
double transf::rad2deg(double rad)
{
    return (180.0 / M_PI) * rad;
}
double transf::deg2rad(double deg)
{
    return (M_PI / 180.0) * deg;
}
point transf::enu2world(point ned)
{
    _enu = ned;
    double dx_rad = _enu.y / EARTH_R;
    double dx_deg = transf::rad2deg(dx_rad);
    _world.x = _home.x + dx_deg;
    double dy_rad = (_enu.x / EARTH_R) / cos(transf::deg2rad(_world.x));
    double dy_deg = transf::rad2deg(dy_rad);
    _world.y = _home.y + dy_deg;
    return _world;
}
point transf::world2enu(point world)
{
    _world = world;
    _d_world.x = _world.x - _home.x;
    _d_world.y = _world.y - _home.y;
    double dx_rad = transf::deg2rad(_d_world.x);
    double dy_rad = transf::deg2rad(_d_world.y);
    double dy = dx_rad * EARTH_R;
    double dx = dy_rad * EARTH_R * cos(transf::deg2rad(_world.x));
    _enu.x = dx;
    _enu.y = dy;
    return _enu;
}
point::point()
{
    x = 0;
    y = 0;
}
point::point(double _x, double _y)
{
    x = _x;
    y = _y;
}