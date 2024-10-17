#include "cubic_spline_curve.h"

CubicSplineCurve::CubicSplineCurve()
{
}

Point3D CubicSplineCurve::interpolate(double t)
{
    if (_t.empty() || _x.empty() || _y.empty() || _z.empty() || z_x.empty() || z_y.empty() || z_z.empty())
    {
        throw std::logic_error("Control points or spline coefficients not initialized.");
    }

    if (t < _t[0] || t > _t.back())
    {
        throw std::out_of_range("t is out of the interpolation range");
    }

    // 使用二分查找找到 t 所在的区间
    auto it = std::lower_bound(_t.begin(), _t.end(), t);
    int k = std::distance(_t.begin(), it) - 1;

    // 边界处理，防止超出范围
    if (k < 0)
        k = 0;
    if (k >= _t.size() - 1)
        k = _t.size() - 2;

    double ht = _t[k + 1] - _t[k];
    double diff1 = _t[k + 1] - t;
    double diff2 = t - _t[k];

    // 对 x 进行三次样条插值
    double s1_x = (diff1 * diff1 * diff1) * (z_x[k] / (6 * ht));
    double s2_x = (diff2 * diff2 * diff2) * (z_x[k + 1] / (6 * ht));
    double s3_x = (_x[k + 1] / ht - z_x[k + 1] * ht / 6) * diff2;
    double s4_x = (_x[k] / ht - z_x[k] * ht / 6) * diff1;
    double x_interp = s1_x + s2_x + s3_x + s4_x;

    // 对 y 进行三次样条插值
    double s1_y = (diff1 * diff1 * diff1) * (z_y[k] / (6 * ht));
    double s2_y = (diff2 * diff2 * diff2) * (z_y[k + 1] / (6 * ht));
    double s3_y = (_y[k + 1] / ht - z_y[k + 1] * ht / 6) * diff2;
    double s4_y = (_y[k] / ht - z_y[k] * ht / 6) * diff1;
    double y_interp = s1_y + s2_y + s3_y + s4_y;

    // 对 z 进行三次样条插值
    double s1_z = (diff1 * diff1 * diff1) * (z_z[k] / (6 * ht));
    double s2_z = (diff2 * diff2 * diff2) * (z_z[k + 1] / (6 * ht));
    double s3_z = (_z[k + 1] / ht - z_z[k + 1] * ht / 6) * diff2;
    double s4_z = (_z[k] / ht - z_z[k] * ht / 6) * diff1;
    double z_interp = s1_z + s2_z + s3_z + s4_z;

    return Point3D{x_interp, y_interp, z_interp}; // 返回三维插值后的点
}

void CubicSplineCurve::setControlPoints(std::vector<Point3D> points)
{

    if (points.size() < 2)
    {
        throw std::invalid_argument("At least two control points are required.");
    }

    // 这里使用均匀参数化方法
    this->_x.clear();
    this->_y.clear();
    this->_z.clear();
    this->_t.clear();
    for (size_t i = 0; i < points.size(); ++i)
    {
        this->_x.push_back(points[i].x);
        this->_y.push_back(points[i].y);
        this->_z.push_back(points[i].z);
        _t.push_back(i); // 这里可以是均匀参数化，或者使用弧长参数化
    }

    // 计算三维样条系数
    z_x = calculateNaturalBoundary(_t, _x); // x 方向的样条系数
    z_y = calculateNaturalBoundary(_t, _y); // y 方向的样条系数
    z_z = calculateNaturalBoundary(_t, _z); // z 方向的样条系数
}

std::vector<double> CubicSplineCurve::calculateNaturalBoundary(std::vector<double> t, std::vector<double> y)
{
    size_t len = t.size();
    h.resize(len - 1);
    b.resize(len - 1);
    v.resize(len - 2);
    u.resize(len - 2);
    z.resize(len);

    for (int i = 0; i < len - 1; i++)
    {
        h[i] = t[i + 1] - t[i];
        b[i] = 6 * (y[i + 1] - y[i]) / h[i];
    }

    for (int i = 0; i < len - 2; i++)
    {
        u[i] = 2 * (h[i + 1] + h[i]);
        v[i] = b[i + 1] - b[i];
    }

    for (int i = 1; i < len - 2; i++)
    {
        v[i] = v[i] - (h[i] / u[i - 1]) * (v[i - 1]);
        u[i] = u[i] - h[i] * h[i] / u[i - 1];
    }

    z[0] = 0;
    z[len - 1] = 0;

    for (int i = len - 2; i > 0; i--)
    {
        z[i] = (v[i - 1] - z[i + 1] * h[i]) / u[i - 1];
    }

    return z;
}
