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

Ключевое правило: Виртуальные вызовы в конструкторах/деструкторах

Когда объект конструируется или разрушается, его динамический тип "замораживается" 
на уровне того класса, чей конструктор/деструктор сейчас выполняется. 
Виртуальная таблица (vtable) принудительно переключается на текущий класс,
и вызовы виртуальных функций не могут уйти глубже в иерархию.

Это сделано для безопасности: нельзя вызывать методы ещё не созданного или уже уничтоженного подобъекта.
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