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
	//Get the object at the index
	virtual T Get(std::string index);
	//Save the object at this index position
	virtual void Save(std::string indexName, T object);
	//Remove the object at this index position
	virtual void RemoveObject(std::string index);
private:
	std::map<std::string, T> dictionary;
};

/*
	Gets the Object at the index
	@param index	index position of the index
	@return T		the object at hte index
*/
template<class T>
inline T Dictionary<T>::Get(std::string index)
{

	return dictionary[index];
}

/*
	Saves the Object into an index.
	@param indexName	unique name of the object
	@param object		The object to be stored at index
*/
template<class T>
inline void Dictionary<T>::Save(std::string indexName, T object)
{
	dictionary.insert(std::pair<std::string, T>(indexName, object));
}

/*
	Removes theO Object
	@param index	the index of the object to be removed
*/
template<class T>
inline void Dictionary<T>::RemoveObject(std::string index)
{
	dictionary.erase(index);
}

