#include "pch.h"
#include "CCircuit.h"
#include "const.h"
#include "math.h"

CCircuit::CCircuit(CAbstractModel* _ptrModel)
	: CAbstractView(_ptrModel)
{
	xPosition = 10; //Erstmal willkürlich ausgewählt
	yPosition = 1;
	
}

CCircuit::CCircuit(int _xPosition, int _yPosition, CAbstractModel* _ptrModel)
	:CAbstractView(_ptrModel)
{
	xPosition = _xPosition;
	yPosition = _yPosition;
	
}

void CCircuit::draw(CDC* pDC)
{
	

	int xlamda, ylamda;

	// Parameter für den Schaltplan
	int Hight = yWindowSizeStart / 4;
	int Lenght = xWindowSizeStart/ 2.6;
	int Circleradius = 7;
	int Drawingthickness= 2;
	int HightController = 36;

	// Höhe des gleichschenkligen Dreiecks
	int SeitenLenghtDiode = Hight / 3; //Die Seitenlänge der Diode beträgt 1 Drittel der Höhe des Schaltplan
	int HightDiode = sqrt(3) / 2 * SeitenLenghtDiode;
	int PositionDiodeInCircuit = yPosition + yFactor + Hight / 2;
	
	CPen BlackPenDuenn(PS_SOLID, 1, RGB(0, 0, 0));

	CPen BlackPen(PS_SOLID, yFactor * Drawingthickness, RGB(0, 0, 0));
	CBrush BlackBrush;
	BlackBrush.CreateSolidBrush(RGB(0, 0, 0));
	pDC->SelectObject(&BlackPen);

	//Blauen Stift für den Spannungspfeil erstellen.
	CPen BluePen(PS_SOLID, yFactor * 2, RGB(0, 0, 130));
	CBrush BlueBrush;
	BlueBrush.CreateSolidBrush(RGB(0, 0, 130));
	//Pfeilspitze zeichnen
	int BreitePfeilspitze = 5;
	int HightPeilspitze = 10;

	//Definition der Texte die auf dem Dialog angezeigt werden sollen
	
	
	//!!!!!Beachte xPosition und yPosition werden nicht mit den Faktoren multipliziert, diese werden in "CalsSizeOF" bereits multipliziert
	

	//Dieser Algorithmus zeichnet den Schaltplan. Für einfache Änderung müssen lediglich die Werte oben geändert werden. Beginnt link oben
	pDC->MoveTo(xPosition, yPosition);
	pDC->Ellipse(xPosition - yFactor * Circleradius, yPosition - yFactor * Circleradius, xPosition + yFactor * Circleradius, yPosition + yFactor * Circleradius);
	pDC->MoveTo(xPosition + xFactor * (Circleradius-1), yPosition);

	pDC->LineTo(xlamda = xPosition + xFactor * (Lenght/2.5/3), ylamda = yPosition); //(Lenght/2.5/3) bedeudet, dass die lücke des Schalters 1/3 der Linie lang ist.
	pDC->MoveTo(xlamda = xlamda + xFactor * (Lenght / 2.5 / 3), ylamda);							//Lücke um einen Schalter einzufügen
	pDC->LineTo(xlamda = xPosition + xFactor * Lenght / 2.5, ylamda = yPosition);

	pDC->LineTo(xlamda , ylamda = ylamda + yFactor * Hight); //Linie der Diode;
	pDC->MoveTo(xlamda, ylamda = ylamda - yFactor * Hight);

	pDC->LineTo(xlamda = xlamda + xFactor * Lenght / 2.5 / 4, ylamda); //Das ist die Linie der Spule
	
	pDC->SelectObject(&BlackPenDuenn);

	pDC->SelectObject(&BlackPen);
	pDC->MoveTo(xlamda = xlamda + xFactor * (Lenght / 2.5/ 2), ylamda); //Das ist die Lücke für den Spulencontroller
	pDC->LineTo(xlamda = xlamda + xFactor * Lenght / 2.5 / 4, ylamda);

	


	pDC->LineTo(xlamda, ylamda = ylamda + yFactor * Hight *3/8); //Linie des Kondensators
	pDC->MoveTo(xlamda, ylamda = ylamda + yFactor * Hight / 4); //Lücke für den Kondensator
	pDC->LineTo(xlamda, ylamda = ylamda + yFactor * Hight * 3 / 8);
	pDC->MoveTo(xlamda, ylamda = ylamda - yFactor * Hight); //Bewegung wieder nach oben zur Linie des Kondensators
	

	pDC->LineTo(xlamda = xlamda + xFactor * Lenght / 5, ylamda); //Strich um vom Kondensator zur Linie des Widerstands zu kommen (nach rechts)
	pDC->LineTo(xlamda, ylamda = ylamda + yFactor * Hight/4);
	pDC->MoveTo(xlamda, ylamda = ylamda + yFactor * Hight / 2); //Lücke für den Widerstand
	pDC->LineTo(xlamda, ylamda = ylamda + yFactor * Hight / 4);


	pDC->LineTo(xlamda = xPosition, ylamda);
	pDC->Ellipse(xlamda - yFactor * Circleradius, ylamda - yFactor * Circleradius, xlamda + yFactor * Circleradius, ylamda + yFactor * Circleradius);


	//Punkte an den Zweigen zeichnen
	Circleradius = Circleradius - 2;

	pDC->SelectObject(&BlackBrush);
	pDC->MoveTo(xlamda = xPosition + xFactor * Lenght / 2.5, ylamda = yPosition);
	pDC->Ellipse(xlamda - yFactor * Circleradius, ylamda - yFactor * Circleradius, xlamda + yFactor * Circleradius, ylamda + yFactor * Circleradius);
	pDC->MoveTo(xlamda = xlamda + xFactor * Lenght / 2.5, ylamda);
	pDC->Ellipse(xlamda - yFactor * Circleradius, ylamda - yFactor * Circleradius, xlamda + yFactor * Circleradius, ylamda + yFactor * Circleradius);
	pDC->MoveTo(xlamda, ylamda = ylamda + yFactor * Hight);
	pDC->Ellipse(xlamda - yFactor * Circleradius, ylamda - yFactor * Circleradius, xlamda + yFactor * Circleradius, ylamda + yFactor * Circleradius);
	pDC->MoveTo(xlamda = xlamda - xFactor * Lenght / 2.5 , ylamda);
	pDC->Ellipse(xlamda - yFactor * Circleradius, ylamda - yFactor * Circleradius, xlamda + yFactor * Circleradius, ylamda + yFactor * Circleradius);


	// Zeichne das gleichschenklige Dreieck für die Diode
	pDC->MoveTo(xlamda = xPosition + xFactor * (Lenght / 2.5) - xFactor * SeitenLenghtDiode / 2, ylamda = yPosition + yFactor * (Hight / 2 + (HightDiode / 2)));
	pDC->LineTo(xlamda = xlamda + xFactor * SeitenLenghtDiode, ylamda);
	pDC->LineTo(xlamda = xlamda - xFactor * SeitenLenghtDiode / 2 , ylamda = ylamda -  yFactor * HightDiode); // Rechte Seite des Dreickes
	pDC->LineTo(xlamda = xlamda - xFactor * SeitenLenghtDiode / 2, ylamda = ylamda + yFactor * HightDiode); //Linke Seite des Dreiecks

	pDC->MoveTo(xlamda, ylamda = ylamda - yFactor * HightDiode);
	pDC->Rectangle(xlamda, ylamda, xlamda + xFactor * SeitenLenghtDiode, ylamda + yFactor *  1);


	//Zeichnen des Pfeils für die Spannungsquelle
	
	pDC->SelectObject(&BlueBrush);

	//pDC->TextOutW(xFactor * xPosition, yFactor * (yPosition + Hight / 2), UE);
	pDC->TextOut(xPosition - xWindowSizeStart/32, yPosition + Hight/2.5*yFactor, CString("UD"));
	
	//pDC->SelectObject(&BluePen);
	//pDC->MoveTo(xPosition, ylamda = yPosition + yFactor * Hight / 10);
	//pDC->LineTo(xPosition, ylamda = ylamda + yFactor * Hight - yFactor * Hight / 5);

	
	// 
	//// Definiere die Koordinaten der Eckpunkte des Dreiecks
	//POINT points[3] = { {xPosition, ylamda}, {xPosition + xFactor * BreitePfeilspitze, ylamda - yFactor * HightPeilspitze}, {xPosition - xFactor * BreitePfeilspitze,ylamda -  yFactor * HightPeilspitze} };

	//// Zeichne das Dreieck
	//pDC->Polygon(points, 3);
	
}

void CCircuit::update(CDC* pDC)
{
	draw(pDC);
}


void CCircuit::setXPosition(int _xPosition)
{
	xPosition = _xPosition;
}

void CCircuit::setYPosition(int _yPosition)
{
	yPosition = _yPosition;
	
}





int CCircuit::getXPosition(void)
{
	return xPosition;
}


int CCircuit::getYPosition(void)
{
	return yPosition;
}