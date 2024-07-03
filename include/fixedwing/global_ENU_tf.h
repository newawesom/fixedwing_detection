#include<math.h>
#include<iostream>
#define EARTH_R 6371393
 class point
{
    public:
    double x;
    double y;
    point();
    point(double, double);
};
class transf
{
    private:
    point _home;
    point _d_world;
    point _enu;
    point _world;
    public:
    transf(point);
    transf(double, double);
    transf();
    void settf(transf tf);
    point enu2world(point);
    point world2enu(point);
    double rad2deg(double);
    double deg2rad(double);
};
