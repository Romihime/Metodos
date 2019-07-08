#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include "cuadradosminimos.h"
#include "eigen.h"


namespace py=pybind11;

// el primer argumento es el nombre...
PYBIND11_MODULE(linearregression, m) {
    py::class_<CuadradosMinimos>(m, "CuadradosMinimos")
        .def(py::init<std::string>())//def(py::init<string>())???
        .def("armarMatrixA", &CuadradosMinimos::armarMatrixA)
        .def("armarMatrixA_trigo", &CuadradosMinimos::armarMatrixA_trigo)
        .def("armarMatrixA_fusion", &CuadradosMinimos::armarMatrixA_fusion)
        .def("fit", &CuadradosMinimos::fit)
        .def("fit_fusion", &CuadradosMinimos::fit_fusion)        
        .def("predict", &CuadradosMinimos::predict);
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
