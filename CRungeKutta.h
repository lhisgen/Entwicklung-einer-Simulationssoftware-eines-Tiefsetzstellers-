#pragma once
#ifndef RUNGE_KUTTA_H
#define RUNGE_KUTTA_H
#include <functional>

// This class contains the runge kutta algorithm to solve ODEs
class CRungeKutta {
private:
    using Function_2args = std::function<double(double, double)>;
    using Function_3args = std::function<double(double, double, double)>;

public:
    // Constructor
    CRungeKutta(Function_2args f, double _h);
    CRungeKutta(Function_3args f, double _h);

    // Method to calculate one runge kutta step
    double step(double x0, double y0);                // ... for a first order ODE
    double step(double x0, double dy0, double y0);    // ... for a second order ODE

private:
    Function_2args func_2args;
    Function_3args func_3args;
    double h;
};

#endif
