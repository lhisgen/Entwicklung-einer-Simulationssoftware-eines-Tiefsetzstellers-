#pragma once
#include <functional>

class CSolverAlgorithm
{
protected:
    double h; 

    // Defining function-datatypes used for the description of the ODE to be solved
    using Function_2args = std::function<double(double, double)>;
    using Function_3args = std::function<double(double, double, double)>;

    Function_2args func_2args;
    Function_3args func_3args;

public:
    // Constructors
    CSolverAlgorithm(void);
    CSolverAlgorithm(Function_2args f, double _h);
    CSolverAlgorithm(Function_3args f, double _h);

    virtual double step(double x0, double y0) = 0;
    virtual double step(double x0, double dy0, double y0) = 0;

    virtual void setFunction(Function_2args f);
    virtual void setFunction(Function_3args f);
};


