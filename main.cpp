#define HG_SAFEPOINTER_CHECK_POINTERS 1
#include "safepointer.h"

#include <iostream>

class A : public SafePointable
{
};

class B
{
public:
	A* a = new A();
	
	HG_MAKE_SAFEPOINTER(a);
};

int main()
{
	B b;
	std::cout << (bool)b.aSafePointer << std::endl;
	HG_ASSERT_SAFEPOINTER(b.a);
	
	// Could happen on another thread
	delete b.a;
	
	std::cout << (bool)b.aSafePointer << std::endl;
	HG_ASSERT_SAFEPOINTER(b.a);
}
