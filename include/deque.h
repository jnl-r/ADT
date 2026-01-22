#pragma once
#include <cstddef>

template <typename T>
struct Deque
{
	// Adds x to the front of the deque.
	virtual void addFirst(const T& x) = 0;

	// Adds x to the back of the deque.
	virtual void addLast(const T& x) = 0;

	// Removes the item at the front of the deque.
	// Returns the removed item.
	virtual T removeFirst() = 0;

	// Removes the item at the back of the deque.
	// Returns the removed item.
	virtual T removeLast() = 0;

	// Returns (without removing) the item at the front of the deque.
	virtual const T peekFirst() const = 0;

	// Returns (without removing) the item at the back of the deque.
	virtual const T peekLast() const = 0;

	// Returns whether the structure is empty or not.
	virtual bool isEmpty() const = 0;

	// Clears (removes) the data structure of items.
	virtual void clear() = 0;

	virtual size_t size() const = 0;
};