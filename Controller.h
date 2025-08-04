#pragma once
#include "atltypes.h"
#include "AbstractModel.h"
#include "ControllableObject.h"
class CCtrTyp;
class CCtrDesign;

class CController {
protected:
	CPoint org;
	CPoint act;
	int hotWidth;
	int hotHeight;
	int minPx;
	int maxPx;
	int minLen;
	int maxLen;
	COLORREF lineColor;
	COLORREF areaColor;
	CAbstractModel *pModel;
	CCtrTyp * pTypeOfCtr;
	CControllableObject *pCO;
	CCtrDesign * pDesignOfCtr;
public:
	virtual ~CController();
	CController(CPoint _org, CPoint _act, CAbstractModel* _pModel, CControllableObject* _pCO, CCtrTyp* _pCtrTyp, CCtrDesign* _pDesign, COLORREF _lineCol, COLORREF _areaCol);
	CController(CPoint _org, CPoint _act, CAbstractModel* _pModel, CControllableObject* _pCO, COLORREF _lineCol, COLORREF _areaCol);
	virtual bool isCtrActive(CPoint _mousePos);
	virtual void calcActualValue(CPoint _pos, CDC *pDC) ;
	virtual void draw(CDC * pDC);

	void setControllableObject(CControllableObject * _pCO);
	CControllableObject * getControllableObject()const;
	void setOrgX(int _x);
	void setOrgY(int _y);
	void setActPointX(int _x);
	void setActPointY(int _y);
	void setMinPx(int _px);
	void setMaxPx(int _px);
	int getActY(void)const;
	int getActX(void)const;
	int getMinPx(void)const;
	int getMaxPx(void)const;
	CControllableObject* getPCO(void)const;
	CAbstractModel* getPModel(void)const;
	COLORREF getLineCol();
	COLORREF getAreaCol();
	CPoint getAct();
	CPoint getOrg();
	int getHotWidth();
	int getHotHeight();
	void setHeigth(int _hotHeight);
	void setWidth(int _width);
	void setMinLen(int _minLen);
	void setMaxLen(int _maxLen);
	int getMinLen(void)const;
	int getMaxLen(void)const;
	void setCtrTyp(CCtrTyp *_pCtrTyp);
	void setCtrDesign(CCtrDesign *_pCtrDes);
};

