#pragma once

#include "types.h"

class LinearRegression {
public:
    LinearRegression();

    void fit(Matrix X, Matrix y);
    MatrixXd get_AtA(void);
    MatrixXd get_coef(void);

    Matrix predict(Matrix X);
private:
    MatrixXd _AtA;
    MatrixXd _Atb;
    MatrixXd _coef;
};