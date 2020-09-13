#pragma once
#include "Cache.h"
#include <list>
#include <unordered_map>
#include <cassert>
template <typename T, typename Ktype = int>
class CacheLFU :
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

	//Store how many times data is called from cache (freq)
	struct CacheElem {
		T data;
		size_t freq;
	};

	typedef typename std::list<CacheElem>::iterator list_it;
	size_t size_; //maximum size of _cache, _hash and _freq_hash

	/*
	* Cache list. It's always sorted by function CacheLFU::LookUp
	* It store CacheElem whitch sorted by freq ascending
	*
	* Access from outside the function CacheLFU::LookUp may brake whole cache 
	*/
	std::list<CacheElem> cache_;

	/*
	* Contain pairs of id and iterator to the element with this id in _cache
	*
	* Access from outside the function CacheLFU::LookUp may brake whole cache  
	*/
	std::unordered_map<Ktype, list_it> hash_;

	/*
	* Contain pairs of frequency and iterator to thee LAST element with this frequency in _cache
	* Used for O(1) sorting _cache in CacheLFU::LookUp
	* If there are no elements in _cache with freq == n, it means _freq_hash[n] doesn't exist  
	*
	* Access from outside the function CacheLFU::LookUp may brake whole cache
	*/
	std::unordered_map<size_t, list_it> freq_hash_;

	//Check if number of elements in _cache bigger than _size
	bool IsFull() const;

	//Remove least used element from cache
	void PopFront();

	//Remove least used element from cache if cache is full. Add new element to cache after it
	void AddNewElem(const T* elem);

	//Increase freq of element in hit_it and reorganize _cache to keep it sorted
	void AccessToCache(list_it hit_it);
};


template <typename T, typename Ktype>
bool CacheLFU<T, Ktype>::LookUp(const T* elem)
{
	auto hit = hash_.find(elem->id); //finding element in cache

	if (hit == hash_.end()) { //if it not in cache
		AddNewElem(elem);
		return false;
	}
	else  //if it in cache, add 1 to freq and sort _cache
		AccessToCache(hit->second);

	return true;
}

template <typename T, typename Ktype>
bool CacheLFU<T, Ktype>::IsFull() const
{
	return cache_.size() >= size_;
}

template <typename T, typename Ktype>
void CacheLFU<T, Ktype>::SetSize(size_t new_size)
{
	size_ = new_size;
	ClearCache();
}

template <typename T, typename Ktype>
void CacheLFU<T, Ktype>::PrintCache()
{
	for (auto i = cache_.begin(); i != cache_.end(); i++)
		std::cout << i->data.id << "(" << i->freq << ") ";
	std::cout << "\n";
}

template <typename T, typename Ktype>
void CacheLFU<T, Ktype>::ClearCache()
{
	hash_.clear();
	cache_.clear();
	freq_hash_.clear();
}

template <typename T, typename Ktype>
void CacheLFU<T, Ktype>::PopFront()
{
	hash_.erase(cache_.begin()->data.id);
	auto min_freq_it = freq_hash_.find(cache_.begin()->freq);
	assert(min_freq_it != freq_hash_.end());
	if (min_freq_it->second == cache_.begin())
		freq_hash_.erase(cache_.begin()->freq);
	cache_.pop_front();
}

template <typename T, typename Ktype>
void CacheLFU<T, Ktype>::AddNewElem(const T* elem)
{
	if (cache_.begin() == cache_.end()) {  //special code to put first element into _cache
		cache_.insert(cache_.begin(), { *elem, 1 });
		hash_[elem->id] = cache_.begin();
		freq_hash_[1] = cache_.begin();
	}
	else {
		if (IsFull()) { //if cache is full, pop element with lowest freq
			PopFront();
		}

		if (cache_.begin()->freq != 1) { //if _freq_hash[1] doesn't exist, put new element to begin
			cache_.insert(cache_.begin(), { *elem, 1 });
			hash_[elem->id] = cache_.begin();
			freq_hash_[1] = cache_.begin();
		}
		else { //put new element as far as possible keeping _cache sorted by freq
			auto insert_pos = freq_hash_[cache_.begin()->freq]; //find position for new element
			cache_.insert(std::next(insert_pos), { *elem, 1 });
			hash_[elem->id] = std::next(insert_pos);
			freq_hash_[1] = std::next(insert_pos);
		}
	}
}

template <typename T, typename Ktype>
void CacheLFU<T, Ktype>::AccessToCache(list_it hit_it)
{
	auto prev_hit_it = hit_it == cache_.begin() ? hit_it : std::prev(hit_it);
	auto next_freq_end = freq_hash_.find(hit_it->freq + 1);
	bool remove_freq = false;
	bool move_freq = false;

	auto hit_freq_end = freq_hash_.find(hit_it->freq);
	assert(hit_freq_end != freq_hash_.end());

	if (hit_freq_end->second == hit_it) {
		//if hit_it is last element with freq = n, set flag that _freq_hash[n] should be erased
		if (hit_it == cache_.begin() || std::prev(hit_it)->freq != hit_it->freq)
			remove_freq = true;
		else //if hit_it isn't last element with freq = n, but _freq_hash[n] == hit_it, set flag that _freq_hash[n] should be changed
			move_freq = true;
	}

	auto new_pos = next_freq_end == freq_hash_.end() ? hit_freq_end->second : next_freq_end->second;
	cache_.splice(std::next(new_pos), cache_, hit_it, std::next(hit_it));
	freq_hash_[hit_it->freq + 1] = hit_it;

	if (remove_freq) //_freq_hash[n] erased
		freq_hash_.erase(hit_it->freq);
	if (move_freq) //_freq_hash[n] changed and now point to last element with freq == n
		freq_hash_[hit_it->freq] = prev_hit_it;

	hit_it->freq++;
}