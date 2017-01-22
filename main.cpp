#include <iostream>
#include "LinkedList.h"
#include "PerformanceMeasure.h"

static unsigned int gValue = 0;
struct Data
{
	Data() :a(gValue++), b(gValue++) {}
	int a;
	int b;
};

void main()
{
	PerformanceMeasure pm;
	LinkedList<Data> list;

	pm.Start();
	for (int i = 0; i < 10; ++i)
	{
		list.Insert(Data());
	}
	pm.End();
	cout << "LinkedList Performance Time : " << pm.GetEplaseTime() << "ms" << endl;
	list.ShowList();
}