// https://www.ibm.com/docs/en/zos/2.4.0?topic=only-overloading-operators-c

// You can overload any of the following operators:
// + 	- 	* 	⁄ 	% 	‸ 	& 	| 	~
// ! 	= 	< 	> 	+= 	-= 	*= 	⁄= 	%=
// ‸= 	&= 	|= 	<< 	>> 	<<= 	>>= 	== 	!=
// <= 	>= 	&& 	|| 	++ 	-- 	, 	->* 	->
// () 	[] 	new 	delete 	new[] 	delete[]


//You cannot overload the following operators:
//. 	.* 	:: 	?:

// https://isocpp.org/wiki/faq/operator-overloading
// https://github.com/MicrosoftDocs/cpp-docs/blob/master/docs/cpp/operator-overloading.md


// https://en.cppreference.com/w/cpp/language/cast_operator

// User-defined conversions
struct X {
    //implicit conversion
    operator int() const { return 7; }
 
    // explicit conversion
    explicit operator int*() const { return nullptr; }
 
//  Error: array operator not allowed in conversion-type-id
//  operator int(*)[3]() const { return nullptr; }
    using arr_t = int[3];
    operator arr_t*() const { return nullptr; } // OK if done through typedef
//  operator arr_t () const; // Error: conversion to array not allowed in any case
};

// https://stackoverflow.com/questions/8239356/can-a-cast-operator-be-explicit
// https://www.ibm.com/docs/en/zos/2.2.0?topic=only-user-defined-conversions-c

class S
{
    using R = int;
    using U = double;
public:
    // Arithmetic
    R operator +(S b) { };
    R operator -(S b) { };
    R operator +() { };
    R operator -() { };
    R operator *(S b) { };
    R operator /(S b) { };
    R operator %(S b) { };
    R operator +=(S b) { };
    R operator -=(S b) { };
    R operator *=(S b) { };
    R operator /=(S b) { };
    R operator %=(S b) { };
    // Note: C++ uses the unnamed dummy-parameter int to differentiate between prefix and suffix increment operators.
    R operator ++() { };
    R operator ++(int) { };
    R operator --() { };
    R operator --(int) { };

    // Comparison
    R operator ==(S b) { };
    R operator !=(S b) { };
    R operator >(S b) { };
    R operator <(S b) { };
    R operator >=(S b) { };
    R operator <=(S b) { };

    // Member Access and Functor-behavior
    R operator [](S b) { };
    operator R() { };
    R operator *() { };
    R operator ->() { };
    R operator ->*(S a) { };
    R operator ()(S a1, U a2, ...) { };
    R operator ,(S b) { };

    // Assignment, reference & copy
    R operator &() { };
    R operator =(S b) { };

    // (De)Allocation
    // void* operator new(size_t x) { };
    // void* operator new[](size_t x) { };
    // void operator delete(void* x) { };
    // void operator delete[](void* x) { };

    // Logic
    R operator !() { };
    R operator &&(S b) { };
    R operator ||(S b) { };

    // Bitwise
    R operator ~() { };
    R operator &(S b) { };
    R operator |(S b) { };
    R operator ^(S b) { };
    R operator <<(S b) { };
    R operator >>(S b) { };
    R operator &=(S b) { };
    R operator |=(S b) { };
    R operator ^=(S b) { };
    R operator <<=(S b) { };
    R operator >>=(S b) { };
};
