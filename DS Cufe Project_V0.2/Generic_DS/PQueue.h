#pragma once
#include "Queue.h"

template <typename T>
class PQueue :
	public Queue
{

	bool enqueue(const T& newEntry);



};

template<typename T>
inline bool PQueue<T>::enqueue(const T& newEntry)
{
	return false;
}
