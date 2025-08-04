#include "pch.h"
#include "CBuckConverterModel_SteadyState.h"

double CBuckConverterModel_SteadyState::GetInitialCurrentValue() {
	double V_out_amplitude = V_out / L * (1 - PWM_d) * (1 / PWM_f) * (1 / PWM_f) / (16 * C);
	return PWM_d * V_in / R - V_out_amplitude / R;
};