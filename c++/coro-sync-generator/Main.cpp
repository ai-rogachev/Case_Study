/*
* Example generator impl on coroutines.
* Based on articales https://www.jacksondunstan.com/articles/6311
*/

//#define SERVICE
#include "MyCoroGen.h"

/// <summary>
/// Simple generator.
/// Create sequence of squares first 5 numbers.
/// </summary>
void TestCoroIterator()
{
    DebugLog("Calling coroutine");
    for (auto item : SquaresGenerator(10))
    {
        DebugLog(item);
    }
}

int main()
{
	TestCoroIterator();
	return 0;
}