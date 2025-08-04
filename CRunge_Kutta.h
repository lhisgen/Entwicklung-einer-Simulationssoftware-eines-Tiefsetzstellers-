#pragma once
#include "CSolverAlgorithm.h"

class CRunge_Kutta : public CSolverAlgorithm
{
public:
    // Konstruktoren
    CRunge_Kutta(Function_2args f, double _h) : CSolverAlgorithm(f, _h) {}
    CRunge_Kutta(Function_3args f, double _h) : CSolverAlgorithm(f, _h) {}

    double step(double x0, double y0) override;
    double step(double x0, double dy0, double y0) override;
};
