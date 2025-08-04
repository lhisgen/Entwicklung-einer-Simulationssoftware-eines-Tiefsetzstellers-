#include "pch.h"
#include "CSwitch.h"
#include "const.h"
#include "math.h"

CSwitch::CSwitch(CAbstractModel* _ptrModel)
	: CAbstractView(_ptrModel)
{
	xPosition = 0; 
	yPosition = 0;

}

CSwitch::CSwitch(int _xPosition, int _yPosition, CAbstractModel* _ptrModel)
	:CAbstractView(_ptrModel)
{
	xPosition = _xPosition;
	yPosition = _yPosition;
}


void CSwitch::drawOpen(CDC* pDC)
{
	int xlamda = 0;
	int ylamda = 0;
	int Radius = 5;
	int Hoehe = yWindowSizeStart / 4;
	int Laenge = xWindowSizeStart / 2.6;
	double angle = 0.523599; // 30°
	
	
	CBrush backGrnd(RGB(255, 255, 255));  // Beispiel: Weißer Hintergrund
	CPen WhitePen(PS_SOLID, yFactor * 2, RGB(255, 255, 255));
	pDC->SelectObject(&WhitePen);
	pDC->SelectObject(&backGrnd);	//Selbst gemacht, um zu Beginn einen weißen Hintergrund zu zeichnen.

	//CRect rect(xPosition + xFactor * (Laenge / 2.5 / 3), yPosition-50, xPosition + xFactor * 2*(Laenge / 2.5 / 3), yPosition-50);
	CRect rect(xPosition + xFactor * (Laenge / 2.5 / 3), yPosition-50*yFactor, xPosition + xFactor * 2 * (Laenge / 2.5 / 3), yPosition+50*xFactor);
	pDC->Rectangle(rect);

	CBrush backGrnd2(RGB(0,0,0));  // Beispiel: Weißer Hintergrund
	pDC->SelectObject(&backGrnd2);
	CPen BlackPen(PS_SOLID, yFactor * 2, RGB(0, 0, 0));
	pDC->SelectObject(&BlackPen);


	

	pDC->MoveTo(xlamda = xPosition + xFactor * (Laenge / 2.5 / 3), ylamda = yPosition);
	pDC->Ellipse(xlamda - yFactor * Radius, ylamda - yFactor * Radius, xlamda + yFactor * Radius, ylamda + yFactor * Radius);
	pDC->LineTo(xlamda + xFactor * (Laenge / 2.5 / 3) * cos(angle),ylamda - xFactor * (Laenge / 2.5 / 3) * sin(angle));
	pDC->MoveTo(xlamda = xPosition + 2 *xFactor * (Laenge / 2.5 / 3), ylamda = yPosition);
	
	CPen pen_dashed(PS_DOT, 0, RGB(0, 0, 0)); //dashed line for frequency and duty cicle
	pDC->SelectObject(&pen_dashed);
	pDC->MoveTo(xPosition + 1.5 * xFactor * (Laenge / 2.5 / 3),  yPosition);
	pDC->LineTo(xPosition + 1.5 * xFactor * (Laenge / 2.5 / 3), ylamda + Hoehe/6 );
	pDC->MoveTo(xlamda, ylamda);
	
	
	pDC->SelectObject(&BlackPen);
	pDC->Ellipse(xlamda - yFactor * Radius, ylamda - yFactor * Radius, xlamda + yFactor * Radius, ylamda + yFactor * Radius);



}

void CSwitch::drawClosed(CDC* pDC)
{
	CPen BlackPen(PS_SOLID, yFactor * 2, RGB(0, 0, 0));
	pDC->SelectObject(&BlackPen);
	int xlamda = 0;
	int ylamda = 0;
	int Radius = 5;
	int Hoehe = yWindowSizeStart / 4;
	int Laenge = xWindowSizeStart / 2.6;
	double angle = 0; // 30°

	CBrush WhitebackGrnd(RGB(255, 255, 255));  // Beispiel: Weißer Hintergrund
	CPen WhitePen(PS_SOLID, yFactor * 2, RGB(255, 255, 255));
	pDC->SelectObject(&WhitePen);
	pDC->SelectObject(&WhitebackGrnd);	//Selbst gemacht, um zu Beginn einen weißen Hintergrund zu zeichnen.
	CRect rect(xPosition + xFactor * (Laenge / 2.5 / 3), yPosition - 50 * yFactor, xPosition + xFactor * 2 * (Laenge / 2.5 / 3), yPosition + 50 * xFactor);
	//CRect rect(xPosition + xFactor * (Laenge / 2.5 / 3), yPosition - 50*yFactor, xPosition + xFactor * 2.1 * (Laenge / 2.5 / 3), yPosition + 50*yFactor);
	pDC->Rectangle(rect);
	CBrush blackGrnd(RGB(0, 0, 0));



	CBrush backGrnd(RGB(0, 0, 0));  // Beispiel: Weißer Hintergrund
	pDC->SelectObject(&backGrnd);
	CPen BlackPen2(PS_SOLID, yFactor * 2, RGB(0, 0, 0));
	pDC->SelectObject(&BlackPen2);

	pDC->MoveTo(xlamda = xPosition + xFactor * (Laenge / 2.5 / 3), ylamda = yPosition);
	pDC->Ellipse(xlamda - yFactor * Radius, ylamda - yFactor * Radius, xlamda + yFactor * Radius, ylamda + yFactor * Radius);
	pDC->LineTo(xlamda= xlamda + xFactor * (Laenge / 2.5 / 3) * cos(angle), ylamda=  ylamda - xFactor * (Laenge / 2.5 / 3) * sin(angle));
	pDC->Ellipse(xlamda - yFactor * Radius, ylamda - yFactor * Radius, xlamda + yFactor * Radius, ylamda + yFactor * Radius);

	CPen pen_dashed(PS_DOT, 0, RGB(0, 0, 0)); //dashed line for frequency and duty cicle
	pDC->SelectObject(&pen_dashed);
	pDC->MoveTo(xPosition + 1.5 * xFactor * (Laenge / 2.5 / 3), yPosition);
	pDC->LineTo(xPosition + 1.5 * xFactor * (Laenge / 2.5 / 3), ylamda + Hoehe /6 );
	pDC->MoveTo(xlamda, ylamda);



}

void CSwitch::draw(CDC* pDC)
{
	
	drawClosed(pDC);
	drawOpen(pDC);

}

void CSwitch::update(CDC* pDC)
{

	draw(pDC);
}


void CSwitch::setXPosition(int _xPosition)
{
	xPosition = _xPosition;
}

void CSwitch::setYPosition(int _yPosition)
{
	yPosition = _yPosition;

}





int CSwitch::getXPosition(void)
{
	return xPosition;
}


int CSwitch::getYPosition(void)
{
	return yPosition;
}

void CSwitch::setPosition(int _xPosition, int _yPosition)
{
	xPosition = _xPosition;
	yPosition = _yPosition;

}