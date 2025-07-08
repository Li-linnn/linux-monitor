#include "monitor/cpu_load_monitor.h"

#include "utils/read_file.h"

#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

namespace monitor {
void CpuLoadMonitor::UpdateOnce(monitor::proto::MonitorInfo* monitor_info) {
  ReadFile cpu_load_file(std::string("/proc/loadavg"));
  std::vector<std::string> cpu_load;
  cpu_load_file.ReadLine(&cpu_load);
  load_avg_1_ = std::stof(cpu_load[0]);// stof: string to float
  load_avg_3_ = std::stof(cpu_load[1]);
  load_avg_15_ = std::stof(cpu_load[2]);

  auto cpu_load_msg = monitor_info->mutable_cpu_load();
  cpu_load_msg->set_load_avg_1(load_avg_1_);
  cpu_load_msg->set_load_avg_3(load_avg_3_);
  cpu_load_msg->set_load_avg_15(load_avg_15_);

  return;
}

}  // namespace monitor

/*
/proc/loadavg 文件存储：
          0.75 0.50 0.25 1/100 12345
          |     |     |    |     |---- 最近创建的进程 PID
          |     |     |    |---------- 当前运行进程数/总进程数
          |     |--------------------- 15 分钟平均负载
          |--------------------------- 1 分钟和 5 分钟平均负载
ReadLine 方法：
    cpu_load = {"0.75", "0.50", "0.25", "1/100", "12345"};

auto cpu_load_msg = monitor_info->mutable_cpu_load();
    第一次调用 mutable_cpu_load 时为字段 cpu_load 分配内存，后续再调用 
    mutable_cpu_load 直接返回第一次创建的字段的指针。
*/