#pragma once
#include <iostream>
#include <string>
#include <vector>

template <typename T>
class Registry {
  std::vector<T> items;

 public:
  void add(const T& item) { items.push_back(item); }

  void printAll() {
    for (const auto& item : items) {
      std::cout << item << std::endl;
    }
  }
};

template <>
class Registry<std::string> {
  std::vector<std::string> items;

 public:
  void add(const std::string& item) { items.push_back("[LOG] " + item); }
  void printAll() {
    for (const auto& s : items) {
      std::cout << s << std::endl;
    }
  }
};