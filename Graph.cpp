#include "pch.h"
#include "Graph.h"
#include "CData.h"



CGraph::CGraph(CAbstractModel * _ptrModel)
	: xMin(0)
	, xMax(0.4)
	, yMin(-10)
	, yMax(10)
	, startX(50)
	, startY(UPPER_MARGIN)
	, orgX(startX + LEFT_MARGIN)
	, orgY(startY + UPPER_MARGIN)
	, width(450)
	, height(130)
	, CAbstractView(_ptrModel)
	,name("")
{}

CGraph::CGraph(int _startX, int _startY, string _name, CAbstractModel* _ptrModel)
	: startX(_startX)
	, startY(_startY)
	, orgX(startX + LEFT_MARGIN)
	, orgY(startY + UPPER_MARGIN)
	, width(450)
	, height(130)
	, xMin(0)
	, xMax(0.01)
	, yMin(-5) //To change the scale
	, yMax(5)
	, CAbstractView(_ptrModel)
	, name(_name)
{
	
}

CGraph::CGraph(int _startX, int _startY,int _yMin,int _yMax, string _name, CAbstractModel* _ptrModel)
	: startX(_startX)
	, startY(_startY)
	, orgX(startX + LEFT_MARGIN)
	, orgY(startY + UPPER_MARGIN)
	, width(450)
	, height(130)
	, xMin(0)
	, xMax(0.01)
	, yMin(_yMin) //To change the scale
	, yMax(_yMax)
	, CAbstractView(_ptrModel)
	, name(_name)
	

{

}

CGraph::~CGraph(void)
{}


void CGraph::setXmax(double _xMax) {
 
	xMax = _xMax;
}
void CGraph::setYmax(double _yMax) {
 
	yMax = _yMax;
}
void CGraph::setXmin(double _xMin) {
 
	xMin = _xMin;
}
void CGraph::setYmin(double _yMin) {
 
	yMin = _yMin;
}

void CGraph::setXstartXorg(double _startX) {
	startX = _startX;
	orgX = startX + LEFT_MARGIN;
}

void CGraph::setYstartYorg(double _startY) {
	startY = _startY;
	orgY = startY + UPPER_MARGIN;
}

void CGraph::setWidth(double _width) {
	width = _width;
}

void CGraph::setHeight(double _height) {
	height = _height;
}

void CGraph::DrawRotatedText(CDC* _pDC, const CString& text, int x, int y)
{
	// Text invertieren
	_pDC->SetBkMode(TRANSPARENT);
	_pDC->SetTextColor(RGB(255, 255, 255));

	// Text rotieren
	_pDC->SaveDC();
	_pDC->SetGraphicsMode(GM_ADVANCED);
	XFORM xform;
	xform.eM11 = 0;
	xform.eM12 = -1;
	xform.eM21 = 1;
	xform.eM22 = 0;
	xform.eDx = x;
	xform.eDy = y + _pDC->GetTextExtent(text).cy;
	_pDC->SetWorldTransform(&xform);

	// Text in schwarz zeichnen
	_pDC->SetTextColor(RGB(100, 100, 100));
	_pDC->TextOut(0, 0, text);

	_pDC->RestoreDC(-1);
}

void CGraph::DrawFilledSquare(CDC* pDC, int x, int y, int sideLength, COLORREF fillColor)
{
	// Berechnen der Koordinaten des umgebenden Rechtecks
	int left = x;
	int top = y;
	int right = x + sideLength;
	int bottom = y + sideLength;

	// Erstellen eines Brush mit der angegebenen Farbe
	CBrush brush(fillColor);

	// Erstellen eines Pens mit der gleichen Farbe
	CPen pen(PS_SOLID, 1, fillColor);

	// Füllen des Quadrats und Zeichnen der Umrandung mit dem erstellten Brush und Pen
	CBrush* pOldBrush = pDC->SelectObject(&brush);
	CPen* pOldPen = pDC->SelectObject(&pen);
	pDC->Rectangle(left, top, right, bottom);

	// Wiederherstellen der vorherigen Einstellungen
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}

int CGraph::math2GrafikY(double _yWert) {

	return orgY+ height - (int)((_yWert - yMin) * height / (yMax - yMin));
	//return orgY + height - (int) ((_yWert - yMin)*height / (yMax - yMin));
}

int CGraph::Math2GrafikY(int _minCoordValue, int _maxCoordValue, double _yWert)
{
	

	return 0;
}


int CGraph::math2GrafikX(double _xWert) {
	return orgX + (int) ((_xWert - xMin)*width / (xMax - xMin));
}

