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
#include <jadx/api/JavaMethod.hpp>

namespace jni::jadx::api {

JavaMethod::JavaMethod(JNIEnv& env, const Object_t& obj) {
  this->env_ = &env;
  this->obj_ = NewLocal(env, obj);
}

JavaMethod::JavaMethod(JNIEnv& env, const Object<>& obj) {

  this->env_ = &env;
  auto&& casted = Cast<JavaMethodTag>(this->env(), this->clazz(), obj);
  this->obj_ = NewLocal(env, casted);
}


bool JavaMethod::is_constructor(void) const {
  static auto&& isConstructor = this->clazz().template GetMethod<jboolean()>(this->env(), "isConstructor");
  return this->obj_.Call(this->env(), isConstructor);
}

bool JavaMethod::is_class_init(void) const {
  static auto&& isClassInit = this->clazz().template GetMethod<jboolean()>(this->env(), "isClassInit");
  return this->obj_.Call(this->env(), isClassInit);
}

std::string JavaMethod::to_string(void) const {
  static auto&& toString = this->clazz().template GetMethod<String()>(this->env(), "toString");
  return Make<std::string>(this->env(), this->obj_.Call(this->env(), toString));
}


//JavaClass JavaMethod::declaring_class(void) {
//  return const_cast<JavaClass>(static_cast<const JavaMethod*>(this)->declaring_class());
//}
//
//const JavaClass JavaMethod::declaring_class(void) const {
//}

size_t JavaMethod::hash_code(void) const {
  static auto&& hashCode = this->clazz().template GetMethod<jint()>(this->env(), "hashCode");
  return this->obj_.Call(this->env(), hashCode);
}

bool JavaMethod::operator==(const JavaMethod& other) const {
  static auto&& equals = this->clazz().template GetMethod<jboolean(Object<>)>(this->env(), "equals");
  return this->obj_.Call(this->env(), equals, other.get());
}
bool JavaMethod::operator!=(const JavaMethod& other) const {
  return not (*this == other);
}

std::ostream& operator<<(std::ostream& os, const JavaMethod& meth) {
  os << meth.to_string();
  return os;
}


}
