#define HGDSP_CHECK_POINTERS 1
#include "safepointer.h"

#include <iostream>

class A
#if HGDSP_CHECK_POINTERS
	: public hgdsp::SafePointable
#endif
{
};

class B
{
public:
	A* a = new A();
	
	HGDSP_MAKE_SAFEPOINTER(a);
};

int main()
{
	B b;
	std::cout << b.aSafePointer << std::endl;
	std::cout << *b.aSafePointer << std::endl;
	HGDSP_CHECK_SAFEPOINTER(b.a);
	
	// Could happen on another thread
	delete b.a;
	
	std::cout << b.aSafePointer << std::endl;
	std::cout << *b.aSafePointer << std::endl;
	HGDSP_CHECK_SAFEPOINTER(b.a);
}
