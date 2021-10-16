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


// Arithmetic
R T::operator +(S b);
R T::operator -(S b);
R T::operator +();
R T::operator -();
R T::operator *(S b);
R T::operator /(S b);
R T::operator %(S b);
R T::operator +=(S b);
R T::operator -=(S b);
R T::operator *=(S b);
R T::operator /=(S b);
R T::operator %=(S b);
// Note: C++ uses the unnamed dummy-parameter int to differentiate between prefix and suffix increment operators.
R T::operator ++();
R T::operator ++(int);
R T::operator --();
R T::operator --(int);

// Comparison
R T::operator ==(S b);
R T::operator !=(S b);
R T::operator >(S b);
R T::operator <(S b);
R T::operator >=(S b);
R T::operator <=(S b);

// Member Access and Functor-behavior
R T::operator [](S b);
T::operator R();
R T::operator *();
R T::operator ->();
R T::operator ->*(S a);
R T::operator ()(S a1, U a2, ...);
R T::operator ,(S b);

// Assignment, reference & copy
R T::operator &();
R T::operator =(S b);

// (De)Allocation
void* T::operator new(size_t x);
void* T::operator new[](size_t x);
void T::operator delete(void* x);
void T::operator delete[](void* x);

// Logic
R T::operator !();
R T::operator &&(S b);
R T::operator ||(S b);

// Bitwise
R T::operator ~();
R T::operator &(S b);
R T::operator |(S b);
R T::operator ^(S b);
R T::operator <<(S b);
R T::operator >>(S b);
R T::operator &=(S b);
R T::operator |=(S b);
R T::operator ^=(S b);
R T::operator <<=(S b);
R T::operator >>=(S b);