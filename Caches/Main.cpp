#include <iostream>
#include <fstream>
#include "./Caches/Cache.h"
#include "./Caches/CacheLFU.h"
#include "./Caches/CacheRNG.h"
#include "./Caches/CacheLRU.h"

//Data that cache store
struct TestStruct
{
	int id;
};

int main()
{
	CacheLFU<TestStruct> cacheLFU;

	size_t input_count, cache_size, hits = 0;
	std::cin >> cache_size >> input_count;

	cacheLFU.SetSize(cache_size);

	for (size_t i = 0; i < input_count; i++) {
		int a = 0;
		std::cin >> a;
		TestStruct input = { a };
		if (cacheLFU.LookUp(&input))
			hits++;
	}
	std::cout << hits;

	return 0;
}