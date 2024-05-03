#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

#include <iostream>
#include <math.h>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version ;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel >> version;
  }
  return (kernel + " " + version);
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() 
{
  string line;
  string name;
  long value;
  long MemTotal, MemFree;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> name >> value;
      if (name == "MemTotal") {
        MemTotal = value;
      }
      if (name == "MemFree") {
        MemFree = value;
        break;
      }
    }
  }

  return (((float)MemTotal - (float)MemFree) / MemTotal);
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime()
{
  string line;
  float uptime;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);

  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::stringstream linestream(line);
    linestream >> uptime;
  }

  return (long)(uptime);
}

// // TODO: Read and return the number of jiffies for the system
// long LinuxParser::Jiffies() { return 0; }

// // TODO: Read and return the number of active jiffies for a PID
// // REMOVE: [[maybe_unused]] once you define the function
// long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// // TODO: Read and return the number of active jiffies for the system
// long LinuxParser::ActiveJiffies() { return 0; }

// // TODO: Read and return the number of idle jiffies for the system
// long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
/*
  Data present by index of cpuStat
  [1]: user
  [2]: nice
  [3]: system
  [4]: idle
  [5]: iowait
  [6]: irq
  [7]: softirq
  [8]: steal
  [9]: guest
  [10]: guest_nice
*/
vector<string> LinuxParser::CpuUtilization()
{ 
  vector<string> cpuStat;
  std::string line, key, value;
  std::ifstream filestream(kProcDirectory + kStatFilename);

  std::getline(filestream, line);
  std::stringstream linestream(line);
  while (linestream >> value) {
    cpuStat.emplace_back(value);
  }
  if (cpuStat[0] == "cpu") return cpuStat;

  return {};
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses()
{
  string line;
  string name;
  long value;
  std::ifstream filestream(kProcDirectory + kStatFilename);

  while(std::getline(filestream, line)) {
    std::stringstream linestream(line);
    linestream >> name >> value;
    if (name == "processes") {
      return value;
    } 
  }

  return 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses()
{
  string line;
  string name;
  long value;
  std::ifstream filestream(kProcDirectory + kStatFilename);

  while(std::getline(filestream, line)) {
    std::stringstream linestream(line);
    linestream >> name >> value;
    if (name == "procs_running") {
      return value;
    }
  }
  return 0;
}

// Read and return CPU utilization of a process
float LinuxParser::CpuUtilization(int pid)
{ 
  vector<string> ProcessStats;
  std::string line, value;
  float totaltime, elapsedtime;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);

  if (std::getline(filestream, line)) {
    std::stringstream linestream(line);
    while (linestream >> value) {
      ProcessStats.emplace_back(value);
    }

    float uptime = UpTime();
    float utime = stof(ProcessStats[13]);
    float stime = stof(ProcessStats[14]);
    float cutime = stof(ProcessStats[15]);
    float cstime = stof(ProcessStats[16]);
    float starttime = stof(ProcessStats[21]);

    totaltime = utime + stime + cutime + cstime;
    elapsedtime = uptime - (starttime / sysconf(_SC_CLK_TCK));

    return ((totaltime / sysconf(_SC_CLK_TCK)) / elapsedtime);
  }

  return 0.0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid)
{
  string line;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);

  if (std::getline(filestream, line)) {
    return line;
  }

  return string();
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid)
{
  string line;
  string name;
  long value;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);

  while(std::getline(filestream, line)) {
    std::stringstream linestream(line);
    linestream >> name >> value;
    if (name == "VmSize:") {
      return to_string(value / 1024);
    }
  }
  return "0";
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid)
{
  string line;
  string name;
  long value;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);

  while(std::getline(filestream, line)) {
    std::stringstream linestream(line);
    linestream >> name >> value;
    if (name == "Uid:") {
      return to_string(value);
    } 
  }

  return "0";
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid)
{
  string line;
  string name, dummy;
  long value;
  std::ifstream filestream(kPasswordPath);

  while(std::getline(filestream, line)) {
    std::replace(line.begin(), line.end(), ':', ' ');
    std::stringstream linestream(line);

    linestream >> name >> dummy >> value;
    if (to_string(value) == Uid(pid)) {
      return name;
    } 
  }

  return "unknown";
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid)
{
  string line;
  string value;
  const int uptimeIndex = 22;
  float uptime = UpTime();
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);

  if (std::getline(filestream, line)) {
    std::stringstream linestream(line);

    for (int i = 0; i < uptimeIndex; i++) {
      value = "";
      linestream >> value;
    }
  }

  return (uptime - (stol(value) / sysconf(_SC_CLK_TCK)));
}