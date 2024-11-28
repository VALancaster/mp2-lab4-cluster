#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "stack.h"

template<typename T>
class TQueue
{
	size_t sz;
	TStack<T> leftStack;
	TStack<T> rightStack;
public:
	TQueue() : sz(0) {}
	size_t size() const
	{
		return sz;
	}
	bool IsEmpty() const
	{
		return sz == 0;
	}
	void Push(const T& value)
	{
		leftStack.push(value);
		sz++;
	}
	T Pop()
	{
		if (rightStack.IsEmpty())
		{
			while (!leftStack.IsEmpty())
			{
				rightStack.push(leftStack.getTop());
				leftStack.pop();
			}
		}
		T value = rightStack.getTop();
		rightStack.pop();
		sz--;
		return value;
	}
};

#endif
