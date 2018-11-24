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

std::string get_jadx_prefix(void);

class Jadx {
  public:
  Jadx(void);
  jadx::api::JadxDecompiler load(const std::string& apk_path);

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


