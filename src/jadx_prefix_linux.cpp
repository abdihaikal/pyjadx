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
#include "core.hpp"
#include <link.h>
namespace jni {

std::string get_jadx_prefix(void) {
  std::string found;
  dl_iterate_phdr([] (dl_phdr_info* info, size_t size, void* data) {
      std::string* out = reinterpret_cast<std::string*>(data);
      if (info->dlpi_name == nullptr) {
        return 0;
      }
      std::string path = info->dlpi_name;
      if (path.find("pyjadx.") != std::string::npos) {
        *out = path;
        return 1;
      }
      return 0;
  }, &found);
  if (not found.empty()) {
    size_t dir_idx = found.find_last_of("/");
    return found.substr(0, dir_idx);
  }
  return "";
}

}
