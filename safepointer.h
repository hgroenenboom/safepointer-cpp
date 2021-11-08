#include <cassert>
#include <memory>

namespace hgdsp
{

class SafePointable
{
public:
	SafePointable()
	{
		exists = std::make_shared<bool>(true);
	}
	
	~SafePointable()
	{
		*exists = false;
	}

	std::shared_ptr<bool> reference() { return exists; }

private:
	std::shared_ptr<bool> exists;
};

class SafePointer : public std::shared_ptr<bool>
{
public:
	SafePointer(SafePointable& safePointable)
	{
		*(static_cast<std::shared_ptr<bool>*>(this)) = safePointable.reference();
	}
};

}

#ifdef HGDSP_CHECK_POINTERS
#define HGDSP_MAKE_SAFEPOINTER(x) hgdsp::SafePointer x##SafePointer { *x };
#define HGDSP_CHECK_SAFEPOINTER(x) assert(*x##SafePointer == true);
#else
#define HGDSP_MAKE_SAFEPOINTER(x) ;
#define HGDSP_CHECK_SAFEPOINTER(x) ;
#endif
