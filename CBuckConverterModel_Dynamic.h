#pragma once
#include "CBuckConverterModelAbstract.h"

class CBuckConverterModel_Dynamic :
    public CBuckConverterModelAbstract
{
    double GetInitialCurrentValue() override;
};

