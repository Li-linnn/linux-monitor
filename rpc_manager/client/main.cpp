#pragma once

#include <string>
#include "rpc_client.h"
#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

int main(int argc, char* argv[]) {
  // Setup request

  monitor::proto::MonitorInfo monitor_info;

  auto soft_irq = monitor_info.add_soft_irq();
  soft_irq->set_cpu("cpu1");
  auto soft_irq2 = monitor_info.add_soft_irq();
  soft_irq2->set_cpu("cpu2");
  
  //构造 rpc客户端
  monitor::RpcClient rpc_client;
  rpc_client.SetMonitorInfo(monitor_info);
  //rpc服务端：暴露远程接口等待调用，客户端：调用远程接口
  return 0;
}