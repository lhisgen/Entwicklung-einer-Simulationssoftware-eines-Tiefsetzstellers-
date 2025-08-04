#pragma once
#include "CtrDesign.h"
class CWiderstandDesign :   public CCtrDesign {
public:
	CWiderstandDesign(CController* _pCtr);
	~CWiderstandDesign();
	void draw(CDC* _pDC);
};

