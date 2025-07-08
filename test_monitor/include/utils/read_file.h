#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace monitor {
class ReadFile {
 public:
  explicit ReadFile(const std::string& name) : ifs_(name) {}//explicit：禁止隐式转换参数类型
  ~ReadFile() { ifs_.close(); }

  bool ReadLine(std::vector<std::string>* args);
  /*
  static std::vector<std::string> GetStatsLines(const std::string& stat_file,
                                                const int line_count) {
    std::vector<std::string> stats_lines;
    std::ifstream buffer(stat_file);
    for (int line_num = 0; line_num < line_count; ++line_num) {
      std::string line;
      std::getline(buffer, line);
      if (line.empty()) {
        break;
      }
      stats_lines.push_back(line);
    }
    return stats_lines;
  }
  */

 private:
 // 文件流
  std::ifstream ifs_;
};
}  // namespace monitor
