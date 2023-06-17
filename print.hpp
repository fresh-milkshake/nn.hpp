#ifndef PRINT_HPP
#define PRINT_HPP

#include <iostream>
#include <sstream>
#include <string>

namespace detail {

template <typename T> std::string toString(const T &arg) {
  std::ostringstream oss;
  oss << arg;
  return oss.str();
}

template <> std::string toString<bool>(const bool &arg) {
  return arg ? "true" : "false";
}

std::string format_helper(std::string s) {
  if (s.find("{}") != std::string::npos) {
    std::cerr << "[ERROR: More placeholders than provided values]\n";
  }
  return s;
}

template <typename T, typename... Args>
std::string format_helper(std::string s, T value, Args... args) {
  std::size_t index = s.find("{}");
  if (index == std::string::npos) {
    std::cerr << "[ERROR: More values provided than placeholders]\n";
  } else {
    s.replace(index, 2, toString(value));
  }
  return format_helper(s, args...);
}
} // namespace detail

template <typename... Ts>
std::string format(const std::string &format, const Ts... args) {
  return detail::format_helper(format, args...);
}

template <typename... Ts>
void print(const std::string &format_string, const Ts... args) {
  std::cout << format(format_string, args...);
}

template <typename... Ts>
void println(const std::string &format, const Ts... args) {
  print(format, args...);
  std::cout << std::endl;
}

#endif // PRINT_HPP
