#include "processor.h"
#include "linux_parser.h"
#include <vector>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization()
{
  std::vector<std::string> cpuStat = LinuxParser::CpuUtilization();
  
  float Idle = std::stof(cpuStat[IDLE]) + std::stof(cpuStat[IOWAIT]);
  float NonIdle = std::stof(cpuStat[USER]) + std::stof(cpuStat[NICE])
                    + std::stof(cpuStat[SYSTEM]) + std::stof(cpuStat[IRQ])
                    + std::stof(cpuStat[SOFTIRQ]) + std::stof(cpuStat[STEAL]);
  float Total = Idle + NonIdle;

  return ((Total - Idle) / Total);
}