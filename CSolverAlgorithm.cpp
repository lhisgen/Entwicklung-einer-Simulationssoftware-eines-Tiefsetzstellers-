#include "pch.h"
#include "CSolverAlgorithm.h"

CSolverAlgorithm::CSolverAlgorithm(void) {}
CSolverAlgorithm::CSolverAlgorithm(Function_2args f, double _h) : func_2args(f), h(_h) {}
CSolverAlgorithm::CSolverAlgorithm(Function_3args f, double _h) : func_3args(f), h(_h) {}

void CSolverAlgorithm::setFunction(Function_2args f) {
    func_2args = f;
}

void CSolverAlgorithm::setFunction(Function_3args f) {
    func_3args = f;
}