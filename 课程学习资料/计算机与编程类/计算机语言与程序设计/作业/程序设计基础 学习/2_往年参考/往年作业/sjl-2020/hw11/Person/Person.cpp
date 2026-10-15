#include<iostream>
#include"Person.h"
using namespace std;
Person::Person(const int& height,const float& weight)
{
	this->height=height;
	this->weight=weight;
}
void Person::showInfo()
{
	printf("%d,%.2f",height,weight);
}