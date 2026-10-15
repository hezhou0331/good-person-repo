#include<iostream>
#include"Rect.h"
using namespace std;
Rect::Rect(const float& top,const float& left,const float& bottom,const float& right)
{
	this->top=top;
	this->left=left;
	this->right=right;
	this->bottom=bottom;
}
float Rect::getArea() const
{
	return (top-bottom)*(right-left);
}