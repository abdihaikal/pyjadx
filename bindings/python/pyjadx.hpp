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
#ifndef PY_JADX_H_
#define PY_JADX_H_

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#define RST_CLASS_REF(X) ":class:`~"#X"`"
#define RST_CLASS_REF_FULL(X) ":class:`"#X"`"

#define RST_ATTR_REF(X) ":attr:`~"#X"`"
#define RST_ATTR_REF_FULL(X) ":attr:`"#X"`"

namespace py = pybind11;

using namespace pybind11::literals;

#endif
