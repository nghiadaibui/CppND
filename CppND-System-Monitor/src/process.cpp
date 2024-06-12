#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) {
  if (pid > 0) {
    pid_ = pid;
    cpuUsage_ = CpuUtilization();
    // fprintf(stdout, "%d cpu %0.2f\r\n", pid, cpuUsage_);
  }
}
// TODO: Return this process's ID
int Process::Pid() {
  return pid_;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
  return LinuxParser::CpuUtilization(pid_);
}

// TODO: Return the command that generated this process
string Process::Command() {
  return LinuxParser::Command(pid_);
}

// TODO: Return this process's memory utilization
string Process::Ram() {
  return LinuxParser::Ram(pid_);
}

// TODO: Return the user (name) that generated this process
string Process::User() {
  return LinuxParser::User(pid_);
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
  return LinuxParser::UpTime(pid_);
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& another) const {
  return another.cpuUsage_ < cpuUsage_; }