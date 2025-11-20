#include <iostream>
#include <string>
#include <cstring>
#include "../core/collector.h"
#include "../core/reporter.h"
#include "../core/analyzer.h"
#include "cli.h"

using namespace std;

void userInput(int argc, char *argv[]) {

     if (argc < 2) {
        cerr << "Usage: minimon [cpu|mem|disk|net|TOP%]" << endl;
        return;
    }

if (strcmp(argv[1], "cpu") == 0) {
    getCPUUsage();
    reportCPUUsage();
} else if (strcmp(argv[1], "mem") == 0) {
    getMemoryInfo();
    reportMemoryInfo();
} else if (strcmp(argv[1], "disk") == 0) {
    getDiskInfo();
    reportDiskInfo();
} else if (strcmp(argv[1], "net") == 0) {
    getNetworkInfo();
    reportNetworkInfo();
}else if (strcmp(argv[1], "top") == 0) {

    int processNum = atoi(argv[2]);
    collectProcesses(processNum);
    reportTopProcess(processNum);
}else if(strcmp(argv[1], "conn") == 0) {
    if (argc < 3) {
        cerr << "Usage: minimon conn [PID]" << endl;
        return;
    }
    int pid = atoi(argv[2]);
    reportConnectionInfo(pid);
}else if(strcmp(argv[1], "check") == 0){
        int pid = atoi(argv[2]);
        getProcessCPUUsage(pid);

}
else{
    cerr << "Invalid argument. Use 'cpu', 'mem', 'disk', 'net', or 'top **','check **'." << endl;
   
}

}