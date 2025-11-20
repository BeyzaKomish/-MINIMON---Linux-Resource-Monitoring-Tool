
# MINIMON - Linux Resource Monitoring Tool

**Author:** Beyza Komiş
**Student Number:** B231202072

---

## 📌 Project Overview

**MINIMON** is a lightweight Linux system resource monitoring tool built using C++. It retrieves and reports detailed information about CPU, memory, disk, network, and processes. Reports are printed to the console and also exported as JSON and CSV files for further analysis.

---

## ⚙️ Platform & Environment

> **Important Note**:
> Due to limitations on running virtual machines on my Windows machine, I used **Windows Subsystem for Linux (WSL)** to emulate a Linux environment. This enabled full compatibility with Linux commands and virtual file structures like `/proc`.

---

## 📁 Project Structure

```
minimon/
├── README.md
├── Makefile
├── main.cpp                // Entry point with userInput() function
├── minimon                 // Compiled binary
├── core/
│   ├── collector.h/.cpp    // Collect data from Linux system
│   ├── analyzer.h/.cpp     // Analyze resource trends (optional use)
│   ├── reporter.h/.cpp     // Print to console / Export to CSV & JSON
├── ui/
│   ├── cli.h/.cpp          // Command-line interface
├── csvFiles/
│   ├── cpu_usage.csv
│   ├── memory_info.csv
│   ├── disk_info.csv
│   ├── network_info.csv
│   └── top_process.csv
├── jsonFiles/
│   ├── cpu_usage.json
│   ├── memory_info.json
│   ├── disk_info.json
│   ├── network_info.json
│   └── top_process.json
```

---

## 🛠️ Build Instructions

### Prerequisites

* Linux or WSL (Windows Subsystem for Linux)
* g++ with C++17 support
* `make`

### Build

```bash
make
```

### Run

```bash
./minimon [cpu|mem|disk|net|top N|conn PID|check PID]
```

#### Example Usage

```bash
./minimon cpu      # Shows CPU usage
./minimon mem      # Shows memory info
./minimon top 5    # Shows top 5 CPU-consuming processes
./minimon conn 123 # Shows network connections for process with PID 123
```

---

## 🧩 Features

### 1. Resource Monitoring Functions

* `vector<ProcessInfo> collectProcesses(int n)`
* `CPUUsage getCPUUsage()`
* `MemoryInfo getMemoryInfo()`
* `DiskInfo getDiskInfo()`
* `NetworkInfo getNetworkInfo()`
* `vector<ConnectionInfo> getConnectionInfo(int pid)`
* `long getProcessRAMUsage(int pid)`
* `float getProcessCPUUsage(int pid)`

### 2. Reporting Functions

* Print to **console**, **CSV**, and **JSON**
* `reportCPUUsage()`
* `reportMemoryInfo()`
* `reportDiskInfo()`
* `reportNetworkInfo()`
* `reportTopProcess(int n)`
* `reportConnectionInfo(int pid)`

### 3. Simple Command-Line Interface

Handled using:

```cpp
void userInput(int argc, char *argv[]);
```

Provides user feedback for invalid input and guides correct usage.

---

## 🧠 Logic Behind Data Collection

Most data is collected by reading from Linux virtual filesystems like `/proc`. Here's a breakdown of the logic behind the function `collectProcesses(int n)`:

* Iterate over `/proc` directories.
* Filter numeric names (valid PIDs).
* Open `/proc/[pid]/stat` to extract CPU time.
* Use helper functions to get:

  * RAM usage
  * Process status
* Store in `ProcessInfo` struct.
* Sort by CPU time and return top `n`.

Other resource functions follow a similar pattern of **reading**, **filtering**, **parsing**, and **structuring**.

---

## 🧪 Analyzer Module

Although included, the analyzer functions had limited use due to the small scope. Example functions:

* `CPUUsage calculatePrevAndNewUsage(...)`
* `bool isCPUUsageIncreased(...)`
* `vector<ProcessInfo> sortProcess(...)`

---

## 📂 Files Used for Monitoring

| File Path             | Purpose              |
| --------------------- | -------------------- |
| `/proc/[pid]/stat`    | Process stats        |
| `/proc/[pid]/status`  | Process state        |
| `/proc/[pid]/cmdline` | Command line         |
| `/proc/meminfo`       | Memory and swap info |
| `/proc/stat`          | CPU stats            |
| `/proc/diskstats`     | Disk I/O stats       |
| `/proc/net/dev`       | Network device info  |
| `/proc/net/tcp`       | TCP connections      |
| `/proc/net/udp`       | UDP connections      |

---

## 🧰 Libraries Used

* `<dirent.h>` - For directory handling (`/proc`)
* `<arpa/inet.h>` - IP/port parsing
* `<unistd.h>` - Sleep and system config
* `<sys/statvfs.h>` - Disk stats

---

## 🔎 Filtering Logic

Filtering is applied in several layers:

* **Memory Info**: Filters "MemTotal", "MemFree", "MemAvailable"
* **Disk Info**: Filters lines starting with "sda"
* **Network Info**: Filters known interfaces: `eth0`, `wlan0`, `enp0s3`

This ensures that only relevant data is processed and displayed.

---

## ❗ Limitations

* Requires a **Linux environment**. Windows users must use WSL.
* Analyzer functions were not fully leveraged due to project simplicity.
* Some edge-case processes may not return full data.

---

## 📌 Final Notes

MINIMON demonstrates how to build a modular, console-based system monitoring tool by leveraging the Linux `/proc` virtual filesystem, C++ structs/vectors, and file-based I/O. Though simplified, it sets a strong foundation for more advanced real-time monitoring tools.

