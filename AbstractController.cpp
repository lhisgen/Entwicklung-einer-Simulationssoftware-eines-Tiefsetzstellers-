#include "pch.h"
#include "AbstractController.h"



CAbstractController::~CAbstractController()
{}


CAbstractController::CAbstractController(CPoint _org, CPoint _act, CAbstractModel* _pModel, CControllableObject* _ptrControllableObject)
	: org(_org)
	, act(_act)
	, hotWidth(10)
	, hotHeight(10)
	, minPx(50) //10
	, maxPx(100) //50
	, ptrModel(_pModel)
	, ptrControllableObject(_ptrControllableObject)
{
	
	ptrModel->registerCtr(this);
}


CAbstractController::CAbstractController(CPoint _org, CPoint _act, int _hotWidth, int _hotHeight, int _minPx, int _maxPx, CAbstractModel *_pModel, CControllableObject * _ptrControllableObject)
	: org(_org)
	, act(_act)
	, hotWidth(_hotWidth)
	, hotHeight(_hotHeight)
	, minPx(_minPx)
	, maxPx(_maxPx)
	, ptrModel(_pModel)
	, ptrControllableObject(_ptrControllableObject)
{
	ptrModel->registerCtr(this);

}

bool CAbstractController::isCtrActive(CPoint _mousePos) 
{
	if ((_mousePos.x >= (act.x - hotWidth / 2)) && (_mousePos.x <= (act.x + hotWidth / 2))
		&& (_mousePos.y >= (act.y - hotHeight / 2)) && (_mousePos.y <= (act.y + hotHeight / 2)))
	{
		return true;
	}
	else { return false; }
}


void CAbstractController::setControllableObject(CControllableObject * _ptrControllableObject) {
	ptrControllableObject = _ptrControllableObject;
}


CControllableObject * CAbstractController::getControllableObject()const {
	return ptrControllableObject;
}

void CAbstractController::setActPointX(int _x) {
	this->act.x = _x;
}

void CAbstractController::setActPointY(int _y) {
	this->act.y = _y;
}
void CAbstractController::setOrgX(int _x) {
	this->org.x = _x;
}

void CAbstractController::setOrgY(int _y) {
	this->org.y = _y;
}

void CAbstractController::setMaxPx(int _px) {
	this->maxPx = _px;
}

void CAbstractController::setMinPx(int _px){
	this->minPx = _px;
}

void CAbstractController::setWindowSizeStart(int _xWindowSizeStart, int _yWindowSizeStart)
{
	xWindowSizeStart = _xWindowSizeStart;
	yWindowSizeStart = _yWindowSizeStart;
}

void CAbstractController::CalcSizeOfView(int _xCurrentWindowSize, int _yCurrentWindowSize, CDC* pDC)
{
	int xCurrentWindowSizeCache = xCurrentWindowSize;
	int yCurrentWindowSizeCache = yCurrentWindowSize;

	xCurrentWindowSize = _xCurrentWindowSize;
	yCurrentWindowSize = _yCurrentWindowSize;

	xFactor = static_cast<double>(xCurrentWindowSize) / xCurrentWindowSizeCache;
	yFactor = static_cast<double>(yCurrentWindowSize) / yCurrentWindowSizeCache;

	xPosition = (xWindowSizeStart / 2 + xWindowSizeStart / 16) * xFactor;
	yPosition = yWindowSizeStart / 8 * yFactor;

	if (xFactor != std::numeric_limits<double>::infinity()) //Damit die Werte gleich beim Start nicht geändert werden, weil XFactor beim start unendlich ist
	{
		org.x = org.x * xFactor;
		org.y = org.y * yFactor;
		act.x = act.x * xFactor;
		act.y = act.y * yFactor;
		hotHeight = hotHeight * yFactor;
		hotWidth = hotWidth * xFactor;
		minPx = minPx * xFactor;
		maxPx = maxPx * xFactor;
	}
	


}

void CAbstractController::CalcSizeOfViewStart(int _xCurrentWindowSize, int _yCurrentWindowSize, CDC* pDC)
{


	xCurrentWindowSize = _xCurrentWindowSize;
	yCurrentWindowSize = _yCurrentWindowSize;

	xFactor = static_cast<double>(xCurrentWindowSize) / xWindowSizeStart;
	yFactor = static_cast<double>(yCurrentWindowSize) / yWindowSizeStart;

	xPosition = (xWindowSizeStart / 2 + xWindowSizeStart / 16) * xFactor;
	yPosition = yWindowSizeStart / 8 * yFactor;

	if (xFactor != std::numeric_limits<double>::infinity()) //Damit die Werte gleich beim Start nicht geändert werden, weil XFactor beim start unendlich ist
	{
		org.x = org.x * xFactor;
		org.y = org.y * yFactor;
		act.x = act.x * xFactor;
		act.y = act.y * yFactor;
		hotHeight = hotHeight * yFactor;
		hotWidth = hotWidth * xFactor;
		minPx = minPx * xFactor;
		maxPx = maxPx * xFactor;
	}



}