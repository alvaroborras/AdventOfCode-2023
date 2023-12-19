#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <chrono>
#include <string>

std::string format_duration(std::chrono::microseconds us);

#endif // TIME_UTILS_H