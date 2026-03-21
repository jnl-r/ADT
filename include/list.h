#pragma once
#include <cstddef>

template <typename T>
class List
{
public:
	virtual ~List() = default;
	virtual void add(size_t i, const T &x) = 0;
	virtual T remove(size_t i) = 0;
	virtual T get(size_t i) const = 0;
	virtual T set(size_t i, const T &x) = 0;
	virtual size_t size() const = 0;
	virtual void clear() = 0;
};