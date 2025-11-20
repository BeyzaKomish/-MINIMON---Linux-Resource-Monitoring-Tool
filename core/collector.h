#ifndef COLLECTOR_H
#define COLLECTOR_H

#include <string>
#include <vector>

using namespace std;

struct ProcessInfo
{
   int pid;
   string name;
   long utime;
    long stime;
    long ramUsageGB;
    string status;

    long totalTime() const {
        return utime + stime;
    }
};

vector<ProcessInfo> collectProcesses(int n);

struct CPUUsage{
    float user;
    float system;
    float idle;
};

CPUUsage getCPUUsage();

struct MemoryInfo{
    long totalMem;
    long freeMem;
    long availableMem;
    long swapTotal;
    long swapFree;
};

MemoryInfo getMemoryInfo();

struct DiskInfo{ 
    string device;
    long reads;
    long writes;
    unsigned long totalSpace;
    unsigned long usedSpace;
    unsigned long freeSpace;
};

DiskInfo getDiskInfo();

struct NetworkInfo
{
    string device;
    long rxBytes;
    long txBytes;
};


NetworkInfo getNetworkInfo();

struct ConnectionInfo
{
    string protocol;
    string localAddress;
    string remoteAddress;
    string state;
    int pid;

};
 vector<ConnectionInfo> getConnectionInfo(int pid);
string getProcessCmdLine(int pid);
string getProcessStatus(int pid);
int getSystemConnectionCount();
 long getProcessRAMUsage(int pid);
  float getProcessCPUUsage(int pid);



#endif