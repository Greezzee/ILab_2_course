#pragma once
#include "Cache.h"
#include <list>
#include <unordered_map>
template <typename T, typename Ktype = int>
class CacheLRU :
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

    typedef typename std::list<T>::iterator list_it;
    size_t _size;

	/*
	* Cache list
	*
	* Access from outside the function CacheLFU::LookUp may brake whole cache
	*/
    std::list<T> _cache;

	/*
	* Contain pairs of id and iterator to the element with this id in _cache
	*
	* Access from outside the function CacheLRU::LookUp may brake whole cache
	*/
    std::unordered_map<Ktype, list_it> _hash;

    bool IsFull() const;
};


template <typename T, typename Ktype>
bool CacheLRU<T, Ktype>::LookUp(const T* elem)
{
	auto hit = _hash.find(elem->id); //try to find elem in cache

	if (hit == _hash.end()) { //if elem not in cache
		if (IsFull()) { //remove last element from cache
			_hash.erase(_cache.back().id);
			_cache.pop_back();
		}
		_cache.push_front(*elem); //put elem to cache
		_hash[elem->id] = _cache.begin();
		return false;
	}

	auto hit_it = hit->second; //if elem in cache, move it to beginning of _cache
	if (hit_it != _cache.begin())
		_cache.splice(_cache.begin(), _cache, hit_it, std::next(hit_it));
	return true;
}

template <typename T, typename Ktype>
bool CacheLRU<T, Ktype>::IsFull() const
{
	return _cache.size() >= _size;
}

template <typename T, typename Ktype>
void CacheLRU<T, Ktype>::SetSize(size_t new_size)
{
	_size = new_size;
}

template <typename T, typename Ktype>
void CacheLRU<T, Ktype>::PrintCache()
{
	for (auto i = _cache.begin(); i != _cache.end(); i++)
		std::cout << i->id << " ";
	std::cout << "\n";
}

template <typename T, typename Ktype>
void CacheLRU<T, Ktype>::ClearCache()
{
	_hash.clear();
	_cache.clear();
}

