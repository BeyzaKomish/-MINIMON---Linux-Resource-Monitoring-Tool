#ifndef REPORTER_H
#define REPORTER_H
#include "collector.h"


void reportCPUUsage();
void reportMemoryInfo();
void reportDiskInfo();
void reportNetworkInfo();
void reportTopProcess(int n);
void reportConnectionInfo(int pid);
#endif 