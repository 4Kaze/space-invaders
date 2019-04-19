#include "Log.h"
#include <stdexcept>

Log::Log() {
  file.open("log");
  if(!file.good()) {
    throw std::logic_error("Nie można utworzyć pliku do logowania.");
  }
  file << "Logging initialized" << std::endl;

}
void Log::nl() {
  file << std::endl;
}
Log& Log::get() {
  static Log singleton;
  return singleton;
}

Log::~Log() {
  file.close();
}
