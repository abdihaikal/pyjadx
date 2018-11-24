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

#ifndef JAVA_UTIL_ARRAYLIST_H_
#define JAVA_UTIL_ARRAYLIST_H_

#include <jni/jni.hpp>
#include <string>

namespace jni::java::util {

template<class U>
class ArrayList {
  public:
  struct Tag { static constexpr auto Name() { return "java/util/ArrayList"; } };

  using Object_t = Object<Tag>;
  using Class_t  = Class<Tag>;

  const Class_t& clazz(void) const {
    return Class_t::Singleton(this->env());
  }

  ArrayList(JNIEnv& env, const std::vector<std::string>& list);

  size_t size(void) const;

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

template<class U>
ArrayList<U>::ArrayList(JNIEnv& env, const std::vector<std::string>& list) :
  env_{&env}
{

  static auto&& ctor = this->clazz().template GetConstructor<jint>(this->env());
  static auto&& add  = this->clazz().template GetMethod<jboolean(Object<>)>(this->env(), "add");

  this->obj_         = this->clazz().New(this->env(), ctor, static_cast<jint>(list.size()));

  for (const std::string& e : list) {
  //  //Local<String> element = Make<String>(env, str);
    U jelement{this->env(), e};
    this->obj_.Call(this->env(), add, jelement.get());
  }
}


template<class U>
size_t ArrayList<U>::size(void) const {
  static auto&& size = this->clazz().template GetMethod<jint()>(this->env(), "size");
  return this->obj_.Call(this->env(), size);
}




}
#endif
