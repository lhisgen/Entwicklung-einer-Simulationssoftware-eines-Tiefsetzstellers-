#pragma once
#include "CBuckConverterModelAbstract.h"
#include "CRunge_Kutta.h"
#include <vector>
#include "CData.h"

class CSolver
{
private:
	CBuckConverterModelAbstract* BuckConverterModel;
	double simulation_duration;
	double stepsize;
	CData i_values;
	CData i_dot_values;
	CData switch_state;

public:

	// Constructor
	CSolver(CBuckConverterModelAbstract* _BuckConverterModel, double _simulation_duration, double _stepsize);
	CSolver();

	// Set Strategy (steady state or dynamic simulation)
	void SetStrategy(CBuckConverterModelAbstract* _strategy);

	// Set simulation duration and stepsize
	void SetSimulationParams(double _duration, double _stepsize);

	// initialize model
	void initializeModel(CBuckConverterModelAbstract* _model);

	// This method solves the ODEs of the buck converter current and fills the data containers
	void simulate();

	// Get i values
	CData get_i_Values();

	// get i dot values
	CData get_i_dot_Values();

	// get switch_state values
	CData get_switch_state();

};


