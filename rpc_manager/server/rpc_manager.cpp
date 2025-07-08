#include "rpc_manager.h"
#include <iostream>

namespace monitor {
GrpcManagerImpl::GrpcManagerImpl() {}

GrpcManagerImpl::~GrpcManagerImpl() {}
::grpc::Status GrpcManagerImpl::SetMonitorInfo(
    ::grpc::ServerContext* context,
    const ::monitor::proto::MonitorInfo* request,
    ::google::protobuf::Empty* response) {
  monitor_infos_.Clear();
  monitor_infos_ = *request;
  std::cout << "jinru" << request->soft_irq_size() << std::endl;
  //   for (int i = 0; i < request->soft_irq_size(); i++) {
  //     std::cout << request->soft_irq(i).cpu() << " " <<
  //     request->soft_irq(i).hi() << std::endl;
  //   }
  return grpc::Status::OK;
}
::grpc::Status GrpcManagerImpl::GetMonitorInfo(
    ::grpc::ServerContext* context, const ::google::protobuf::Empty* request,
    ::monitor::proto::MonitorInfo* response) {
  //   for (int i = 0; i < monitor_infos_.soft_irq_size(); i++) {
  //     std::cout << monitor_infos_.soft_irq(i).cpu() << " "
  //               << monitor_infos_.soft_irq(i).hi() << " "
  //               << monitor_infos_.soft_irq(i).timer() << " "
  //               << monitor_infos_.soft_irq(i).net_tx() << " "
  //               << monitor_infos_.soft_irq(i).net_rx() << " "
  //               << monitor_infos_.soft_irq(i).block() << " "
  //               << monitor_infos_.soft_irq(i).irq_poll() << std::endl;
  //   }
  *response = monitor_infos_;
  return grpc::Status::OK;
}

}  // namespace monitor
