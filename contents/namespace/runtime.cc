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

// Currently, the runtime namespace is only to isolate
// libc_malloc_hooks/debug.so in the Runtime APEX. libc/l/d are loaded in the
// default namespace.

#include "linkerconfig/namespacebuilder.h"

using android::linkerconfig::modules::AsanPath;
using android::linkerconfig::modules::Namespace;

namespace android {
namespace linkerconfig {
namespace contents {

Namespace BuildRuntimeNamespace([[maybe_unused]] const Context& ctx) {
  Namespace ns("runtime",
               /*is_isolated=*/true,
               /*is_visible=*/true);

  ns.AddSearchPath("/apex/com.android.runtime/${LIB}", AsanPath::SAME_PATH);
  ns.AddPermittedPath("/system/${LIB}");

  return ns;
}

}  // namespace contents
}  // namespace linkerconfig
}  // namespace android
