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
#ifndef JADX_JNI_CORE_H_
#define JADX_JNI_CORE_H_
#include <jni/jni.hpp>
#include <jadx/jadx.hpp>

#include <vector>
namespace jni {

#if defined(JVM_STATIC_LINK)
static constexpr bool jvm_static_link = true;
#else
static constexpr bool jvm_static_link = false;
#endif

using JNI_CreateJavaVM_t = std::add_pointer_t<decltype(JNI_CreateJavaVM)>;
using JNI_GetCreatedJavaVMs_t = std::add_pointer_t<decltype(JNI_GetCreatedJavaVMs)>;

std::string get_jadx_prefix(void);
std::vector<std::string> get_potential_libjvm_paths();
int try_dlopen(std::vector<std::string> potential_paths, void*& out_handle);
bool resolve_create_jvm(JNI_CreateJavaVM_t& hdl);
bool resolve_get_created_jvm(JNI_GetCreatedJavaVMs_t& hdl);

class Jadx {
  public:
  Jadx(void);
  jadx::api::JadxDecompiler load(const std::string& apk_path,
      bool escape_unicode = true,
      bool show_inconsistent_code = true,
      bool deobfuscation_on = false,
      size_t deobfuscation_min_length = 3,
      size_t deobfuscation_max_length = 64
      );

  ~Jadx(void);

  private:
  inline JNIEnv& env(void) {
    return *(this->env_);
  }

  inline JNIEnv& env(void) const {
    return *(this->env_);
  }

  JavaVM* jvm_{nullptr};
  JNIEnv* env_{nullptr};


};
}

#endif


