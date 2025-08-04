#pragma once
#include "AbstractModel.h"
class CAbstractView {
public:
	CAbstractView(CAbstractModel * _ptrModel);
	virtual ~CAbstractView();
	virtual void update(CDC * pDC) = 0;
	void setWindowSizeStart(int _xWindowSizeStart, int _yWindowSizeStart);
	void CalcSizeOfView(int xWindowSize, int yWindowSize, CDC* pDC);
protected:
	CAbstractModel *ptrModel;
	int xPosition;
	int yPosition;
	double xFactor;
	double yFactor;
	
	int xCurrentWindowSize;
	int yCurrentWindowSize;

	int xWindowSizeStart;
	int yWindowSizeStart;
};

