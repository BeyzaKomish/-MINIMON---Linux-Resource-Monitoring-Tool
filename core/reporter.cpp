//json - cvs reporting
#include "reporter.h"
#include <iostream>
#include "collector.h"
#include <fstream>
#include "analyzer.h"

using namespace std;

void reportCPUUsage()
{
    CPUUsage usage = getCPUUsage();
    cout << "CPU Usage:\n";
    cout << "  - User: " << usage.user << "%\n";
    cout << "  - System: " << usage.system << "%\n";
    cout << "  - Idle: " << usage.idle << "%\n";

    ofstream jsonFile("jsonFiles/cpu_usage.json");
    if(jsonFile.is_open()) {
        jsonFile << "{\n";
        jsonFile << "  \"CPU Usage\": {\n";
        jsonFile << "    \"User\": " << usage.user << ",\n";
        jsonFile << "    \"System\": " << usage.system << ",\n";
        jsonFile << "    \"Idle\": " << usage.idle << "\n";
        jsonFile << "  }\n";
        jsonFile << "}\n";
        jsonFile.close();
    } else {
        cerr << "Unable to open file for writing CPU usage report." << endl;
    }

    ofstream csvFile("csvFiles/cpu_usage.csv");
    if(csvFile.is_open()) {
        csvFile << "CPU Usage,User,System,Idle\n";
        csvFile << "CPU Usage," << usage.user << "," << usage.system << "," << usage.idle << "\n";  
        csvFile.close();
    }

};

void reportMemoryInfo()
{

    
    MemoryInfo memInfo = getMemoryInfo();
    cout << "Memory Info:\n";
    cout << "  - Total Memory: " << memInfo.totalMem / (1024.0 * 1024.0)<< " GB\n";            
    cout << "  - Free Memory: " << memInfo.freeMem / (1024.0 * 1024.0) << " GB\n";
    cout << "  - Available Memory: " << memInfo.availableMem /(1024.0 * 1024.0)<< " GB\n";
    cout << "  - Swap Total: "<< memInfo.swapTotal / 1024<<" MB"<<endl;
    cout << "  - Swap Free: "<<memInfo.swapFree / 1024<<" MB"<<endl;

    ofstream memJsonFile("jsonFiles/memory_info.json");
    if(memJsonFile.is_open()) {
        memJsonFile << "{\n";
        memJsonFile << "  \"Memory Info\": {\n";
        memJsonFile << "    \"Total Memory\": " << memInfo.totalMem / (1024.0 * 1024.0) << ",\n";
        memJsonFile << "    \"Free Memory\": " << memInfo.freeMem /(1024.0 * 1024.0)<< ",\n";
        memJsonFile << "    \"Available Memory\": " << memInfo.availableMem /(1024.0 * 1024.0)<< ",\n";
        memJsonFile << "    \"Swap Total\": " <<"\""<<memInfo.swapTotal / 1024 << " MB\",\n";
        memJsonFile << "    \"Swap Free\": " <<"\""<< memInfo.swapFree / 1024 << " MB\"\n";
        memJsonFile << "  }\n";
        memJsonFile << "}\n";
        memJsonFile.close();
    } else {    
        cerr << "Unable to open file for writing Memory info report." << endl;
    }

    ofstream memCsvFile("csvFiles/memory_info.csv");
    if(memCsvFile.is_open()) {
        memCsvFile << "Memory Info,Total Memory,Free Memory,Available Memory,Swap Total,Swap Free\n";
        memCsvFile << "Memory Info," << memInfo.totalMem /(1024.0 * 1024.0)<< "GB," << memInfo.freeMem /(1024.0 * 1024.0)<< "GB," << memInfo.availableMem / (1024.0 * 1024.0) << "GB,"<<memInfo.swapTotal<<"MB,"<<memInfo.swapFree<<" MB"<<"\n";  
        memCsvFile.close();
    } else {
        cerr << "Unable to open file for writing Memory info report." << endl;
    }
};

