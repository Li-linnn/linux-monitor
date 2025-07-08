#pragma once

#include <boost/chrono.hpp>

namespace monitor {
class Utils {
 public:
 /*
  static double SteadyTimeSecond(double t1, double t2){
    double time_second = t1 - t2;
    return time_second;
  }
 */
    static double SteadyTimeSecond(
      const boost::chrono::steady_clock::time_point &t1,
      const boost::chrono::steady_clock::time_point &t2) {
    boost::chrono::duration<double> time_second = t1 - t2;
    return time_second.count();
  }

};
}  // namespace monitor