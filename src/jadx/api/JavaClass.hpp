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
#ifndef JADX_API_JAVA_CLASS_H_
#define JADX_API_JAVA_CLASS_H_

#include <jni/jni.hpp>
#include <jadx/api/JavaNode.hpp>
#include <jadx/api/JavaMethod.hpp>
#include <string>


namespace jni::jadx::api {

struct JavaClassTag { static constexpr auto Name() { return "jadx/api/JavaClass"; } };
class JavaClass : public JavaNode<JavaClass, JavaClassTag, Object<JavaClassTag>, Class<JavaClassTag>> {
  public:
  using methods_list_t = std::vector<JavaMethod>;

  using Object_t = Object<JavaClassTag>;
  using Class_t  = Class<JavaClassTag>;

  JavaClass(JNIEnv& env, const Object_t& obj);
  JavaClass(JNIEnv& env, const Object<>& obj);

  std::string getCode(void);

  bool save(const std::string& path);

  methods_list_t methods(void);
};

}
#endif
