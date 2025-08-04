#include "pch.h"
#include "AbstractView.h"



CAbstractView::CAbstractView(CAbstractModel * _ptrModel)
	:ptrModel(_ptrModel), xWindowSizeStart(1), yWindowSizeStart(1)
{
	ptrModel->registerView(this);
	
}

CAbstractView::~CAbstractView()
{}



void CAbstractView::setWindowSizeStart(int _xWindowSizeStart, int _yWindowSizeStart)
{
	xWindowSizeStart = _xWindowSizeStart;
	yWindowSizeStart = _yWindowSizeStart;
}

void CAbstractView::CalcSizeOfView(int _xCurrentWindowSize, int _yCurrentWindowSize, CDC* pDC)
{
	xCurrentWindowSize = _xCurrentWindowSize;
	yCurrentWindowSize = _yCurrentWindowSize;

	xFactor = static_cast<double>(xCurrentWindowSize) / xWindowSizeStart;
	yFactor = static_cast<double>(yCurrentWindowSize) / yWindowSizeStart;

	xPosition = (xWindowSizeStart / 2 + xWindowSizeStart / 16) * xFactor;
	yPosition = yWindowSizeStart / 8 * yFactor;


}