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

void Test(const std::vector<TestStruct>& input, ICache<TestStruct>* cache, std::string message = "Test started", bool show_cache = false)
{
	std::cout << message << "\n";
	unsigned hits = 0;
	for (int i = 0; i < input.size(); i++) {
		bool out = cache->LookUp(&input[i]);
		
		if (show_cache) {
			std::cout << input[i].id << " ";
			if (out) {
				hits++;
				std::cout << "In Cache\n";
			}
			else
				std::cout << "Not in Cache\n";
			std::cout << "New cache: ";
			cache->PrintCache();
			std::cout << "\n";
		}
		else if (out)
			hits++;
		
	}
	if (input.size() != 0)
		std::cout << "Cache hits: " << hits << " out of " << input.size() << " (" << hits * 100 / input.size() << "%)\n";
	std::cout << "-------------Testing Exiting------------\n";
}

void LoadTest(std::string filename, std::vector<TestStruct>& input)
{
	std::ifstream file;
	file.open(filename);
	input.resize(0);
	int S;
	while (file >> S)
		input.push_back({ S });
	file.close();
}

struct SubjectForTest
{
	std::string name;
	ICache<TestStruct>* cache;
};

void TestSubjects(std::vector<SubjectForTest> subject, size_t cache_size, const std::vector<TestStruct>& input, std::string message = "Test started", bool show_cache = false)
{
	for (int i = 0; i < subject.size(); i++) {
		subject[i].cache->SetSize(cache_size);
		Test(input, subject[i].cache, subject[i].name + " " + message, show_cache);
		subject[i].cache->ClearCache();
	}
	std::cout << "\n\n";
}

int main()
{
	std::vector<TestStruct> input;
	CacheLFU<TestStruct> cacheLFU;
	CacheLRU<TestStruct> cacheLRU;
	CacheRNG<TestStruct> cacheRNG;
	std::vector<SubjectForTest> subject = { {"LFU", &cacheLFU}, {"LRU", &cacheLRU}, {"RNG", &cacheRNG} };

	// Writted by hands test 1 (
	LoadTest("Tests/Test1.txt", input);
	TestSubjects(subject, 5, input, "Test 1");
	input.clear();
	///////////////////////////////////////////////

	// Writted by hands test 2
	LoadTest("Tests/Test2.txt", input);
	TestSubjects(subject, 5, input, "Test 2");
	input.clear();
	///////////////////////////////////////////////

	// Writted by hands test 3
	LoadTest("Tests/Test3.txt", input);
	TestSubjects(subject, 5, input, "Test 3");
	input.clear();
	///////////////////////////////////////////////

	// Test with random data
	input.resize(0);
	for (unsigned i = 0; i < 100000; i++)
		input.push_back({ rand() % 1000 });
	TestSubjects(subject, 250, input, "Full Random Test");
	input.clear();
	///////////////////////////////////////////////

	// Simulate weekly internet serfing. One type of information interesting in weekdays, another in weekends
	input.resize(0);
	for (unsigned week = 0; week < 52; week++) {
		for (unsigned i = 0; i < 1 * 500; i++)
			input.push_back({ rand() % 120 });
		for (unsigned i = 0; i < 1 * 200; i++)
			input.push_back({ rand() % 120 + 80});
	}
	TestSubjects(subject, 100, input, "Week simulation test");
	input.clear();
	///////////////////////////////////////////////

	// Test with same median but random dispersion
	input.resize(0);
	for (int i = 0; i < 100000; i++)
	{
		if (rand() % 10 == 0)
			input.push_back({ rand() % 500 - 250});
		else if (rand() % 4 == 0)
			input.push_back({ rand() % 300 - 150});
		else
			input.push_back({ rand() % 150 - 75 });
	}

	TestSubjects(subject, 150, input, "Random disp test");
	input.clear();
	///////////////////////////////////////////////
	
	// Test with random median switches but same dispersion
	input.resize(0);
	int interest = 0;
	for (int i = 0; i < 400; i++)
	{
		if (rand() % 50 == 0) {
			if (rand() % 2)
				interest++;
			else
				interest--;
		}
		for (int j = 0; j < rand() % 50; j++)
			input.push_back({ rand() % 150 + interest * 100 });
	}

	TestSubjects(subject, 50, input, "Median switch test");
	input.clear();
	///////////////////////////////////////////////

	//Test with random median swithes but median has borders. Also sometimes have purely random elements
	input.resize(0);
	interest = 0;
	for (int i = 0; i < 100000; i++)
	{
		if (rand() % 20 == 0)
			interest = rand() % 10;

		if (rand() % 10 == 0)
			input.push_back({ rand() % 20000 });
		else {
			input.push_back({ rand() % 1000 + interest * 500 });
		}
	}

	TestSubjects(subject, 2000, input, "Median switch with borders");
	input.clear();
	///////////////////////////////////////////////

	//Test with constant count of median swithes
	input.resize(0);
	interest = 0;
	int median = rand() % 300;
	int median_switches = 10;
	int tests = 10 * 1000;
	for (int i = 0; i < tests; i++)
	{
		int jump = rand() % 200;
		if (i % (tests / median_switches) == 0)
			median = rand() % 400;
		input.push_back({ median + jump });
	}

	TestSubjects(subject, 25, input, "Constant median swithes");
	input.clear();
	///////////////////////////////////////////////
	return 0;
}