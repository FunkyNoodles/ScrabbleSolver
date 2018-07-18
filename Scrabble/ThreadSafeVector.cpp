#include "ThreadSafeVector.h"

template <class T>
ThreadSafeVector<T>::ThreadSafeVector()
{
}

template <class T>
ThreadSafeVector<T>::~ThreadSafeVector()
{
}

template<class T>
bool ThreadSafeVector<T>::empty() const
{
	std::lock_guard<std::mutex> lock(m);
	return l.empty();
}

template<class T>
void ThreadSafeVector<T>::push(const T & value)
{
	std::lock_guard<std::mutex> lock(m);
	l.push_back(value);
}

template<class T>
void ThreadSafeVector<T>::pop(T & result)
{
	std::lock_guard<std::mutex> lock(m);
	result = l.back();
	l.pop_back();
}
