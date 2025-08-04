#include "pch.h"
#include "CBuckConverterModelAbstract.h"

// Base Construcor
CBuckConverterModelAbstract::CBuckConverterModelAbstract(double _R, double _L, double _C, double _V_in, double _PWM_f)
	: R(_R), L(_L), C(_C), V_in(_V_in), PWM_f(_PWM_f) {};

CBuckConverterModelAbstract::CBuckConverterModelAbstract(void)
	: R(1), L(2), C(2), V_in(5), PWM_f(50)
{};

// ...
void CBuckConverterModelAbstract::SetResistance(double _R) {
	R = _R;
};

// ...
double CBuckConverterModelAbstract::GetResistance() {
	return R;
};

// ...
void CBuckConverterModelAbstract::SetInductance(double _L) {
	L = _L;
};

// ...
double CBuckConverterModelAbstract::GetInductance() {
	return L;
};

// ...
void CBuckConverterModelAbstract::SetCapacitance(double _C) {
	C = _C;
};

// ...
double CBuckConverterModelAbstract::GetCapacitance() {
	return C;
};

// ...
void CBuckConverterModelAbstract::SetInputVoltage(double _V_in) {
	V_in = _V_in;
};

// ...
double CBuckConverterModelAbstract::GetInputVoltage() {
	return V_in;
};

// ...
void CBuckConverterModelAbstract::SetPWMfrequency(double _PWM_f) {
	PWM_f = _PWM_f;
};

// ...
double CBuckConverterModelAbstract::GetPWMfrequency() {
	return PWM_f;
};

// ...
void CBuckConverterModelAbstract::SetTime(double _t) {
	time = _t;
};

// ...
void CBuckConverterModelAbstract::SetDesiredOutputVoltage(double _V_out) {
	V_out = _V_out;
	PWM_d = V_out / V_in;
};

// ...
double CBuckConverterModelAbstract::GetDesiredOutputVoltage() {
	return V_out;
};

// ...
void CBuckConverterModelAbstract::SetDutyCycle(double _PWM_d) {
	PWM_d = _PWM_d;
	V_out = PWM_d * V_in;
};

// ...
double CBuckConverterModelAbstract::GetDutyCycle() {
	return PWM_d;
};

// ...
int CBuckConverterModelAbstract::GetSwitchState() {
	if (fmod(time + 0.5 * PWM_d * (1 / PWM_f), (1 / PWM_f)) < PWM_d * (1 / PWM_f)) {
		return 1; // On
	}
	else {
		return 0; // Off
	}
};

// ...
std::function<double(double, double, double)> CBuckConverterModelAbstract::GetCurrentODE() {
	double R_ = R;
	double L_ = L;
	double C_ = C;
	double V_in_ = V_in;
	double PWM_d_ = PWM_d;
	double PWM_f_ = PWM_f;
	return [R_, L_, C_, V_in_, PWM_d_, PWM_f_](double t, double di, double i) {
		if (fmod(t + 0.5 * PWM_d_ * (1 / PWM_f_), (1 / PWM_f_)) < PWM_d_ * (1 / PWM_f_)) {
			return 1 / (L_ * R_ * C_) * V_in_ - 1 / (R_ * C_) * di - 1 / (L_ * C_) * i; // On
		}
		else {
			return -1 / (R_ * C_) * di - 1 / (L_ * C_) * i; // Off
		};
		};
};

// ...
double CBuckConverterModelAbstract::CalcInductanceCurrent(double i, double id) {
	return i - C * R * id;
};

// ...
double CBuckConverterModelAbstract::CalcOutputVoltage(double i) {
	return i * R;
};

double CBuckConverterModelAbstract::CalcCapacitanceCurrent(double id) {
	return C * R * id;
}

double CBuckConverterModelAbstract::CalcInductanceVoltage(double id) {
	return L * id;
}