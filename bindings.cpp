#include <pybind11/pybind11.h>
#include <pybind11/stl.
#include "matrix.h"
#include "matrixOps.h"   

namespace py = pybind11;

// Helper to bind Matrix templates
template <typename T>
void bind_matrix_class(py::module &m, const std::string &typestr) {
    using Class = Matrix<T>;
    std::string pyclass_name = "Matrix" + typestr;

    py::class_<Class>(m, pyclass_name.c_str())
    
        .def(py::init<>())
        .def(py::init<int, int>())
        .def(py::init<const std::vector<std::vector<T>>&>())
        
        
        .def("displayVector", &Class::displayVector)
        .def("noOfRows", &Class::noOfRows)
        .def("noOfColumns", &Class::noOfColumns)
        .def("Rows", &Class::Rows)
        .def("Columns", &Class::Columns)
        .def("data", &Class::data)
        

        .def("inverseOfMatrix", &Class::inverseOfMatrix)
        .def("EqnSolver", &Class::EqnSolver)
        

        .def_static("identity", &Class::identity)
        

        .def("__call__", [](Class &self, int r, int c) {
            return self(r, c);
        })

        .def("__getitem__", [](Class &self, int index) {
            return self[index];
        });
}

PYBIND11_MODULE(matrix_module, m) {
    m.doc() = "Comprehensive Matrix Library Bindings";

  
    py::class_<LUResult>(m, "LUResult")
        .def_readwrite("lmat", &LUResult::lmat)
        .def_readwrite("umat", &LUResult::umat);

   
    bind_matrix_class<double>(m, "Double");
    bind_matrix_class<int>(m, "Int");

    
    m.def("computeLU", &computeLU, "Performs LU decomposition with LRU caching");
    m.def("hashMatrix", &hashMatrix, "Generates a hash for a MatrixDouble");

}
