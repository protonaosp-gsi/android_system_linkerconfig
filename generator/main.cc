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

#include <getopt.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#include "linkerconfig/baseconfig.h"
#include "linkerconfig/variableloader.h"

namespace {
const static struct option program_options[] = {
    {"target", required_argument, 0, 't'},
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}};

struct ProgramArgs {
  std::string target_file;
};

[[noreturn]] void PrintUsage(int status = EXIT_SUCCESS) {
  std::cerr << "Usage : linkerconfig [--target <target_file>] [--help]"
            << std::endl;
  exit(status);
}

bool ParseArgs(int argc, char* argv[], ProgramArgs* args) {
  int parse_result;
  while ((parse_result =
              getopt_long(argc, argv, "th:", program_options, NULL)) != -1) {
    switch (parse_result) {
      case 't':
        args->target_file = optarg;
        break;
      case 'h':
        PrintUsage();
      default:
        return false;
    }
  }

  if (optind < argc) {
    return false;
  }

  return true;
}

android::linkerconfig::modules::Configuration GetConfiguration() {
  // TODO : Use legacy if needed

  // TODO : Use vndk lite if needed

  // TODO : Use recovery if needed

  // Use base configuration in default
  return android::linkerconfig::contents::CreateBaseConfiguration();
}
}  // namespace

int main(int argc, char* argv[]) {
  ProgramArgs args;

  if (!ParseArgs(argc, argv, &args)) {
    PrintUsage(EXIT_FAILURE);
  }

  std::ostream* out = &std::cout;
  std::ofstream file_out;

  if (args.target_file != "") {
    file_out.open(args.target_file);
    if (file_out.fail()) {
      std::cerr << "Failed to open file " << args.target_file << " : "
                << std::strerror(errno) << std::endl;
      return EXIT_FAILURE;
    }
    out = &file_out;
  }

  android::linkerconfig::generator::LoadVariable();
  auto config = GetConfiguration();
  android::linkerconfig::modules::ConfigWriter config_writer;

  config.WriteConfig(config_writer);
  *out << config_writer.ToString();
  if (!out->good()) {
    std::cerr << "Failed to write content to " << args.target_file << " : "
              << std::strerror(errno) << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}