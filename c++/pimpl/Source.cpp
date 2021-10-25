// https://habr.com/ru/post/111602/
// https://evileg.com/ru/post/322/
// https://en.cppreference.com/w/cpp/language/pimpl
// https://ru.stackoverflow.com/questions/908373/%D0%A2%D0%B5%D1%85%D0%BD%D0%B8%D0%BA%D0%B0-pimpl-c

#include "Source.h"
#include <iostream>
	
void* operator new(size_t count) {
	std::cout << "allocating " << count << " bytes\n";
	return malloc(count);
}
	
void operator delete(void* ptr) noexcept {
	std::cout << "global op delete called\n";
	free(ptr);
}
	
class MyClassImpl
{
public:
	MyClassImpl(MyClass* pBackPtr) : m_pMainClass(pBackPtr) { }
	~MyClassImpl() = default;
	
	void DoSth() { std::cout << "Val (incremented): " << ++m_val << "\n";}
	
	// try to uncomment (or comment 'const' for the method)
	void DoConst() const { 
		std::cout << "Val: " << /*++*/m_val << "\n"; 
	} 
	
private:
	int m_val {0};
	MyClass* m_pMainClass {nullptr}; // back pointer
};
	
MyClass::MyClass() : m_pImpl(new MyClassImpl(this)) 
{
	std::cout <<  __PRETTY_FUNCTION__ << "\n";
}
	
MyClass::~MyClass() { std::cout <<  __PRETTY_FUNCTION__ << "\n"; }
MyClass::MyClass(MyClass &&) noexcept = default;
MyClass& MyClass::operator=(MyClass &&) noexcept = default;
	
MyClass::MyClass(const MyClass& rhs)
	: m_pImpl(new MyClassImpl(*rhs.m_pImpl))
{}
	
MyClass& MyClass::operator=(const MyClass& rhs) {
	if (this != &rhs) 
		m_pImpl.reset(new MyClassImpl(*rhs.m_pImpl));
	
	return *this;
}
	
void MyClass::DoSth()
{
	Pimpl()->DoSth();
}
	
void MyClass::DoConst() const
{
	Pimpl()->DoConst();
}


int maint()
{
	MyClass myObject;
	myObject.DoSth();
	
	const MyClass secondObject;
	secondObject.DoConst();

	return 0;
}