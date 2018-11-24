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
#ifndef JADX_API_JAVA_PACKAGE_H_
#define JADX_API_JAVA_PACKAGE_H_

#include <jni/jni.hpp>
#include <jadx/api/JavaNode.hpp>
#include <jadx/api/JavaClass.hpp>
#include <string>


namespace jni::jadx::api {

struct JavaPackageTag { static constexpr auto Name() { return "jadx/api/JavaPackage"; } };
class JavaPackage : public JavaNode<JavaPackage, JavaPackageTag, Object<JavaPackageTag>, Class<JavaPackageTag>> {
  public:
  using classes_list_t = std::vector<JavaClass>;

  using Object_t = Object<JavaPackageTag>;
  using Class_t  = Class<JavaPackageTag>;

  JavaPackage(JNIEnv& env, const Object_t& obj);
  JavaPackage(JNIEnv& env, const Object<>& obj);

  classes_list_t classes(void);
};

}
#endif
