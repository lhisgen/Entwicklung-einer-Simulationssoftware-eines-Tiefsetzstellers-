#include "pch.h"
#include "Controller.h"
#include "ctrDesign.h"
#include "CtrTyp.h"


CController::~CController() {
	delete this->pDesignOfCtr;
	delete this->pTypeOfCtr;
}


CController::CController(CPoint _org, CPoint _act, CAbstractModel *_pModel, CControllableObject * _pCO, CCtrTyp * _pTypeOfCtr,  CCtrDesign * _pDesign, COLORREF _lineCol, COLORREF _areaCol)
	: org(_org)
	, act(_act)
	, hotWidth(10)
	, hotHeight(10)
	, minLen(10)
	, maxLen(50)
	, pModel(_pModel)
	, pCO(_pCO)
	, pTypeOfCtr(_pTypeOfCtr)
	, pDesignOfCtr(_pDesign)
	, lineColor(_lineCol)
	, areaColor(_areaCol)
{
	// Beim Model anmelden
	pModel->addCtr(this);
}

CController::CController(CPoint _org, CPoint _act, CAbstractModel* _pModel, CControllableObject* _pCO,COLORREF _lineCol, COLORREF _areaCol)
	: org(_org)
	, act(_act)
	, hotWidth(10)
	, hotHeight(10)
	, minLen(10)
	, maxLen(50)
	, pModel(_pModel)
	, pCO(_pCO)
	, pTypeOfCtr(NULL)
	, pDesignOfCtr(NULL)
	, lineColor(_lineCol)
	, areaColor(_areaCol)
{
	// Beim Model anmelden
	pModel->addCtr(this);
}
bool CController::isCtrActive(CPoint _mousePos) {
	if ((_mousePos.x >= (act.x - hotWidth / 2)) && (_mousePos.x <= (act.x + hotWidth / 2))
		&& (_mousePos.y >= (act.y - hotHeight / 2)) && (_mousePos.y <= (act.y + hotHeight / 2)))
	{
		return true;
	}
	else { return false; }
}

void CController::draw(CDC* _pDC) {
	pDesignOfCtr->draw(_pDC);
}

void CController::calcActualValue(CPoint _pos, CDC* pDC) {
	pTypeOfCtr->calcController(_pos, pDC);
}

void CController::setControllableObject(CControllableObject * _pCO) {
	pCO = _pCO;
}

CControllableObject * CController::getControllableObject()const {
	return pCO;
}

void CController::setActPointX(int _x) {
	this->act.x = _x;
}

void CController::setActPointY(int _y) {
	this->act.y = _y;
}
void CController::setOrgX(int _x) {
	this->org.x = _x;
}

void CController::setOrgY(int _y) {
	this->org.y = _y;
}

void CController::setMaxPx(int _px) {
	this->maxPx = _px;
}

void CController::setMinPx(int _px){
	this->minPx = _px;
}

int CController::getMinPx(void)const {
	return minPx;
}

int CController::getMaxPx(void) const {
	return maxPx;
}

int CController::getActY(void)const {
	return act.y;
}

int CController::getActX(void) const {
	return act.x;
}

CControllableObject* CController::getPCO(void)const {
	return pCO;
}

CAbstractModel* CController::getPModel(void) const {
	return pModel;
}

COLORREF CController::getLineCol() {
	return lineColor;
};
COLORREF CController::getAreaCol() {
	return areaColor;
}
CPoint CController::getAct() {
	return act;
}
CPoint CController::getOrg() {
	return org;
}

int CController::getHotHeight() {
	return hotHeight;
}
int CController::getHotWidth() {
	return hotWidth;
}

void CController::setWidth(int _hotWidth) {
	hotWidth = _hotWidth;
}

void CController::setHeigth(int _hotHeight) {
	hotHeight = _hotHeight;
}


void CController::setMinLen(int _minLen) {
	minLen = _minLen;
}

int CController::getMinLen(void) const {
	return minLen;
}

int CController::getMaxLen(void) const {
	return maxLen;
}
void CController::setMaxLen(int _maxLen) {
	maxLen = _maxLen;
}


void CController::setCtrTyp(CCtrTyp *_pCtrTyp) {
	pTypeOfCtr = _pCtrTyp;
}

void CController::setCtrDesign(CCtrDesign *_pCtrDesign) {
	pDesignOfCtr = _pCtrDesign;
}
