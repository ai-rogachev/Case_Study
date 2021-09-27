#include <iostream>
#include <vector>
#include <string>
#include <limits>

namespace RabinCarpMatcher
{
	unsigned char getUchar(const char& i)
	{
		return static_cast<unsigned char>(i);
	}

	std::vector<std::size_t> Matcher(
		const std::string& text,
		const std::string& pattern)
	{
		std::vector<std::size_t> res;

		std::size_t base = 301;
		std::size_t p = std::numeric_limits<std::size_t>::max();
		std::size_t tmp = p / base;
		while (p > tmp)
			p >>= 1;

		auto txtLength = text.length();
		auto ptnLength = pattern.length();
		if (ptnLength == 0 || ptnLength > txtLength)
			return res;
		std::uint64_t hash_ptn = 0;
		std::uint64_t hash_txt = 0;

		std::size_t h = 0;
		for (std::size_t i = 0; i < ptnLength; ++i)
		{
			h = h == 0 ? 1 : (h * base) % p;
			hash_ptn = (hash_ptn * base + getUchar(pattern[i])) % p;
			hash_txt = (hash_txt * base + getUchar(text[i])) % p;
		}

		for (std::size_t i = 0; i <= txtLength - ptnLength; ++i)
		{
			if (hash_ptn == hash_txt)
			{
				if (text.compare(i, ptnLength, pattern) == 0)
					res.push_back(i);
			}
			if (i != txtLength - ptnLength)
			{
				auto tmp = (getUchar(text[i]) * h) % p;
				tmp = (hash_txt + p - tmp) % p;
				tmp = (tmp * base) % p;
				hash_txt = (tmp + getUchar(text[i + ptnLength])) % p;
			}
		}
		return res;
	}
}

int main()
{
	std::string text;
	std::string pattern;

	std::cin >> pattern;
	std::cin >> text;

	auto res = RabinCarpMatcher::Matcher(text, pattern);
	for (auto& i : res)
		std::cout << i << " ";

	return 0;
}