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
#include <java/io/File.hpp>

namespace jni::java::io {

File::File(JNIEnv& env, const std::string& path) :
  env_{&env}
{
  static auto&& ctor = this->clazz().GetConstructor<String>(this->env());
  this->obj_         = this->clazz().New(this->env(), ctor, Make<String>(env, path));
}

const File::Class_t& File::clazz(void) const {
  return Class_t::Singleton(this->env());
}

Local<File::Object_t> File::get(void) {
  return NewLocal(this->env(), this->obj_);
}
}
