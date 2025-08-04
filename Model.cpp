#include "pch.h"
#include "Model.h"
#include <cmath>


CModel::CModel()
	: Solver()

{
	// initialize the simulation parameters
	double init_sim_duration = 0.01;
	double init_stepsize = 0.00001;
	double data_length = round(init_sim_duration / init_stepsize);
	Solver.SetSimulationParams(init_sim_duration, init_stepsize);

	// create CData objects to be filled with the calculated data
	CData u_sz = CData("u_sz");
	u_sz.setLength(data_length);

	CData u_Control = CData("u_Control");
	u_Control.setLength(data_length);

	CData u_Diode = CData("u_Diode");
	u_Diode.setLength(data_length);

	CData u_Out = CData("u_Out");
	u_Out.setLength(data_length);

	CData u_L = CData("u_L");
	u_L.setLength(data_length);

	CData i_L = CData("i_L");
	i_L.setLength(data_length);

	CData i_R = CData("i_R");
	i_R.setLength(data_length);

	CData i_C = CData("i_C");
	i_C.setLength(data_length);

	CData i_dot = CData("i_dot");
	i_dot.setLength(data_length);

	CData switch_state = CData("switch_state");
	switch_state.setLength(data_length);

	listData.push_back(u_sz);
	listData.push_back(u_Control);
	listData.push_back(u_Diode);
	listData.push_back(u_Out);
	listData.push_back(u_L);
	listData.push_back(i_L);
	listData.push_back(i_R);
	listData.push_back(i_C);
	listData.push_back(i_dot);
	listData.push_back(switch_state);

	BuckConverterModel = new CBuckConverterModel_SteadyState();

	//BuckConverterModel->SetDutyCycle(0.5);

	this->Solver.initializeModel(BuckConverterModel);

}

CModel::~CModel()
{
	delete BuckConverterModel;
}

void CModel::SetParams(double _R, double _L, double _C, double _V_in, double _PWM_d, double _PWM_f) {
	BuckConverterModel->SetResistance(_R);
	BuckConverterModel->SetInductance(_L);
	BuckConverterModel->SetCapacitance(_C);
	BuckConverterModel->SetInputVoltage(_V_in);
	BuckConverterModel->SetDutyCycle(_PWM_d);
	BuckConverterModel->SetPWMfrequency(_PWM_f);
	Solver.initializeModel(BuckConverterModel);
}

void CModel::initializeSolver(double _sim_duration, double _stepsize) {
	Solver.initializeModel(BuckConverterModel);
	Solver.SetSimulationParams(_sim_duration, _stepsize);
}

void CModel::setDataVectors(string _name, std::vector<double> _X_vector, std::vector<double> _Y_vector) {

	list<CData>::iterator it;
	// Iterate through the list

	for (it = listData.begin(); it != listData.end(); it++)
	{
		// Check if the current element's name matches the provided name
		if (it->getName() == _name) {
			/*it->setXVector(_X_vector);
			it->setYVector(_Y_vector);*/
		}

		// If no match is found, return nullptr

	}
}

void CModel::setSimulationStrategy() {
	if (BuckConverterModel) {
		if (dynamic_cast<CBuckConverterModel_SteadyState*>(BuckConverterModel)) {
			// Change to the dynamic model if the current model is the steady state model
			// delete BuckConverterModel;
			BuckConverterModel = new CBuckConverterModel_Dynamic;
			Solver.SetStrategy(BuckConverterModel);
		}
		else if (dynamic_cast<CBuckConverterModel_Dynamic*>(BuckConverterModel)) {
			// Change to the steady state model if the current model is the dynamic model
			// delete BuckConverterModel;
			BuckConverterModel = new CBuckConverterModel_SteadyState;
			Solver.SetStrategy(BuckConverterModel);
		}
	}
}

void CModel::setSimulationParams(double _duration, double _stepsize) {
	Solver.SetSimulationParams(_duration, _stepsize);
}


void CModel::calcModel(CDC* pDC) {


	// execute the simulation
	Solver.simulate();

	i_R = Solver.get_i_Values();
	i_dot = Solver.get_i_dot_Values();
	switch_state = Solver.get_switch_state();
	double init_sim_duration = 0.01;
	double init_stepsize = 0.00001;
	double data_length = round(init_sim_duration / init_stepsize);

	//Calculate the remaining quantities
	int i;
	for (i = 0; i < data_length; i++) {

		// get the current i and i_dot values which are needed for the calculation
		double t_value = i_R.getDataValueX(i);
		double i_value = i_R.getDataValueY(i);
		double i_dot_value = i_dot.getDataValueY(i);

		// calculation of the remaining quantities
		double i_C_value = BuckConverterModel->CalcCapacitanceCurrent(i_dot_value);
		double i_L_value = BuckConverterModel->CalcInductanceCurrent(i_value, i_dot_value);
		double v_L_value = BuckConverterModel->CalcInductanceVoltage(i_dot_value);
		double v_Out_value = BuckConverterModel->CalcOutputVoltage(i_value);

		list<CData>::iterator it;
		for (it = listData.begin(); it != listData.end(); it++)
		{
			if (it->getName() == "u_Out")
			{
				it->setDataValueY(v_Out_value, i);
				it->setDataValueX(t_value, i);
			}
			if (it->getName() == "u_L")
			{
				it->setDataValueY(v_L_value, i);
				it->setDataValueX(t_value, i);
			}
			if (it->getName() == "i_L")
			{
				it->setDataValueY(i_L_value, i);
				it->setDataValueX(t_value, i);
			}
			if (it->getName() == "i_C")
			{
				it->setDataValueY(i_C_value, i);
				it->setDataValueX(t_value, i);
			}
			if (it->getName() == "i_R")
			{
				it->setDataValueY(i_R.getDataValueY(i), i);
				it->setDataValueX(i_R.getDataValueX(i), i);
			}
			if (it->getName() == "switch_state")
			{
				it->setDataValueY(switch_state.getDataValueY(i), i);
				it->setDataValueX(switch_state.getDataValueX(i), i);
			}

		}

	}


	CAbstractModel::calcModel(pDC);
}

CControllableObject* CModel::getFrequency() {
	return &ctrFrequency;
}

CControllableObject* CModel::getAmpDot() {
	return &ctrAmplitude;
}

CControllableObject* CModel::getCapacitor()
{
	return &ctrCapacitor;
}


CControllableObject* CModel::getCoil()
{
	return &ctrCoil;
}

CControllableObject* CModel::getResistor()
{
	return &ctrResistor;
}

CControllableObject* CModel::getVoltage()
{
	return &ctrVoltage;
}

CControllableObject* CModel::getDutyCycle()
{
	return &ctrDutyCycle;
}



//CData* CModel::getData(void) {
//	return &Data;
//}

CData* CModel::getData(string _name)
{

	list<CData>::iterator it;
	// Iterate through the list



	for (it = listData.begin(); it != listData.end(); it++)
	{
		// Check if the current element's name matches the provided name
		if (it->getName() == _name) {
			// If a match is found, return a pointer to the current element
			return &(*it);
		}

		// If no match is found, return nullptr

	}

}

void CModel::setControllerValues(double _R_Controller, double _C_Controller, double _L_Controller, double _UD_Controller, double _f_Controller, double _D_Controller)
{
	R_Controller = _R_Controller;
	C_Controller = _C_Controller;
	L_Controller = _L_Controller;
	UD_Controller = _UD_Controller;
	f_Controller = _f_Controller;
	D_Controller = _D_Controller;

}
