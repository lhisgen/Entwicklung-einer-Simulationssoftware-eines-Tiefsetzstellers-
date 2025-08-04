#pragma once
#include "AbstractController.h"
class CFrequencyController : public CAbstractController {
public:
	CFrequencyController(CPoint _org, CPoint _act, CAbstractModel* _pModel, CControllableObject* _ptrControllableObject);
	CFrequencyController(CPoint _org, CPoint _act, int _hotWidth, int _hotHeight, int _minPx, int _maxPx, CAbstractModel* _pModel, CControllableObject* _ptrControllableObject);
	virtual ~CFrequencyController();
	virtual void draw(CDC* pDC);
	virtual void calcActualValue(CPoint _pos, CDC* pDC);
	double calcFrequency(void);
	void setPositon(CPoint _org, CPoint _act, int _hotWidth, int _hotHeight, int _minPx, int _maxPx);
	void update(CDC* _pDC);
};

