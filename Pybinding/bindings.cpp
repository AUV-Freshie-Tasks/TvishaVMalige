#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include "matrix.h"
#include "matrix.cpp"
#include "matrixOps.h"
#include "LinearRegression.h"

namespace py = pybind11;

PYBIND11_MODULE(matrix_module, m) {
    m.doc() = "PYBINDING";
    py::class_<Matrix<double>>(m, "MatrixDouble")
        
        .def(py::init<>())
        .def(py::init<int, int>(), py::arg("rows"), py::arg("cols"))
        .def(py::init<const std::vector<std::vector<double>>&>())

        
        .def_property_readonly("rows", &Matrix<double>::Rows)
        .def_property_readonly("cols", &Matrix<double>::Columns)
        
        
        .def("display", &Matrix<double>::displayVector)
        .def("to_list", &Matrix<double>::data)

        
        .def("__getitem__", [](Matrix<double> &self, std::pair<int, int> i) {
            return self(i.first, i.second);
        })
        .def("__setitem__", [](Matrix<double> &self, std::pair<int, int> i, double val) {
            self(i.first, i.second) = val;
        })

        
        
        .def("__add__", [](const Matrix<double> &a, const Matrix<double> &b) {
            return a + b; 
        }, py::is_operator())

        
        .def("__matmul__", [](const Matrix<double> &a, const Matrix<double> &b) {
            return a * b;
        }, py::is_operator())

        
        .def("inverse", &Matrix<double>::inverseOfMatrix)
        .def("eqn_solver", &Matrix<double>::EqnSolver) // Uses LRU Cache internally
        .def_static("identity", &Matrix<double>::identity)

        
        .def("__repr__", [](const Matrix<double> &self) {
            return "<MatrixDouble (" + std::to_string(self.Rows()) + "x" + std::to_string(self.Columns()) + ")>";
        });


    py::class_<Matrix<float>>(m, "MatrixFloat")
        .def(py::init<>())
        .def(py::init<int, int>(), py::arg("rows"), py::arg("cols"))
        .def(py::init<const std::vector<std::vector<float>>&>())
        
        .def_property_readonly("rows", &Matrix<float>::Rows)
        .def_property_readonly("cols", &Matrix<float>::Columns)
        .def("display", &Matrix<float>::displayVector)
        .def("to_list", &Matrix<float>::data)

        .def("__getitem__", [](Matrix<float> &self, std::pair<int, int> i) {
            return self(i.first, i.second);
        })
        .def("__setitem__", [](Matrix<float> &self, std::pair<int, int> i, float val) {
            self(i.first, i.second) = val;
        })

        .def("__add__", [](const Matrix<float> &a, const Matrix<float> &b) {
            return a + b; 
        }, py::is_operator())

        .def("__matmul__", [](const Matrix<float> &a, const Matrix<float> &b) {
            return a * b;
        }, py::is_operator())

        .def("inverse", &Matrix<float>::inverseOfMatrix)
        .def("eqn_solver", &Matrix<float>::EqnSolver) 
        .def_static("identity", &Matrix<float>::identity)

        .def("__repr__", [](const Matrix<float> &self) {
            return "<MatrixFloat (" + std::to_string(self.Rows()) + "x" + std::to_string(self.Columns()) + ")>";
        });

    py::class_<Matrix<int>>(m, "MatrixInt")
        .def(py::init<>())
        .def(py::init<int, int>(), py::arg("rows"), py::arg("cols"))
        .def(py::init<const std::vector<std::vector<int>>&>())
        
        .def_property_readonly("rows", &Matrix<int>::Rows)
        .def_property_readonly("cols", &Matrix<int>::Columns)
        .def("display", &Matrix<int>::displayVector)
        .def("to_list", &Matrix<int>::data)

        .def("__getitem__", [](Matrix<int> &self, std::pair<int, int> i) {
            return self(i.first, i.second);
        })
        .def("__setitem__", [](Matrix<int> &self, std::pair<int, int> i, int val) {
            self(i.first, i.second) = val;
        })

        .def("__add__", [](const Matrix<int> &a, const Matrix<int> &b) {
            return a + b; 
        }, py::is_operator())

        .def("__matmul__", [](const Matrix<int> &a, const Matrix<int> &b) {
            return a * b;
        }, py::is_operator())

        .def("inverse", &Matrix<int>::inverseOfMatrix)
        .def("eqn_solver", &Matrix<int>::EqnSolver) 
        .def_static("identity", &Matrix<int>::identity)

        .def("__repr__", [](const Matrix<int> &self) {
            return "<MatrixInt (" + std::to_string(self.Rows()) + "x" + std::to_string(self.Columns()) + ")>";
        });

    py::class_<LinearRegression>(m, "LinearRegression")
	.def(py::init<double, int>(), 
             py::arg("lr") = 0.01, 
             py::arg("iters") = 1000)
        
        
        .def("fit", &LinearRegression::fit, 
             py::arg("X"), py::arg("Y"), 
             "Train the model")
        
        
        .def("predict", &LinearRegression::predict, 
             py::arg("Xtest"), 
             "Predict values for new data")
        
        
        .def_property_readonly("weights", &LinearRegression::getWeights);              
	
        
        
}
