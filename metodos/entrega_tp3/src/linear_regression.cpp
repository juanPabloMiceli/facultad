#include <algorithm>
//#include <chrono>
//#include <pybind11/pybind11.h>
#include <iostream>
#include <exception>
#include "linear_regression.h"

using namespace std;
//namespace py=pybind11;

LinearRegression::LinearRegression(): _AtA(), _Atb(){}


MatrixXd LinearRegression::get_AtA() {
    return _AtA;
}

MatrixXd LinearRegression::get_coef() {
    return _coef;
}

void LinearRegression::fit(Matrix X, Matrix y)
{
    _AtA=X.transpose()*X;
    _Atb=X.transpose()*y;
    _coef = _AtA.fullPivHouseholderQr().solve(_Atb);
    cout<<"AtA: "<<_AtA<<"\n"<<"Atb: "<<_Atb<<endl;
}


Matrix LinearRegression::predict(Matrix X)
{
//  auto ret = MatrixXd::Zero(X.rows(), 1);

    return X*_coef;
}








