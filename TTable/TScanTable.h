#pragma once
#include "TArrayTable.h"

class TScanTable : public TArrayTable
{
public:
	TScanTable(int size = 100) : TArrayTable(size) {}

	bool find(TKey key) {
		for (int i = 0; i < dataCount; i++) {
			eff++;
			if (key == mas[i].key) {
				curr = i;
				return true;
			}
		}
		curr = dataCount;
		return false;
	}

	bool insert(TRecord rec) {
		if (isFull()) return false;
		if (find(rec.key)) return false;

		mas[curr] = rec;
		dataCount++;
		eff++;
		return true;
	}

	bool del(TKey key) {
		if (isEmpty()) return false;
		if (!find(key)) return false;

		mas[curr] = mas[dataCount - 1];
		dataCount--;
		eff++;
		return true;
	}
};

