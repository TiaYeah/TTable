#pragma once

template <class T>

class TStack
{
	int size;
	T* mas;
	int NumLast;
public:
	TStack(int _size = 10)
	{
		if (size < 0)
			throw size;
		size = _size;
		mas = new T[size];
		NumLast = -1;
	}
	TStack(const TStack& c)
	{
		size = c.size;
		mas = new T[size];
		NumLast = c.NumLast;
		for (int i = 0; i <= NumLast; i++)
		{
			mas[i] = c.mas[i];
		}
	}
	~TStack()
	{
		delete[] mas;
	}
	bool IsEmpty() const
	{
		return (NumLast == -1);
	}
	bool IsFull() const
	{
		return(NumLast == size - 1);
	}
	void ClearStack()
	{
		NumLast = -1;
	}
	int GetNumLast()
	{
		return NumLast;
	}
	void Push(const T& el)
	{
		if (IsFull())
			throw("Stack is full");
		mas[NumLast + 1] = el;
		NumLast++;
	}
	T Pop()
	{
		if (IsEmpty())
			throw("Stack is empty");
		NumLast--;
		return mas[NumLast + 1];
	}
	T Top()
	{
		return(mas[NumLast]);
	}
	bool  operator==(TStack c)
	{
		if (NumLast != c.NumLast)
			return false;
		else
			for (int i = 0; i <= NumLast; i++)
				if (mas[i] != c.mas[i])
					return false;
		return true;
	}
	bool  operator!=(TStack c)
	{
		if (NumLast != c.NumLast)
			return true;
		else
			for (int i = 0; i <= NumLast; i++)
				if (mas[i] != c.mas[i])
					return true;
		return false;
	}
};

