#define USE_PROFILE

#include <iostream>
#include "performanceProfiler.h"

using namespace std;

void main()
{

	int count = 0;
	for(int cycle = 0; cycle < 100; cycle++)
	{
		SCOPE_PROFILE("root", test);
		for (int i = 0; i < 100; i++)
		{
			PROFILE_START("roop100");
			count+= 1;
			printf("%d\n", count);
			//for (int j = 0; j < 100; j++)
			//{
			//	PROFILE("roop10000");
			//	for (int k = 0; k < 100; k++)
			//	{
			//		PROFILE("roop1000000");
			//	}
			//}
			PROFILE_END("roop100");
			
		}
	}

	printf("%d\n", count);
}