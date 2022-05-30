#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../TTable/TSortTable.h"
#include "TArrayTable.h"
#include "TScanTable.h"

using namespace std;

void main() {
	TScanTable ts;
	TRecord insertRec;
	srand(time(NULL));

	for (int i = 0; i < 5; i++) {
		insertRec.key = rand()%100;
		insertRec.val = "value" + i;
		//t.insert(insertRec);
		ts.insert(insertRec);
	}

	cout << ts;
	TSortTable t(ts);
	cout << t;
	int lastEff = t.getEff();
	cout << lastEff;

	t.find(3);
	cout << "\n" << t.getEff() - lastEff << endl;

	t.del(2);
	cout << t << endl;

	t.sort();
	cout << t;
}