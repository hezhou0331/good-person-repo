#include<iostream>
#include"Circle.h"
using namespace std;
Circle::Circle(const float& radius)
{
    this->radius=radius;
}

float Circle::getArea()
{
    return 3.141592*radius*radius;
}