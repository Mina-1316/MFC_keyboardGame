#pragma once
#include <atltypes.h>

class CPointList {
public:
	CPointList();
	CPointList(CPoint point, CPointList* prevPtr);

	~CPointList();

	float calcPointDist(CPoint iPoint);
	void deleteElement(int index);
	void deleteElement();
	void addElement(CPoint iPoint);

public:
	CPointList* prevIndex, * nextIndex;
	CPoint point;

};
