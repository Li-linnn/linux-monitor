#include <iostream>
#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>
#include "rpc_manager.h"

// 监听端口
constexpr char kServerPortInfo[] = "0.0.0.0:50051";

void InitServer() {
  grpc::ServerBuilder builder;
  builder.AddListeningPort(kServerPortInfo, grpc::InsecureServerCredentials());

  // 创建服务器
  monitor::GrpcManagerImpl grpc_server; 
  // 注册服务
  builder.RegisterService(&grpc_server);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  server->Wait();

  return;
}

int main() {
  InitServer();
  return 0;
}