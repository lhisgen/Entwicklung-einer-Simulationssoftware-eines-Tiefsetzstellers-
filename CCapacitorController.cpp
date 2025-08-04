#include "pch.h"
#include "CCapacitorController.h"
#include "math.h"


CCapacitorController::CCapacitorController(CPoint _org, CPoint _act, CAbstractModel* _pModel, CControllableObject* _pCO)
	: CAbstractController(_org, _act, _pModel, _pCO)
{
	// ausgehend vom actualVal des ControllableObject die aktuelle Position act.x des Controller berechnen
	// hier wird von einem HORIZONTALEN Controller ausgegangen
	//act.x = (int)((ptrControllableObject->getActualVal() - ptrControllableObject->getMinVal()) * (maxPx - minPx) / (ptrControllableObject->getMaxVal() - ptrControllableObject->getMinVal()) + (org.x + minPx));
}

CCapacitorController::CCapacitorController(CPoint _org, CPoint _act, int _hotWidth, int _hotHeight, int _minPx, int _maxPx, CAbstractModel* _pModel, CControllableObject* _pCO)
	: CAbstractController(_org, _act, _hotWidth, _hotHeight, _minPx, _maxPx, _pModel, _pCO)
{
	// ausgehend vom actualVal des ControllableObject die aktuelle Position act.x des Controller berechnen
	// hier wird von einem HORIZONTALEN Controller ausgegangen
	//act.x = (int)((ptrControllableObject->getActualVal() - ptrControllableObject->getMinVal()) * (maxPx - minPx) / (ptrControllableObject->getMaxVal() - ptrControllableObject->getMinVal()) + (org.x + minPx));
}

CCapacitorController::~CCapacitorController()
{}

void CCapacitorController::draw(CDC* _pDC) {

	int bias = 6 * xFactor;
	int base_capacitor_width = 6 * xFactor;

	// Draw black rectangle
	CPen pen2(PS_SOLID, 0, RGB(0, 0, 0));
	_pDC->SelectObject(&pen2);



	CBrush black(RGB(0, 0, 0));
	_pDC->SelectObject(black);
	_pDC->Rectangle(1 * (org.x - bias), 1 * (org.y - hotHeight / 2), 1 * act.x, 1 * (org.y - hotHeight / 6)); //upper capacitor plate
	_pDC->Rectangle(2 * org.x - act.x - hotWidth / 2, 1 * (org.y - hotHeight / 2), 1 * (org.x - bias), 1 * (org.y - hotHeight / 6)); //mirrowed upper capacitor plate
	_pDC->Rectangle(1 * (org.x - bias), 1 * (org.y + hotHeight / 2), 1 * act.x, 1 * (org.y + hotHeight / 6)); //lower capacitor plate
	_pDC->Rectangle(2 * org.x - act.x - hotWidth / 2, 1 * (org.y + hotHeight / 2), 1 * (org.x - bias), 1 * (org.y + hotHeight / 6)); //mirrowed upper capacitor plate
	_pDC->TextOut(org.x , org.y - hotHeight / 6, CString("C"));

	// Draw red rectangle
	CBrush red(RGB(255, 0, 0));
	_pDC->SelectObject(red);
	_pDC->Rectangle(1 * (act.x - hotWidth / 2), 1 * (act.y - hotHeight / 2), 1 * (act.x + hotWidth / 2), 1 * (act.y - hotHeight / 6));
	_pDC->Rectangle(1 * (act.x - hotWidth / 2), 1 * (act.y + hotHeight / 6), 1 * (act.x + hotWidth / 2), 1 * (act.y + hotHeight / 2));


	CBrush white(RGB(255, 255, 255));
	//white.CreateStockObject(NULL_BRUSH);
	_pDC->SelectObject(white);
	int rightEdge = min(act.x + hotWidth / 2 - 1, maxPx); // Ensure we don't exceed maxPx //Zahlen gewählt, damit man rechtsn nichts rotes sieht
	int mirrowedrightEdge = max((2 * org.x) - (act.x + hotWidth / 2 - 1), (2 * org.x) - maxPx); // Ensure we don't exceed maxPx //Zahlen gewhlt, damit man rechtsn nichts rotes sieht
	_pDC->Rectangle(rightEdge, org.y - hotHeight / 2, maxPx, org.y - hotHeight / 6); //upper mirrowed upper capacitor whitespace
	_pDC->Rectangle(mirrowedrightEdge, org.y - hotHeight / 2, (2 * org.x) - maxPx, org.y - hotHeight / 6); //mirrowed upper capacitor whitespace
	_pDC->Rectangle(rightEdge, org.y + hotHeight / 2, maxPx, org.y + hotHeight / 6); //lower mirrowed upper capacitor whitespace
	_pDC->Rectangle(mirrowedrightEdge, org.y + hotHeight / 2, (2 * org.x) - maxPx, org.y + hotHeight / 6); //mirrowed lower capacitor whitespace
	//_pDC->Rectangle(rightEdge, org.y - hotHeight / 2, maxPx, org.y - hotHeight / 6);
	//_pDC->Rectangle(rightEdge, org.y + hotHeight / 2, maxPx, org.y + hotHeight / 6);

}


void CCapacitorController::calcActualValue(CPoint _pos, CDC* pDC) {
	act.x = _pos.x;
	if (act.x < minPx)
		act.x = minPx;
	if (act.x > maxPx - 5 * xFactor) // Um die maximale Auslekung der rechten Seite zu begrenzen
		act.x = maxPx - 5 * xFactor;
	double actValue = ptrControllableObject->getMinVal() + ((double)act.x - (double)minPx) * (ptrControllableObject->getMaxVal() - ptrControllableObject->getMinVal()) / ((double)maxPx - (double)minPx);
	// setzen des "controllten" Wertes im zugehörigen ControllableObject
	ptrControllableObject->setActualValue(actValue);
	// Model neu berechnen
	//ptrModel->calcModel(pDC);

}


double CCapacitorController::calcCapacity(void)
{
	double upper_constraint_var = 0.001; //mh
	double lower_constraint_var = 0.00025; //mh
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

void CCapacitorController::setPositon(CPoint _org, CPoint _act, int _hotWidth, int _hotHeight, int _minPx, int _maxPx)
{
	org = _org;
	act = _act;
	hotWidth = _hotWidth;
	hotHeight = _hotHeight;
	minPx = _minPx;
	maxPx = _maxPx;
}

void CCapacitorController::update(CDC* _pDC) {
	draw(_pDC);
}