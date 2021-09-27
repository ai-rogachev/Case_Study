#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>
#include <string>
#include <fstream>

struct point
{
	int x;
	int y;
};

using points_arr = std::vector<point>;
using points_arr_it = points_arr::const_iterator;

bool sortByX(const point& a, const point& b)
{
	return a.x < b.x;
}

bool sortByY(const point& a, const point& b)
{
	return a.y < b.y;
}

double squareDist(const point& a, const point& b)
{
	double deltaX = a.x - b.x;
	double deltaY = a.y - b.y;

	return deltaX * deltaX + deltaY * deltaY;
}

double bruteForce(const points_arr_it& begin, const points_arr_it& end)
{
	double min = std::numeric_limits<double>::max();
	for (auto i = begin; i != end; ++i)
	{
		for (auto j = std::next(i); j != end; ++j)
		{
			double d = squareDist(*i, *j);
			if (d < min)
				min = d;
		}
	}
	return min;
}

double closestDistInStrip(points_arr& pointsInStrip, double minSquareDist)
{
	auto ptArrBegin = pointsInStrip.begin();
	auto ptArrEnd = pointsInStrip.end();

	for (auto it = ptArrBegin; it != ptArrEnd; ++it)
	{
		for (auto itNext = std::next(it); itNext != ptArrEnd; ++itNext)
		{
			double distY = it->y - itNext->y;
			double squareDistY = distY * distY;

			if (squareDistY > minSquareDist)
				break;

			double squareDistInStrip = squareDist(*it, *itNext);
			if (squareDistInStrip < minSquareDist)
				minSquareDist = squareDistInStrip;
		}
	}
	return minSquareDist;
}

double closestDist(const points_arr& sortedPointsByY, points_arr_it begin, points_arr_it end)
{
	auto subArraySize = std::distance(begin, end);
	if (subArraySize <= 3)
		return bruteForce(begin, end);

	auto middle = std::next(begin, subArraySize / 2);

	points_arr sortedPointsByYLeft;
	points_arr sortedPointsByYRight;

	for (auto& point : sortedPointsByY)
	{
		if (point.x <= middle->x)
			sortedPointsByYLeft.emplace_back(point);
		else
			sortedPointsByYRight.emplace_back(point);
	}

	double squareDistLeft = closestDist(sortedPointsByYLeft, begin, middle);
	double squareDistRight = closestDist(sortedPointsByYRight, middle, end);

	double minSquareDist = std::min(squareDistLeft, squareDistRight);

	points_arr pointsInStrip;
	for (auto& point : sortedPointsByY)
	{
		double distX = point.x - middle->x;
		double squareDistX = distX * distX;

		if (squareDistX < minSquareDist)
		{
			pointsInStrip.push_back(point);
		}
	}

	double distInStrip = closestDistInStrip(pointsInStrip, minSquareDist);
	return std::min(distInStrip, minSquareDist);
}

double closestDist(points_arr points)
{
	points_arr sortedPointsByX(points);
	std::sort(sortedPointsByX.begin(), sortedPointsByX.end(), sortByX);

	points_arr sortedPointsByY(points);
	std::sort(sortedPointsByY.begin(), sortedPointsByY.end(), sortByY);

	double closestSquareDist = closestDist(sortedPointsByY, sortedPointsByX.begin(), sortedPointsByX.end());
	return sqrt(closestSquareDist);
}

int main()
{
	int points_count = 0;
	std::cin >> points_count;

	points_arr points(points_count);
	for (auto& point : points)
	{
		std::cin >> point.x >> point.y;
	}

	std::cout.precision(10);
	std::cout << closestDist(std::move(points)) << std::endl;

	return 0;
}

double test_closestPoints(std::string file_data)
{
	std::ifstream infile(file_data);
	points_arr P;

	int size = 0;
	infile >> size;
	P.reserve(size);

	while (size > 0)
	{
		int x, y;
		x = y = 0;
		infile >> x >> y;
		P.push_back({ x, y });
		--size;
	}
	return closestDist(P);
}