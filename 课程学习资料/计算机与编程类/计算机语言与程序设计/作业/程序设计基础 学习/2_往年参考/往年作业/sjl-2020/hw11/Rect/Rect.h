#ifndef RECT_H_INCLUDE
#define RECT_H_INCLUDE

class Rect
{
private:
	float top;
	float left;
	float bottom;
	float right;
public:
	Rect(const float& top,const float& left,const float& bottom,const float& right);
	float getArea() const;
};

#endif