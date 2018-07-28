#pragma once
#include <vector>
#include <mutex>

template<class T>
class ThreadSafeVector
{
public:
	ThreadSafeVector();
	~ThreadSafeVector();
	bool empty() const;
	void push(const T & value);
	void pop(T & result);

private:
	std::vector<T> l;

	mutable std::mutex m;
};

