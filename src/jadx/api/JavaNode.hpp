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
#ifndef JADX_API_JAVA_NODE_H_
#define JADX_API_JAVA_NODE_H_

#include <jni/jni.hpp>
#include <string>


namespace jni::jadx::api {


template<class T, class TAG, class OBJ_T, class CLASS_T>
class JavaNode {
  public:
  using Tag = TAG;

  using Object_t = OBJ_T;
  using Class_t  = CLASS_T;

  JavaNode(void) :
    env_{nullptr},
    obj_{nullptr}
  {}

  JavaNode(JNIEnv& env, const Object_t& obj) :
    env_{&env},
    obj_{NewLocal(env, obj)}
  {}

  JavaNode(JNIEnv& env, const Object<>& obj) :
    env_{&env},
    obj_{nullptr}
  {
    auto&& casted = Cast<Tag>(this->env(), this->clazz(), obj);
    this->obj_ = NewLocal(env, casted);

  }


  const Class_t& clazz(void) const {
    return Class_t::Singleton(this->env());
  }

  Local<Object_t> get(void) const {
    return NewLocal(this->env(), this->obj_);
  }



  std::string name(void) {
    static auto&& getName = this->clazz().template GetMethod<String()>(this->env(), "getName");

    return Make<std::string>(this->env(), this->obj_.Call(this->env(), getName));
  }

  std::string fullname(void) {
    static auto&& getFullname = this->clazz().template GetMethod<String()>(this->env(), "getFullName");

    return Make<std::string>(this->env(), this->obj_.Call(this->env(), getFullname));
  }

  size_t decompiled_line(void) {
    static auto&& getDecompiledLine = this->clazz().template GetMethod<jint()>(this->env(), "getDecompiledLine");

    return this->obj_.Call(this->env(), getDecompiledLine);
  }

  protected:
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
