#include "monitor/cpu_softirq_monitor.h"

#include "utils/read_file.h"
#include "utils/utils.h"
#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

namespace monitor {
void CpuSoftIrqMonitor::UpdateOnce(monitor::proto::MonitorInfo* monitor_info) {
  ReadFile softirqs_file(std::string("/proc/softirqs"));
  std::vector<std::string> one_softirq;
  std::vector<std::vector<std::string>> softirq;
  while (softirqs_file.ReadLine(&one_softirq)) {
    softirq.push_back(one_softirq);
    one_softirq.clear();
  }

  for (int i = 0; i < softirq[0].size() - 1; i++) {
    std::string name = softirq[0][i];
    struct SoftIrq info;
    info.cpu_name = name;
    info.hi = std::stoull(softirq[1][i + 1]);
    info.timer = std::stoull(softirq[2][i + 1]);
    info.net_tx = std::stoull(softirq[3][i + 1]);
    info.net_rx = std::stoull(softirq[4][i + 1]);
    info.block = std::stoull(softirq[5][i + 1]);
    info.irq_poll = std::stoull(softirq[6][i + 1]);
    info.tasklet = std::stoull(softirq[7][i + 1]);
    info.sched = std::stoull(softirq[8][i + 1]);
    info.hrtimer = std::stoull(softirq[9][i + 1]);
    info.rcu = std::stoull(softirq[10][i + 1]);
    info.timepoint = boost::chrono::steady_clock::now();//采样时间
    // stoull：无符号，stoll：有符号

    auto iter = cpu_softirqs_.find(name);
    if (iter != cpu_softirqs_.end()) {
      //struct SoftIrq& old = (*iter).second;  
      struct SoftIrq old = std::move(iter->second);// move：从iter->second移动到old，避免多余开销
      double period = Utils::SteadyTimeSecond(info.timepoint, old.timepoint);//两次采样间隔时间
      auto one_softirq_msg = monitor_info->add_soft_irq();
      one_softirq_msg->set_cpu(info.cpu_name);
      one_softirq_msg->set_hi((info.hi - old.hi) / period);//单位时间内hi中断次数
      one_softirq_msg->set_timer((info.timer - old.timer) / period);
      one_softirq_msg->set_net_tx((info.net_tx - old.net_tx) / period);
      one_softirq_msg->set_net_rx((info.net_rx - old.net_rx) / period);
      one_softirq_msg->set_block((info.block - old.block) / period);
      one_softirq_msg->set_irq_poll((info.irq_poll - old.irq_poll) / period);
      one_softirq_msg->set_tasklet((info.tasklet - old.tasklet) / period);
      one_softirq_msg->set_sched((info.sched - old.sched) / period);
      one_softirq_msg->set_hrtimer((info.hrtimer - old.hrtimer) / period);
      one_softirq_msg->set_rcu((info.rcu - old.rcu) / period);
    }
    cpu_softirqs_[name] = info;
  }
  return;
}

}  // namespace monitor