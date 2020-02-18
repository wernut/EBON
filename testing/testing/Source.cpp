#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

#include <chrono>

using namespace std;

int main()
{
	while (true)
	{
		auto start = std::chrono::system_clock::now();
		auto end = std::chrono::system_clock::now();
		chrono::duration<double> diff = end - start;
		float time = diff.count();
		float adjust = -(10.0f * sin(2 * M_PI * 0.25f * time + 1.0f) + 1.0f);
		cout << time << endl;
	}

	system("pause");
	return 0;
}