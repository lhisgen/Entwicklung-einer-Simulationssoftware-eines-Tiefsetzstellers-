#include "pch.h"
#include "AbstractModel.h"
#include "AbstractView.h"
#include "AbstractController.h"

CAbstractModel::CAbstractModel()
{}

CAbstractModel::~CAbstractModel()
{}

void CAbstractModel::registerView(CAbstractView * _ptrView) {
	viewList.push_back(_ptrView);
}
void CAbstractModel::notifyViews(CDC * pDC) {
	for (vector<CAbstractView *>::iterator it = viewList.begin(); it != viewList.end(); it++) {
		(*it)->update(pDC);
	}
}
void CAbstractModel::notifyCtr(CDC * pDC) {
	for (vector<CAbstractController *>::iterator it = controllerList.begin(); it != controllerList.end(); it++)
	{
		(*it)->update(pDC);
	}
}

void CAbstractModel::registerCtr(CAbstractController * _ptrCtr) {
	controllerList.push_back(_ptrCtr);
}

void CAbstractModel::calcModel(CDC * pDC) {
	this->notifyViews(pDC);
	this->notifyCtr(pDC);
}

CAbstractController * CAbstractModel::getCtrPtr(CPoint _pos)
{
	for (vector<CAbstractController *>::iterator it = controllerList.begin(); it != controllerList.end(); it++) {
		if ((*it)->isCtrActive(_pos))
			return *it;
	}
	return NULL;
}
