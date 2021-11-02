int foo();
int& foo1();
const int foo2();
const int& foo3();

int main()
{
  auto ri = foo();
  auto ri1 = foo1();
  auto ri2 = foo2();
  auto ri3 = foo3();

  auto& ri4 = foo();
  auto& ri5 = foo1();
  auto& ri6 = foo2();
  auto& ri7 = foo3();

  auto&& ri8 = foo();
  auto&& ri9 = foo1();
  auto&& ri10 = foo2();
  auto&& ri11 = foo3();

  int k = 5;
  decltype(k)&& rk = k;

  decltype(foo())&& ri12 = foo();
  decltype(foo1())&& ri13 = foo1();
  
  int i = 3;
  decltype(i) ri14;
  decltype((i)) ri15;
}