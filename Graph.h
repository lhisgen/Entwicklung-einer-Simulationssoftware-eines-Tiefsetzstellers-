#pragma once
#include "Const.h"
#include "AbstractView.h"
class CGraph: public CAbstractView  {
private:

	double xMin;
	double xMax;
	double yMin;
	double yMax;
	int startX;
	int startY;
	int orgX;
	int orgY;
	int width;
	int height;
	string name;

public:
	CGraph(CAbstractModel* _ptrModel);
	CGraph(int _startX, int _startY, string _name, CAbstractModel* _ptrModel);
	CGraph(int _startX, int _startY, int _yMin, int _yMax, string _name, CAbstractModel* _ptrModel);
	~CGraph(void);
	void setXmax(double _xMax);
	void setYmax(double _yMax);
	void setXmin(double _xMin);
	void setYmin(double _yMin);
	void setXstartXorg(double _startX);
	void setYstartYorg(double _startY);
	void setWidth(double _width);
	void setHeight(double _height);
	void DrawRotatedText(CDC* _pDC, const CString& text, int x, int y);
	void DrawFilledSquare(CDC* pDC, int x, int y, int sideLength, COLORREF fillColor);

	int math2GrafikY(double _yWert);
	int math2GrafikX(double _xWert);
	int Math2GrafikY(int _minCoordValue, int _maxCoordValue, double _yWert);

	void DrawGraph(string _name, CDC* _pDC);

	void draw(CDC * _pDC);
	void setLineColor(COLORREF _lineColor);
	void setLineStyle(int _style);
	void setLineWidth(int _width);
	void update(CDC * _pDC);
};

