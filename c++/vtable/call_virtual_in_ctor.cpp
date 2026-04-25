/*
Program stdout

A()
A::f
B()
B::f
C()
C::f
C::f
~C()
C::f
C::f
~B()
B::f
~A()
A::f

*/

#include <iostream>

class A {
public:
    A() {
        std::cout << "A()" << std::endl;
        call_virtual();
    }
    ~A() {
        std::cout << "~A()" << std::endl;
        call_virtual();
    }

    void call_virtual() {
        f();
    }
private:
    virtual void f() {
        std::cout << "A::f" << std::endl;
    }
};

class B : public A {
public:
    B() {
        std::cout << "B()" << std::endl;
        call_virtual();
    }
    ~B() {
        std::cout << "~B()" << std::endl;
        call_virtual();
    }

    void call_virtual() {
        f();
    }
private:
    virtual void f() {
        std::cout << "B::f" << std::endl;
    }
};

class C : public B {
public:
    C() {
        std::cout << "C()" << std::endl;
        A::call_virtual();
        B::call_virtual();
    }

    ~C() {
        std::cout << "~C()" << std::endl;
        A::call_virtual();
        B::call_virtual();
    }

    void call_virtual() {
        f();
    }
private:
    virtual void f() {
        std::cout << "C::f" << std::endl;
    }
};

int main() {
    C c;
}