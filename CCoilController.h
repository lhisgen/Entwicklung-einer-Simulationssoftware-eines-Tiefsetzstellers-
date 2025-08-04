#pragma once
#include "AbstractController.h"
class CCoilController : public CAbstractController {
public:
	CCoilController(CPoint _org, CPoint _act, CAbstractModel* _pModel, CControllableObject* _ptrControllableObject);
	CCoilController(CPoint _org, CPoint _act, int _hotWidth, int _hotHeight, int _minPx, int _maxPx, CAbstractModel* _pModel, CControllableObject* _ptrControllableObject);
	virtual ~CCoilController();
	virtual void draw(CDC* pDC);
	virtual void calcActualValue(CPoint _pos, CDC* pDC);
	double calcInductance(void);
	void setPositon(CPoint _org, CPoint _act, int _hotWidth, int _hotHeight, int _minPx, int _maxPx);
	void update(CDC* _pDC);
};

