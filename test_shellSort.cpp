#include <stdio.h>
#include <iostream>
#include <ctime>
#include <cassert>
#include <random>
#include <functional>
#include <vector>
#include "shellSort.h"


template <typename T>
void print_array(const T array[], int nsize) {
	for (int i = 0; i < nsize; i++)
		printf("%d\t", *(array + i));
	printf("\n");
}

#define MAX_NUM 1000*1000

int main(int argc, char** argv) {
	std::default_random_engine engine(time(NULL));
	std::uniform_int_distribution<int> dis_int(0, MAX_NUM);
	auto dice_int = std::bind(dis_int, engine);

	//integer
	std::vector<int> integer_array;
	integer_array.reserve(MAX_NUM);
	for (int i = 0; i < MAX_NUM; i++)
		integer_array.emplace_back(dice_int());

	auto start = clock();
	shellSort(&integer_array[0], integer_array.size());
	std::cout << "\nshellSort integer_array Time ms: ";
	std::cout << (((double)clock() - start)) << std::endl;
	//print_array(&integer_array[0], integer_array.size());

	return 0;
}