#include "time_utils.h"

std::string format_duration(std::chrono::microseconds us) {
  using namespace std::chrono;
  auto ms = duration_cast<milliseconds>(us);
  us -= duration_cast<microseconds>(ms);
  auto secs = duration_cast<seconds>(ms);
  ms -= duration_cast<milliseconds>(secs);
  if (secs.count() > 0)
    return std::to_string(secs.count()) + "s " + std::to_string(ms.count()) + "ms " + std::to_string(us.count()) + "us";
  else if (ms.count() > 0)
    return std::to_string(ms.count()) + "ms " + std::to_string(us.count()) + "us";
  else
    return std::to_string(us.count()) + "us";
}