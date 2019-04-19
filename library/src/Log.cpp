#include "Log.h"

std::ofstream Log::f;
void Log::init() {
  Log::f.open("log");
  if(!Log::f.good()) exit(-1);
  Log:: f << "Logging initialized" << std::endl;

}
void Log::nl() {
  Log::f << std::endl;
}
Log::~Log() {
  Log::f.close();
}
