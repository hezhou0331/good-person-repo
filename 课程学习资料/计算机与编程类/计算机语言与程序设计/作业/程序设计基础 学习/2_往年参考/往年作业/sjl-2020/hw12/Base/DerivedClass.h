#ifndef _DERIVEDCLASS_H_
#define _DERIVEDCLASS_H_
#include<iostream>
#include"BaseClass.h"
using namespace std;
class DerivedClass:public BaseClass
{
public:
	void fn1(){cout<<"DerivedClass fn1 run!"<<endl;}
	void fn2(){cout<<"DerivedClass fn2 run!"<<endl;}
};
#endif