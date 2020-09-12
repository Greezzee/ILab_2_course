#pragma once
#include "Cache.h"
#include <list>
#include <unordered_map>
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
	size_t _size; //maximum size of _cache, _hash and _freq_hash

	/*
	* Cache list. It's always sorted by function CacheLFU::LookUp
	* It store CacheElem whitch sorted by freq ascending
	*
	* Access from outside the function CacheLFU::LookUp may brake whole cache 
	*/
	std::list<CacheElem> _cache;

	/*
	* Contain pairs of id and iterator to the element with this id in _cache
	*
	* Access from outside the function CacheLFU::LookUp may brake whole cache  
	*/
	std::unordered_map<Ktype, list_it> _hash;

	/*
	* Contain pairs of frequency and iterator to thee LAST element with this frequency in _cache
	* Used for O(1) sorting _cache in CacheLFU::LookUp
	* If there are no elements in _cache with freq == n, it means _freq_hash[n] doesn't exist  
	*
	* Access from outside the function CacheLFU::LookUp may brake whole cache
	*/
	std::unordered_map<size_t, list_it> _freq_hash;

	//Check if number of elements in _cache bigger than _size
	bool IsFull() const;
};


template <typename T, typename Ktype>
bool CacheLFU<T, Ktype>::LookUp(const T* elem)
{
	auto hit = _hash.find(elem->id); //finding element in cache

	if (hit == _hash.end()) { //if it not in cache
		if (_cache.begin() == _cache.end()) { //special code to put first element into _cache
			_cache.push_front({ *elem, 1 });
			_hash[elem->id] = _cache.begin();
			_freq_hash[1] = _cache.begin();
		}
		else {

			if (IsFull()) { //if cache is full, pop element with lowest freq
				_hash.erase(_cache.begin()->data.id);
				if (_freq_hash[_cache.begin()->freq] == _cache.begin())
					_freq_hash.erase(_cache.begin()->freq);
				_cache.pop_front();
			}

			if (_cache.begin()->freq != 1) { //if _freq_hash[1] doesn't exist, put new element to begin
				_cache.insert(_cache.begin(), { *elem, 1 });
				_hash[elem->id] = _cache.begin();
				_freq_hash[1] = _cache.begin();
			}
			else { //put new element as far as possible keeping _cache sorted by freq
				auto insert_pos = _freq_hash[_cache.begin()->freq]; //find position for new element
				_cache.insert(std::next(insert_pos), { *elem, 1 });
				_hash[elem->id] = std::next(insert_pos);
				_freq_hash[1] = std::next(insert_pos);
			}
		}
		return false;
	}
	else { //if it in cache, add 1 to freq and sort _cache

		auto hit_it = hit->second;
		auto prev_hit_it = hit_it == _cache.begin() ? hit_it : std::prev(hit_it);
		auto next_freq_end = _freq_hash.find(hit_it->freq + 1);
		bool remove_freq = false;
		bool move_freq = false;

		//if hit_it is last element with freq = n, set flag that _freq_hash[n] should be erased
		if (_freq_hash[hit_it->freq] == hit_it && (hit_it == _cache.begin() || std::prev(hit_it)->freq != hit_it->freq))
			remove_freq = true;
		//if hit_it isn't last element with freq = n, but _freq_hash[n] == hit_it, set flag that _freq_hash[n] should be changed
		else if (_freq_hash[hit_it->freq] == hit_it && std::prev(hit_it)->freq == hit_it->freq)
			move_freq = true;

		if (next_freq_end == _freq_hash.end()) { //if _freq_hash[n + 1] doesn't exist
			_cache.splice(std::next(_freq_hash[hit_it->freq]), _cache, hit_it, std::next(hit_it));
			_freq_hash[hit_it->freq + 1] = hit_it;
		}
		else {
			_cache.splice(std::next(_freq_hash[hit_it->freq]), _cache, hit_it, std::next(hit_it));
		}

		if (remove_freq) //_freq_hash[n] erased
			_freq_hash.erase(hit_it->freq);
		if (move_freq) //_freq_hash[n] changed and now point to last element with freq == n
			_freq_hash[hit_it->freq] = prev_hit_it;

		hit_it->freq++;
	}

	return true;
}

template <typename T, typename Ktype>
bool CacheLFU<T, Ktype>::IsFull() const
{
	return _cache.size() >= _size;
}

template <typename T, typename Ktype>
void CacheLFU<T, Ktype>::SetSize(size_t new_size)
{
	_size = new_size;
	ClearCache();
}

template <typename T, typename Ktype>
void CacheLFU<T, Ktype>::PrintCache()
{
	for (auto i = _cache.begin(); i != _cache.end(); i++)
		std::cout << i->data.id << "(" << i->freq << ") ";
	std::cout << "\n";
}

template <typename T, typename Ktype>
void CacheLFU<T, Ktype>::ClearCache()
{
	_hash.clear();
	_cache.clear();
	_freq_hash.clear();
}
