#pragma once
#include "AbstractController.h"
class CDutyCycleController : public CAbstractController {
public:
	CDutyCycleController(CPoint _org, CPoint _act, CAbstractModel* _pModel, CControllableObject* _ptrControllableObject);
	CDutyCycleController(CPoint _org, CPoint _act, int _hotWidth, int _hotHeight, int _minPx, int _maxPx, CAbstractModel* _pModel, CControllableObject* _ptrControllableObject);
	virtual ~CDutyCycleController();
	virtual void draw(CDC* pDC);
	virtual void calcActualValue(CPoint _pos, CDC* pDC);
	double calcDutyCycle(void);
	void setPositon(CPoint _org, CPoint _act, int _hotWidth, int _hotHeight, int _minPx, int _maxPx);
	void update(CDC* _pDC);
};

