#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>
#include "knn.h"
#include "pca.h"
#include "eigen.h"

namespace py=pybind11;

// el primer argumento es el nombre...
PYBIND11_MODULE(sentiment, m) {
    py::class_<KNNClassifier>(m, "KNNClassifier")
        .def(py::init<unsigned int>())
        .def("fit", &KNNClassifier::fit)
        .def("predict", &KNNClassifier::predict)
        .def("vectores", &KNNClassifier::vectores)
        .def("labels", &KNNClassifier::labels)
        .def("norma", &KNNClassifier::norma);

    py::class_<PCA>(m, "PCA")
        .def(py::init<unsigned int>())
        .def("fit", &PCA::fit)
        .def("transform", &PCA::transform)
        .def("cov", &PCA::cov)
        .def("cam_base", &PCA::cam_base)
        .def("autoval", &PCA::autoval);
    m.def(
        "power_iteration", &power_iteration,
        "Function that calculates eigenvector",
        py::arg("X"),
        py::arg("num_iter")=5000,
        py::arg("epsilon")=1e-16
    );
    m.def("generate_vocabulary", &generate_vocabulary,
        "Una funcion que entrena",
        py::arg("criticas"),
        py::arg("umbral_sup"),
        py::arg("umbral_inf"));    
    m.def("entrenar", &entrenar,
        "Una funcion que entrena",
        py::arg("critica"),
        py::arg("vocabulary"));        
    m.def("entrenar_varios", &entrenar_varios,
        "Una funcion que entrena",
        py::arg("criticas"),
        py::arg("positibidad"),
        py::arg("vocabulary"));
    m.def(
        "get_first_eigenvalues", &get_first_eigenvalues,
        "Function that calculates eigenvector",
        py::arg("X"),
        py::arg("num"),
        py::arg("num_iter")=5000,
        py::arg("epsilon")=1e-16
    );

}
