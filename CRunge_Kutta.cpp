#include "pch.h"
#include "CRunge_Kutta.h"

// Methode zur Lösung der ODE (erster Ordnung)
double CRunge_Kutta::step(double x0, double y0) {
    double y;

    double k1 = h * func_2args(x0, y0);
    double k2 = h * func_2args(x0 + h / 2, y0 + k1 / 2);
    double k3 = h * func_2args(x0 + h / 2, y0 + k2 / 2);
    double k4 = h * func_2args(x0 + h, y0 + k3);

    y = y0 + (k1 + 2 * k2 + 2 * k3 + k4) / 6;

    return y;
}

// Methode zur Lösung der ODE (zweiter Ordnung)
double CRunge_Kutta::step(double x0, double dy0, double y0) {
    double dy;

    double k1 = h * func_3args(x0, dy0, y0);
    double k2 = h * func_3args(x0 + h / 2, dy0 + h * k1 / 2, y0 + h * k1 / 2);
    double k3 = h * func_3args(x0 + h / 2, dy0 + h * k2 / 2, y0 + h * k2 / 2);
    double k4 = h * func_3args(x0 + h, dy0 + h * k3, y0 + h * k3);

    dy = dy0 + (k1 + 2 * k2 + 2 * k3 + k4) / 6;

    return dy;
}