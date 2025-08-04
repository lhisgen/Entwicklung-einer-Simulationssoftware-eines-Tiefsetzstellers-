#pragma once
#include "CBuckConverterModelAbstract.h"

class CBuckConverterModel_SteadyState :
    public CBuckConverterModelAbstract
{
    double GetInitialCurrentValue() override;
};

