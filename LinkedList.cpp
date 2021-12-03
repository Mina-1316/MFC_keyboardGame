#include "LinkedList.h"
#include <cmath>

CPointList::CPointList() {
	this->prevIndex = nullptr;
	this->nextIndex = nullptr;

	this->point.SetPoint(0, 0);
}

CPointList::CPointList(CPoint point, CPointList* prevPtr) {
	this->prevIndex = prevPtr;
	this->nextIndex = nullptr;

	this->point.SetPoint(point.x, point.y);
}

CPointList::~CPointList() {
	prevIndex->nextIndex = this->nextIndex;
	if (nextIndex != nullptr) {
		nextIndex->prevIndex = this->prevIndex;
	}
	//delete this;
}

void CPointList::addElement(CPoint iPoint) {
	if (nextIndex == nullptr) {
		nextIndex = new CPointList(iPoint, this);
	}
	else {
		nextIndex->addElement(iPoint);
	}
}

void CPointList::deleteElement(int index) {
	if (index == 0) {
		this->~CPointList();
	}
	else {
		if (this->nextIndex != nullptr) {
			this->nextIndex->deleteElement(index - 1);
		}
	}
}

void CPointList::deleteElement() {
	this->~CPointList();
}

float CPointList::calcPointDist(CPoint iPoint) {
	using namespace std;

	return sqrt(pow(iPoint.x - this->point.x, 2) + pow(iPoint.y - this->point.y, 2));
}

