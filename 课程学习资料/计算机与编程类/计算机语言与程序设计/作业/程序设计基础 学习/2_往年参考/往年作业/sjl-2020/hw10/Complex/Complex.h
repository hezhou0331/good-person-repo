#ifndef COMPLEX_H_INCLUDE
#define COMPLEX_H_INCLUDE
class Complex
{
private:
float re;
float im;
public:
Complex(float r, float i=0);
void add(Complex com);
void show();
};
#endif