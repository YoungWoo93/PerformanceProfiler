#include <iostream>
#include "performanceProfiler.h"

using namespace std;

void main()
{

	int count = 0;
	for(int cycle = 0; cycle < 100; cycle++)
	{
		scopeProfiler s2("roop");
		for (int i = 0; i < 100; i++)
		{
			startProfile("test");
			scopeProfiler s2("roop100");
			count+= 1;
			printf("%d\n", count);
			for (int j = 0; j < 100; j++)
			{
				scopeProfiler s3("roop in 10000");
				for (int k = 0; k < 100; k++)
				{
					scopeProfiler s4("roop in 1000000");
				}
			}
		}
	}

	printf("%d\n", count);

}