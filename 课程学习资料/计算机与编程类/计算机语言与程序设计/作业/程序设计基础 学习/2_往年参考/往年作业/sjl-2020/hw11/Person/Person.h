#ifndef PERSON_H_INCLUDE
#define PERSON_H_INCLUDE

class Person
{
public:
	Person(const int& height,const float& weight);
	void showInfo();
private:
	int height;
	float weight;
};

#endif;