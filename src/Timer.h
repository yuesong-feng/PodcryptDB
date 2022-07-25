#pragma once
#include <string>
using std::string;

class Timer {
 private:
  string scope_;
  clock_t start_;
  clock_t last_;

 public:
  Timer() = delete;
  Timer(string &&str);
  ~Timer();
  void time();
};

