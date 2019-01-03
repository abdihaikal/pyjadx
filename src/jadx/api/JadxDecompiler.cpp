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
#include <jadx/api/JadxDecompiler.hpp>
#include <java/util/List.hpp>

#include <algorithm>

namespace jni::jadx::api {

JadxDecompiler::JadxDecompiler(JNIEnv& env, JadxArgs& args) :
  env_{&env}
{
  static auto&& ctor = this->clazz().GetConstructor<Object<JadxArgs::Tag>>(this->env());
  this->obj_         = this->clazz().New(this->env(), ctor, args.get());
}

const JadxDecompiler::Class_t& JadxDecompiler::clazz(void) const {
  return Class_t::Singleton(this->env());
}

Local<JadxDecompiler::Object_t> JadxDecompiler::get(void) {
  return NewLocal(this->env(), this->obj_);
}

void JadxDecompiler::load(void) {
  static auto&& load = this->clazz().template GetMethod<void()>(this->env(), "load");
  return this->obj_.Call(this->env(), load);
}


JadxDecompiler::classes_list_t JadxDecompiler::classes(void) {
  using List_t = java::util::List<JavaClass>;
  static auto&& getClasses = this->clazz().template GetMethod<Object<List_t::Tag>()>(this->env(), "getClasses");

  auto&& jclasses = this->obj_.Call(this->env(), getClasses);

  List_t jlist{this->env(), jclasses};

  JadxDecompiler::classes_list_t classes;
  classes.reserve(jlist.size());

  for (size_t i = 0; i < jlist.size(); ++i) {
    classes.emplace_back(jlist.at(i));
  }

  return classes;
}


JadxDecompiler::packages_list_t JadxDecompiler::packages(void) {
  using List_t = java::util::List<JavaPackage>;
  static auto&& getPackages = this->clazz().template GetMethod<Object<List_t::Tag>()>(this->env(), "getPackages");

  auto&& jpackages = this->obj_.Call(this->env(), getPackages);

  List_t jlist{this->env(), jpackages};

  packages_list_t packages;
  packages.reserve(jlist.size());

  for (size_t i = 0; i < jlist.size(); ++i) {
    packages.emplace_back(jlist.at(i));
  }

  return packages;
}


bool JadxDecompiler::has_class(const std::string& name) {
  classes_list_t classes = this->classes();

  auto&& it = std::find_if(
      std::begin(classes),
      std::end(classes),
      [&name] (JavaClass& cls) {
        return cls.name() == name or cls.fullname() == name;
      });
  return it != std::end(classes);
}

bool JadxDecompiler::has_package(const std::string& name) {
  packages_list_t pkg = this->packages();

  auto&& it = std::find_if(
      std::begin(pkg),
      std::end(pkg),
      [&name] (JavaPackage& p) {
        return p.name() == name or p.fullname() == name;
      });
  return it != std::end(pkg);
}


std::string JadxDecompiler::getVersion(void) const {
  static auto&& getVersion = this->clazz().template GetMethod<String()>(this->env(), "getVersion");

  return Make<std::string>(this->env(), this->obj_.Call(this->env(), getVersion));
}


JavaClass JadxDecompiler::get_class(const std::string& name) {
  classes_list_t classes = this->classes();

  auto&& it = std::find_if(
      std::begin(classes),
      std::end(classes),
      [&name] (JavaClass& cls) {
        return cls.name() == name or cls.fullname() == name;
      });

  if (it == std::end(classes)) {
    throw std::runtime_error("Not found!");
  }
  return std::move(*it);
}

JavaPackage JadxDecompiler::get_package(const std::string& name) {
  packages_list_t pkg = this->packages();

  auto&& it = std::find_if(
      std::begin(pkg),
      std::end(pkg),
      [&name] (JavaPackage& p) {
        return p.name() == name or p.fullname() == name;
      });

  if (it == std::end(pkg)) {
    throw std::runtime_error("Not found!");
  }
  return std::move(*it);
}


}
