#include <vector>
#include <iostream>
#include <cmath>

struct Point3D
{
    double x;
    double y;
    double z;
};

// 这个是自然边界的三次样条
class CubicSplineCurve
{
public:
    CubicSplineCurve();

    void setControlPoints(std::vector<Point3D> points);
    Point3D interpolate(double t);

    std::vector<double> calculateNaturalBoundary(std::vector<double> x, std::vector<double> y);

private:
    std::vector<Point3D> control_points;
    std::vector<double> h;
    std::vector<double> u;
    std::vector<double> b;
    std::vector<double> v;
    std::vector<double> z;//这个是二阶导数系数，用来确定每个段表达式
    std::vector<double> z_x;// x方向的二阶导数系数
    std::vector<double> z_y;// y方向的二阶导数系数
    std::vector<double> z_z;// z方向的二阶导数系数
    std::vector<double> _x;
    std::vector<double> _y;
    std::vector<double> _z;
    std::vector<double> _t;//参数化
};