void reportDiskInfo()
{
    DiskInfo diskInfo = getDiskInfo();
    cout << "Disk Info:\n";
    cout << "  - Device: " << diskInfo.device << "\n";
    cout << "  - Reads: " << diskInfo.reads << "\n";
    cout << "  - Writes: " << diskInfo.writes << "\n";
    cout << "  - Total Space: " << diskInfo.totalSpace / (1024.0 * 1024 * 1024) << " GB\n";
    cout << "  - Used Space: " << diskInfo.usedSpace / (1024.0 * 1024 * 1024) << " GB\n";
    cout << "  - Free Space: " << diskInfo.freeSpace / (1024.0 * 1024 * 1024) << " GB\n";

    ofstream diskJsonFile("jsonFiles/disk_info.json");
    if(diskJsonFile.is_open()) {
        diskJsonFile << "{\n";
        diskJsonFile << "  \"Disk Info\": {\n";
        diskJsonFile << "    \"Device\": \"" << diskInfo.device << "\",\n";
        diskJsonFile << "    \"Reads\": " << diskInfo.reads << ",\n";
        diskJsonFile << "    \"Writes\": " << diskInfo.writes << "\n";
        diskJsonFile << "    \"Total Space\": " << diskInfo.totalSpace / (1024.0 * 1024 * 1024) << ",\n";
        diskJsonFile << "    \"Used Space\": " << diskInfo.usedSpace /(1024.0 * 1024 * 1024) << ",\n";
        diskJsonFile << "    \"Free Space\": " << diskInfo.freeSpace /(1024.0 * 1024 * 1024)<< "\n";
        diskJsonFile << "  }\n";
        diskJsonFile << "}\n";
        diskJsonFile.close();
    } else {
        cerr << "Unable to open file for writing Disk info report." << endl;
    }
    ofstream diskCsvFile("csvFiles/disk_info.csv");
    if(diskCsvFile.is_open()) {
        diskCsvFile << "Disk Info,Device,Reads,Writes,Total Space,Used Space,Free Space\n";
        diskCsvFile << "Disk Info," << diskInfo.device << "," << diskInfo.reads << "," << diskInfo.writes <<","<<diskInfo.totalSpace / (1024.0 * 1024 * 1024)<<","<<diskInfo.usedSpace / (1024.0 * 1024 * 1024)<<","<<diskInfo.freeSpace / (1024.0 * 1024 * 1024)<< "\n";  
        diskCsvFile.close();
    } else {
        cerr << "Unable to open file for writing Disk info report." << endl;
    }
}

void reportNetworkInfo()
{
    NetworkInfo netInfo = getNetworkInfo();
    cout << "Network Info:\n";
    cout << "  - Device: " << netInfo.device << "\n";
    cout << "  - RX Bytes: " << netInfo.rxBytes << "\n";
    cout << "  - TX Bytes: " << netInfo.txBytes << "\n";
    cout << "  - System Count: " << getSystemConnectionCount() << "\n";

    ofstream networkJsonFile("jsonFiles/network_info.json");
    if(networkJsonFile.is_open()) {
        networkJsonFile << "{\n";
        networkJsonFile << "  \"Network Info\": {\n";
        networkJsonFile << "    \"Device\": \"" << netInfo.device << "\",\n";
        networkJsonFile << "    \"RX Bytes\": " << netInfo.rxBytes << ",\n";
        networkJsonFile << "    \"TX Bytes\": " << netInfo.txBytes << "\n";
        networkJsonFile << "    \"System Count\": " << getSystemConnectionCount() << "\n";
        networkJsonFile << "  }\n";
        networkJsonFile << "}\n";
        networkJsonFile.close();
    } else {
        cerr << "Unable to open file for writing Network info report." << endl;
    }

    ofstream networkCsvFile("csvFiles/network_info.csv");
    if(networkCsvFile.is_open()) {
        networkCsvFile << "Network Info,Device,RX Bytes,TX Bytes,System Count\n";
        networkCsvFile << "Network Info," << netInfo.device << "," << netInfo.rxBytes<< ","<<netInfo.txBytes<<","<<getSystemConnectionCount()<< "\n";  
        networkCsvFile.close();
    } else {
        cerr << "Unable to open file for writing Network info report." << endl;
    }

};

