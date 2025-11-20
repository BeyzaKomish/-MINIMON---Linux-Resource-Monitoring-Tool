#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>
#include <algorithm>
#include <cctype>
#include <vector>
#include "collector.h"
#include <dirent.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/statvfs.h>





using namespace std;

// .LIBRARIES AND THE FUNCTIONS CAN GICE ERROR BECAUSE THEY ARE USED AND RUN IN THE LINUX ENVIROMENT PLEASE CHECK THE DOCUMNETATION FIRST 

vector<ProcessInfo> collectProcesses(int n) {
    vector<ProcessInfo> processes;
    DIR* dir = opendir("/proc");
    if (!dir) {
        cout << "Could not open /proc directory." << endl;
        return processes;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (!isdigit(entry->d_name[0])) continue; // Only numeric dirs (PIDs)
        string pidStr = entry->d_name;
        string statPath = "/proc/" + pidStr + "/stat";
        ifstream statFile(statPath);
        string line;  
        if (!statFile.is_open()) continue;

     
        int pid;
        string comm;
        char state;
        long dummy, utime, stime;
        statFile >> pid >> comm >> state;
        // Skip to utime (14th) and stime (15th) fields
        for (int i = 0; i < 11; ++i) statFile >> dummy;
        statFile >> utime >> stime;

        ProcessInfo p;
        p.pid = pid;
        p.name = comm;
        p.utime = utime;
        p.stime = stime;
        p.status= getProcessStatus(pid);
        p.ramUsageGB = getProcessRAMUsage(pid);


        processes.push_back(p);
    }
    closedir(dir);


    // Sort by total CPU time (utime + stime), descending
    sort(processes.begin(), processes.end(), [](const ProcessInfo& a, const ProcessInfo& b) {
        return (a.utime + a.stime) > (b.utime + b.stime);
    });
if (n > 0 && static_cast<size_t>(n) < processes.size()) {
        processes.resize(n);
    }

    return processes;
 }

 string getProcessCmdLine(int pid){
    ifstream cmdFile("/proc/" + to_string(pid) + "/cmdline");
    string cmd;
    if (cmdFile.is_open()) {
        getline(cmdFile, cmd ,'\0'); 
        replace(cmd.begin(),cmd.end(), '\0' ,' ');
        cmdFile.close();
    } else {
        cerr << "Could not open cmdline file for PID " << pid << endl;
    }
    return cmd;
 }

 string getProcessStatus(int pid) {    
    ifstream file("/proc/" + to_string(pid) + "/status");
    string line;
    string status;
    while (getline(file,line))
    {
        if(line.find("State:") != string::npos) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                status = line.substr(pos + 1);
            }
        }
    }
    return status;
 }

 long getProcessRAMUsage(int pid) {
    ifstream file("/proc/" + to_string(pid) + "/status");
    string line;
    
    ProcessInfo p;
     long ramUsageGB;
    

      while (getline(file, line)) {
             if(line.find("VmRSS:") != 0) {
                istringstream iss(line);
                string key;
                iss >> key >> ramUsageGB;
               
               
             }
        }

        return ramUsageGB;
 }

 long getSystemTotalTime()
 {
    ifstream file("/proc/stat");
    string line;
    getline(file, line); // Read the first line
    istringstream iss(line);
    string cpu;
    long user, nice, system, idle , iowait, irq, softirq , steal;
    iss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
    long total = user + nice + system + idle + iowait + irq + softirq + steal;

    return total;
 }

 long getProcessTotalTime(int pid){
    ifstream file("/proc/" + to_string(pid) + "/stat");
    if(!file.is_open()) return 0;
    string line;
    getline(file, line);
    istringstream iss(line);
    string skipPid;
    string comm;
    char state;
    long dummy , utime, stime;
    iss >> skipPid >> comm >> state;
    for (int i = 0; i < 11; i++) iss>> dummy;
    iss >> utime >> stime;
    long totalTime = utime + stime;
    return totalTime;
 }

 float getProcessCPUUsage(int pid) {
    long proc1 = getProcessTotalTime(pid);
    long sys1 = getSystemTotalTime();
    usleep(1000); // Sleep for 1 second
    long proc2 = getProcessTotalTime(pid);
    long sys2 = getSystemTotalTime();

    long procDiff = proc2 - proc1;
    long sysDiff = sys2 - sys1;
    if(sysDiff == 0) return 0.0; // Avoid division by zero

    long tickPerSecond = sysconf(_SC_CLK_TCK);

    float cpuPercent = 100.0f *( (float (procDiff ) / tickPerSecond) / (float (sysDiff) / tickPerSecond));
    return cpuPercent;
 }

 int getSystemConnectionCount(){
    int count = 0;
    ifstream file("/proc/net/tcp");
    string line;
    getline(file, line); // Skip the first line (header)
    getline(file, line); // Skip the second line (header)
    while(getline(file,line)) ++count;
    ifstream file2("/proc/net/udp");
    getline(file2,line);
    getline(file2,line);
    while(getline(file2,line)) ++count;

    return count;
 }

    string hexToIpPort(const string& hex) {
         size_t colon = hex.find(':');
         if (colon == string::npos) return "";
         string ipHEx = hex.substr(0, colon);
            string portHex = hex.substr(colon + 1);
        
            unsigned int ip;
            stringstream ss;
            ss << hex << ipHEx;
            ss >> ip;
            struct in_addr addr;
            addr.s_addr = htonl(ip);
            string ipStr = inet_ntoa(addr);
            unsigned int portInt;
            stringstream ssPort;
            ssPort << hex << portHex;
            ssPort >> portInt;

            return ipStr + ":" + to_string(portInt);
    }

        string tcpState(const string& state) {
            if (state == "01") return "ESTABLISHED";
            else if (state == "02") return "SYN_SENT";
            else if (state == "03") return "SYN_RECV";
            else if (state == "04") return "FIN_WAIT1";
            else if (state == "05") return "FIN_WAIT2";
            else if (state == "06") return "TIME_WAIT";
            else if (state == "07") return "CLOSE";
            else if (state == "08") return "CLOSE_WAIT";
            else if (state == "09") return "LAST_ACK";
            else if (state == "0A") return "LISTEN";
            else if (state == "0B") return "CLOSING";
            else return state;
        }
