//------------------------------------------------------------------------------
//【文件名】           Square.hpp
//【功能模块和目的】   声明 Square 正方形类，直接继承 Shape 以保持清晰的图形层次。
//【开发者及日期】   刘江宇, 2026-07-08
//【更改记录】       2026-07-08 统一注释格式，规范文件头位置。
//                 2026-07-08 调整 Square 直接继承 Shape，避免正方形继承矩形破坏
//                 里氏替换原则。
//------------------------------------------------------------------------------

#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "Shape.hpp"

//------------------------------------------------------------------------------
//【类名】       Square
//【功能】       保存正方形边长，并提供边长访问和面积计算接口。
//【接口说明】   GetSideLength/SetSideLength 访问边长；GetArea 返回正方形面积。
//【开发者及日期】   刘江宇, 2026-07-08
//【更改记录】       2026-07-08 统一注释格式，精简冗余说明。
//                 2026-07-08 取消 Square 对 Rectangle 的继承关系，改为与
//                 Rectangle 并列继承 Shape。
//------------------------------------------------------------------------------
class Square : public Shape {
public:
    //必要的构造、赋值、析构行为
    Square();
    explicit Square(double SideLength);
    Square(const Square& Source);
    Square& operator=(const Square& Source);
    ~Square() override;

    //边长接口
    double GetSideLength() const;
    void SetSideLength(double SideLength);

    //面积接口
    double GetArea() const override;

private:
    double m_dSideLength;
};

#endif