void reportTopProcess(int n)
{
    vector<ProcessInfo> process = collectProcesses(n);

    cout << "Top " << n << " Processes:\n";
    for (const auto& proc : process) {
        cout << "  - PID: " << proc.pid << "\n";
        cout << "    - Name: " << proc.name << "\n";
        cout << "    - Total Time: " << proc.totalTime() << "\n";
        cout << "    - User Time: " << proc.utime << "\n";
        cout << "    - Current State:"<< proc.status<< "\n";
         cout << "    - RAM Usage: " << proc.ramUsageGB<< " KB\n"; 
         cout << "    - CPU Usage: " << getProcessCPUUsage(proc.pid) << "%\n";

        
         string cmdline = getProcessCmdLine(proc.pid);
         cout<< "    - CmdLine:  "<<cmdline <<endl;
         string status = getProcessStatus(proc.pid);
         
        
        }

    ofstream topJsonFile("jsonFiles/top_processes.json");
    if(topJsonFile.is_open()) {
        topJsonFile << "{\n";
        topJsonFile << "  \"Top Processes\": [\n";
        for (size_t i = 0; i < process.size(); ++i) {
            topJsonFile << "    {\n";
            topJsonFile << "      \"PID\": " << process[i].pid << ",\n";
            topJsonFile << "      \"Name\": \"" << process[i].name << "\",\n";
            topJsonFile << "      \"Total Time\": " << process[i].totalTime() << "\n";
            topJsonFile << "      \"User Time\": " << process[i].utime << "\n";
            topJsonFile << "      \"CmdLine\": \"" << getProcessCmdLine(process[i].pid) << "\"\n";
            topJsonFile << "    }" << (i < process.size() - 1 ? "," : "") << "\n";
        }
        topJsonFile << "  ]\n";
        topJsonFile << "}\n";
        topJsonFile.close();
    } else {
        cerr << "Unable to open file for writing Top processes report." << endl;
    }

    ofstream topCsvFile("csvFiles/top_processes.csv");
    if(topCsvFile.is_open()) {
        topCsvFile << "Top Processes,PID,Name,Total Time,User Time,CmdLine\n";
        for (const auto& proc : process) {
            topCsvFile << "Top Processes," << proc.pid << "," << proc.name << "," << proc.totalTime() << "," << proc.utime <<","<< getProcessCmdLine(proc.pid)<< "\n";
            }
        topCsvFile.close();
    }
    

}
void reportConnectionInfo(int pid)
{
    vector<ConnectionInfo> connections = getConnectionInfo(pid);
    cout << "Connections for PID " << pid << ":\n";
    for (const auto& conn : connections) {
        cout << "  - Protocol: " << conn.protocol << "\n";
        cout << "    - Local Address: " << conn.localAddress << "\n";
        cout << "    - Remote Address: " << conn.remoteAddress << "\n";
        cout << "    - State: " << conn.state << "\n";
        cout << "    - PID: " << conn.pid << "\n";
    }

    ofstream connJsonFile("jsonFiles/connections.json");
    if(connJsonFile.is_open()) {
        connJsonFile << "{\n";
        connJsonFile << "  \"Connections\": [\n";
        for (size_t i = 0; i < connections.size(); ++i) {
            connJsonFile << "    {\n";
            connJsonFile << "      \"Protocol\": \"" << connections[i].protocol << "\",\n";
            connJsonFile << "      \"Local Address\": \"" << connections[i].localAddress << "\",\n";
            connJsonFile << "      \"Remote Address\": \"" << connections[i].remoteAddress << "\",\n";
            connJsonFile << "      \"State\": \"" << connections[i].state << "\",\n";
            connJsonFile << "      \"PID\": " << connections[i].pid << "\n";
            connJsonFile << "    }" << (i < connections.size() - 1 ? "," : "") << "\n";
        }
        connJsonFile << "  ]\n";
        connJsonFile << "}\n";
        connJsonFile.close();
    } else {
        cerr << "Unable to open file for writing Connections report." << endl;
    }

    ofstream connCsvFile("csvFiles/connections.csv");
    if(connCsvFile.is_open()) {
        connCsvFile << "Connections,Protocol,Local Address,Remote Address,State,PID\n";
        for (const auto& conn : connections) {
            connCsvFile << "Connections," << conn.protocol << "," << conn.localAddress << "," << conn.remoteAddress << "," << conn.state << "," << conn.pid << "\n";
        }
        connCsvFile.close();
    } else {
        cerr << "Unable to open file for writing Connections report." << endl;
    }
}