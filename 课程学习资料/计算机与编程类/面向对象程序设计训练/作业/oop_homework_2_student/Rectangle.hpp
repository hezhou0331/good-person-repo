//------------------------------------------------------------------------------
//【文件名】           Rectangle.hpp
//【功能模块和目的】   声明 Rectangle 矩形类，通过长和宽计算面积。
//【开发者及日期】   刘江宇, 2026-07-08
//【更改记录】       2026-07-08 统一注释格式，规范文件头位置。
//------------------------------------------------------------------------------

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Shape.hpp"

//------------------------------------------------------------------------------
//【类名】       Rectangle
//【功能】       保存矩形长宽，并提供尺寸访问和面积计算接口。
//【接口说明】   GetLength/GetWidth 读取尺寸；SetLength/SetWidth 修改尺寸；
//               GetArea 返回矩形面积。
//【开发者及日期】   刘江宇, 2026-07-08
//【更改记录】       2026-07-08 统一注释格式，精简冗余说明。
//------------------------------------------------------------------------------
class Rectangle : public Shape {
public:
    //必要的构造、赋值、析构行为
    Rectangle();
    Rectangle(double Length, double Width);
    Rectangle(const Rectangle& Source);
    Rectangle& operator=(const Rectangle& Source);
    ~Rectangle() override;

    //尺寸接口
    double GetLength() const;
    double GetWidth() const;
    void SetLength(double Length);
    void SetWidth(double Width);

    //面积接口
    double GetArea() const override;

private:
    void SetSize(double Length, double Width);

    double m_dLength;
    double m_dWidth;
};

#endif
