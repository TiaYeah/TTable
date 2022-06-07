#pragma once
#include "THashTable.h"
class TArrayHashTable : public THashTable
{
    TRecord* mas;
    int size, step, curr;
    TRecord free, delRec;
public:
    TArrayHashTable(int _size = 100, int _step = 7)
    {
        size = _size;
        step = _step;
        mas = new TRecord[size];
        free.key = -1;
        delRec.key = -2;
        for (int i = 0; i < size; ++i)
        {
            mas[i] = free;
        }
    }
    ~TArrayHashTable()
    {
        delete[] mas;
    }
    int getSize() { return size; }
    TRecord getCurrentRecord()
    {
        return mas[curr];
    }
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
            else if (mas[pos] == delRec && delPos == -1) {
                delPos = pos;
                curr = pos;
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
        mas[curr] = delRec;
        dataCount--;
        eff++;
        return true;
    }
    void reset()
    {
        for (curr = 0; curr < size; curr++) {
            if (mas[curr] != free && mas[curr] != delRec) {
                return;
            }
        }
    }
    void goNext()
    {
        for (curr++ ; curr < size; curr++) {
            if (mas[curr] != free && mas[curr] != delRec) {
                return;
            }
        }
    }
    bool isEnd()
    {
        return curr == size;
    }

    TRecord getCurrRec() {
        return mas[curr];
    }
    bool isFull() const
    {
        return curr == size;
    }

    void print(std::ostream& os)
    {
        for (reset(); !isEnd(); goNext()) {
            os << mas[curr] << std::endl;
        }
        reset();
        os << std::endl;
    }
};