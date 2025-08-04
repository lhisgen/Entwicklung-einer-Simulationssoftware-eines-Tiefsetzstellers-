#pragma once
#include "atltypes.h"
#include "AbstractModel.h"
#include "ControllableObject.h"

class CAbstractController {
protected:
	CPoint org;
	CPoint act;
	int hotWidth;
	int hotHeight;
	int minPx;
	int maxPx;
	CAbstractModel* ptrModel;
	CControllableObject* ptrControllableObject;

	int xPosition;
	int yPosition;
	double xFactor;
	double yFactor;

	int xCurrentWindowSize;
	int yCurrentWindowSize;

	int xWindowSizeStart;
	int yWindowSizeStart;

public:
	virtual ~CAbstractController();
	CAbstractController(CPoint _org, CPoint _act, CAbstractModel *_ptrModel, CControllableObject * _ptrControllableObject);
	CAbstractController(CPoint _org, CPoint _act, int _hotWidth, int _hotHeight, int _minPx, int _maxPx, CAbstractModel *_ptrModel, CControllableObject * _ptrControllableObject);
	virtual bool isCtrActive(CPoint _mousePos);
	virtual void calcActualValue(CPoint _pos, CDC *pDC) = 0;
	virtual void update(CDC* pDC) = 0;

	virtual void draw(CDC * pDC) = 0;
	void setControllableObject(CControllableObject * _pCO);
	CControllableObject * getControllableObject()const;
	void setOrgX(int _x);
	void setOrgY(int _y);
	void setActPointX(int _x);
	void setActPointY(int _y);
	void setMinPx(int _px);
	void setMaxPx(int _px);
	void setWindowSizeStart(int _xWindowSizeStart, int _yWindowSizeStart);
	void CalcSizeOfView(int xWindowSize, int yWindowSize, CDC* pDC);
	void CalcSizeOfViewStart(int xWindowSize, int yWindowSize, CDC* pDC);
	virtual void setPositon(CPoint _org, CPoint _act, int _hotWidth, int _hotHeight, int _minPx, int _maxPx) = 0;
};

