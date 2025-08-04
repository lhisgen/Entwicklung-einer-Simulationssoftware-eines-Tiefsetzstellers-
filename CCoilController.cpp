#include "pch.h"
#include "CCoilController.h"
#include "math.h"


CCoilController::CCoilController(CPoint _org, CPoint _act, CAbstractModel* _pModel, CControllableObject* _pCO)
	: CAbstractController(_org, _act, _pModel, _pCO)
{}

CCoilController::CCoilController(CPoint _org, CPoint _act, int _hotWidth, int _hotHeight, int _minPx, int _maxPx, CAbstractModel* _pModel, CControllableObject* _pCO)
	: CAbstractController(_org, _act, _hotWidth, _hotHeight, _minPx, _maxPx, _pModel, _pCO)
{}

CCoilController::~CCoilController()
{}

void CCoilController::draw(CDC* _pDC) {
	
	int bias = 6 * xFactor;
	

		CBrush black(RGB(0, 0, 0));
		_pDC->SelectObject(black);
		_pDC->Rectangle(1 *(org.x - bias), 1 * (org.y - hotHeight / 2), 1 * act.x, 1 * (org.y + hotHeight / 2));
		_pDC->TextOut(  org.x + (maxPx-org.x)/2, org.y -  hotHeight , CString("L"));

		// Draw red rectangle
		CBrush red(RGB(255, 0, 0));
		_pDC->SelectObject(red);
		_pDC->Rectangle(1 * (act.x - hotWidth / 2), 1 * (act.y - hotHeight / 2), 1 * (act.x + hotWidth / 2), 1*(act.y + hotHeight / 2));

	
		CBrush white(RGB(255, 255, 255));
		//white.CreateStockObject(NULL_BRUSH);
		_pDC->SelectObject(white);
		int rightEdge = min(act.x + hotWidth / 2 -1, maxPx); // Ensure we don't exceed maxPx //Zahlen gewählt, damit man rechtsn nichts rotes sieht
		_pDC->Rectangle(rightEdge, org.y - hotHeight / 2, maxPx, org.y + hotHeight / 2);

		



}


void CCoilController::calcActualValue(CPoint _pos, CDC* pDC) {
	act.x = _pos.x;
	if (act.x < minPx)
		act.x = minPx;
	if (act.x > maxPx-5*xFactor) // Um die maximale Auslekung der rechten Seite zu begrenzen
		act.x = maxPx-5* xFactor;
	double actValue = ptrControllableObject->getMinVal() + ((double)act.x - (double)minPx) * (ptrControllableObject->getMaxVal() - ptrControllableObject->getMinVal()) / ((double)maxPx - (double)minPx);
	// setzen des "controllten" Wertes im zugehörigen ControllableObject
	ptrControllableObject->setActualValue(actValue);
	//ptrModel->calcModel(pDC);
	
}


double CCoilController::calcInductance(void)
{
	double upper_constraint_var = 0.001; //mH
	double lower_constraint_var = 0.0001; //mH
	double diff_constraints = upper_constraint_var - lower_constraint_var;
	double maxPx_scaled = maxPx - 5 * xFactor;
	double result = (diff_constraints) / (maxPx_scaled - minPx) * act.x + upper_constraint_var - (diff_constraints) / (maxPx_scaled - minPx) * maxPx_scaled;

	// Round of decimal places
	if (result * 100000 - std::floor(result * 100000) >= 0.5) {
		result = std::ceil(result * 100000) / 100000;
	}
	else {
		result = std::floor(result * 100000) / 100000;
	}

	return result;

}

void CCoilController::setPositon(CPoint _org, CPoint _act, int _hotWidth, int _hotHeight, int _minPx, int _maxPx)
{
	org = _org;
	act = _act;
	hotWidth = _hotWidth;
	hotHeight = _hotHeight;
	minPx = _minPx;
	maxPx = _maxPx;
}

void CCoilController::update(CDC* _pDC) {
	draw(_pDC);
}