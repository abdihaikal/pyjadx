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
#ifndef JAVA_UTIL_LIST_H_
#define JAVA_UTIL_LIST_H_

#include <jni/jni.hpp>
#include <string>

namespace jni::java::util {

template<class U>
class List {
  public:
  struct Tag { static constexpr auto Name() { return "java/util/List"; } };

  using Object_t = Object<Tag>;
  using Class_t  = Class<Tag>;

  List(JNIEnv& env, const Object_t& obj) :
    env_{&env}
  {
    this->obj_ = NewLocal(this->env(), obj);
  }

  static const Class_t& from_env(JNIEnv& env) {
    return Class_t::Singleton(env);
  }

  const Class_t& clazz(void) const {
    return Class_t::Singleton(this->env());
  }


  size_t size(void) const {
    static auto&& size = this->clazz().template GetMethod<jint()>(this->env(), "size");
    return this->obj_.Call(this->env(), size);
  }


  U at(size_t idx) {
    static auto&& get = this->clazz().template GetMethod<Object<>(jint)>(this->env(), "get");
    Local<Object<>> jobj = this->obj_.Call(this->env(), get, static_cast<jint>(idx));
    U element{this->env(), jobj};
    return element;
  }

  Local<Object_t> get(void) {
    return NewLocal(this->env(), this->obj_);
  }

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
