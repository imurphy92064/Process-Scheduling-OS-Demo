#ifndef TASK_H
#define TASK_H

#include <string>

using namespace std;

class Task {
private:
    string _task_name;
    int _priority;
    int _cpu_burst;
    int _remaining_cpu_burst;
    int _waiting_time;
    int _turnaround_time;
public:
    Task(string, int, int);

    string& task_name();
    const string& task_name() const;
    int& priority();
    const int& priority() const;
    int& cpu_burst();
    const int& cpu_burst() const;
    int& remaining_cpu_burst();
    const int& remaining_cpu_burst() const;
    int& waiting_time();
    const int& waiting_time() const;
    int& turnaround_time();
    const int& turnaround_time() const;
};

#endif