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
#include <jadx/api/JadxArgs.hpp>

#include <java/io/File.hpp>
#include <java/util/ArrayList.hpp>
#include <java/util/List.hpp>

namespace jni::jadx::api {

JadxArgs::JadxArgs(JNIEnv& env) :
  env_{&env}
{
  static auto&& ctor = this->clazz().GetConstructor<>(this->env());
  this->obj_         = this->clazz().New(this->env(), ctor);
}

const JadxArgs::Class_t& JadxArgs::clazz(void) const {
  return Class_t::Singleton(this->env());
}

Local<JadxArgs::Object_t> JadxArgs::get(void) {
  return NewLocal(this->env(), this->obj_);
}


void JadxArgs::setInputFiles(const std::vector<std::string>& inputs) {
  java::util::ArrayList<java::io::File> jinputs{this->env(), inputs};

  using List_t = java::util::List<std::string>;
  static auto&& setInputFiles = this->clazz().template GetMethod<void(Object<List_t::Tag>)>(this->env(), "setInputFiles");

  auto&& file_list = Cast<List_t::Tag>(this->env(), List_t::from_env(this->env()), jinputs.get());
  return this->obj_.Call(this->env(), setInputFiles, file_list);
}


void JadxArgs::show_inconsistent_code(bool value) {
  static auto&& setShowInconsistentCode = this->clazz().template GetMethod<void(jboolean)>(this->env(), "setShowInconsistentCode");

  return this->obj_.Call(this->env(), setShowInconsistentCode, static_cast<jboolean>(value));
}

void JadxArgs::escape_unicode(bool value) {
  static auto&& setEscapeUnicode = this->clazz().template GetMethod<void(jboolean)>(this->env(), "setEscapeUnicode");

  return this->obj_.Call(this->env(), setEscapeUnicode, static_cast<jboolean>(value));
}

}
