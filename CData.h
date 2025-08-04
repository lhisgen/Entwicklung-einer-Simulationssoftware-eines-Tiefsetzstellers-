#pragma once
//#include "Model.h"

class CData {
protected:
	double* ptrXVal;		//Datenfeld für X-Koordinaten
	double* ptrYVal;		//Datenfeld für Y-Koordinaten
	/*std::vector<double> X_vector;
	std::vector<double> Y_vector;*/
	double length;				//Länge des Feldes
	string name;			//name des Verlaufs;
	bool pointView;			//Punktdarstellung ON/OFF
	int lineStyle;
	int lineWidth;
	COLORREF lineCol;
public:
	CData& getModel();
	void setDataValueY(double _value, int _index);
	void setDataValueX(double _value, int _index);
	double getDataValueX(int _index);
	double getDataValueY(int _index);
	double getLength(void)const;
	void setName(string _name);
	void setLength(double _length);
	string getName(void)const;
	double* getXData(void);
	double* getYData(void);
	CData(string _name);	
	CData(void);
	//Standard-Konstruktor
	CData(const CData& CD);		//Kopier-Konstruktor
	CData(int _width, int _style, string _name, bool _pointView, int _length);
	~CData();

};

