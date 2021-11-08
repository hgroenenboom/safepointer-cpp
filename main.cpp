#define HGDSP_CHECK_POINTERS 1
#include "safepointer.h"

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
	HGDSP_CHECK_SAFEPOINTER(b.a);
	delete b.a;
	HGDSP_CHECK_SAFEPOINTER(b.a);
}
