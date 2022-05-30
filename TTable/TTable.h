#pragma once
#include "TRecord.h"

class TTable {
protected:
	int dataCount;
	int eff;

public:
	TTable() { dataCount = eff = 0; }

	virtual ~TTable() {}

	int getDataCount() const { return dataCount; }

	int getEff() const { return eff; }
	
	void clearEff() { eff = 0; }

	bool isEmpty() const { return dataCount == 0; }

	virtual bool isFull() const = 0;

	virtual bool find(TKey key) = 0;

	virtual bool insert(TRecord rec) = 0;

	virtual bool del(TKey key) = 0;

	virtual void reset() = 0;

	virtual bool isEnd() = 0;

	virtual void goNext() = 0;

	virtual TRecord getCurrRec() = 0;

	friend std::ostream& operator<< (std::ostream& os, TTable& t) {
		for (t.reset(); !t.isEnd(); t.goNext()) {
			os << t.getCurrRec() << std::endl;
		}
		return os;
	}
};

