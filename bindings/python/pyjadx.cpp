/* Copyright 2018 R. Thomas
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "pyjadx.hpp"
#include "version.h"
#include <jadx/jadx.hpp>
#include "core.hpp"
#include <sstream>

py::module jadx_module("pyjadx", "JADX Python API");

using namespace jni::jadx::api;

PYBIND11_MODULE(pyjadx, jadx_module) {

  jadx_module.attr("__version__")          = py::str(PYJADX_VERSION);
  jadx_module.attr("__pyjadx_tag__")       = py::str(PYJADX_TAG);
  jadx_module.attr("__pyjadx_is_tagged__") = py::bool_(PYJADX_TAGGED);

  py::class_<jni::Jadx>(jadx_module, "Jadx", "")
    .def(py::init<>())
    .def("load", &jni::Jadx::load);


  py::class_<JadxDecompiler>(jadx_module, "JadxDecompiler", "")
    .def("load",
        &JadxDecompiler::load,
        "Load an APK or Dex file to decompile")

    .def_property_readonly("classes",
        &JadxDecompiler::classes,
        "List of :class:`~pyjadx.JavaClass`")

    .def_property_readonly("packages",
        &JadxDecompiler::packages,
        "List of :class:`~pyjadx.JavaPackage`")

    .def("get_class",
        &JadxDecompiler::get_class,
        "Return the :class:`~pyjadx.JavaClass` object from "
        "the name given in first parameter",
        "class_name"_a);

  py::class_<JavaMethod>(jadx_module, "JavaMethod", "")
    .def_property_readonly("name",
        &JavaMethod::name,
        "Method name as a ``str``")

    .def_property_readonly("fullname",
        &JavaMethod::fullname,
        "Method fullname as a ``str``")

    .def_property_readonly("decompiled_line",
        &JavaMethod::decompiled_line,
        "Line number in decompiled code associated with this method")

    .def("__str__", &JavaMethod::to_string)
    .def("__hash__", &JavaMethod::hash_code)
    .def("__eq__", &JavaMethod::operator==);

  py::class_<JavaClass>(jadx_module, "JavaClass", "")
    .def_property_readonly("code",
        &JavaClass::getCode,
        "Java decompiled code as a ``str``")


    .def_property_readonly("code_highlight",
        [] (JavaClass& cls) -> py::object {
          try {
            auto&& pygments              = py::module::import("pygments");
            auto&& get_lexer_by_name     = py::module::import("pygments.lexers").attr("get_lexer_by_name");
            auto&& get_formatter_by_name = py::module::import("pygments.formatters").attr("get_formatter_by_name");
            auto&& highlight             = pygments.attr("highlight");

            auto&& lexer     = get_lexer_by_name("java");
            auto&& formatter = get_formatter_by_name("terminal256", "style"_a="monokai", "linenos"_a=false);
            return highlight(cls.getCode(), lexer, formatter);
          } catch (const std::exception& e) {
            py::print(e.what());
          }
          return py::str(cls.getCode());
        },
        "Highlight decompiled code (Require Pygments)")

    .def("save",
        [] (JavaClass& cls, py::object output) {
          std::string str_output;

          auto&& pathlib = py::module::import("pathlib");
          auto&& Path = pathlib.attr("Path");
          if (py::isinstance<py::str>(output)) {
            str_output = output.cast<std::string>();
          }
          else if (py::isinstance(output, Path)) {
            str_output = output.attr("as_posix")().cast<std::string>();

          } else {
            std::string error_str = py::repr(output).cast<std::string>();
            error_str = error_str + " is not supported!";
            throw py::type_error(error_str.c_str());
          }

          return cls.save(str_output);
        },
        "Save decompiled code in the file given in first parameter\n\n"
        "Return False is an error occurred",
        "output_path"_a)

    .def_property_readonly("methods",
        &JavaClass::methods,
        "List of :class:`~pyjadx.JavaMethod`")

    .def_property_readonly("name",
        &JavaClass::name,
        "Class name as a ``str``")

    .def_property_readonly("fullname",
        &JavaClass::fullname,
        "Class fullname as a ``str``")

    .def_property_readonly("decompiled_line",
        &JavaClass::decompiled_line,
        "Line number in decompiled code associated with this class");


  py::class_<JavaPackage>(jadx_module, "JavaPackage", "")
    .def_property_readonly("classes",
        &JavaPackage::classes,
        "List of :class:`~pyjadx.JavaClass`")

    .def_property_readonly("name",
        &JavaPackage::name,
        "Package name")

    .def_property_readonly("fullname",
        &JavaPackage::fullname,
        "Package fullname")

    .def_property_readonly("decompiled_line",
        &JavaPackage::decompiled_line,
        "Line number in decompiled code associated with this package");







}
