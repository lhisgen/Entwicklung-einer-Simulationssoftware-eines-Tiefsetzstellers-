#pragma once
#include "AbstractModel.h"
class CControllableObject {
protected:
	double minVal;
	double maxVal;
	string name;
	double actualVal;
	CAbstractController *pCtr;
public:
	CControllableObject();
	CControllableObject(double _minVal, double _actVal, double _maxVal, string _name, CAbstractController * _pCtr);
	virtual ~CControllableObject();
	double getMaxVal();
	double getMinVal();
	double getActualVal();
	string getName();
	void setActualValue(double _actualValue);
};

