#pragma once

#include <string>
#include <unordered_map>

#include <boost/chrono.hpp>

#include "monitor/monitor_inter.h"
#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

//记录软中断次数
namespace monitor {
class CpuSoftIrqMonitor : public MonitorInter {
  struct SoftIrq {
    std::string cpu_name;
    int64_t hi;
    int64_t timer;
    int64_t net_tx;
    int64_t net_rx;
    int64_t block;
    int64_t irq_poll;
    int64_t tasklet;
    int64_t sched;
    int64_t hrtimer;
    int64_t rcu;
    boost::chrono::steady_clock::time_point timepoint;
  };

 public:
  CpuSoftIrqMonitor() {}
  void UpdateOnce(monitor::proto::MonitorInfo* monitor_info);
  void Stop() override {}

 private:
  std::unordered_map<std::string, struct SoftIrq> cpu_softirqs_;
};

}  // namespace monitor

/*
TIMER（定时中断）
NET_TX(网络发送)
NET_RX（网络接收）
SCHED（内核调度）
RCU（RCU 锁）中，网络接收变化最快
*/
