#pragma once
#include <iostream>
#include <fstream>

class Log {
public:
  ~Log();

  static std::ofstream f;
  static void init();
  static void nl();
  /*template<typename T>
  Log& operator<< (const T& data)
  {
      Log::f << data;
      return *this;
  }*/


private:
  Log();
};