void CGraph::draw(CDC * _pDC)
{
	CPen pen;

	// Hintergrund für zeitVerlauf weiss einfaerben
	CBrush backGrnd(RGB(255, 255, 255));
	_pDC->SelectObject(&backGrnd);

	// Zeichnen des Rahmens in SCHWARZ mit Linienstärke 1
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	_pDC->SelectObject(&pen);

	// Hintergrundrechteck zeichnen
	_pDC->Rectangle(startX, startY, startX + 2 * LEFT_MARGIN + width, startY + 2 * UPPER_MARGIN + height);


	// a) y-Achse
	_pDC->MoveTo(this->orgX, this->orgY);
	_pDC->LineTo(this->orgX, this->orgY + height);
	// b) x-Achse
	if (name == "GraphTop") {
		_pDC->MoveTo(this->orgX, this->orgY + height);
		_pDC->LineTo(this->orgX + width, this->orgY + height);
	}

	if (name == "GraphMid" || name == "GraphBottom") {
		_pDC->MoveTo(this->orgX, this->orgY + height / 2);
		_pDC->LineTo(this->orgX + width, this->orgY + height / 2);
		// c) Skalenstrich
		//_pDC->LineTo(this->orgX + width, this->orgY + height / 2 + 15);
	}


	pen.DeleteObject();


	CPen penDesign;
	penDesign.CreatePen(PS_SOLID, 1, RGB(211, 211, 211));

	_pDC->SelectObject(&penDesign);
	_pDC->SetTextColor(RGB(100, 100, 100));

	//x-Achsen Beschriftungen
	_pDC->TextOut(this->orgX, this->orgY + height + 4, CString("0"));
	_pDC->TextOut(this->orgX + width * 0.2 - 20, this->orgY + height + 4, CString("0.002"));
	_pDC->TextOut(this->orgX + width * 0.4 - 20, this->orgY + height + 4, CString("0.004"));
	_pDC->TextOut(this->orgX + width * 0.6 - 20, this->orgY + height + 4, CString("0.006"));
	_pDC->TextOut(this->orgX + width * 0.8 - 20, this->orgY + height + 4, CString("0.008"));
	_pDC->TextOut(this->orgX + width - 20, this->orgY + height + 4, CString("0.010"));

	//Achsenbeschritungslinien Vertikal
	_pDC->MoveTo(this->orgX + 0.2 * width, orgY);
	_pDC->LineTo(this->orgX + 0.2 * width, orgY + height);

	_pDC->MoveTo(this->orgX + 0.4 * width, orgY);
	_pDC->LineTo(this->orgX + 0.4 * width, orgY + height);

	_pDC->MoveTo(this->orgX + 0.6 * width, orgY);
	_pDC->LineTo(this->orgX + 0.6 * width, orgY + height);

	_pDC->MoveTo(this->orgX + 0.8 * width, orgY);
	_pDC->LineTo(this->orgX + 0.8 * width, orgY + height);

	_pDC->MoveTo(this->orgX + width, orgY);
	_pDC->LineTo(this->orgX + width, orgY + height);


	_pDC->SelectObject(&pen);

	if (name == "GraphTop")
	{

		//y-Achsen Beschriftung
		//Graph 1
		_pDC->SelectObject(&penDesign);
		_pDC->TextOut(this->orgX - 16, this->orgY + height - 9, CString("0"));
		_pDC->TextOut(this->orgX - 16, this->orgY + 0.8 * height - 9, CString("2"));
		_pDC->TextOut(this->orgX - 16, this->orgY + 0.6 * height - 9, CString("4"));
		_pDC->TextOut(this->orgX - 16, this->orgY + 0.4 * height - 9, CString("6"));
		_pDC->TextOut(this->orgX - 16, this->orgY + 0.2 * height - 9, CString("8"));
		_pDC->TextOut(this->orgX - 23, this->orgY - 9, CString("10"));

		//Achsenbeschriftungslinien
		//_pDC->MoveTo(this->orgX - 6, this->orgY + height);
		//_pDC->LineTo(this->orgX + width, this->orgY + height);

		_pDC->MoveTo(this->orgX + 1, this->orgY + 0.8 * height);
		_pDC->LineTo(this->orgX + width, this->orgY + 0.8 * height);

		_pDC->MoveTo(this->orgX + 1, this->orgY + 0.6 * height);
		_pDC->LineTo(this->orgX + width, this->orgY + 0.6 * height);

		_pDC->MoveTo(this->orgX + 1, this->orgY + 0.4 * height);
		_pDC->LineTo(this->orgX + width, this->orgY + 0.4 * height);

		_pDC->MoveTo(this->orgX + 1, this->orgY + 0.2 * height);
		_pDC->LineTo(this->orgX + width, this->orgY + 0.2 * height);

		_pDC->MoveTo(this->orgX + 1, this->orgY);
		_pDC->LineTo(this->orgX + width, this->orgY);


		_pDC->SelectObject(&pen);

		_pDC->TextOutW(this->startX + 0.3 * LEFT_MARGIN, this->startY + 2 * UPPER_MARGIN + height, CString("Zeit / s"));
		DrawRotatedText(_pDC, _T("Spannung / V"), startX - (0.6 * LEFT_MARGIN), orgY + height);

		CPen pen3;
		pen3.CreatePen(PS_SOLID, 2, RGB(190, 25, 255));
		_pDC->SelectObject(&pen3);


		_pDC->SetTextColor(RGB(100, 100, 100));

		DrawFilledSquare(_pDC, startX + width - 0.8 * LEFT_MARGIN, startY + 0.3 * UPPER_MARGIN, 15, RGB(190, 25, 255));
		_pDC->TextOutW(this->startX + width - 0.2 * LEFT_MARGIN, this->startY + 0.3 * UPPER_MARGIN, CString("u_Out"));

		DrawGraph("u_Out", _pDC);

		CPen penGreen;
		penGreen.CreatePen(PS_SOLID, 2, RGB(0, 180, 0));
		_pDC->SelectObject(&penGreen);

		DrawGraph("u_L", _pDC);

		DrawFilledSquare(_pDC, startX + width - 2.7 * LEFT_MARGIN, startY + 0.3 * UPPER_MARGIN, 15, RGB(0, 180, 0));
		_pDC->TextOutW(this->startX + width - 2.1 * LEFT_MARGIN, this->startY + 0.3 * UPPER_MARGIN, CString("u_L"));
	}

	CPen pen2;
	pen2.CreatePen(PS_SOLID, 2, RGB(180, 0, 0));
	_pDC->SelectObject(&pen2);

	if (name == "GraphMid")
	{
		//y-Beschriftung
		//Graph 2
		_pDC->SelectObject(&penDesign);
		_pDC->TextOut(this->orgX - 27, this->orgY + height - 7, CString("-11"));
		_pDC->TextOut(this->orgX - 20, this->orgY + 0.75 * height - 7, CString("-5"));
		_pDC->TextOut(this->orgX - 16, this->orgY + 0.5 * height - 7, CString("0"));
		_pDC->TextOut(this->orgX - 16, this->orgY + 0.25 * height - 7, CString("5"));
		_pDC->TextOut(this->orgX - 23, this->orgY - 7, CString("11"));

		//Achsenbeschriftungslinien
		_pDC->MoveTo(this->orgX + 1, this->orgY + height);
		_pDC->LineTo(this->orgX + width, this->orgY + height);

		_pDC->MoveTo(this->orgX + 1, this->orgY + 0.75 * height);
		_pDC->LineTo(this->orgX + width, this->orgY + 0.75 * height);

		//_pDC->MoveTo(this->orgX - 6, this->orgY + 0.5 * height);
		//_pDC->LineTo(this->orgX + width, this->orgY + 0.5 * height);

		_pDC->MoveTo(this->orgX + 1, this->orgY + 0.25 * height);
		_pDC->LineTo(this->orgX + width, this->orgY + 0.25 * height);

		_pDC->MoveTo(this->orgX + 1, this->orgY);
		_pDC->LineTo(this->orgX + width, this->orgY);

		//Ändere Koordnsystersdf
		_pDC->TextOutW(this->startX + 0.3 * LEFT_MARGIN, this->startY + 2 * UPPER_MARGIN + height, CString("Zeit / s"));
		DrawRotatedText(_pDC, _T("Strom / A"), startX - (0.6 * LEFT_MARGIN), orgY + height);

		_pDC->SelectObject(&pen2);
		
		_pDC->SetTextColor(RGB(100, 100, 100));
		_pDC->TextOutW(this->startX + width + 0.3 * LEFT_MARGIN, this->startY + 0.3 * UPPER_MARGIN, CString("i_C"));
		_pDC->TextOutW(this->startX + width - 1.8 * LEFT_MARGIN, this->startY + 0.3 * UPPER_MARGIN, CString("i_L"));
		_pDC->TextOutW(this->startX + width - 3.9 * LEFT_MARGIN, this->startY + 0.3 * UPPER_MARGIN, CString("i_R"));
		DrawFilledSquare(_pDC, startX + width - 0.3 * LEFT_MARGIN, startY + 0.3 * UPPER_MARGIN, 14, RGB(180, 0, 0));
		DrawFilledSquare(_pDC, startX + width - 2.4 * LEFT_MARGIN, startY + 0.3 * UPPER_MARGIN, 14, RGB(0, 180, 0));
		DrawFilledSquare(_pDC, startX + width - 4.5 * LEFT_MARGIN, startY + 0.3 * UPPER_MARGIN, 14, RGB(0, 0, 180));
		DrawGraph("i_C", _pDC);

		CPen penGreen;
		penGreen.CreatePen(PS_SOLID, 2, RGB(0, 180, 0));
		_pDC->SelectObject(&penGreen);

		DrawGraph("i_L", _pDC);

		CPen penBlue;
		penBlue.CreatePen(PS_SOLID, 2, RGB(0, 0, 180));
		_pDC->SelectObject(&penBlue);

		DrawGraph("i_R", _pDC);
		
	}

	if (name == "GraphBottom")
	{

		//y-Beschriftung
		//Graph 3
		_pDC->SelectObject(&penDesign);
		_pDC->TextOut(this->orgX - 27, this->orgY + 0.5 * height - 7, CString("OFF"));
		_pDC->TextOut(this->orgX - 23, this->orgY + 0.25 * height - 7, CString("ON"));

		//Achsenbeschriftungslinien Horizontal
		_pDC->MoveTo(this->orgX + 1, this->orgY + height);
		_pDC->LineTo(this->orgX + width, this->orgY + height);

		_pDC->MoveTo(this->orgX + 1, this->orgY + 0.75 * height);
		_pDC->LineTo(this->orgX + width, this->orgY + 0.75 * height);

		_pDC->MoveTo(this->orgX + 1, this->orgY + 0.25 * height);
		_pDC->LineTo(this->orgX + width, this->orgY + 0.25 * height);

		_pDC->MoveTo(this->orgX + 1, this->orgY);
		_pDC->LineTo(this->orgX + width, this->orgY);

		_pDC->TextOutW(this->startX + 0.3 * LEFT_MARGIN, this->startY + 2 * UPPER_MARGIN + height, CString("Zeit / s"));
		DrawRotatedText(_pDC, _T("Schaltzustand"), startX - (0.6 * LEFT_MARGIN), orgY + height);

		_pDC->SelectObject(&pen2);

		_pDC->SetTextColor(RGB(100, 100, 100));
		_pDC->TextOutW(this->startX + width - 2 * LEFT_MARGIN, this->startY + 0.3 * UPPER_MARGIN, CString("Schaltzustand"));
		DrawFilledSquare(_pDC, startX + width - 2.6 * LEFT_MARGIN, startY + 0.3 * UPPER_MARGIN, 15, RGB(0, 0, 180));

		

		CPen penGreen;
		penGreen.CreatePen(PS_SOLID, 2, RGB(0, 180, 0));
		_pDC->SelectObject(&penGreen);

		DrawGraph("u_Diode", _pDC);

		CPen penBlue;
		penBlue.CreatePen(PS_SOLID, 2, RGB(0, 0, 180));
		_pDC->SelectObject(&penBlue);

		DrawGraph("switch_state", _pDC);


	}
	pen2.DeleteObject();
	penDesign.DeleteObject();
	
}



void CGraph::update(CDC * _pDC) {
	draw(_pDC);
}

void CGraph::DrawGraph(string _name, CDC* _pDC)
{
	for (int i = 1; i < ptrModel->getData(_name)->getLength(); i++) {
		// wenn Werte innerhalb des Diagramms liegen ...
		if ((xMin < ptrModel->getData(_name)->getXData()[i]) && (xMax > (ptrModel->getData(_name)->getXData()[i])) && (yMin < ptrModel->getData(_name)->getYData()[i]) && (yMax > ptrModel->getData(_name)->getYData()[i])) {
			// Zeichnen des Kurvenzugs mit der ausgewählten Linienstärke und Farbe
			_pDC->MoveTo(math2GrafikX(ptrModel->getData(_name)->getXData()[i - 1]), math2GrafikY(ptrModel->getData(_name)->getYData()[i - 1]));
			_pDC->LineTo(math2GrafikX(ptrModel->getData(_name)->getXData()[i]), math2GrafikY(ptrModel->getData(_name)->getYData()[i]));
		}
	}
}