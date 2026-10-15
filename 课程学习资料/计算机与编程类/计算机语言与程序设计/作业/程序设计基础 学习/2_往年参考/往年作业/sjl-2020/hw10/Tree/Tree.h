#ifndef Tree_H_INCLUDE
#define Tree_H_INCLUDE

class Tree
{
private:
	int ages;
public:
	Tree(int a);
	void grow(int year);
	int age();
};
#endif