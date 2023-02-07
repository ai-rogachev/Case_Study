#include <iostream>
#include <string>
#include <limits>
#include <fstream>

// this custom num_put outputs squares of all double
struct double_num_put : std::num_put<char>
{
	iter_type do_put(iter_type out, std::ios_base& str,
		char_type fill, double val) const
	{
		if (std::isnormal(val) || std::isfinite(val))
			return std::num_put<char>::do_put(out, str, fill, val);

		static constexpr char quates = '\"';
		*out++ = quates;
		std::num_put<char>::do_put(out, str, fill, val);
		*out++ = quates;

		return out;
	}
};

int main()
{
	std::ofstream file{ "foo.txt", std::ofstream::out };
	file.imbue(std::locale(std::cout.getloc(), new double_num_put));

	//std::cout.imbue(std::locale(std::cout.getloc(), new squaring_num_put));

	constexpr double qtNan = std::numeric_limits<double>::quiet_NaN();
	constexpr double inf = std::numeric_limits<double>::infinity();
	constexpr double signNan = std::numeric_limits<double>::signaling_NaN();

	file << qtNan << std::endl;
	file << 3.14f << std::endl;
  file << 7.62 << std::endl;
	file << 0.0 << std::endl;
	file << (DBL_MIN / 2.0) << std::endl;
	file << inf << std::endl;
	file << signNan << std::endl;

	return 0;
}