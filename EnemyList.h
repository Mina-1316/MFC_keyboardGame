#pragma once
#include "LinkedList.h"
#include <cmath>

class EnemyList : public CPointList{
private:
	CPoint vector;

	EnemyList() : CPointList() {
		this->vector.SetPoint(0, 0);
	}

	EnemyList(CPoint point, CPoint vector, EnemyList* prevPtr) :
		CPointList(point, (CPointList*)prevPtr) {
		this->vector = vector;
	}

	
	

};