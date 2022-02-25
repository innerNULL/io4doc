/// file: pymodule.cpp
/// date: 2022-02-26


#include <string>
#include <vector>
#include <tuple>
#include <set>
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>

#include "./keywords.h"


namespace py = pybind11;


PYBIND11_MODULE(keytext4py_ext_cpp, m) {
  m.def(
    "keywords_by_pos", &keytext4py_ext::keywords_by_pos,
    py::arg("tokens"), 
    py::arg("top_k")=-1, 
    py::arg("target_pos")=std::set<std::string>({"NR", "NN"}), 
    py::arg("min_word_len")=1, 
    py::arg("weight_norm")=true, 
    py::arg("weight_scale")=100.0, 
    py::arg("pos_bucketing")=false);
}
