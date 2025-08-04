#pragma once
#include "AbstractView.h"
class CCircuit :
    public CAbstractView
{
private:

    



public:
    CCircuit(CAbstractModel* _ptrModel);
    CCircuit( int _xPosition, int _yPosition, CAbstractModel* _ptrModel);

    void draw(CDC* pDC);
    //void draw(int _xPosition, int _yPosition, CDC* pDC);
    void update(CDC* pDC);

    void setXPosition(int _xPosition);
    void setYPosition(int _yPosition);
    int getXPosition(void);
    int getYPosition(void);
    

   // void CalcSizeOfView(int xWindowSize, int yWindowSize, CDC* pDC);



};

