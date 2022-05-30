#pragma once
#include "THashTable.h"
class TArrayHashTable : public THashTable
{
    TRecord* mas;
    int size, step, curr;
    TRecord free, del;
public:
    TArrayHashTable(int _size = 100, int _step= 7)
    {
        size = _size;
        step = _step;
        mas = new TRecord[size];
        free.key = -1;
        del.key = -2;
        for (int i = 0; i < size; ++i)
        {
            mas[i] = free;
        }
    }
    int getSize() { return size; }
    TRecord getCurrentRecord();
    bool find(TKey key)
    {
        int pos = HashFunc(key) % size, delPos = -1;
        bool res = false;
        for (int i = 0; i < size; i++) {
            eff++;
            if (mas[pos] == free) {
                curr = pos;
                break;
            }
            else if (mas[pos].key == key) {
                curr = pos;
                res = true;
                break;
            }
            else if (mas[pos] == del && delPos == -1) {
                delPos = pos;
            }
            pos = (pos + step) % size;
        }
        if (delPos != -1 && res == false) {
            curr = delPos;
        }
        return res;
    }
    bool insert(TRecord rec)
    {
        if (isFull() || find(rec.key)) {
            return false;
        }
        mas[curr] = rec;
        dataCount++;
        eff++;
        return true;
    }
    bool del(TKey key)
    {
        if (isEmpty() || !find(key)) {
            return false;
        }
        mas[curr] = del;
        dataCount--;
        eff++;
        return true;
    }
    void reset()
    {
        for (curr = 0; curr < size; curr++) {
            if (mas[curr] != free && mas[curr] != del) {
                return;
            }
        }
    }
    void goNext()
    {
        for (curr = 0; curr < size; curr++) {
            if (mas[curr] == free || mas[curr] == del) {
                return;
            }
        }
    }
    bool isFull()
    {
        return curr == size;
    }
    bool isEnd()
    {
        return curr == dataCount;
    }
};

