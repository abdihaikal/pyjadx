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
#ifndef JAVA_IO_FILE_H_
#define JAVA_IO_FILE_H_

#include <jni/jni.hpp>
#include <string>

namespace jni::java::io {

class File {
  public:
  struct Tag { static constexpr auto Name() { return "java/io/File"; } };

  using Object_t = Object<Tag>;
  using Class_t  = Class<Tag>;

  File(JNIEnv& env, const std::string& path);

  const Class_t& clazz(void) const;
  Local<Object_t> get(void);

  private:
  inline JNIEnv& env(void) {
    return *(this->env_);
  }

  inline JNIEnv& env(void) const {
    return *(this->env_);
  }

  mutable JNIEnv*         env_{nullptr};
  Local<Object_t> obj_{nullptr};
};

}
#endif
