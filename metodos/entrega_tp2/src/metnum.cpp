#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include "knn.h"
#include "pca.h"
#include "eigen.h"

namespace py=pybind11;

// el primer argumento es el nombre...
PYBIND11_MODULE(metnum, m) {
    py::class_<KNNClassifier>(m, "KNNClassifier")
        .def(py::init<unsigned int>())
        .def("fit", &KNNClassifier::fit)
        .def("predict", &KNNClassifier::predict)
        .def("set_n_neig", &KNNClassifier::set_n_neig);

    py::class_<PCA>(m, "PCA")
        .def(py::init<unsigned int>())
        .def("fit", &PCA::fit)
        .def("read_csv", &PCA::read_csv)
        .def("write_csv", &PCA::write_csv)
        .def("ret_autovect", &PCA::ret_autovect)
        .def("ret_autoval", &PCA::ret_autoval)
        .def("transform", &PCA::transform)
        .def("custom_transform", &PCA::custom_transform)
        .def("read_binary", &PCA::read_binary)
        .def("write_binary", &PCA::write_binary)
        .def("var_pec", &PCA::var_perc);
    m.def(
        "power_iteration", &power_iteration,
        "Function that calculates eigenvector",
        py::arg("X"),
        py::arg("num_iter")=5000,
        py::arg("epsilon")=1e-16
    );
    m.def(
        "get_first_eigenvalues", &get_first_eigenvalues,
        "Function that calculates eigenvector",
        py::arg("X"),
        py::arg("num"),
        py::arg("num_iter")=5000,
        py::arg("epsilon")=1e-16
    );

}