CPUUsage getCPUUsage() {
    ifstream file("/proc/stat");
    string line;
    getline(file, line); // Read the first line

    istringstream iss(line);
    string cpu;
    float user, nice, system, idle;
    iss >> cpu >> user >> nice >> system >> idle;

    float total = user + nice + system + idle;
    CPUUsage usage;
    usage.user  = (user + nice) / total * 100;
    usage.system = system / total * 100;
    usage.idle = idle / total * 100;

    return usage;
}

MemoryInfo getMemoryInfo() {
    ifstream file("/proc/meminfo");
    string line;
    long totalMem = 0, freeMem = 0, availableMem = 0 , swapTotal = 0, swapFree = 0;

    while (getline(file, line)) {
        if (line.find("MemTotal:") == 0) {
            istringstream iss(line);
            string key;
            iss >> key >> totalMem;
        } else if (line.find("MemFree:") == 0) {
            istringstream iss(line);
            string key;
            iss >> key >> freeMem;
        } else if (line.find("MemAvailable:") == 0) {
            istringstream iss(line);
            string key;
            iss >> key >> availableMem;
        }else if (line.find("SwapTotal:")==0)
        {
           istringstream iss(line);
           string key;
           iss>> key>> swapTotal;
        }else if (line.find("SwapFree:")==0)
        {
           istringstream iss(line);
           string key;
           iss>> key>> swapFree;
        }
        
    }
    return MemoryInfo{totalMem, freeMem, availableMem,swapTotal,swapFree};
}

DiskInfo getDiskInfo() {
    ifstream file("/proc/diskstats");
    string line;
    DiskInfo diskInfo;

    while (getline(file, line)) {
        istringstream iss(line);
        int major , minor;
        string device;
        long reads, writes;

        iss >> major >> minor >> device;
        iss>> reads;

        if( device == "sda" || device=="nvme0n1")
        {      
            long dummy;
            for (int i = 0; i < 6; ++i) iss >> dummy;
            iss >>  writes;

            diskInfo.device = device;
            diskInfo.reads = reads;
            diskInfo.writes = writes;

            struct statvfs stat;
            if (statvfs("/" , &stat) == 0) {
                unsigned long total = stat.f_blocks * stat.f_frsize;
                unsigned long free = stat.f_bfree * stat.f_frsize;
                unsigned long used = total - free;

                diskInfo.totalSpace = total;
                diskInfo.freeSpace = free;
                diskInfo.usedSpace = used;

            } else {
                cerr << "Could not get disk space information." << endl;
            }

            }
    }
    return diskInfo;
}

NetworkInfo getNetworkInfo() {
    ifstream file("/proc/net/dev");
    string line;

    getline(file, line);
    getline(file, line);
    
    
    while (getline(file, line)) {
        size_t pos = line.find(':');
        if (pos == string::npos) continue; 

        string name = line.substr(0, pos);
        name.erase(0,name.find_first_not_of(" \t")); // Remove whitespace
        if (name == "eth0" || name == "enp0s3" || name == "wlan0") { // Filter for the first network interface
            istringstream iss(line.substr(pos + 1));
             unsigned long rxBytes, test ,txBytes ;

            iss >> rxBytes; 
            for (int i = 0; i < 7; ++i)iss >> test; 
            iss >> txBytes;

             NetworkInfo netInfo;
                netInfo.device = name;
                netInfo.rxBytes = rxBytes;
                netInfo.txBytes = txBytes;

                return netInfo;
        }

    }
    return NetworkInfo{};
}

vector<ConnectionInfo> getConnectionInfo(int pid) {
    vector<ConnectionInfo> connections;
   
    auto parseFile = [&](const string& proto,const string& path) {
        ifstream file(path);
        string line;
        getline(file, line); // Skip the first line (header)
        getline(file, line); // Skip the second line (header)


        while (getline(file, line)) {
            istringstream iss(line);
            string sl, localAddr, remoteAddr, state , ignore;
            int pid;

            iss >> sl >> localAddr >> remoteAddr >> state;
            for (int i = 0; i < 7; i++)iss>>ignore;
            iss >> pid;
            
                ConnectionInfo conn;
                conn.protocol = proto;
                conn.localAddress = hexToIpPort(localAddr);
                conn.remoteAddress = hexToIpPort(remoteAddr);
                conn.state =(proto == "tcp") ?  tcpState(state) : "";
                conn.pid = pid;
                connections.push_back(conn);
            
        }
    };

    string base = "/proc/"+to_string(pid) + "/net/";
    parseFile("tcp" , base + "tcp");
    parseFile("udp" , base + "udp");
    parseFile("tcp6" , base + "tcp6");

    return connections;
}



