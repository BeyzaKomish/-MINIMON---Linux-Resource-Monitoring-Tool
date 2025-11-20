//filtering and ordering
#include "analyzer.h"
#include "collector.h"

CPUUsage calculatePrevandNewUsage(const CPUUsage& oldUsage, const CPUUsage& newUsage) {
    CPUUsage usage;
    usage.user = newUsage.user - oldUsage.user;
    usage.system = newUsage.system - oldUsage.system;
    usage.idle = newUsage.idle - oldUsage.idle;
    return usage;
}

bool isCPUUsageIncreased(const CPUUsage& usage, float threshold ) {
    return (usage.user + usage.system) >  threshold;
}