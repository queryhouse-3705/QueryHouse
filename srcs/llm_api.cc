#include "llm_api.h"

#include <pybind11/embed.h>
#include <pybind11/stl.h>

#include <string>

#ifdef LOG_LLM
#include <chrono>
#include <fstream>
#include <iostream>
#endif

namespace py = pybind11;

std::string call_llm(const std::string &input_query) {
#ifdef LOG_LLM
    std::ofstream llm_log("/tmp/llm.Fuzzlog", std::ios::app);
#endif

  try {
#ifdef LOG_LLM
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    llm_log << "Invoked at: " << std::ctime(&now_time_t);
#endif

    // $HOME environment variable
    const char *home_dir = std::getenv("HOME");
    if (home_dir == nullptr) {
      //std::cerr << "Environment variable HOME is not set.\n";
      return "";
    }

    // Python module path
    std::string module_path = std::string(home_dir) + "/QueryHouse/srcs";
    py::module sys = py::module::import("sys");
    sys.attr("path").attr("append")(module_path);

    // Load Python module
    py::module llm_module = py::module::import("llm_api");
    py::object query_chatgpt = llm_module.attr("query_chatgpt");

    // LLM invocation
    py::object result = query_chatgpt(input_query);
    std::string llm_response = result.cast<std::string>();

#ifdef LOG_LLM
    llm_log << "Response: " << llm_response << "\n\n";
    llm_log.close();
#endif

    return llm_response;
  } catch (const py::error_already_set &e) {
#ifdef LOG_LLM
    llm_log << "LLM failed (Error: " << e.what() << ")\n\n";
    llm_log.close();
#endif
    return "";
  }
}