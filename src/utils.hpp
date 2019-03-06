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
#ifndef JADX_UTILS_H_
#define JADX_UTILS_H_
#include <string>

bool endswith(const std::string& str, const std::string& suffix);
bool startswith(const std::string& str, const std::string& prefix);

std::string normalize_class_name(const std::string& name);

// La;
// Lsome/pkg/Class;
// some.pkg.Class
//
std::string pretty_class_name(const std::string& name, bool with_ext = false);

#endif
