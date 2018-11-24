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
#include <jadx/api/JavaClass.hpp>

#include <java/util/List.hpp>

namespace jni::jadx::api {

JavaClass::JavaClass(JNIEnv& env, const Object_t& obj) {
  this->env_ = &env;
  this->obj_ = NewLocal(env, obj);
}

JavaClass::JavaClass(JNIEnv& env, const Object<>& obj) {

  this->env_ = &env;
  auto&& casted = Cast<JavaClassTag>(this->env(), this->clazz(), obj);
  this->obj_ = NewLocal(env, casted);
}

std::string JavaClass::getCode() {
  static auto&& getCode = this->clazz().GetMethod<String()>(this->env(), "getCode");
  return Make<std::string>(this->env(), this->obj_.Call(this->env(), getCode));
}


JavaClass::methods_list_t JavaClass::methods(void) {
  using List_t = java::util::List<JavaMethod>;
  static auto&& getMethods = this->clazz().template GetMethod<Object<List_t::Tag>()>(this->env(), "getMethods");

  auto&& jmethods = this->obj_.Call(this->env(), getMethods);

  List_t jlist{this->env(), jmethods};

  JavaClass::methods_list_t methods;
  methods.reserve(jlist.size());

  for (size_t i = 0; i < jlist.size(); ++i) {
    methods.emplace_back(jlist.at(i));
  }

  return methods;
}

}
