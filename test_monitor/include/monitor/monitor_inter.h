#pragma once

#include <string>

#include "monitor/monitor_inter.h"
#include "monitor_info.grpc.pb.h"
// 抽象基类
namespace monitor {
class MonitorInter {
 public:
  MonitorInter() {}
  virtual ~MonitorInter() {}

  // 纯虚函数（接口方法），定义数据采集 及 停止监测的接口，各子类重写基类虚函数
  virtual void UpdateOnce(monitor::proto::MonitorInfo* monitor_info) = 0;
  virtual void Stop() = 0;
};
}  // namespace monitor