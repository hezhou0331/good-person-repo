#include<iostream>
using namespace std;

class animal
{
public:
	int age;
};
class dog:public animal
{
public:
	void SetAge(int n){age=n;};
};
int main()
{
	dog doga;
	doga.SetAge(8);
	return 0;
}