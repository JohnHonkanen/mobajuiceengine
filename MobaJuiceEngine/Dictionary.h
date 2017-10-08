/*
	Dictionary facade for map.
	Dev: John Honkanen
*/

#pragma once
#include <map>
template <class T>
class Dictionary
{
public:
	Dictionary() {};
	~Dictionary() {};

	virtual T Get(std::string index);
	virtual void Save(std::string indexName, T object);
	virtual void RemoveObject(std::string index);
private:
	std::map<std::string, T> dictionary;
};

/*
	Gets the Object at the index
*/
template<class T>
inline T Dictionary<T>::Get(std::string index)
{
	return dictionary[index];
}

/*
	Saves the Object into an index.
*/
template<class T>
inline void Dictionary<T>::Save(std::string indexName, T object)
{
	dictionary.insert(std::pair<std::string, T>(indexName, object));
}

/*
	Removes theO Object
*/
template<class T>
inline void Dictionary<T>::RemoveObject(std::string index)
{
	dictionary.erase(index);
}

