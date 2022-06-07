#pragma once
#include "TArrayTable.h"
#include "TScanTable.h"

class TSortTable : public TArrayTable
{
public:
    TSortTable(int size = 100) : TArrayTable(size) {}
    TSortTable(TScanTable& st) : TArrayTable(st.getSize())
    {
		st.reset();
        for (int i = 0; i < st.getDataCount(); i++) {
            mas[i] = st.getCurrRec();
			dataCount++;
			st.goNext();
        }

        sort();
    }
	void qSort(int s, int f)
	{
		int s1 = s, f1 = f;
		int mid = (s + f) / 2;
		TKey midEl = mas[mid].key;
		while (s1 < f1)
		{
			while (mas[s1].key < midEl)
			{
				s1++;
				eff++;
			}
			while (mas[f1].key > midEl)
			{
				f1--;
				eff++;
			}
			if (s1 <= f1)
			{
				TRecord tmp = mas[s1];
				mas[s1] = mas[f1];
				mas[f1] = tmp;
				s1++;
				f1--;
			}
		}
		if (s < f1)
		{
			qSort(s, f1);
		}
		if (s1 < f)
		{
			qSort(s1, f);
		}
	}
	void sort()
	{
		for (int i = 0; i < dataCount - 1; i++) {
			int min_index = i;
			for (int j = i + 1; j < dataCount; j++) {
				if (mas[j] < mas[min_index]) {
					min_index = j;
				}
			}
			if (min_index != i) {
				TRecord tmp = mas[i];
				mas[i] = mas[min_index];
				mas[min_index] = tmp;
			}
		}
	}
    bool find(TKey key)
	{
		int left = 0, right = dataCount - 1, mid;
		while (left <= right) {
			eff++;
			mid = (left + right) / 2;
			if (mas[mid].key < key) {
				left = mid + 1;
			}
			else if (mas[mid].key > key) {
				right = mid - 1;
			}
			else {
				curr = mid;
				return true;
			}
		}
		curr = left;
		return false;
	}
	bool insert(TRecord rec)
	{
		if (isFull() || find(rec.key)) {
			return false;
		}
		for (int i = dataCount; i > curr; i--) {
			mas[i] = mas[i - 1];
		}
		mas[curr] = rec;
		dataCount++;
		eff++;
		return true;
	}
	bool del(TKey key)
	{
		if (!find(key) || isEmpty()) {
			return false;
		}
		for (int i = curr; i < dataCount - 1; i++) {
			mas[i] = mas[i + 1];
			eff++;
		}
		dataCount--;

		return true;
	}

	void print(std::ostream& os)
	{
		for (int i = 0; i < dataCount; i++) {
			os << mas[i] << std::endl;
		}
		os << std::endl;
	}
};

