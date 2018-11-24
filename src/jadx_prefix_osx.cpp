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
#include <mach-o/dyld.h>
namespace jni {

std::string get_jadx_prefix(void) {
  std::string found;
  uint32_t count = _dyld_image_count();
  for (size_t i = 0; i < count; ++i) {
    std::string image_name = _dyld_get_image_name(i);
    if (image_name.find("pyjadx.") != std::string::npos) {
      found = image_name;
      break;
    }
  }

  if (not found.empty()) {
    size_t dir_idx = found.find_last_of("/");
    return found.substr(0, dir_idx);
  }
  return "";
}

}
