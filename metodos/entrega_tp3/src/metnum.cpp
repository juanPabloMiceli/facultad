#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include "linear_regression.h"

namespace py=pybind11;

// el primer argumento es el nombre...
PYBIND11_MODULE(metnum, m) {
    py::class_<LinearRegression>(m, "LinearRegression")
        .def(py::init<>())
        .def("get_AtA", &LinearRegression::get_AtA)
        .def("get_coef", &LinearRegression::get_coef)
        .def("fit", &LinearRegression::fit)
        .def("predict", &LinearRegression::predict);
}
