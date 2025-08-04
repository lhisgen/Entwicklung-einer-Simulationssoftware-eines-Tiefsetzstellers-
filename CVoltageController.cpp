#include "pch.h"
#include "CVoltageController.h"
#include "math.h"


CVoltageController::CVoltageController(CPoint _org, CPoint _act, CAbstractModel* _pModel, CControllableObject* _pCO)
	: CAbstractController(_org, _act, _pModel, _pCO)
{

}

CVoltageController::CVoltageController(CPoint _org, CPoint _act, int _hotWidth, int _hotHeight, int _minPx, int _maxPx, CAbstractModel* _pModel, CControllableObject* _pCO)
	: CAbstractController(_org, _act, _hotWidth, _hotHeight, _minPx, _maxPx, _pModel, _pCO)
{

}

CVoltageController::~CVoltageController()
{}

void CVoltageController::draw(CDC* _pDC)
{
	CPen whitePen(PS_SOLID, 2, RGB(255, 255, 255));
	_pDC->SelectObject(whitePen);
	CBrush whiteBrush(RGB(255, 255, 255));
	//white.CreateStockObject(NULL_BRUSH);
	_pDC->SelectObject(whiteBrush);
	int upEdge = min(org.x + hotWidth, maxPx);
	_pDC->Rectangle(org.x - hotWidth/2, org.y-30 + hotHeight - 1, org.x + hotWidth, upEdge+11);

	CPen blackPen(PS_SOLID, 1, RGB(0, 0, 0));
	_pDC->SelectObject(blackPen);

	



	CBrush black(RGB(0, 0,0 ));
	_pDC->SelectObject(black);

	_pDC->Rectangle(org.x - hotWidth / 4+2, org.y-15, org.x + (hotWidth / 4)-1, act.y);
	CBrush red(RGB(255, 0, 0));
	_pDC->SelectObject(red);
	POINT trianglePoints[3];
	trianglePoints[0] = { act.x - hotWidth/2, act.y - hotHeight/2}; // Erster Punkt des Dreiecks
	trianglePoints[1] = { act.x + hotWidth/2, act.y - hotHeight/2 }; // Zweiter Punkt des Dreiecks
	trianglePoints[2] = { act.x, act.y + hotHeight/2 }; // Dritter Punkt des Dreiecks



	_pDC->Polygon(trianglePoints, 3);

	// Draw black rectangle
	/*CPen pen3(PS_SOLID, 0, RGB(0, 0, 0));
	_pDC->SelectObject(&pen3);*/

	
	//_pDC->Rectangle(1 * (act.x - hotWidth / 2), 1 * (act.y - hotHeight / 2), 1 * (act.x + hotWidth / 2), 1 * (act.y + hotHeight / 2));

	//CPen whitePen(PS_SOLID, 2, RGB(255, 255, 255));
	//_pDC->SelectObject(whitePen);
	// Draw black rectangle
	

	//CBrush white(RGB(255, 255, 255));
	////white.CreateStockObject(NULL_BRUSH);
	//_pDC->SelectObject(white);
	//int upEdge = min(org.x + hotWidth / 2, maxPx);
	//_pDC->Rectangle(org.x - hotWidth / 2, act.y + hotHeight / 2 - 1, org.x + hotWidth / 2, upEdge);

}


void CVoltageController::calcActualValue(CPoint _pos, CDC* pDC) {
	act.y = _pos.y;
	if (act.y < minPx)
		act.y = minPx;
	if (act.y > maxPx)
		act.y = maxPx;
	double actValue = ptrControllableObject->getMinVal() + ((double)act.y - (double)minPx) * (ptrControllableObject->getMaxVal() - ptrControllableObject->getMinVal()) / ((double)maxPx - (double)minPx);
	// Setzen des "beeinflussten" Wertes im zugehörigen ControllableObject
	ptrControllableObject->setActualValue(actValue);
	// Model neu berechnen
	//ptrModel->calcModel(pDC);

}


double CVoltageController::calcVoltage(void)
{


	double maxVoltage = 10;
	double result = (maxVoltage - 0.001) / ((maxPx - 5 * xFactor) - minPx) * act.y + maxVoltage - (maxVoltage - 0.001) / ((maxPx - 5 * xFactor) - minPx) * (maxPx - 5 * xFactor);

	if (result > maxVoltage)
	{
		result = maxVoltage;
	}

	// Round of decimal places
	if (result * 100 - std::floor(result * 100) >= 0.5) {
		result = std::ceil(result * 100) / 100;
	}
	else {
		result = std::floor(result * 100) / 100;
	}

	return result;
}

void CVoltageController::setPositon(CPoint _org, CPoint _act, int _hotWidth, int _hotHeight, int _minPx, int _maxPx)
{
	org = _org;
	act = _act;
	hotWidth = _hotWidth;
	hotHeight = _hotHeight;
	minPx = _minPx;
	maxPx = _maxPx;
}

void CVoltageController::update(CDC* _pDC) {
	draw(_pDC);
}