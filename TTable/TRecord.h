#pragma once
#include <iostream>
#include <string>

typedef int TKey;
typedef std::string TValue;

struct TRecord {
	TKey key;
	TValue val;


	TRecord(TKey _key = -1, TValue _val = "")
	{
		key = _key;
		val = _val;
	}

	bool operator > (const TRecord& rec) const 
	{
		return key > rec.key;
	}

	bool operator < (const TRecord& rec) const 
	{
		return key < rec.key;
	}

	bool operator == (const TRecord& rec) const 
	{
		return key == rec.key;
	}

	bool operator != (const TRecord& rec) const 
	{
		return key != rec.key;
	}

	friend std::ostream& operator<< (std::ostream& os, const TRecord rec)
	{
		os << rec.key << " " << rec.val;
		return os;
	}
};
