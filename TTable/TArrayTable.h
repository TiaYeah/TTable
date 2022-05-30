#pragma once
#include "TTable.h"

class TArrayTable : public TTable
{
protected:
    TRecord* mas;
    int maxSize, curr;
public:
	TArrayTable(int _maxSize = 100) 
	{
		maxSize = _maxSize;
		mas = new TRecord[maxSize];
		curr = -1;
	}

	~TArrayTable() { delete[] mas; }

	bool isFull() const { return dataCount == maxSize; }

	void reset() { curr = 0; }

	bool isEnd() { return curr == dataCount; }

	void goNext() { curr++; }

	TRecord getCurrRec() { return mas[curr]; }

	int getSize() { return maxSize; }
};

