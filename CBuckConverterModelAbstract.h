#pragma once
#include <functional>

class CBuckConverterModelAbstract {

protected:
    // Definition of a lambda function with 3 arguments (for the ODE)
    using Function_3args = std::function<double(double, double, double)>;

protected:
    double R;
    double L;
    double C;
    double V_in;
    double V_out;
    double PWM_f;
    double PWM_d;
    double time;

public:
    // Base Constructor
    CBuckConverterModelAbstract(void);
    CBuckConverterModelAbstract(double _R, double _L, double _C, double _V_in, double _PWM_f);

    // Set Methods

    virtual void SetResistance(double _R);
    virtual double GetResistance();

    virtual void SetInductance(double _L);
    virtual double GetInductance();

    virtual void SetCapacitance(double _C);
    virtual double GetCapacitance();

    virtual void SetInputVoltage(double _V_in);
    virtual double GetInputVoltage();

    virtual void SetPWMfrequency(double _PWM_f);
    virtual double GetPWMfrequency();

    virtual void SetTime(double _t); // needed to determine the current switch state

    virtual void SetDesiredOutputVoltage(double _V_out);
    virtual double GetDesiredOutputVoltage();

    virtual void SetDutyCycle(double _PWM_d);
    virtual double GetDutyCycle();

    // ...
    virtual double GetInitialCurrentValue() { return 0; };

    // Method to observe the current switch state
    virtual int GetSwitchState();

    // Method to get the Current (i) ODE
    virtual Function_3args GetCurrentODE();

    // Method to calculate the present inductivity current value i_L
    virtual double CalcInductanceCurrent(double i, double id);

    // Method to calculate the present output voltage
    virtual double CalcOutputVoltage(double i);

    // Method to calculate the present capacitance current
    virtual double CalcCapacitanceCurrent(double id);

    // Method to calculate the present inductance voltage
    virtual double CalcInductanceVoltage(double id);
};

