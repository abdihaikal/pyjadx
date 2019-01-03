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
#ifndef JADX_API_JADXDECOMPILER_H_
#define JADX_API_JADXDECOMPILER_H_

#include <jadx/api/JadxArgs.hpp>
#include <jadx/api/JavaClass.hpp>
#include <jadx/api/JavaPackage.hpp>

#include <jni/jni.hpp>
#include <string>


namespace jni::jadx::api {

class JadxDecompiler {
  public:
  struct Tag { static constexpr auto Name() { return "jadx/api/JadxDecompiler"; } };

  using Object_t = Object<Tag>;
  using Class_t  = Class<Tag>;
  using classes_list_t = std::vector<JavaClass>;
  using packages_list_t = std::vector<JavaPackage>;

  JadxDecompiler(JNIEnv& env, JadxArgs& args);

  const Class_t& clazz(void) const;
  Local<Object_t> get(void);

  void load(void);
  classes_list_t classes(void);
  packages_list_t packages(void);

  bool has_class(const std::string& name);
  bool has_package(const std::string& name);

  JavaClass get_class(const std::string& name);
  JavaPackage get_package(const std::string& name);

  std::string getVersion(void) const;

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
