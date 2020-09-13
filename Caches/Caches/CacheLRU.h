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
    size_t size_;

	/*
	* Cache list
	*
	* Access from outside the function CacheLFU::LookUp may brake whole cache
	*/
    std::list<T> cache_;

	/*
	* Contain pairs of id and iterator to the element with this id in _cache
	*
	* Access from outside the function CacheLRU::LookUp may brake whole cache
	*/
    std::unordered_map<Ktype, list_it> hash_;

    bool IsFull() const;
};


template <typename T, typename Ktype>
bool CacheLRU<T, Ktype>::LookUp(const T* elem)
{
	auto hit = hash_.find(elem->id); //try to find elem in cache

	if (hit == hash_.end()) { //if elem not in cache
		if (IsFull()) { //remove last element from cache
			hash_.erase(cache_.back().id);
			cache_.pop_back();
		}
		cache_.push_front(*elem); //put elem to cache
		hash_[elem->id] = cache_.begin();
		return false;
	}

	auto hit_it = hit->second; //if elem in cache, move it to beginning of _cache
	if (hit_it != cache_.begin())
		cache_.splice(cache_.begin(), cache_, hit_it, std::next(hit_it));
	return true;
}

template <typename T, typename Ktype>
bool CacheLRU<T, Ktype>::IsFull() const
{
	return cache_.size() >= size_;
}

template <typename T, typename Ktype>
void CacheLRU<T, Ktype>::SetSize(size_t new_size)
{
	size_ = new_size;
}

template <typename T, typename Ktype>
void CacheLRU<T, Ktype>::PrintCache()
{
	for (auto i = cache_.begin(); i != cache_.end(); i++)
		std::cout << i->id << " ";
	std::cout << "\n";
}

template <typename T, typename Ktype>
void CacheLRU<T, Ktype>::ClearCache()
{
	hash_.clear();
	cache_.clear();
}

