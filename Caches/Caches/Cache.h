#pragma once
/*
* Interface for cache classes
* 
* T is a datatype cache contain
* T should contain public element with name id and type Ktype
* 
* Ktype is a type of id
*/
template <typename T, typename Ktype = int>
class ICache
{
public:
	/*
	* Trying to find *elem in cache
	*
	* If *elem in cache, return true
	* If *elem not in cache, load it into cache and return false 
	*/
	virtual bool LookUp(const T* elem) = 0;

	
	//Set max size of the cache 
	virtual void SetSize(size_t new_size) = 0;

	//Print all elements' id in cache using std::cout (Should be possible to use std::cout with Ktype)
	virtual void PrintCache() = 0;

	//Clear all data in cache
	virtual void ClearCache() = 0;
};
