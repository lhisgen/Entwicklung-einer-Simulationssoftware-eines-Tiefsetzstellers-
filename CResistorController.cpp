#include "pch.h"
#include "CResistorController.h"
#include "math.h"


CResistorController::CResistorController(CPoint _org, CPoint _act, CAbstractModel* _pModel, CControllableObject* _pCO)
	: CAbstractController(_org, _act, _pModel, _pCO)
{

}

CResistorController::CResistorController(CPoint _org, CPoint _act, int _hotWidth, int _hotHeight, int _minPx, int _maxPx, CAbstractModel* _pModel, CControllableObject* _pCO)
	: CAbstractController(_org, _act, _hotWidth, _hotHeight, _minPx, _maxPx, _pModel, _pCO)
{

}

CResistorController::~CResistorController()
{}

void CResistorController::draw(CDC* _pDC) {

	//int bias = 6 * xFactor;


	// Draw black rectangle
	CPen pen3(PS_SOLID, 1, RGB(0, 0, 0));
	_pDC->SelectObject(&pen3);
	_pDC->TextOut(org.x + 1.2 * hotWidth /2, org.y + (maxPx - org.y) / 2, CString("R"));

	
	CBrush gray(RGB(245, 245, 245));
	_pDC->SelectObject(gray);
	_pDC->Rectangle(org.x - hotWidth / 2, org.y, org.x + hotWidth / 2, act.y - hotHeight / 2);
	//_pDC->Rectangle(1 *(org.x - bias), 1 * (org.y - hotHeight / 2), 1 * act.x, 1 * (org.y + hotHeight / 2));
	//_pDC->Rectangle(1 * (org.x - bias), 1 * (org.y - hotHeight / 2), 1 * org.x, 1 * (act.y + hotHeight / 2));

	
	// Draw red rectangle
	CBrush red(RGB(255, 0, 0));
	_pDC->SelectObject(red);
	_pDC->Rectangle(org.x - hotWidth / 2, act.y - hotHeight / 2, org.x + hotWidth / 2, act.y + hotHeight / 2);

	CBrush white(RGB(255, 255, 255));
	//white.CreateStockObject(NULL_BRUSH);
	_pDC->SelectObject(white);
	_pDC->Rectangle(org.x - hotWidth / 2, min(act.y + hotHeight / 2, maxPx + hotHeight / 2), org.x + hotWidth / 2, maxPx + hotHeight / 2);

}


void CResistorController::calcActualValue(CPoint _pos, CDC* pDC) {
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


double CResistorController::calcResistance(void)
{
	double upper_constraint_var = 5;
	double lower_constraint_var = 0.5;
	double diff_constraints = upper_constraint_var - lower_constraint_var;
	double maxPx_scaled = maxPx;// +5 * yFactor;
	double result = (diff_constraints) / (maxPx_scaled - minPx) * act.y + upper_constraint_var - (diff_constraints) / (maxPx_scaled - minPx) * maxPx_scaled;

	// Round of decimal places
	if (result * 100 - std::floor(result * 100) >= 0.5) {
		result = std::ceil(result * 100) / 100;
	}
	else {
		result = std::floor(result * 100) / 100;
	}

	return result;

}

void CResistorController::setPositon(CPoint _org, CPoint _act, int _hotWidth, int _hotHeight, int _minPx, int _maxPx)
{
	org = _org;
	act = _act;
	hotWidth = _hotWidth;
	hotHeight = _hotHeight;
	minPx = _minPx;
	maxPx = _maxPx;
}

void CResistorController::update(CDC* _pDC) {
	draw(_pDC);
}