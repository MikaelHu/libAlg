#include <stdio.h>
#include <iostream>
#include <ctime>
#include <cassert>
#include <random>
#include <functional>
#include <vector>
#include "radixSort.h"

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
	std::uniform_int_distribution<int> dis_short(0, MAX_NUM);
	auto dice_int = std::bind(dis_int, engine);
	auto dice_short = std::bind(dis_short, engine);

	//integer
	std::vector<int> integer_array;
	integer_array.reserve(MAX_NUM);
	for (int i = 0; i < MAX_NUM; i++)
		integer_array.emplace_back(dice_int());

	auto start = clock();
	radixSort(&integer_array[0], integer_array.size());
	std::cout << "\nradixSort integer_array Time ms: ";
	std::cout << (((double)clock() - start)) << std::endl;
	//print_array(&integer_array[0], integer_array.size());

	//short
	std::vector<int> short_array;
	short_array.reserve(MAX_NUM);
	for (int i = 0; i < MAX_NUM; i++)
		short_array.emplace_back(dice_short());

	start = clock();
	radixSort(&short_array[0], short_array.size());
	std::cout << "\nradixSort short_array Time ms: ";
	std::cout << (((double)clock() - start)) << std::endl;
	//print_array(&short_array[0], short_array.size());


	//int integer_array[]{100, 1001, 24, 317, 314, 2000, 2009, 7009};
	//short short_array[]{10, 20, 11, 317, 314, 510, 12, 709};

	//auto start = clock();
	//radixSort(integer_array, sizeof(integer_array) / sizeof(int));
	//std::cout << "\nradixSort integer_array Time ms: ";
	//std::cout << (((double)clock() - start)) << std::endl;
	//print_array(integer_array, sizeof(integer_array) / sizeof(int));

	//start = clock();
	//radixSort(short_array, sizeof(short_array) / sizeof(short));
	//std::cout << "\nradixSort short_array Time ms: ";
	//std::cout << (((double)clock() - start)) << std::endl;
	//print_array(short_array, sizeof(short_array) / sizeof(short));

	return 0;
}