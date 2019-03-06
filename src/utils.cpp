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
#include <algorithm>
#include "utils.hpp"

bool endswith(const std::string& str, const std::string& suffix) {
  if (suffix.size() > str.size()) {
    return false;
  }

  return str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

bool startswith(const std::string& str, const std::string& prefix) {
  if (prefix.size() > str.size()) {
    return false;
  }

  return str.compare(0, prefix.size(), prefix, prefix.size()) == 0;
}

std::string normalize_class_name(const std::string& name) {
  std::string normalized = name;

  // Remove '.java'
  if (endswith(normalized, ".java")) {
    size_t pos = normalized.rfind(".java");
    normalized = normalized.substr(0, pos - 1);
  }

  // Replace all '.' with '/'
  std::replace(std::begin(normalized), std::end(normalized), '.', '/');

  if (normalized.front() != 'L') {
    normalized = 'L' + normalized;
  }

  if (normalized.back() != ';') {
    normalized = normalized + ';';
  }
  return normalized;
}

std::string pretty_class_name(const std::string& name, bool with_ext) {
  std::string pretty = normalize_class_name(name);

  // Remove L and ;
  pretty = pretty.substr(1, pretty.size() - 2);

  // Replace '/' with '.'
  std::replace(std::begin(pretty), std::end(pretty), '/', '.');

  if (with_ext) {
    pretty += ".java";
  }
  return pretty;
}
