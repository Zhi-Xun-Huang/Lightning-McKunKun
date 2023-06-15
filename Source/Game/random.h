#include <windows.h>
#include <random>

using namespace std;

int random(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> range(min, max);
	return range(gen);
}