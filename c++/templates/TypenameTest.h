#include <iostream>

class Rose {};

class A 
{ 
public:
    typedef Rose rose; 
};

template<typename T>
class B : public T 
{
public:
    typedef typename T::rose foo;
};

template<typename T>
void smell(T) { std::cout << "Ugly" << std::endl; }

void smell(Rose) { std::cout << "Perfect" << std::endl; }
