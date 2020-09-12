#pragma once
#include "Cache.h"
#include <vector>
#include <unordered_map>
template <typename T, typename Ktype = int>
class CacheRNG :
	public ICache<T, Ktype>
{
public:
	/*
	 * Trying to find *elem in cache
	 *
	 * If *elem in cache, return true
	 * If *elem not in cache, load it into cache and return false
	 */
	bool LookUp(const T* elem) override;

	//Set max size of the cache. Clear cache
	void SetSize(size_t new_size) override;

	//Print all elements' id in cache using std::cout (Should be possible to use std::cout with Ktype)
	void PrintCache() override;

	//Clear all data in cache
	void ClearCache() override;
private:
	typedef typename std::vector<T>::iterator list_it;
	size_t _size;

	/*
	* Cache array
	*
	* Access from outside the function CacheRNG::LookUp may brake whole cache
	*/
	std::vector<T> _cache;

	/*
	* Contain pairs of id and iterator to the element with this id in _cache
	*
	* Access from outside the function CacheRNG::LookUp may brake whole cache
	*/
	std::unordered_map<Ktype, list_it> _hash;

	bool IsFull() const;
};


template <typename T, typename Ktype>
bool CacheRNG<T, Ktype>::LookUp(const T* elem)
{
	auto hit = _hash.find(elem->id); //try to find elem in _cache

	if (hit == _hash.end()) { //if it not in cache
		if (IsFull()) { //if _cache is full, replace random element in _cache to elem
			size_t pos = std::rand() % _size;
			_hash.erase(_cache[pos].id);
			_cache[pos] = *elem;
			_hash[elem->id] = _cache.begin() + pos;
		}
		else { //if _cache not full, add elem to cache
			_cache.push_back(*elem);
			_hash[elem->id] = _cache.end() - 1;
		}
		return false;
	}

	//if elem in _cache, do nothing
	return true;
}

template <typename T, typename Ktype>
bool CacheRNG<T, Ktype>::IsFull() const
{
	return _cache.size() >= _size;
}

template <typename T, typename Ktype>
void CacheRNG<T, Ktype>::SetSize(size_t new_size)
{
	_size = new_size;
}

template <typename T, typename Ktype>
void CacheRNG<T, Ktype>::PrintCache()
{
	for (auto i = _cache.begin(); i != _cache.end(); i++)
		std::cout << i->id << " ";
	std::cout << "\n";
}

template <typename T, typename Ktype>
void CacheRNG<T, Ktype>::ClearCache()
{
	_hash.clear();
	_cache.clear();
}
