#include <iostream>
#include <string>

// https://habr.com/ru/post/59558/
// https://arne-mertz.de/2016/07/const-correctness/
// https://isocpp.org/wiki/faq/const-correctness


// Q : Should I try to get things const correct “sooner” or “later”?  
// A : At the very, very, very beginning.


// Q : Should the constness of my public member functions be based 
//		on what the method does to the object’s logical state, or physical state?
// A : Logical.
//		There’s no way to make this next part easy.
//		It is going to hurt.Best recommendation is to sit down. 
//		And please, for your safety, make sure there are no sharp implements nearby.


// a const member function must not change(or allow a caller to change)
// the this object’s logical state(AKA abstract state AKA meaningwise state).

void TryToChangeString(const std::string& str)
{
	// error C2678: binary '=': no operator found which takes a left-hand operand of type 'const std::string'
	// str = "123";

	// error C3892: 'str': you cannot assign to a variable that is const
	// str[1] = '2';

	std::cout << str[0] << std::endl;
}


class Test
{
public:
	Test() : i(10) {}

	int GetI() const { return i; } // This member promises NOT to change *this
	void Mutate() { i += 3; }          // This member function might change *this

private:
	int i;
};

class Person {
public:
	const std::string& name_good() const;  // Right: the caller can't change the Person's name
	std::string& name_evil() const;        // Wrong: the caller can change the Person's name
	int age() const;                       // Also right: the caller can't change the Person's age
	// ...
};

void myCode(const Person& p)  // myCode() promises not to change the Person object...
{
	p.name_evil() = "Igor";     // But myCode() changed it anyway!!
}

int main()
{
	const Test test;
	std::cout << test.GetI() << std::endl;

	// error C2662: 'void Test::Mutate(void)': 
	// cannot convert 'this' pointer from 'const Test' to 'Test &'
	test.Mutate();

	const int i = 0;
	int j = 9;

	// error C3892: 'i': you cannot assign to a variable that is const
	// i = j;

	const int* ptr = &j;
	ptr = &i;
	// error C3892: 'ptr': you cannot assign to a variable that is const
	//*ptr = 10;

	int* const constPtr = &j;
	// error C2440 : '=' : cannot convert from 'const int *' to 'int *const '
	// constPtr = &i;

	*constPtr = i;

	const char* arrayOne = new char[10];
	const char* const arrayTwo = new char[10];

	// error C3892 : 'arrayOne' : you cannot assign to a variable that is const
	// arrayOne[0] = 5;
	// arrayOne[1] = 7;
	// arrayOne[5] = 10;

	arrayOne = arrayTwo;

	// error C3892: 'arrayTwo': you cannot assign to a variable that is const
	// arrayTwo[0] = 5;
	// arrayTwo[1] = 7;
	// arrayTwo[5] = 10;

	// error C3892 : 'arrayTwo' : you cannot assign to a variable that is const
	// arrayTwo = arrayOne;

	char* const arrayTree = new char[10];

	arrayTree[0] = 5;
	arrayTree[1] = 7;
	arrayTree[5] = 10;

	// error C2440: '=': cannot convert from 'const char *const ' to 'char *const '
	// arrayTree = arrayTwo;

	int g = 10;
	const int& refG = g;

	// error C3892: 'refG': you cannot assign to a variable that is const
	// refG = 20;
	// refG = i;

	std::string str{"12345"};
	TryToChangeString(str);

	std::cin.get();
	return 0;
}