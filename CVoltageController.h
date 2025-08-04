#pragma once
#include "AbstractController.h"
class CVoltageController :
    public CAbstractController
{
public:

	CVoltageController(CPoint _org, CPoint _act, CAbstractModel* _pModel, CControllableObject* _ptrControllableObject);
	CVoltageController(CPoint _org, CPoint _act, int _hotWidth, int _hotHeight, int _minPx, int _maxPx, CAbstractModel* _pModel, CControllableObject* _ptrControllableObject);
	virtual ~CVoltageController();
	virtual void draw(CDC* pDC);
	virtual void calcActualValue(CPoint _pos, CDC* pDC);
	double calcVoltage(void);
	void setPositon(CPoint _org, CPoint _act, int _hotWidth, int _hotHeight, int _minPx, int _maxPx);
	void update(CDC* _pDC);
};

