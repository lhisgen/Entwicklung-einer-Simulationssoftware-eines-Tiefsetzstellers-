#include "pch.h"
#include "WiderstandDesign.h"

CWiderstandDesign::CWiderstandDesign(CController* _pCtr)
	: CCtrDesign()
{
	pCtr = _pCtr;
}

CWiderstandDesign::~CWiderstandDesign()
{}

void CWiderstandDesign::draw(CDC* _pDC) {
	CPen pen(PS_SOLID, 1, pCtr->getLineCol());
	_pDC->SelectObject(&pen);
	CPoint act = pCtr->getAct();
	int hotWidth = pCtr->getHotWidth();
	int hotHeight = pCtr->getHotHeight();
	CBrush white(RGB(255, 255, 255));
	_pDC->SelectObject(white);
	_pDC->Rectangle(pCtr->getOrg().x, pCtr->getOrg().y - hotHeight / 2, act.x, pCtr->getOrg().y + hotHeight / 2);
	CBrush red(RGB(255, 0, 0));
	_pDC->SelectObject(red);
	_pDC->Rectangle(act.x - hotWidth / 2, act.y - hotHeight / 2, act.x + hotWidth / 2, act.y + hotHeight / 2);
}