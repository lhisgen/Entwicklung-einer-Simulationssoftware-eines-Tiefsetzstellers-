#include "pch.h"
#include "CSolver.h"

// Constructor
CSolver::CSolver(CBuckConverterModelAbstract* _BuckConverterModel, double _simulation_duration, double _stepsize)
	: BuckConverterModel(_BuckConverterModel), simulation_duration(_simulation_duration), stepsize(_stepsize)
{
	i_values = CData("i_R");
	i_dot_values = CData("i_dot_values");
	switch_state = CData("switch_state");
}

CSolver::CSolver() {
	i_values = CData("i_R");
	i_dot_values = CData("i_dot_values");
	switch_state = CData("switch_state");
}


// Change Strategy
void CSolver::SetStrategy(CBuckConverterModelAbstract* _strategy) {
	double R_ = BuckConverterModel->GetResistance();
	double L_ = BuckConverterModel->GetInductance();
	double C_ = BuckConverterModel->GetCapacitance();
	double V_in_ = BuckConverterModel->GetInputVoltage();
	double PWM_f_ = BuckConverterModel->GetPWMfrequency();
	double PWM_d_ = BuckConverterModel->GetDutyCycle();
	_strategy->SetResistance(R_);
	_strategy->SetInductance(L_);
	_strategy->SetCapacitance(C_);
	_strategy->SetInputVoltage(V_in_);
	_strategy->SetPWMfrequency(PWM_f_);
	_strategy->SetDutyCycle(PWM_d_);
	BuckConverterModel = _strategy;
}

// initialize model
void CSolver::initializeModel(CBuckConverterModelAbstract* _model) {
	BuckConverterModel = _model;
}

// Set simulation parameters (duration and stepsize)
void CSolver::SetSimulationParams(double _duration, double _stepsize) {
	simulation_duration = _duration;
	stepsize = _stepsize;
	double data_length = round(simulation_duration / stepsize);
	i_dot_values.setLength(data_length);
	i_values.setLength(data_length);
	switch_state.setLength(data_length);
}

// get i values 
CData CSolver::get_i_Values() {
	return i_values;
}

// get i dot values
CData CSolver::get_i_dot_Values() {
	return i_dot_values;
}

CData CSolver::get_switch_state() {
	return switch_state;
}


// This method solves the ODEs of the buck converter current and fills the data containers
void CSolver::simulate() {

	// get the switch ON ODE from the buck converter object
	std::function<double(double, double, double)> ODE = this->BuckConverterModel->GetCurrentODE();

	// create a runge kutta object for solving the switch ON ODE
	CRunge_Kutta RungeKutta(ODE, this->stepsize);

	// set the initial current (i) state
	i_dot_values.setDataValueX(0.0, 0);
	i_dot_values.setDataValueY(0.0, 0);
	double last_i_dot_value = 0.0;

	i_values.setDataValueX(0.0, 0);
	i_values.setDataValueY(BuckConverterModel->GetInitialCurrentValue(), 0);
	double last_i_value = BuckConverterModel->GetInitialCurrentValue();

	// do a runge kutta step until the simulation duration is reached
	int i = 0;
	for (double t = 0; t <= simulation_duration; t += stepsize) {

		// Set current time value within the buck converter model
		this->BuckConverterModel->SetTime(t);

		// Observe the switch state
		int current_switch_state = this->BuckConverterModel->GetSwitchState();
		switch_state.setDataValueX(t, i);
		switch_state.setDataValueY(current_switch_state, i);

		if (i != 0) {
			double next_i_dot_value = RungeKutta.step(t, last_i_dot_value, last_i_value);
			double next_i_value = last_i_value + this->stepsize * next_i_dot_value;

			i_dot_values.setDataValueX(t, i);
			i_dot_values.setDataValueY(next_i_dot_value, i);

			i_values.setDataValueX(t, i);
			i_values.setDataValueY(next_i_value, i);

			last_i_dot_value = next_i_dot_value;
			last_i_value = next_i_value;
		}

		i = i + 1;
	}
}
