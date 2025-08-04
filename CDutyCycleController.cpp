#include "pch.h"
#include "CDutyCycleController.h"
#include "math.h"


CDutyCycleController::CDutyCycleController(CPoint _org, CPoint _act, CAbstractModel* _pModel, CControllableObject* _pCO)
	: CAbstractController(_org, _act, _pModel, _pCO)
{}

CDutyCycleController::CDutyCycleController(CPoint _org, CPoint _act, int _hotWidth, int _hotHeight, int _minPx, int _maxPx, CAbstractModel* _pModel, CControllableObject* _pCO)
	: CAbstractController(_org, _act, _hotWidth, _hotHeight, _minPx, _maxPx, _pModel, _pCO)
{}

CDutyCycleController::~CDutyCycleController()
{}

void CDutyCycleController::draw(CDC* _pDC) {

	int bias = 6 * xFactor;


	// Draw black rectangle
	//CPen pen_dashed(PS_DOT, 0, RGB(0, 0, 0));
	//_pDC->SelectObject(pen_dashed);
	//_pDC->TextOut(this->org.x-5*xFactor, this->org.y-40*yFactor, CString("Spule"));
	//_pDC->MoveTo(org.x + (maxPx- org.x) / 2, org.y - hotHeight / 2 );
	//_pDC->LineTo(org.x + (maxPx - org.x) / 2, org.y - hotHeight / 2 * 1.5* bias);


	CPen pen(PS_SOLID, 0, RGB(0, 0, 0));
	CBrush black(RGB(0, 0, 255));
	_pDC->SelectObject(pen);
	_pDC->SelectObject(black);
	_pDC->Rectangle(1 * (org.x - bias), 1 * (org.y - hotHeight / 2), 1 * act.x, 1 * (org.y + hotHeight / 2));
	_pDC->TextOut(org.x - bias * 6.5, org.y - hotHeight / 2, CString("D"));

	// Draw red rectangle
	CBrush red(RGB(255, 0, 0));
	_pDC->SelectObject(red);
	_pDC->Rectangle(1 * (act.x - hotWidth / 2), 1 * (act.y - hotHeight / 2), 1 * (act.x + hotWidth / 2), 1 * (act.y + hotHeight / 2));


	CBrush white(RGB(255, 255, 255));
	//white.CreateStockObject(NULL_BRUSH);
	_pDC->SelectObject(white);
	int rightEdge = min(act.x + hotWidth / 2 - 1, maxPx); // Ensure we don't exceed maxPx //Zahlen gewählt, damit man rechtsn nichts rotes sieht
	_pDC->Rectangle(rightEdge, org.y - hotHeight / 2, maxPx, org.y + hotHeight / 2);

	//CPen pen_dashed(PS_DOT, 0, RGB(0, 0, 0));
	//_pDC->SelectObject(pen_dashed);
//_pDC->TextOut(this->org.x-5*xFactor, this->org.y-40*yFactor, CString("Spule"));
//_pDC->MoveTo(org.x + (maxPx- org.x) / 2, org.y - hotHeight / 2 );
//_pDC->LineTo(org.x + (maxPx - org.x) / 2, org.y - hotHeight / 2 * 1.5* bias)



}


void CDutyCycleController::calcActualValue(CPoint _pos, CDC* pDC) {
	act.x = _pos.x;
	if (act.x < minPx)
		act.x = minPx;
	if (act.x > maxPx - 5 * xFactor) // Um die maximale Auslekung der rechten Seite zu begrenzen
		act.x = maxPx - 5 * xFactor;
	double actValue = ptrControllableObject->getMinVal() + ((double)act.x - (double)minPx) * (ptrControllableObject->getMaxVal() - ptrControllableObject->getMinVal()) / ((double)maxPx - (double)minPx);
	// setzen des "controllten" Wertes im zugehörigen ControllableObject
	ptrControllableObject->setActualValue(actValue);
	//ptrModel->calcModel(pDC);

}


double CDutyCycleController::calcDutyCycle(void)
{
	//double minValue = 0.1; //mh
	//double maxValue = 1; //mh

	double upper_constraint_var = 1; 
	double lower_constraint_var = 0.1; 
	double diff_constraints = upper_constraint_var - lower_constraint_var;
	double maxPx_scaled = maxPx - 5 * xFactor;
	double result = (diff_constraints) / (maxPx_scaled - minPx) * act.x + upper_constraint_var - (diff_constraints) / (maxPx_scaled - minPx) * maxPx_scaled;

	if (result * 100 - std::floor(result * 100) >= 0.5) {
		result = std::ceil(result * 100) / 100;
	}
	else {
		result = std::floor(result * 100) / 100;
	}

	return result;

}

void CDutyCycleController::setPositon(CPoint _org, CPoint _act, int _hotWidth, int _hotHeight, int _minPx, int _maxPx)
{
	org = _org;
	act = _act;
	hotWidth = _hotWidth;
	hotHeight = _hotHeight;
	minPx = _minPx;
	maxPx = _maxPx;
}

void CDutyCycleController::update(CDC* _pDC) {
	draw(_pDC);
}