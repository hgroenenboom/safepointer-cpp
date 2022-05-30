#include <cassert>
#include <memory>

class SafePointable
{
public:
	#ifdef HG_SAFEPOINTER_CHECK_POINTERS
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
	#else
	SafePointable() = default;
	~SafePointable() = default;
	#endif
};

class SafePointer : private std::shared_ptr<bool>
{
public:
	SafePointer(SafePointable& safePointable)
	{
		*(static_cast<std::shared_ptr<bool>*>(this)) = safePointable.reference();
	}
	
	bool operator ==(bool other) const 
	{
		return other == (bool)*this;
	}
	
	operator bool() const 
	{
		return **(static_cast<const std::shared_ptr<bool>*>(this));
	}
	
	bool valid() const 
	{
		return (bool)*this;
	}
};

#ifdef HG_SAFEPOINTER_CHECK_POINTERS
#define HG_MAKE_SAFEPOINTER(x) SafePointer x##SafePointer { *x };
#define HG_ASSERT_SAFEPOINTER(x) assert(x##SafePointer.valid());
#else
#define HG_MAKE_SAFEPOINTER(x) ;
#define HG_ASSERT_SAFEPOINTER(x) ;
#endif
