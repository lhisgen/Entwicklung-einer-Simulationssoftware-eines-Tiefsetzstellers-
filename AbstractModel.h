#pragma once

class CAbstractView;
class CAbstractController;
class CData;

class CAbstractModel {
protected:
	vector <CAbstractView *> viewList;
	vector <CAbstractController *> controllerList;
public:
	CAbstractModel();
	virtual ~CAbstractModel();
	void registerView(CAbstractView * _ptrView);
	void registerCtr(CAbstractController* _ptrCtr);
	void notifyViews(CDC * pDC);
	void notifyCtr(CDC * pDC);
	virtual void calcModel(CDC * pDC)=0;
	CAbstractController * getCtrPtr(CPoint _pos);	
	virtual CData* getData(string _name) = 0;
};

