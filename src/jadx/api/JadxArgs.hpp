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
#ifndef JADX_API_JADXARGS_H_
#define JADX_API_JADXARGS_H_

#include <jni/jni.hpp>
#include <string>


namespace jni::jadx::api {

class JadxArgs {
  public:
  struct Tag { static constexpr auto Name() { return "jadx/api/JadxArgs"; } };

  using Object_t = Object<Tag>;
  using Class_t  = Class<Tag>;

  JadxArgs(JNIEnv& env);

  const Class_t& clazz(void) const;
  Local<Object_t> get(void);

  void setInputFiles(const std::vector<std::string>& inputs);
  void show_inconsistent_code(bool value);
  void escape_unicode(bool value);

  private:
  inline JNIEnv& env(void) {
    return *(this->env_);
  }

  inline JNIEnv& env(void) const {
    return *(this->env_);
  }

  mutable JNIEnv* env_{nullptr};
  Local<Object_t> obj_{nullptr};
};

}
#endif
