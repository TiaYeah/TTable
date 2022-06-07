#pragma once
#include "TTreeTable.h"
class TBalTree : public TTreeTable
{
public:
	int leftTreeBalIns(TNode*& p) {
		eff++;
		int result = 0;

		if (p->balance == 1) {
			p->balance = 0;
			result = 0;
		}
		else if (p->balance == 0) {
			p->balance = -1;
			result = 1;
		}
		else {
			TNode* leftNode = p->pL;

			if (leftNode->balance == -1) {
				p->pL = leftNode->pR;
				leftNode->pR = p;
				p->balance = 0;
				leftNode->balance = 0;
				result = 0;
				p = leftNode;
			}
			else if (leftNode->balance == 1) {
				TNode* rightNode = leftNode->pR;

				leftNode->pR = rightNode->pR;
				p->pL = rightNode->pR;
				rightNode->pL = leftNode;
				rightNode->pR = p;

				if (rightNode->balance == -1) {
					rightNode->balance = 0;
					leftNode->balance = 1;
					p->balance = 1;
				}
				else {
					rightNode->balance = 1;
					leftNode->balance = 0;
					p->balance = 0;
				}

				result = 0;
				p = rightNode;
			}
		}

		return result;
	}

	int rightTreeBalIns(TNode*& p) {
		eff++;
		int result = 0;

		if (p->balance == 0) {
			p->balance = 1;
			result = 1;
		}
		else if (p->balance == -1) {
			p->balance = 0;
			result = 0;
		}
		else {
			TNode* rightNode = p->pR;

			if (rightNode->balance == 1) {
				p->pR = rightNode->pL;
				rightNode->pL = p;
				p->balance = 0;
				rightNode->balance = 0;
				result = 0;
				p = rightNode;
			}
			else if (rightNode->balance == -1) {
				TNode* leftNode = rightNode->pL;

				rightNode->pL = leftNode->pR;
				p->pR = leftNode->pL;
				leftNode->pR = rightNode;
				leftNode->pL = p;

				if (leftNode->balance == -1) {
					rightNode->balance = 0;
					leftNode->balance = -1;
					p->balance = 0;
				}
				else {
					rightNode->balance = -1;
					leftNode->balance = 0;
					p->balance = -1;
				}

				result = 0;
				p = leftNode;
			}
		}

		return result;
	}

	int leftTreeBalDel(TNode*& p) {
		eff++;
		int result = 0;

		if (p->balance == 1)
		{
			p->balance = 0;
			result = -1;
		}
		else if (p->balance == 0)
		{
			p->balance = -1;
			result = 0;
		}
		else {
			TNode* leftNode = p->pL;

			if (leftNode->balance == -1)
			{
				p->pL = leftNode->pR;
				leftNode->pR = p;

				leftNode->balance = 0;
				p->balance = 0;

				p = leftNode;
				result = -1;
			}
			else if (leftNode->balance == 1)
			{
				TNode* plpr = leftNode->pR;

				leftNode->pR = plpr->pL;
				plpr->pL = leftNode;
				p->pL = plpr->pR;
				plpr->pR = p;
				if (plpr->balance == -1)
				{
					p->balance = 1;
				}
				else
				{
					p->balance = 0;
				}
				if (plpr->balance == 1)
				{
					leftNode->balance = -1;
				}
				else
				{
					leftNode->balance = 0;
				}
				p = plpr;
				p->balance = 0;
				result = -1;
			}
			else
			{
				TNode* pp = p;
				TNode* plpl = leftNode->pL;
				TNode* plpr = leftNode->pR;

				p = leftNode;
				p->pL = plpl;
				p->pR = pp;
				pp->pL = plpr;
				leftNode->balance = 1;
				return 0;
			}
		}
		return result;
	}

	int rightTreeBalDel(TNode*& p) {
		eff++;
		int result = 0;

		if (p->balance == -1)
		{
			p->balance = 0;
			result = -1;
		}
		else if (p->balance == 0)
		{
			p->balance = 1;
			result = 0;
		}
		else
		{
			TNode* rightNode = p->pR;
			if (rightNode->balance == 1)
			{
				p->pR = rightNode->pL;
				rightNode->pL = p;

				rightNode->balance = 0;
				p->balance = 0;

				p = rightNode;
				result = -1;
			}
			else if (rightNode->balance == -1)
			{
				TNode* prpl = rightNode->pL;

				rightNode->pL = prpl->pR;
				prpl->pR = rightNode;
				p->pR = prpl->pL;
				prpl->pL = p;
				if (prpl->balance == 1)
				{
					p->balance = -1;
				}
				else
				{
					p->balance = 0;
				}
				if (prpl->balance == -1)
				{
					rightNode->balance = 1;
				}
				else
				{
					rightNode->balance = 0;
				}
				p = prpl;
				p->balance = 0;
				result = -1;
			}
			else
			{
				TNode* pp = p;
				TNode* prpl = rightNode->pL;
				TNode* prpr = rightNode->pR;

				p = rightNode;
				p->pL = pp;
				p->pR = prpr;
				pp->pR = prpl;
				rightNode->balance = -1;
				return 0;
			}
		}
		return result;
	}

	int insBalTree(TNode*& p, TRecord rec) {
		eff++;
		int result = 0;

		if (p == NULL) {
			p = new TNode(rec);
			result = 1;
			dataCount++;
		}
		else if (p->rec.key > rec.key) {
			int tmp = insBalTree(p->pL, rec);

			if (tmp == 1) {
				result = leftTreeBalIns(p);
			}
		}
		else {
			int tmp = insBalTree(p->pR, rec);

			if (tmp == 1) {
				result = rightTreeBalIns(p);
			}
		}

		return result;
	}

	int delBalTree(TNode*& p, TKey key) {
		eff++;
		int result = 0;

		if (p == NULL) {
			return result;
		}
		if (key > p->rec.key) {
			int tmp = delBalTree(p->pR, key);

			if (tmp != 0) {
				result = leftTreeBalDel(p);
			}
		}
		else if (key < p->rec.key) {
			int tmp = delBalTree(p->pL, key);

			if (tmp != 0) {
				result = rightTreeBalDel(p);
			}
		}
		else if (key == p->rec.key) {
			dataCount--;
			if (p->pL == NULL && p->pR == NULL) {
				delete p;
				p = NULL;
				result = -1;
			}
			else if (p->pL != NULL && p->pR == NULL) {
				p->rec = p->pL->rec;
				delete p->pL;
				p->pL = NULL;
				p->balance = 0;
				result = -1;
			}
			else if (p->pL == NULL && p->pR != NULL) {
				p->rec = p->pR->rec;
				delete p->pR;
				p->pR = NULL;
				p->balance = 0;
				result = 1;
			}
			else {
				TNode* leftNode = p->pL;
				TNode* rightNode = p->pR;
				TNode* pMax = findMax(leftNode);

				p->rec = pMax->rec;
				int tmp = delBalTree(p->pL, pMax->rec.key);

				if (tmp != 0) {
					result = rightTreeBalDel(p->pR);
				}
			}
		}
		return result;
	}

	TNode* findMax(TNode* p) const {
		while (p->pR != NULL) {
			p = p->pR;
		}
		return p;
	}

	bool insert(TRecord rec) {
		if (find(rec.key)) return false;

		insBalTree(pRoot, rec);
		return true;
	}

	bool del(TKey key) {
		if (!find(key)) return false;

		delBalTree(pRoot, key);
		return true;
	}

};

