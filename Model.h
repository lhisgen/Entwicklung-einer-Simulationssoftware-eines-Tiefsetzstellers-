#pragma once
#include "const.h"
#include "CData.h"
#include "Graph.h"
#include "AbstractModel.h"
#include "ControllableObject.h"
#include <list>
#include "CSolver.h"
#include "CBuckConverterModel_SteadyState.h"
#include "CBuckConverterModel_Dynamic.h"
#include "CBuckConverterModelAbstract.h"

class CModel: public CAbstractModel {
private:
	double R_Controller;
	double L_Controller;
	double C_Controller;
	double f_Controller;
	double UD_Controller;
	double D_Controller;
	CData u_sz;
	CData u_Control;
	CData u_Diode;
	CData u_Out;
	CData u_L;
	CData i_L;
	CData i_R;
	CData i_C;
	CData i_dot;
	CData switch_state;
	list<CData> listData;

	CBuckConverterModelAbstract* BuckConverterModel;
	CSolver Solver;

	CControllableObject ctrAmplitude;
	CControllableObject ctrCapacitor;
	CControllableObject ctrCoil;
	CControllableObject ctrResistor;
	CControllableObject ctrVoltage;
	CControllableObject ctrFrequency;
	CControllableObject ctrDutyCycle;

public:
	CModel();
	~CModel();
	void calcModel(CDC * pDC);
	void SetParams(double _R, double _L, double _C, double _V_in, double _PWM_d, double _PWM_f);
	void initializeSolver(double _sim_duration, double _stepsize);
	void setDataVectors(string _name, std::vector<double> _X_vector, std::vector<double> _Y_vector);
	void setSimulationStrategy();
	void setSimulationParams(double _duration, double _stepsize);
	void setControllerValues(double _R_Controller, double _C_Controller, double _L_Controller, double _UD_Controller, double _f_Controller, double _D_Controller);
	//CControllableObject * getFreqDot();
	CControllableObject* getFrequency();
	CControllableObject * getAmpDot();
	CControllableObject * getCapacitor();
	CControllableObject * getCoil();
	CControllableObject * getResistor();
	CControllableObject* getVoltage();
	CControllableObject* getDutyCycle();
	CData* getData(string _name);


};

