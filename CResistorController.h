#pragma once
#include "AbstractController.h"
class CResistorController : public CAbstractController {
public:
	CResistorController(CPoint _org, CPoint _act, CAbstractModel* _pModel, CControllableObject* _ptrControllableObject);
	CResistorController(CPoint _org, CPoint _act, int _hotWidth, int _hotHeight, int _minPx, int _maxPx, CAbstractModel* _pModel, CControllableObject* _ptrControllableObject);
	virtual ~CResistorController();
	virtual void draw(CDC* pDC);
	virtual void calcActualValue(CPoint _pos, CDC* pDC);
	double calcResistance(void);
	void setPositon(CPoint _org, CPoint _act, int _hotWidth, int _hotHeight, int _minPx, int _maxPx);
	/*void CalcSizeOfView(int xWindowSize, int yWindowSize, CDC* pDC);*/
	void update(CDC* _pDC);
};

