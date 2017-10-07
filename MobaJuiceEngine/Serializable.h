#pragma once
/*
	Serialization template for saving and loading data. Inherit this and write your own implementation if you would like to save.
	Dev: John Honkanen
*/

class Serializable
{
public:
	template<class Archive>
	virtual void serialize(Archive & archive) = 0;
};

