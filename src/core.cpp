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
#include "core.hpp"
#include <numeric>
namespace jni {

jadx::api::JadxDecompiler Jadx::load(const std::string& apk_path) {
  jni::jadx::api::JadxArgs jadx_args{this->env()};
  jadx_args.setInputFiles({apk_path});
  jni::jadx::api::JadxDecompiler decompiler{this->env(), jadx_args};
  decompiler.load();
  return decompiler;
}

Jadx::Jadx(void) {

  static constexpr std::initializer_list<const char*> jadx_libraries = {
    "image-viewer-1.2.3.jar",
    "annotations-16.0.2.jar",
    "jadx-cli-0.8.0.jar",
    "logback-classic-1.2.3.jar",
    "jcommander-1.74.jar",
    "slf4j-api-1.7.25.jar",
    "logback-core-1.2.3.jar",
    "jadx-core-0.8.0.jar",
    "jfontchooser-1.0.5.jar",
    "android-5.1.jar",
    "gson-2.8.5.jar",
    "commons-io-2.6.jar",
    "jadx-gui-0.8.0.jar",
    "rxjava2-swing-0.2.16.jar",
    "reactive-streams-1.0.2.jar",
    "dx-1.14.jar",
    "objenesis-2.6.jar",
    "cloning-1.9.10.jar",
    "commons-lang3-3.7.jar",
    "asm-6.2.jar",
    "rxjava-2.1.17.jar",
    "rsyntaxtextarea-2.6.1.jar",
  };
  static const std::string prefix = get_jadx_prefix() + "/jadx/0.8.0/";

  std::string classpath = std::accumulate(
      std::begin(jadx_libraries),
      std::end(jadx_libraries),
      std::string{},
      [] (const std::string& lhs, const char* rhs) {
        return lhs.empty() ? prefix + rhs : lhs + ":" + prefix + rhs;
      });

  std::string classpath_option = "-Djava.class.path=" + classpath;

  JavaVMOption opt[2];
  opt[0].optionString = const_cast<char*>(classpath_option.c_str());

  JavaVMInitArgs args;
  args.version = JNI_VERSION_1_6;
  args.options = opt;
  args.nOptions = 1;
  args.ignoreUnrecognized = JNI_FALSE;

  jsize jvm_count = 0;
  JNI_CreateJavaVM(&(this->jvm_), reinterpret_cast<void**>(&this->env_), &args);

  if (this->jvm_ == nullptr) {
    std::cerr << "[-] Error while creating the JVM" << std::endl;
  }
}

Jadx::~Jadx(void) {
  if (this->jvm_) {
    //this->jvm_->DestroyJavaVM();
  }
}


}
