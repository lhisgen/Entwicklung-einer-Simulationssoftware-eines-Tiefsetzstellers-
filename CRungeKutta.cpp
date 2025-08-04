#include "CRungeKutta.h"
//#include "pch.h"

// Constructor
CRungeKutta::CRungeKutta(Function_2args f, double _h) : func_2args(f), h(_h) {}
CRungeKutta::CRungeKutta(Function_3args f, double _h) : func_3args(f), h(_h) {}

// Method to solve the ODE (first order ODE)
double CRungeKutta::step(double x0, double y0) {
    double y;

    double k1 = h * func_2args(x0, y0);
    double k2 = h * func_2args(x0 + h / 2, y0 + k1 / 2);
    double k3 = h * func_2args(x0 + h / 2, y0 + k2 / 2);
    double k4 = h * func_2args(x0 + h, y0 + k3);

    y = y0 + (k1 + 2 * k2 + 2 * k3 + k4) / 6;

    return y;
}

// Method to solve the ODE (second order ODE)
double CRungeKutta::step(double x0, double dy0, double y0) {
    double dy;

    double k1 = h * func_3args(x0, dy0, y0);
    double k2 = h * func_3args(x0 + h / 2, dy0 + h * k1 / 2, y0 + h * k1 / 2);
    double k3 = h * func_3args(x0 + h / 2, dy0 + h * k2 / 2, y0 + h * k2 / 2);
    double k4 = h * func_3args(x0 + h, dy0 + h * k3, y0 + h * k3);

    dy = dy0 + (k1 + 2 * k2 + 2 * k3 + k4) / 6;

    return dy;
}