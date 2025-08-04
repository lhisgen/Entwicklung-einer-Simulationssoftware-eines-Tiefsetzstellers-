#include "pch.h"
#include "ControllableObject.h"


CControllableObject::CControllableObject()
	: minVal(0)
	, maxVal(100) 
	, actualVal(50) 
	, name("")
	, pCtr(NULL)
{}

CControllableObject::CControllableObject(double _minVal, double _actVal, double _maxVal, string _name, CAbstractController * _pCtr)
	: minVal(_minVal)
	, maxVal(_maxVal)
	, actualVal(_actVal)
	, name(_name)
	, pCtr(_pCtr)
{}


CControllableObject::~CControllableObject()
{}


double CControllableObject::getMaxVal() {
	return maxVal;
}

double CControllableObject::getMinVal() {
	return minVal;
}

double CControllableObject::getActualVal() {
	return actualVal;
}
string CControllableObject::getName() {
	return name;
}

void CControllableObject::setActualValue(double _actualValue) {
	
	if ((_actualValue >= minVal) && (_actualValue <= maxVal))
	{
		
		actualVal = _actualValue;


	}
}
