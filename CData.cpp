#include "pch.h"
#include "CData.h"

CData::CData(string _name) {					//Standard-Konstruktor
	name = _name;
	pointView = 0;
	lineStyle = 1; // 1 == PS_SOLID
	lineWidth = 1;
	lineCol = RGB(0, 0, 255);
	// length = 10000;
	// ptrXVal = new double[length];
	//ptrYVal = new double[length];
	/*for (int i = 0; i < length; i++) {
		*(ptrXVal + i) = i * 1.0;
		*(ptrYVal + i) = 0.0;
	}*/

}

CData::CData(void) {					//Standard-Konstruktor
	name = "";
	pointView = 0;
	lineStyle = 1; // 1 == PS_SOLID
	lineWidth = 1;
	lineCol = RGB(0, 0, 255);
	// length = 10000;
	// ptrXVal = new double[length];
	//ptrYVal = new double[length];
	/*for (int i = 0; i < length; i++) {
		*(ptrXVal + i) = i * 1.0;
		*(ptrYVal + i) = 0.0;
	}*/

}

CData::~CData(void) {
	/*delete[] ptrXVal;
	delete[] ptrYVal;*/
}

CData::CData(int _width, int _style, string _name, bool _pointView, int _length) {
	lineWidth = _width;
	lineStyle = _style;
	name = _name;
	length = _length;
	ptrXVal = new double[length];
	ptrYVal = new double[length];
}

CData::CData(const CData& CD) {			//Kopier-Konstruktor
	length = CD.length;
	pointView = CD.pointView;
	lineStyle = CD.lineStyle;
	lineWidth = CD.lineWidth;
	ptrXVal = new double[length];
	ptrYVal = new double[length];
	for (int i = 0; i < length; i++)
	{
		ptrXVal[i] = CD.ptrXVal[i];
	}
	for (int i = 0; i < length; i++)
	{
		ptrYVal[i] = CD.ptrYVal[i];
	}
	name = CD.name;
}


void CData::setName(string _name) {
	name = _name;
}

double* CData::getXData(void) {
	return ptrXVal;
}
double* CData::getYData(void) {
	return ptrYVal;
}
string CData::getName(void) const {
	return name;
}
double CData::getLength(void) const {
	return length;
}
CData& CData::getModel() {
	return *this;
}

// setzt den Y-Wert
void CData::setDataValueY(double _value, int _index) {
	if (_index < this->length) {
		ptrYVal[_index] = _value;
	}
}

// setzt den X-Wert
void CData::setDataValueX(double _value, int _index) {
	if (_index < this->length) {
		ptrXVal[_index] = _value;
	}
}

double CData::getDataValueX(int _index) {
	return ptrXVal[_index];
}

double CData::getDataValueY(int _index) {
	return ptrYVal[_index];
}

void CData::setLength(double _length)
{
	length = _length;
	ptrXVal = new double[_length];
	ptrYVal = new double[_length];
}


