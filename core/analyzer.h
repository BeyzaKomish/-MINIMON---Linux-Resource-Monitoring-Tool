#ifndef ANALYZER_H
#define ANALYZER_H
#include <iostream>
#include <vector>
#include "collector.h"

CPUUsage calcultePrevandNewUsage(const CPUUsage& oldUsage,const CPUUsage& newUsage);

bool isCPUUsageIncreased(const CPUUsage& usage, float threshold = 80.0f);

vector<ProcessInfo> sortProcess(const vector<ProcessInfo>& processes);


#endif