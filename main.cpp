#include <iostream>
#include <cmath>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <random>
#include <algorithm>
#include "cubic_spline_curve.h"

// 随机生成递增数据的函数（适用于xvec）
std::vector<double> generateRandomData(int numPoints, double minValue, double maxValue, bool isSorted = true)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(minValue, maxValue);

    std::vector<double> data;
    for (int i = 0; i < numPoints; ++i)
    {
        data.push_back(dis(gen));
    }

    // 根据需要对数据排序
    if (isSorted)
    {
        std::sort(data.begin(), data.end());
    }

    return data;
}

int main()
{

    // 随机生成递增的x控制点数据和非递增的y控制点数据
    // int numPoints = 3; // 控制点的数量
    // double minValue = 0.0;
    // double maxValue = 500.0;
    // std::vector<double> xvec = generateRandomData(numPoints, minValue, maxValue, false); // xvec 不递增
    // std::vector<double> yvec = generateRandomData(numPoints, minValue, maxValue, false); // yvec 不递增
    // std::vector<double> zvec = generateRandomData(numPoints, minValue, maxValue, false); // zvec 不递增
    // std::fill(zvec.begin(), zvec.end(), 0);
    // // 打开一个名为ctlPoint.txt的文件，用于存储控制点数据
    // std::ofstream ofs("../ctlPoint.txt");
    // for (int i = 0; i < xvec.size(); i++)
    // {
    //     ofs << std::fixed << std::setprecision(15) << xvec[i] << " " << yvec[i] << " " << zvec[i] << std::endl;
    // }

    std::vector<Point3D> points;
    

    // for (int i = 0; i < xvec.size(); i++)
    // {
    //     Point3D p;
    //     p.x = xvec[i];
    //     p.y = yvec[i];
    //     p.z = zvec[i];
    //     points.push_back(p);
    // }

    Point3D p1={1,1,0};
    Point3D p2={2,4.66,0};
    Point3D p3={3,2.2,0};
    Point3D p4={4,3.18,0};
    points.clear();
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);

    std::ofstream ofs("../ctlPoint.txt");
    for (int i = 0; i < points.size(); i++)
    {
        ofs << std::fixed << std::setprecision(15) << points[i].x << " " << points[i].y << " " << points[i].z << std::endl;
    }

    // 进行自然边界三次样条曲线的系数计算
    CubicSplineCurve S;
    auto s1 = std::chrono::steady_clock::now();
    S.setControlPoints(points);
    auto e1 = std::chrono::steady_clock::now();
    std::chrono::duration<float, std::milli> dd1 = e1 - s1;
    std::cout << "Second method time: " << dd1.count() << "ms" << std::endl;

    // 进行插值计算
    int totalNum = 5000;
    double xs = 0;
    double xe = points.size() - 1;
    double step = (xe - xs) / totalNum;

    // 打开一个名为output.txt的文件，用于存储插值结果
    std::ofstream of("../output.txt");
    for (; xs <= xe; xs += step)
    {
        auto P = S.interpolate(xs);
        of << std::fixed << std::setprecision(15) << P.x << " " << P.y << " " << P.z << std::endl;
    }

    return 0;
}
