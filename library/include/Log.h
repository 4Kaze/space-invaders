#pragma once
#include <iostream>
#include <fstream>

class Log {
public:
  std::ofstream file;
  void nl();

  template<typename T>
  Log& operator<< (const T& data) {
      file << data;
      return *this;
  }

  static Log& get();

private:
  Log();
  ~Log();
};
