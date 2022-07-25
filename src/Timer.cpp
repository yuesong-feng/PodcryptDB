#include "Timer.h"
Timer::Timer(string &&str) : scope_(std::move(str)), start_(0), last_(0) {}

void Timer::time() {
  clock_t now = clock();
  printf("time from last checkpoint: %lu us\n", now - last_);
  last_ = now;
}

Timer::~Timer() {
  clock_t end = clock();
  printf("scope: %s, time: %lu us\n", scope_.c_str(), end - start_);
}