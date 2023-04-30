// https://belaycpp.com/2021/05/03/passing-an-enum-by-parameter/
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

template<typename Iter>
std::string join_string(Iter begin, Iter end,
    const char* const separator)
{
    std::ostringstream os;
    std::copy(begin, end - 1, std::ostream_iterator<std::string>(os, separator));
    os << *(end - 1);
    return os.str();
}

template <typename C>
std::string join_string(const C& c, const char* const separator)
{
    if (c.size() == 0)
        return std::string{};
    return join_string(std::begin(c), std::end(c), separator);
}

int main()
{
    using namespace std::string_literals;
    std::vector<std::string> v1{ "this", "is", "an", "example" };

    std::cout << join_string(v1, " ");
    return 0;
}