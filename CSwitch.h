#pragma once
#include "AbstractView.h"
class CSwitch :
    public CAbstractView
{
private:
   
   

public:
    CSwitch(CAbstractModel* _ptrModel);
    CSwitch(int xPosition, int yPosition, CAbstractModel* _ptrModel);
    void drawOpen(CDC* pDC);
    void drawClosed(CDC* pDC);
    void draw(CDC* pDC);
    //void draw(int _xPosition, int _yPosition, CDC* pDC);
    void update(CDC* pDC);

    void setXPosition(int _xPosition);
    void setYPosition(int _yPosition);
    void setPosition(int _xPosition, int _yPosition);
    int getXPosition(void);
    int getYPosition(void);

};

