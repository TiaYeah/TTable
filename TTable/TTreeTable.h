#pragma once
#include "TTable.h"
#include "TStack.h"

struct TNode
{
	TRecord rec;
	TNode* pL, * pR;
	int balance = 0;
	TNode(TRecord _rec) : rec(rec), pL(nullptr), pR(nullptr) {
		rec = _rec;
		pL = NULL;
		pR = NULL;
	}
};

class TTreeTable : public TTable
{
protected:
	TNode* pRoot, * pCurr, * pPrev;
	TStack<TNode*> st;
	int currPos;

public:
	TTreeTable() {
		pRoot = NULL;
		pCurr = NULL;
		pPrev = NULL;
		currPos = 0;
	}

	bool find(TKey key) {
		pCurr = pRoot;
		pPrev = NULL;

		while (pCurr != NULL) {

			eff++;
			if (pCurr->rec.key == key) return true;
			pPrev = pCurr;

			if (pCurr->rec.key > key) {
				pCurr = pCurr->pL;
			}
			else {
				pCurr = pCurr->pR;
			}
		}

		pCurr = pPrev;
		return false;
	}

	bool insert(TRecord rec) {
		if (find(rec.key)) return false;

		TNode* tmp = new TNode(rec);

		if (isEmpty()) {
			pRoot = tmp;
		}
		else {
			if (rec.key > pCurr->rec.key) {
				pCurr->pR = tmp;
			}
			else {
				pCurr->pL = tmp;
			}
		}
		eff++;
		dataCount++;
		return true;
	}

	bool del(TKey key) {
		if (!find(key)) return false;
		TNode* tmp = pCurr;

		if (pCurr->pR == NULL) {
			if (pPrev == NULL) {
				pRoot = pCurr->pL;
			}
			else {
				if (pCurr->rec.key > pPrev->rec.key) {
					pPrev->pR = pCurr->pL;
				}
				else {
					pPrev->pL = pCurr->pL;
				}
			}
		}
		else if (pCurr->pL == NULL) {
			if (pPrev == NULL) {
				pRoot = pCurr->pR;
			}
			else {
				if (pCurr->rec.key > pPrev->rec.key) {
					pPrev->pL = pCurr->pR;
				}
				else {
					pPrev->pR = pCurr->pR;
				}
			}
		}
		else {
			tmp = tmp->pL;
			pPrev = pCurr;

			while (tmp->pR != NULL) {
				pPrev = tmp;
				tmp = tmp->pR;
			}

			pCurr->rec = tmp->rec;
			if (pCurr->pL == tmp) {
				pPrev->pL = tmp->pL;
			}
			else {
				pPrev->pR = tmp->pL;
			}

			delete tmp;
		}

		dataCount--;
		eff++;
		return true;
	}

	TRecord getCurrRec() { return pCurr->rec; }


	void reset() {
		currPos = 0;
		pCurr = pRoot;
		st.ClearStack();
		if (pCurr) {
			while (pCurr->pL) {
				st.Push(pCurr);
				pCurr = pCurr->pL;
			}
		}
		st.Push(pCurr);
	}

	void goNext() {
		pCurr = st.Top();
		st.Pop();

		if (pCurr) {
			if (pCurr->pR) {
				pCurr = pCurr->pR;

				while (pCurr->pL) {
					st.Push(pCurr);
					pCurr = pCurr->pL;
				}
				st.Push(pCurr);

			}
			else {
				if (!st.IsEmpty()) {
					pCurr = st.Top();
				}
			}
			currPos++;
		}
	}

	bool isEnd() { return currPos == dataCount; }

	void printRec(std::ostream& os, TNode* node, int level) {
		if (node) {
			for (int i = 0; i < level; i++) {
				os << ' ';
			}

			os << node->rec.key << std::endl;
			printRec(os, node->pL, level + 1);
			printRec(os, node->pR, level + 1);
		}
	}

	void print(std::ostream& os) {
		printRec(os, pRoot, 0);
		os << std::endl;
	}

	void delTree(TNode* p)
	{
		if (p)
		{
			delTree(p->pL);
			delTree(p->pR);
			delete p;
		}
	}

	bool isFull() const { return false; }
};

