/*
 * Copyright (C) 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "linkerconfig/namespacebuilder.h"

using android::linkerconfig::modules::Namespace;

namespace android {
namespace linkerconfig {
namespace contents {
Namespace BuildPostInstallNamespace([[maybe_unused]] const Context& ctx) {
  Namespace ns("default", /*is_isolated=*/false,
               /*is_visible=*/false);
  ns.AddSearchPath("/system/${LIB}");
  ns.AddSearchPath(Var("SYSTEM_EXT") + "/${LIB}");
  ns.AddSearchPath(Var("PRODUCT") + "/${LIB}");

  return ns;
}
}  // namespace contents
}  // namespace linkerconfig
}  // namespace android