//------------------------------------------------------------------------------
//【文件名】           Circle.hpp
//【功能模块和目的】   声明 Circle 圆形类，通过半径计算面积。
//【开发者及日期】   刘江宇, 2026-07-08
//【更改记录】       2026-07-08 统一注释格式，规范文件头位置。
//------------------------------------------------------------------------------

#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "Shape.hpp"

//------------------------------------------------------------------------------
//【类名】       Circle
//【功能】       保存圆半径，并提供半径访问和面积计算接口。
//【接口说明】   GetRadius/SetRadius 访问半径；GetArea 返回圆面积。
//【开发者及日期】   刘江宇, 2026-07-08
//【更改记录】       2026-07-08 统一注释格式，精简冗余说明。
//------------------------------------------------------------------------------
class Circle : public Shape {
public:
    //必要的构造、赋值、析构行为
    Circle();
    explicit Circle(double Radius);
    Circle(const Circle& Source);
    Circle& operator=(const Circle& Source);
    ~Circle() override;

    //半径接口
    double GetRadius() const;
    void SetRadius(double Radius);

    //面积接口
    double GetArea() const override;

private:
    static constexpr double PI = 3.14159265358979323846;
    double m_dRadius;
};

#endif
