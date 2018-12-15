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
#include <jadx/api/JavaPackage.hpp>

#include <java/util/List.hpp>
#include <fstream>

namespace jni::jadx::api {

JavaPackage::JavaPackage(JNIEnv& env, const Object_t& obj) {
  this->env_ = &env;
  this->obj_ = NewLocal(env, obj);
}

JavaPackage::JavaPackage(JNIEnv& env, const Object<>& obj) {
  this->env_ = &env;
  auto&& casted = Cast<JavaPackageTag>(this->env(), this->clazz(), obj);
  this->obj_ = NewLocal(env, casted);
}

JavaPackage::classes_list_t JavaPackage::classes(void) {
  using List_t = java::util::List<JavaClass>;
  static auto&& getClasses = this->clazz().template GetMethod<Object<List_t::Tag>()>(this->env(), "getClasses");

  auto&& jclasses = this->obj_.Call(this->env(), getClasses);

  List_t jlist{this->env(), jclasses};

  classes_list_t classes;
  classes.reserve(jlist.size());

  for (size_t i = 0; i < jlist.size(); ++i) {
    classes.emplace_back(jlist.at(i));
  }

  return classes;
}


bool JavaPackage::save(const std::string& directory) {
  classes_list_t classes = this->classes();
  std::string directory_normalized = directory;
  if (directory.back() != '/') {
    directory_normalized += '/';
  }
  for (JavaClass& cls : classes) {
    std::string output_path = directory_normalized + cls.name() + ".java";
    std::ofstream output{output_path, std::ios::trunc};
    if (not output) {
      std::cerr << "Can't save '" << cls.fullname() << "' to '" << output_path << "'" << std::endl;
      continue;
    }
    output << cls.getCode();
  }
  return true;
}

}
